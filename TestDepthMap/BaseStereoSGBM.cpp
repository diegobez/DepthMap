#include "stdafx.h"
#include "BaseStereoSGBM.h"
#include "opencv2/calib3d.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/ximgproc/disparity_filter.hpp"

using namespace cv::ximgproc;


void BaseStereoSGBM::compute(const Mat& imgL, const Mat& imgR, Mat& newImage, const int alg, const bool is360, const int disparity, const int blockSize)
{
	//Generates a depthMap with sgbm class of OpenCV

	//1-Reading imgs and iniciaze variables

	Mat img1 = imgL;
	Mat img2 = imgR;
	int fwidth = img1.cols;
	int fheight = img1.rows;

	//2-Only if image is 360 righborder is added to the left
	if(is360){
	addLeftBorder(img1, 5);
	addLeftBorder(img2, 5);
	}

	Mat disp = Mat(img1.rows, img1.cols, CV_8UC1);
	Mat disp2 = Mat(img1.rows, img1.cols, CV_8UC1);
	Mat disp8 = Mat(img1.rows, img1.cols, CV_8UC1);

	//3-Setting up Opencv SGBM

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

	sgbm = StereoSGBM::create(0, disparity, blockSize);

	//P1:					The first parameter controlling the disparity smoothness

	//P2:					The second parameter controlling the disparity smoothness

	//disparity smoothness: The larger the values are, the smoother the disparity is. 
	//						The algorithm requires P2 > P
	//						Recommended, 8*number_of_image_channels*SADWindowSize*SADWindowSize and 32*number_of_image_channels*SADWindowSize*SADWindowSize
	
	sgbm->setP1(8 * img1.channels()*blockSize *blockSize);
	sgbm->setP2(32 * img1.channels()*blockSize* blockSize);

	//uniquenessRatio:	Margin in percentage by which the best(minimum) computed cost function value should “win” 
	//					the second best value to consider the found match correct.
	//					Normally, a value within the 5 - 15 range is good enough.

	sgbm->setUniquenessRatio(10);

	//speckleWindowSize:	Maximum size of smooth disparity regions to consider their noise speckles and invalidate. 
	//						0 to disable speckle filtering. Otherwise, in the 50-200 range.
	sgbm->setSpeckleWindowSize(200);

	//speckleRange:		Maximum disparity variation within each connected component. 
	//					Positive value, it will be implicitly multiplied by 16.
	//					Normally, 1 or 2 is good enough.

	sgbm->setSpeckleRange(2);

	//disp12MaxDiff: Maximum allowed difference (in integer pixel units) in the left-right disparity check

	sgbm->setDisp12MaxDiff(1);

	//Selection of the algorithm for sgbm

	if (alg == BaseStereo::STEREO_HH)
		sgbm->setMode(StereoSGBM::MODE_HH);
	else if (alg == BaseStereo::STEREO_SGBM)
		sgbm->setMode(StereoSGBM::MODE_SGBM);
	else if (alg == BaseStereo::STEREO_3WAY)
		sgbm->setMode(StereoSGBM::MODE_SGBM_3WAY);

	//4-Creating right macher for good post-filtering

	Ptr<StereoMatcher> sgbmStereoMatcher = createRightMatcher(sgbm);

	//5-Generating disparityMaps from left and right matchers

	sgbm->compute(img1, img2, disp);
	sgbmStereoMatcher->compute(img2, img1, disp2);

	//6-Making postfiltering

	depthMapFiltering(sgbm, img1, disp, disp2, disp8);

	//7-If img is 360 is croped by original size from right

	Mat cropImg = disp8;

	if (is360) {
		cropImageBySize(disp8, cropImg, fwidth, fheight);
	}
	newImage = cropImg;


	delete sgbm;
}

BaseStereoSGBM::BaseStereoSGBM()
{
}


BaseStereoSGBM::~BaseStereoSGBM()
{
	delete sgbm;
}
