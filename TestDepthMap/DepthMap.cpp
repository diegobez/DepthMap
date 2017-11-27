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

	std::string myPath	 = "../resources/images/";
	std::string leftImg	 = "imgRealProjectL.png";
	std::string rightImg = "imgRealProjectR.png";
	//std::string leftImg = "imgLeonL.png";
	//std::string rightImg = "imgLeonR.png";
	bool isImg360		 = true;

	//Not works yet
	//SManager->calibrateCamera(std::vector<std::string>{"chessleft2.jpg", "chessright2.jpg" }, "resources/images/");

	//Generating depth map with img360 and tick count for each algorithm

	int64 t = getTickCount();
	SManager->generateDepthMap(leftImg, rightImg, "STEREO_BM.png", BaseStereo::STEREO_BM, myPath, isImg360);
	t = getTickCount() - t;
	printf("STEREO_BM: %fms\n", t * 1000 / getTickFrequency());

	t = getTickCount();
	SManager->generateDepthMap(leftImg, rightImg , "STEREO_SGBM.png", BaseStereo::STEREO_SGBM, "resources/images/", isImg360);
	t = getTickCount() - t;
	printf("STEREO_SGBM: %fms\n", t * 1000 / getTickFrequency());

	t = getTickCount();
	SManager->generateDepthMap(leftImg, rightImg, "STEREO_3WAY.png", BaseStereo::STEREO_3WAY, "resources/images/", isImg360);
	t = getTickCount() - t;
	printf("STEREO_3WAY: %fms\n", t * 1000 / getTickFrequency());

	t = getTickCount();
	SManager->generateDepthMap(leftImg, rightImg, "STEREO_HH.png", BaseStereo::STEREO_HH, "resources/images/", isImg360);
	t = getTickCount() - t;
	printf("STEREO_HH: %fms\n", t * 1000 / getTickFrequency());

	delete SManager;
	
	system("pause");

	//*****************************************************************************
	//Next code it is an initial implementation of disparity map with
	//OpenCV (now works with StereoManager)
	//*****************************************************************************



	////-- 1. Read the images
	//Mat imgLeft = imread("resources/images/imgL.png", IMREAD_GRAYSCALE);
	//Mat imgRight = imread("resources/images/imgR.png", IMREAD_GRAYSCALE);

	//imshow("LeftImage", imgLeft);
	//imshow("RightImage", imgRight);

	////-- And create the image in which we will save our disparitiess
	//Mat imgDisparity16S = Mat(imgLeft.rows, imgLeft.cols, CV_16S);
	//Mat imgDisparity8U = Mat(imgLeft.rows, imgLeft.cols, CV_8UC1);

	//Mat new_imgDisparity16S;
	//Mat new_imgDisparity8U = Mat(imgLeft.rows, imgLeft.cols, CV_8UC1);

	//if (imgLeft.empty() || imgRight.empty())
	//{
	//	std::cout << " --(!) Error reading images " << std::endl; return -1;
	//}

	////-- 2. Call the constructor for StereoBM

	///*BMState->preFilterSize = 21;
	//BMState->preFilterCap = 31;
	//BMState->SADWindowSize = 21;
	//BMState->minDisparity = 0;
	//BMState->numberOfDisparities = 128;
	//BMState->textureThreshold = 10;
	//BMState->uniquenessRatio = 15;*/

	//int ndisparities = 128;   /**< Range of disparity. Must be divisible by 16.  */
	//						/*The disparity range depends on the distance between
	//						the two cameras and the distance between the cameras and the object of interest. 
	//						Increase the DisparityRange when the cameras are far apart or the objects 
	//						are close to the cameras */

	//int SADWindowSize = 21; /**< Size of the block window. Must be odd */

	//Ptr<StereoBM> sbm = StereoBM::create(ndisparities, SADWindowSize);
	//sbm->setPreFilterCap(31);
	//sbm->setPreFilterSize(21);
	//sbm->setTextureThreshold(10);
	//sbm->setUniquenessRatio(15);

	//Ptr<StereoSGBM> ssgbm = StereoSGBM::create(0,ndisparities, SADWindowSize,0, 0,0,0,0,0,1,false);

	////-- 3. Calculate the disparity image
	//sbm->compute(imgLeft, imgRight, imgDisparity16S);
	//ssgbm->compute(imgLeft, imgRight, new_imgDisparity16S);

	////-- Check its extreme values
	//double minVal; double maxVal;
	//double new_minVal; double new_maxVal;

	//minMaxLoc(imgDisparity16S, &minVal, &maxVal);
	//minMaxLoc(new_imgDisparity16S, &new_minVal, &new_maxVal);

	//printf("Min disp: %f\n Max value: %f \n", minVal, maxVal);

	////-- 4. Display it as a CV_8UC1 image
	//imgDisparity16S.convertTo(imgDisparity8U, CV_8UC1, 255 / (maxVal - minVal));
	//namedWindow("Disparity", CV_WINDOW_AUTOSIZE);
	//imshow("Disparity", imgDisparity8U);

	//new_imgDisparity16S.convertTo(new_imgDisparity8U, CV_8UC1, 255 / (maxVal - new_minVal));
	//namedWindow("New_Disparity", CV_WINDOW_AUTOSIZE);
	//imshow("New_Disparity", new_imgDisparity8U);


	////-- 5. Save the image
	//const std::string finalname ("NewImage");
	//imwrite("resources/images/"+finalname+".png", imgDisparity16S);



	//waitKey(0);

	return 0;
}