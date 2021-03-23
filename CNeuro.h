#pragma once
#include<opencv2/opencv.hpp>
#include <tiffio.h>		// ����libtiff��
#include<iostream>
#include<vector>
using namespace  cv;
using namespace std;
#define ENTRY_EASY 6e+6				// ����-����ֵ
#define EASY_MEDIUM 9e+6			// ��-�е���ֵ
#define MEDIUM_DIFFICULT 1.2e+7	// �е�-������ֵ 
#define ENTRY_LEVEL 0			// ���ż���
#define EASY_LEVEL 1				// �򵥼���
#define MEDIUM_LEVEL 2		// �еȼ���
#define DIFFICULT_LEVEL 3		// ���Ѽ���


typedef struct {	// ����ͼ����Ϣ
	vector<Mat>data;
	int width;			// ���
	int height;		// �߶�
	int slices;			// ��֡��
	uint16 channel;		// ͨ����
	uint16 depth;			// ���
	int diffLevel;		// �Ѷȵȼ�
}neuro_info;

class CNeuro
{
public:
	void segment(const char* filePath, int* segCoef, vector<neuro_info> &tifImgs);	// �ָ�ͼ��
	void evaluate(vector<neuro_info> &tifImgs);	// ���ݿ��Ѷȷּ�
	void info(vector<neuro_info> tifImgs, int idx);			// ��ʾͼ����Ϣ
	void save(vector<neuro_info> tifImgs, string path);		// ����ͼ��������ͼ����Ϣ

};

