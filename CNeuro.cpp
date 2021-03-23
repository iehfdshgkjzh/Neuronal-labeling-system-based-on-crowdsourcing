#include "CNeuro.h"


void CNeuro::segment(const char* filePath, int* segCoef, vector<neuro_info> &tifImgs) {
	TIFF* img;
	int _width, _height, _slices;		// 源数据块的宽、高及总帧数
	int samplesperpixel, bitspersample, bitsperpixel;	// 源数据块的通道数，单通道位数，深度

	img = TIFFOpen(filePath, "rwa");		// 打开tif文件，得到img指针, r-读，w-写，a-追加

	if (img == nullptr) {
		cout << "Failed to load TIF image" << endl;
		exit(-1);
	}
	else {
		cout << "TIF image was read successfully" << endl;
	}

	TIFFGetField(img, TIFFTAG_IMAGEWIDTH, &_width);			//获取单帧图像的宽
	TIFFGetField(img, TIFFTAG_IMAGELENGTH, &_height);		//获取单帧图像的高

	TIFFGetField(img, TIFFTAG_BITSPERSAMPLE, &bitspersample);				//获取单通道的位数
	TIFFGetField(img, TIFFTAG_SAMPLESPERPIXEL, &samplesperpixel);		//获取通道数
	bitsperpixel = bitspersample * samplesperpixel;									// 获取图像的深度

	_slices = TIFFNumberOfDirectories(img);					//获取图像的总帧数

	tmsize_t stripSize = TIFFStripSize(img);		//获取单帧图像的总像素
	uint32* count = new uint32[stripSize];		//申请单帧图像所需的内存空间；
	//此时count所指像素坐标为(0, 0)

	int tifIdx;		//	二维向量的索引
	int x = 0; int y = 0; int z = 0;	// x, y, z的组合用于标识各个数据块

	while (z < segCoef[2]) {
		while (y < segCoef[1]) {
			while (x < segCoef[0]) {
				for (int s = 0; s < _slices / segCoef[2]; s++)
				{
					// 建立单张画布；
					Mat MatImage(_height / segCoef[1], _width / segCoef[0], CV_8UC1, Scalar::all(0));

					TIFFSetDirectory(img, s + _slices * z / segCoef[2]);
					// 注意不能用z/segCoef[2]*_slices，因为z/segCoef[2]会被强制转换为0

					// 从下到上(逆序读入)，从左到右读， 每到新的一帧，count更新一次
					TIFFReadRGBAImage(img, _width, _height, count, 0);

					// 构建一个指向最后一行第一个元素的指针, 
					uint32* rowPoint2src = count + (_height - 1)*_width;
					// 此时rowPoint2src在最后一行第一列, (_height-1, 0)

					for (int i = 0; i < _height / segCoef[1]; i++)
					{
						uint32* colPoint2src = rowPoint2src - _height * _width*y / segCoef[1];

						for (int j = 0; j < _width / segCoef[0]; j++)
						{
							MatImage.at<uchar>(i, j) = (uchar)TIFFGetG(*(colPoint2src + _width * x / segCoef[0]));
							colPoint2src++;				// 指针右移
						}
						rowPoint2src -= _width;		// 指针上移
					}
					tifIdx = x + y * segCoef[0] + z * segCoef[0]*segCoef[1];
					tifImgs[tifIdx].data.push_back(MatImage);		// 存放读取的单帧图像数据
					MatImage.release();		// Mat的释放
				}
				// 数据块属性赋值
				tifImgs[tifIdx].width = _width / segCoef[0];
				tifImgs[tifIdx].height = _height / segCoef[1];
				tifImgs[tifIdx].slices = _slices / segCoef[2];
				tifImgs[tifIdx].channel = samplesperpixel;
				tifImgs[tifIdx].depth = bitsperpixel;
				x++;
			}	y++; x = 0;
		}	z++;  x = 0; y = 0;
	}

	TIFFClose(img);	// 关闭图像
	delete[] count;		// delete[] 用于释放new[]分配的空间

}


