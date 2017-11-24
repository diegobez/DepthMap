#include "stdafx.h"
#include "BaseStereoBM.h"
#include "opencv2/calib3d.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/ximgproc/disparity_filter.hpp"

using namespace cv::ximgproc;

void BaseStereoBM::compute(const std::string& imgL, const std::string& imgR, const std::string& newImage, const int alg, const bool is360, const int disparity, const int blockSize)
{
	//Reading imgs and iniciaze variables

	Mat img1 = imread(imgL, IMREAD_GRAYSCALE);
	Mat img2 = imread(imgR, IMREAD_GRAYSCALE);
	int fwidth = img1.cols;
	int fheight = img1.rows;

	//Only if image is 360 righborder is added to the left
	if (is360) {
		addLeftBorder(img1, 5);
		addLeftBorder(img2, 5);
	}
	
	//Open cv bm is created and computed
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

	//Use of the filter on the image created

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

	//Creating final output

	double minVal; double maxVal;
	minMaxLoc(filtered_disp_vis, &minVal, &maxVal);
	filtered_disp_vis.convertTo(disp8, CV_8U, 255 / (maxVal - minVal));

	//If img is 360 is croped by original size from right

	Mat cropImg = disp8;
	if (is360) {
		cropImageBySize(disp8, cropImg, fwidth, fheight);
	}

	imwrite(newImage, cropImg);

	delete bm;
}

BaseStereoBM::BaseStereoBM()
{
}


BaseStereoBM::~BaseStereoBM()
{
	delete bm;
}
