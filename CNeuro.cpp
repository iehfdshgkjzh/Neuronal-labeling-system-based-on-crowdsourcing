#include "CNeuro.h"


void CNeuro::segment(const char* filePath, int* segCoef, vector<neuro_info> &tifImgs) {
	TIFF* img;
	int _width, _height, _slices;		// Դ���ݿ�Ŀ��߼���֡��
	int samplesperpixel, bitspersample, bitsperpixel;	// Դ���ݿ��ͨ��������ͨ��λ�������

	img = TIFFOpen(filePath, "rwa");		// ��tif�ļ����õ�imgָ��, r-����w-д��a-׷��

	if (img == nullptr) {
		cout << "Failed to load TIF image" << endl;
		exit(-1);
	}
	else {
		cout << "TIF image was read successfully" << endl;
	}

	TIFFGetField(img, TIFFTAG_IMAGEWIDTH, &_width);			//��ȡ��֡ͼ��Ŀ�
	TIFFGetField(img, TIFFTAG_IMAGELENGTH, &_height);		//��ȡ��֡ͼ��ĸ�

	TIFFGetField(img, TIFFTAG_BITSPERSAMPLE, &bitspersample);				//��ȡ��ͨ����λ��
	TIFFGetField(img, TIFFTAG_SAMPLESPERPIXEL, &samplesperpixel);		//��ȡͨ����
	bitsperpixel = bitspersample * samplesperpixel;									// ��ȡͼ������

	_slices = TIFFNumberOfDirectories(img);					//��ȡͼ�����֡��

	tmsize_t stripSize = TIFFStripSize(img);		//��ȡ��֡ͼ���������
	uint32* count = new uint32[stripSize];		//���뵥֡ͼ��������ڴ�ռ䣻
	//��ʱcount��ָ��������Ϊ(0, 0)

	int tifIdx;		//	��ά����������
	int x = 0; int y = 0; int z = 0;	// x, y, z��������ڱ�ʶ�������ݿ�

	while (z < segCoef[2]) {
		while (y < segCoef[1]) {
			while (x < segCoef[0]) {
				for (int s = 0; s < _slices / segCoef[2]; s++)
				{
					// �������Ż�����
					Mat MatImage(_height / segCoef[1], _width / segCoef[0], CV_8UC1, Scalar::all(0));

					TIFFSetDirectory(img, s + _slices * z / segCoef[2]);
					// ע�ⲻ����z/segCoef[2]*_slices����Ϊz/segCoef[2]�ᱻǿ��ת��Ϊ0

					// ���µ���(�������)�������Ҷ��� ÿ���µ�һ֡��count����һ��
					TIFFReadRGBAImage(img, _width, _height, count, 0);

					// ����һ��ָ�����һ�е�һ��Ԫ�ص�ָ��, 
					uint32* rowPoint2src = count + (_height - 1)*_width;
					// ��ʱrowPoint2src�����һ�е�һ��, (_height-1, 0)

					for (int i = 0; i < _height / segCoef[1]; i++)
					{
						uint32* colPoint2src = rowPoint2src - _height * _width*y / segCoef[1];

						for (int j = 0; j < _width / segCoef[0]; j++)
						{
							MatImage.at<uchar>(i, j) = (uchar)TIFFGetG(*(colPoint2src + _width * x / segCoef[0]));
							colPoint2src++;				// ָ������
						}
						rowPoint2src -= _width;		// ָ������
					}
					tifIdx = x + y * segCoef[0] + z * segCoef[0]*segCoef[1];
					tifImgs[tifIdx].data.push_back(MatImage);		// ��Ŷ�ȡ�ĵ�֡ͼ������
					MatImage.release();		// Mat���ͷ�
				}
				// ���ݿ����Ը�ֵ
				tifImgs[tifIdx].width = _width / segCoef[0];
				tifImgs[tifIdx].height = _height / segCoef[1];
				tifImgs[tifIdx].slices = _slices / segCoef[2];
				tifImgs[tifIdx].channel = samplesperpixel;
				tifImgs[tifIdx].depth = bitsperpixel;
				x++;
			}	y++; x = 0;
		}	z++;  x = 0; y = 0;
	}

	TIFFClose(img);	// �ر�ͼ��
	delete[] count;		// delete[] �����ͷ�new[]����Ŀռ�

}


void CNeuro::evaluate(vector<neuro_info> &tifImgs) {
	vector<Scalar>voxels(tifImgs.size(), {0,0,0,0});		// Scalar�൱�� double val[4] 
	for (int k = 0; k < tifImgs.size(); k++) {
		neuro_info tempImg = tifImgs[k];		// ȡ����Ϊ��һ�����ݿ�ṹ
		for (int i = 0; i < tempImg.slices; i++) {
			voxels[k] += sum(tempImg.data[i]);
		}
		cout << voxels[k] << endl;		//�������ֵ
		cout << "----------------------------" << endl;
	}

	cout << "A total of "<<tifImgs.size()<<" data blocks were read." << endl;
	vector<vector<int>>level(4, vector<int>(0));	//Ϊ���������Ѷȷּ�Ԥ����ռ�

	for (int i = 0; i < tifImgs.size(); i++) {		// �������������ٽ����Ѷȵȼ�����
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

	size_t count;		//�����Ѷȷּ���
	string grade[4] = { "Entry", "Easy", "Mediim", "Difficult" };		//�����Ѷȷ���
	for (int i = 0; i < 4; i++) {
		count = level[i].size();
		cout << grade[i] << " task��" << count << endl;
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
	// ����ָ���ͼ��
	for (int i = 0; i < tifImgs.size(); i++) {
		string blockPath = path + to_string(i + 1) + ".tif";
		imwrite(blockPath, tifImgs[i].data);		// �����и�õ���С���ݿ�
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

