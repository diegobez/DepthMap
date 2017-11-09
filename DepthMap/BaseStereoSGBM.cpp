#include "stdafx.h"
#include "BaseStereoSGBM.h"


void BaseStereoSGBM::compute(std::string imgL, std::string imgR, std::string newImage, int alg, int disparity, int blockSize)
{

	Mat img1 = imread(imgL, IMREAD_GRAYSCALE);
	Mat img2 = imread(imgR, IMREAD_GRAYSCALE);
	Mat disp = Mat(img1.rows, img1.cols, CV_16S);
	Mat disp8 = Mat(img1.rows, img1.cols, CV_8UC1);


	sgbm = StereoSGBM::create(0, disparity, blockSize);

	sgbm->setP1(8 * img1.channels()*blockSize *blockSize);
	sgbm->setP2(32 * img1.channels()*blockSize* blockSize);
	sgbm->setMinDisparity(0);
	sgbm->setNumDisparities(disparity);
	sgbm->setUniquenessRatio(10);
	sgbm->setSpeckleWindowSize(200);
	sgbm->setSpeckleRange(2);
	sgbm->setDisp12MaxDiff(1);

	if (alg == BaseStereo::STEREO_HH)
		sgbm->setMode(StereoSGBM::MODE_HH);
	else if (alg == BaseStereo::STEREO_SGBM)
		sgbm->setMode(StereoSGBM::MODE_SGBM);
	else if (alg == BaseStereo::STEREO_3WAY)
		sgbm->setMode(StereoSGBM::MODE_SGBM_3WAY);

	sgbm->compute(img1, img2, disp);
	disp.convertTo(disp8, CV_8U, 255 / (disparity*16.));
	imwrite(newImage, disp8);
	//display(disp8);

}

BaseStereoSGBM::BaseStereoSGBM()
{
}


BaseStereoSGBM::~BaseStereoSGBM()
{
}
