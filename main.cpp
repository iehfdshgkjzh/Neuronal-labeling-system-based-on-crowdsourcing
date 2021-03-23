#include "CNeuro.h"


int main() {
	int segCoef[3] = { 4,4,4 };		// 沿x、y、z三个方向的切割系数
	int block_num = segCoef[0] * segCoef[1]*segCoef[2];		// 一个大数据分割得到的小数据块数量
	
	CNeuro neuro;		// 实例化一个对象
	vector<neuro_info>tifImage(block_num);			// 保存多个小数据块信息的向量
	//----------------------源数据块路径
	const char* srcPath = "C:\\File\\2_Expansive Learning\\8_Biology competition\\My_code\\imageProc\\data_2\\192420-5.tif";	

	neuro.segment(srcPath, segCoef, tifImage);		//	切割数据块
	
	neuro.evaluate(tifImage);		//  数据块难度分级
	
	int idx = 11;		// 索引从0开始，编号从1开始
	neuro.info(tifImage, idx);		// 读取索引为idx，编号为idx+1的数据块信息

	string savePath = "C:\\File\\2_Expansive Learning\\8_Biology competition\\My_code\\imageProc\\cut block\\";		// 保存路径
	neuro.save(tifImage, savePath);		// 保存数据块信息

	return 0;
}
