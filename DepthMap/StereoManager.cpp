#include "stdafx.h"


#include <assert.h> 

#include <stdio.h>
#include <iostream>
#include <BaseStereoBM.h>
#include <BaseStereoSGBM.h>

#include "StereoManager.h"

StereoManager::StereoManager()
{
}


bool StereoManager::generateDepthMap(std::string imgL, std::string imgR, std::string newImage, int alg, std::string path, int disparity, int blockSize)
{
	if (alg == BaseStereo::STEREO_BM) {
		 baseStereo = new BaseStereoBM();
	}
	else {
		baseStereo = new BaseStereoSGBM();
	}
	//baseStereo->rectifyImagesCameraNoCalibrated(path + imgL, path + imgR);

	baseStereo->compute(path+imgL, path+imgR, path+newImage, alg, disparity, blockSize);

	return true;
}

bool StereoManager::calibrateCamera(const std::vector<std::string>& imagelist, std::string path)
{
	// ARRAY AND VECTOR STORAGE:

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
/*
	Mat cimg;
	cvtColor(img, cimg, COLOR_GRAY2BGR);
	
	drawChessboardCorners(cimg,boardSize, corners, found);
	double sf = 640. / MAX(img.rows, img.cols);
	imshow("corners", cimg);
	waitKey(0);
	*/
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
}
