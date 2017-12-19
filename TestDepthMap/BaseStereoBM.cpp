#include "stdafx.h"
#include "BaseStereoBM.h"
#include "opencv2/calib3d.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/ximgproc/disparity_filter.hpp"

using namespace cv::ximgproc;

void BaseStereoBM::compute(const Mat& imgL, const Mat& imgR, Mat& newImage, const int alg, const bool is360, const int disparity, const int blockSize)
{
	//Generates a depthMap with bm class of OpenCV

	//1-Reading imgs and iniciaze variables

	Mat img1 = imgL;
	Mat img2 = imgR;
	int fwidth = img1.cols;
	int fheight = img1.rows;

	//2-Only if image is 360 righborder is added to the left
	if (is360) {
		addLeftBorder(img1, 5);
		addLeftBorder(img2, 5);
	}

	Mat disp = Mat(img1.rows, img1.cols, CV_8UC1);
	Mat disp2 = Mat(img1.rows, img1.cols, CV_8UC1);
	Mat disp8 = Mat(img1.rows, img1.cols, CV_8UC1);

	//3-Setting up Opencv BM

	//All information of parameters got from this urls
	//Docs OpenCV sgbm: https://docs.opencv.org/2.4/modules/calib3d/doc/camera_calibration_and_3d_reconstruction.html?highlight=stereobm#stereosgbm
	//Docs OpenCV Disparity map post-filtering (see github link on this page) : https://docs.opencv.org/3.1.0/d3/d14/tutorial_ximgproc_disparity_filtering.html

	//Parameters:

	//minDisparity:		Minimum possible disparity value. 
	//					Normally, it is zero

	//numDisparities:	Maximum disparity minus minimum disparity. 
	//					Must be divisible by 16.

	//SADWindowSize:	Matched block size. 
	//					It must be an odd number >=1 .
	//					Normally, it should be somewhere in the 3..11 range.

	bm = StereoBM::create(disparity, blockSize);

	//uniquenessRatio:	Margin in percentage by which the best(minimum) computed cost function value should “win” 
	//					the second best value to consider the found match correct.
	//					Normally, a value within the 5 - 15 range is good enough.

	bm->setUniquenessRatio(10);

	//speckleWindowSize:	Maximum size of smooth disparity regions to consider their noise speckles and invalidate. 
	//						0 to disable speckle filtering. Otherwise, in the 50-200 range.
	bm->setSpeckleWindowSize(200);

	//speckleRange:		Maximum disparity variation within each connected component. 
	//					Positive value, it will be implicitly multiplied by 16.
	//					Normally, 1 or 2 is good enough.

	bm->setSpeckleRange(2);

	//disp12MaxDiff: Maximum allowed difference (in integer pixel units) in the left-right disparity check

	bm->setDisp12MaxDiff(1);

	//4-Creating right macher for good post-filtering

	Ptr<StereoMatcher> bmRightMatcher = createRightMatcher(bm);

	//5-Generating disparityMaps from left and right matchers

	bm->compute(img1, img2, disp);
	bmRightMatcher->compute(img2, img1, disp2);

	//6-Making postfiltering

	depthMapFiltering(bm, img1, disp, disp2, disp8);

	//7-If img is 360 is croped by original size from right

	Mat cropImg = disp8;

	if (is360) {
		cropImageBySize(disp8, cropImg, fwidth, fheight);
	}
	newImage = cropImg;


	delete bm;
}

BaseStereoBM::BaseStereoBM()
{
}


BaseStereoBM::~BaseStereoBM()
{
	delete bm;
}
