#include "stdafx.h"
#include "BaseStereoBM.h"


void BaseStereoBM::compute(std::string imgL, std::string imgR, std::string newImage, int alg, int disparity, int blockSize)
{

	Mat img1 = imread(imgL, IMREAD_GRAYSCALE);
	Mat img2 = imread(imgR, IMREAD_GRAYSCALE);
	Mat disp = Mat(img1.rows, img1.cols, CV_16S);
	Mat disp8 = Mat(img1.rows, img1.cols, CV_8UC1);

	bm = StereoBM::create(disparity, blockSize);

	//bm->setROI1(roi1);
	//bm->setROI2(roi2);
	bm->setPreFilterCap(31);
	bm->setMinDisparity(0);
	//bm->setNumDisparities(numOfDisparities);
	bm->setTextureThreshold(10);
	bm->setUniquenessRatio(15);
	bm->setSpeckleWindowSize(100);
	bm->setSpeckleRange(32);
	bm->setDisp12MaxDiff(1);

	bm->compute(img1, img2, disp);
	disp.convertTo(disp8, CV_8U, 255 / (disparity*16.));
	imwrite(newImage, disp8);
}

BaseStereoBM::BaseStereoBM()
{
}


BaseStereoBM::~BaseStereoBM()
{
}
