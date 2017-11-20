#include "stdafx.h"
#include "BaseStereoBM.h"
#include "opencv2/calib3d.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/ximgproc/disparity_filter.hpp"

using namespace cv::ximgproc;

void BaseStereoBM::compute(const std::string& imgL, const std::string& imgR, const std::string& newImage, const int alg, const int disparity, const int blockSize)
{

	Mat img1 = imread(imgL, IMREAD_GRAYSCALE);
	Mat img2 = imread(imgR, IMREAD_GRAYSCALE);
	Mat disp = Mat(img1.rows, img1.cols, CV_16S);
	Mat disp2 = Mat(img1.rows, img1.cols, CV_16S);
	Mat disp8 = Mat(img1.rows, img1.cols, CV_8UC1);

	bm = StereoBM::create(disparity, blockSize);

	Ptr<DisparityWLSFilter> wls_filter = createDisparityWLSFilter(bm);

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

	Ptr<StereoMatcher> bm2 = createRightMatcher(bm);


	bm->compute(img1, img2, disp);
	bm2->compute(img2, img1, disp2);

	double lambda = 8000.0;
	double sigma = 1.5;
	double vis_mult = 1.0;
	Mat filtered_disp;

	wls_filter->setLambda(lambda);
	wls_filter->setSigmaColor(sigma);
	wls_filter->filter(disp, img1, filtered_disp, disp2);

	Mat raw_disp_vis;
	getDisparityVis(disp, raw_disp_vis, vis_mult);

	Mat filtered_disp_vis;
	getDisparityVis(filtered_disp, filtered_disp_vis, vis_mult);


	Mat cropImg = filtered_disp_vis;
	double minVal; double maxVal;
	minMaxLoc(filtered_disp_vis, &minVal, &maxVal);

	//cropImage(disp, cropImg);
	cropImg.convertTo(disp8, CV_8U, 255 / (maxVal - minVal));
	imwrite(newImage, disp8);

	delete bm;
}

BaseStereoBM::BaseStereoBM()
{
}


BaseStereoBM::~BaseStereoBM()
{
	delete bm;
}
