#include "CNeuro.h"


int main() {
	int segCoef[3] = { 4,4,4 };		// ��x��y��z����������и�ϵ��
	int block_num = segCoef[0] * segCoef[1]*segCoef[2];		// һ�������ݷָ�õ���С���ݿ�����
	
	CNeuro neuro;		// ʵ����һ������
	vector<neuro_info>tifImage(block_num);			// ������С���ݿ���Ϣ������
	//----------------------Դ���ݿ�·��
	const char* srcPath = "C:\\File\\2_Expansive Learning\\8_Biology competition\\My_code\\imageProc\\data_2\\192420-5.tif";	

	neuro.segment(srcPath, segCoef, tifImage);		//	�и����ݿ�
	
	neuro.evaluate(tifImage);		//  ���ݿ��Ѷȷּ�
	
	int idx = 11;		// ������0��ʼ����Ŵ�1��ʼ
	neuro.info(tifImage, idx);		// ��ȡ����Ϊidx�����Ϊidx+1�����ݿ���Ϣ

	string savePath = "C:\\File\\2_Expansive Learning\\8_Biology competition\\My_code\\imageProc\\cut block\\";		// ����·��
	neuro.save(tifImage, savePath);		// �������ݿ���Ϣ

	return 0;
}
