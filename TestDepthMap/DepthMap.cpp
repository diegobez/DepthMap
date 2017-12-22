#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <StereoManager.h>


#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif

using namespace std;


///////////////////////////////////////////////////////////////////////////////////
//                                                                               //
//                                                                               //
//                                                                               //
///////////////////////////////////////////////////////////////////////////////////
int main()
{
	
	//inicialize stereomanager
	StereoManager* SManager = new StereoManager();

	//inicialize name of images, path and if img is 320

	//std::string myPath	 = "resources/images/";
	std::string myPath = "../../resources/images/";
	std::string leftImg	 = "imgRealProjectL.png";
	std::string rightImg = "imgRealProjectR.png";
	//std::string leftImg = "imgLeonL.png";
	//std::string rightImg = "imgLeonR.png";
	bool isImg360		 = true;




	Mat Limg = imread(myPath+leftImg, IMREAD_GRAYSCALE);
	Mat Rimg = imread(myPath+rightImg, IMREAD_GRAYSCALE);
	Mat LimgFlip, RimgFlip;
	cv::flip(Limg, LimgFlip, 1);
	cv::flip(Rimg, RimgFlip, 1);
	Mat OutBM, OutSGBM, Out3W, OutHH;
	Mat Out3WF, Out3W2;

	if (!Limg.data || !Rimg.data)                              // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	//Generating depth map with img360 and tick count for each algorithm

	int64 t = getTickCount();
	SManager->generateDepthMap(Limg, Rimg, OutBM, BaseStereo::STEREO_BM, isImg360);
	t = getTickCount() - t;
	printf("STEREO_BM: %fms\n", t * 1000 / getTickFrequency());

	t = getTickCount();
	SManager->generateDepthMap(Limg, Rimg, OutSGBM, BaseStereo::STEREO_SGBM, isImg360);
	t = getTickCount() - t;
	printf("STEREO_SGBM: %fms\n", t * 1000 / getTickFrequency());

	t = getTickCount();
	SManager->generateDepthMap(Limg, Rimg, Out3W, BaseStereo::STEREO_3WAY, isImg360);
	SManager->generateDepthMap(RimgFlip, LimgFlip, Out3WF, BaseStereo::STEREO_3WAY, isImg360);
	cv::flip(Out3WF, Out3W2, 1);
	


	t = getTickCount() - t;
	printf("STEREO_3WAY: %fms\n", t * 1000 / getTickFrequency());

	t = getTickCount();
	SManager->generateDepthMap(Limg, Rimg, OutHH, BaseStereo::STEREO_HH, isImg360);
	t = getTickCount() - t;
	printf("STEREO_HH: %fms\n", t * 1000 / getTickFrequency());

	imwrite(myPath + "STEREO_BM.png", OutBM);
	imwrite(myPath + "STEREO_SGBM.png", OutSGBM);
	imwrite(myPath + "STEREO_3WAYL.png", Out3W);
	imwrite(myPath + "STEREO_3WAYRwFlip.png", Out3W2);
	imwrite(myPath + "STEREO_HH.png",OutHH);

	delete SManager;
	
	system("pause");

	return 0;
}