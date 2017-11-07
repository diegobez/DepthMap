#include "stdafx.h"



#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>


#include <assert.h> 



#include "StereoManager.h"


bool StereoManager::createBM()
{


	bm = StereoBM::create(numOfDisparities, 21);



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
	disp.convertTo(disp8, CV_8U, 255 / (numOfDisparities*16.));
	imwrite(path+finalName, disp8);
	display();
	

	return true;
}

bool StereoManager::createSGBM()
{
	sgbm = StereoSGBM::create(0, numOfDisparities, 3);

	sgbm->setP1(8 * img1.channels()*3*3);
	sgbm->setP2(32 * img1.channels()*3*3);
	sgbm->setMinDisparity(0);
	sgbm->setNumDisparities(numOfDisparities);
	sgbm->setUniquenessRatio(10);
	sgbm->setSpeckleWindowSize(100);
	sgbm->setSpeckleRange(32);
	sgbm->setDisp12MaxDiff(1);

	if (alg == StereoManager::STEREO_HH)
		sgbm->setMode(StereoSGBM::MODE_HH);
	else if (alg == StereoManager::STEREO_SGBM)
		sgbm->setMode(StereoSGBM::MODE_SGBM);
	else if (alg == StereoManager::STEREO_3WAY)
		sgbm->setMode(StereoSGBM::MODE_SGBM_3WAY);

	sgbm->compute(img1, img2, disp);
	disp.convertTo(disp8, CV_8U, 255 / (numOfDisparities*16.));
	imwrite(path+finalName, disp8);
	display();

	return true;
}

void StereoManager::display()
{
	namedWindow("left", 1);
	imshow("left", img1);
	namedWindow("right", 1);
	imshow("right", img2);
	namedWindow("disparity", CV_WINDOW_AUTOSIZE);
	imshow("disparity", disp8);
	printf("press any key to continue...\n");
	//fflush(stdout);
	//waitKey(0);
}

StereoManager::StereoManager():img1Name(""), img2Name(""), path(""), finalName("NewImage.png"), numOfDisparities(16), SADWindowSize(3), alg(StereoManager::STEREO_SGBM)
{
}

StereoManager::StereoManager(std::string n_img1, std::string n_img2, std::string n_outputName, std::string n_path, int n_numOfDisparities, int n_SADWindowSize, int n_alg)
	: img1Name(n_img1), img2Name(n_img2), finalName(n_outputName),path(n_path), numOfDisparities(n_numOfDisparities), SADWindowSize(n_SADWindowSize), alg(n_alg)
{
}

bool StereoManager::createStereoImage()
{
	img1 = imread(path+img1Name, IMREAD_GRAYSCALE);
	img2 = imread(path+img2Name, IMREAD_GRAYSCALE);
	disp = Mat(img1.rows, img1.cols, CV_16S);
	disp8 = Mat(img1.rows, img1.cols, CV_8UC1);

	if (alg == StereoManager::STEREO_BM) {
		return createBM();
	}
	else {
		return createSGBM();
	}
	return false;
}


StereoManager::~StereoManager()
{
}
