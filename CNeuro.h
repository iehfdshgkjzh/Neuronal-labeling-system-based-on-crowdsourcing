#pragma once
#include<opencv2/opencv.hpp>
#include <tiffio.h>		// 调用libtiff库
#include<iostream>
#include<vector>
using namespace  cv;
using namespace std;
#define ENTRY_EASY 6e+6				// 入门-简单阈值
#define EASY_MEDIUM 9e+6			// 简单-中等阈值
#define MEDIUM_DIFFICULT 1.2e+7	// 中等-困难阈值 
#define ENTRY_LEVEL 0			// 入门级别
#define EASY_LEVEL 1				// 简单级别
#define MEDIUM_LEVEL 2		// 中等级别
#define DIFFICULT_LEVEL 3		// 困难级别


typedef struct {	// 胞体图像信息
	vector<Mat>data;
	int width;			// 宽度
	int height;		// 高度
	int slices;			// 总帧数
	uint16 channel;		// 通道数
	uint16 depth;			// 深度
	int diffLevel;		// 难度等级
}neuro_info;

class CNeuro
{
public:
	void segment(const char* filePath, int* segCoef, vector<neuro_info> &tifImgs);	// 分割图像
	void evaluate(vector<neuro_info> &tifImgs);	// 数据块难度分级
	void info(vector<neuro_info> tifImgs, int idx);			// 显示图像信息
	void save(vector<neuro_info> tifImgs, string path);		// 保存图像数据与图像信息

};

