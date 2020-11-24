#pragma once
#include "time.h"
/*  
*   �������ڼ����ɫͼ��İ�ƽ��ϵ����ϵ����Mat�ṹ�洢
*   ���룺ͼ��ͼ��ߣ�ͼ���
*   �����ϵ��
*   ��ʱ��18ms����
*/

void CalculateLamda_RB(unsigned char *pBuffer, int width, int height, double** lamda_rgb)
{
	//���������ͼ��ΪBGR
	double*pBuffer_dst =*lamda_rgb;
	int pos = 0;
	for (int i = 0;i < height;++i)
	{
		for (int j = 0;j < width;++j)
		{
			//��ֹ��ĸ��0��ȡ��Сֵ
			pos = i * width * 3 + j * 3;
			if (0 == pBuffer[pos + 0])
				pBuffer[pos + 0] = 1;
			if (0 == pBuffer[pos + 2])
				pBuffer[pos + 2] = 1;

			pBuffer_dst[pos + 0] = (double)pBuffer[pos + 1] / (double)pBuffer[pos+0];//Lamda_B=G/B
			pBuffer_dst[pos + 2] = (double)pBuffer[pos + 1] / (double)pBuffer[pos+2];//Lamda_R=G/R
			pBuffer_dst[pos + 1] = 1.0;//Lamda_G=G/G

		}
	}
}
/*
*	����������ͼ����а�ƽ�����
*	���룺ԭͼ��ϵ������ͼ���ͼ���
*	�����Ŀ��ͼ��
*   ע�⣺Ŀ��ͼ����ڴ�ռ�Ҫ���ⲿ����
*/
void AdjWhiteBalance(unsigned char* src,double *lamda,int width,int height,uchar** dst)
{
	int pos = 0;
	uchar *t_dst = *dst;
	for (int i = 0;i < height;++i)
	{
		for (int j = 0;j < width;++j)
		{
			pos = i * width * 3 + j * 3;
			t_dst[pos + 0] = (int)(src[pos + 0] * lamda[pos + 0]);
			t_dst[pos + 1] = (int)(src[pos + 1] * lamda[pos + 1]);
			t_dst[pos + 2] = (int)(src[pos + 2] * lamda[pos + 2]);
		}
	}
}