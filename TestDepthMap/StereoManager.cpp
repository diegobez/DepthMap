#include "stdafx.h"


#include <assert.h> 
#include <vector>

#include <stdio.h>
#include <iostream>
#include <BaseStereoBM.h>
#include <BaseStereoSGBM.h>

#include "StereoManager.h"

StereoManager::StereoManager()
{
}


bool StereoManager::generateDepthMap(const Mat& imgL, const Mat& imgR, Mat& newImage, const int alg,const bool is360, const int disparity, const int blockSize)
{
	//Depending on algorthim creates a child variable (basestereobm or basestereosgbm) and generate depth map with it

	if (alg == BaseStereo::STEREO_BM) {
		 baseStereo = new BaseStereoBM();
	}
	else {
		baseStereo = new BaseStereoSGBM();
	}

	baseStereo->compute(imgL, imgR, newImage, alg,is360, disparity, blockSize);

	return true;
}

bool StereoManager::calibrateCamera(const std::vector<std::string>& imagelist, const std::string& path)
{
	//No works

	std::vector<std::vector<Point2f> > imagePoints;
	std::vector<std::vector<Point3f> > objectPoints;
	std::vector<Point2f> corners;
	Size boardSize = Size(4, 6);

	int i, j, k, nimages = 1;
	std::vector<std::string> goodImageList;
	Mat img;
	//std::cout << path + imagelist[0] << std::endl;
	//img = imread(path + imagelist[0], IMREAD_GRAYSCALE);
	//namedWindow("corners", CV_WINDOW_AUTOSIZE);
	//imshow("corners", img);
	//fflush(stdout);
	//waitKey(0);
	bool found = false;

	for (i = j = 0; i < nimages; i++)
	{
		for (k = 0; k < 2; k++)
		{
			std::string filename = imagelist[i * 2 + k];
			std::cout << path + filename << std::endl;
			img = imread(path+filename, 0);
			Mat timg;
			timg = img;

			found = findChessboardCorners(timg, boardSize, corners,
				CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);

			imagePoints.push_back(corners);
		}
	}

	float squareSize = 3;
	for (i = 0; i < imagePoints.size(); i++)
	{
		for (j = 0; j < boardSize.height; j++)
			for (k = 0; k < boardSize.width; k++)
				objectPoints[i].push_back(Point3f(k*squareSize, j*squareSize, 0));
	}

	return false;
}


StereoManager::~StereoManager()
{
	delete baseStereo;
}