void CNeuro::evaluate(vector<neuro_info> &tifImgs) {
	vector<Scalar>voxels(tifImgs.size(), {0,0,0,0});		// Scalar相当于 double val[4] 
	for (int k = 0; k < tifImgs.size(); k++) {
		neuro_info tempImg = tifImgs[k];		// 取索引为的一个数据块结构
		for (int i = 0; i < tempImg.slices; i++) {
			voxels[k] += sum(tempImg.data[i]);
		}
		cout << voxels[k] << endl;		//输出像素值
		cout << "----------------------------" << endl;
	}

	cout << "A total of "<<tifImgs.size()<<" data blocks were read." << endl;
	vector<vector<int>>level(4, vector<int>(0));	//为保存任务难度分级预分配空间

	for (int i = 0; i < tifImgs.size(); i++) {		// 根据像素数多少进行难度等级分类
		if (voxels[i][0] <= ENTRY_EASY) {
			level[0].push_back(i);
			tifImgs[i].diffLevel = ENTRY_LEVEL;
		}
		else if (voxels[i][0] > ENTRY_EASY && voxels[i][0] <= EASY_MEDIUM) {
			level[1].push_back(i);
			tifImgs[i].diffLevel = EASY_LEVEL;
		}
		else if (voxels[i][0] > EASY_MEDIUM && voxels[i][0] <= MEDIUM_DIFFICULT) {
			level[2].push_back(i);
			tifImgs[i].diffLevel = MEDIUM_LEVEL;
		}
		else {
			level[3].push_back(i);
			tifImgs[i].diffLevel = DIFFICULT_LEVEL;
		}
	}

	size_t count;		//任务难度分级数
	string grade[4] = { "Entry", "Easy", "Mediim", "Difficult" };		//任务难度分类
	for (int i = 0; i < 4; i++) {
		count = level[i].size();
		cout << grade[i] << " task：" << count << endl;
		cout << "Task number: ";
		for (int j = 0; j < count; j++) {
			cout << level[i][j] + 1 << ' ';
		}
		cout << endl << endl;
	}
}


void CNeuro::info(vector<neuro_info>tifImgs, int idx) {
	cout << "The number of data blocks: " << tifImgs.size() << endl;
	cout << "The information of data block " << idx+1<<": "<<endl;
	cout << "Width: " << tifImgs[idx].width << endl;
	cout << "Height: " << tifImgs[idx].height << endl;
	cout << "Slices: " << tifImgs[idx].slices << endl;
	cout << "Channel: " << tifImgs[idx].channel << endl;
	cout << "Depth: " << tifImgs[idx].depth << endl;
	cout << "DiffLevel: " << tifImgs[idx].diffLevel << endl;
}


void CNeuro::save(vector<neuro_info>tifImgs, string path) {
	// 保存分割后的图像
	for (int i = 0; i < tifImgs.size(); i++) {
		string blockPath = path + to_string(i + 1) + ".tif";
		imwrite(blockPath, tifImgs[i].data);		// 保存切割得到的小数据块
	}
	
	string csv_name = "info.csv";
	string csv_path = path + csv_name;
	ofstream outfile;
	outfile.open(csv_path, ios::out);
	outfile << "SerialNum" << ',' << "Width" << "," << "Height" << ','<<"Slices"<<',' << "Channel" << ',' << "Depth" << ',' << "DiffLevel" << '\n';
	for (int i = 0; i < tifImgs.size(); i++) {
		outfile <<i+1<<','<< tifImgs[i].width<<','<<tifImgs[i].height<<','<<tifImgs[i].slices<<','<<tifImgs[i].channel<<','<<tifImgs[i].depth<<','<<tifImgs[i].diffLevel<<'\n';
	}
	outfile.close();

}

