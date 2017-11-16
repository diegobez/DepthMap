#include "stdafx.h"
#include "BaseStereoSGBM.h"
#include <opencv2/core.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/photo.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"
//#include "opencv2/ximgproc.hpp"

//using namespace cv::ximgproc;


void BaseStereoSGBM::compute(std::string imgL, std::string imgR, std::string newImage, int alg, int disparity, int blockSize)
{

	Mat img1 = imread(imgL, IMREAD_GRAYSCALE);
	Mat img2 = imread(imgR, IMREAD_GRAYSCALE);
	Mat disp = Mat(img1.rows, img1.cols, CV_16S);
	Mat disp2 = Mat(img1.rows, img1.cols, CV_16S);
	Mat disp8 = Mat(img1.rows, img1.cols, CV_8UC1);


	sgbm = StereoSGBM::create(0, disparity, blockSize);

	//Ptr<DisparityWLSFilter> wls_filter = createDisparityWLSFilter(sgbm);;
	

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

	//Ptr<StereoMatcher> sgbm2 = createRightMatcher(sgbm);

	sgbm->compute(img1, img2, disp);
	//sgbm2->compute(img2, img1, disp2);

	double lambda = 8000.0;
	double sigma = 1.5;
	double vis_mult = 1.0;
	Mat filtered_disp;

	//wls_filter->setLambda(lambda);
	//wls_filter->setSigmaColor(sigma);
	//wls_filter->filter(disp, img1, filtered_disp, img2);

	/*Mat raw_disp_vis;
	getDisparityVis(disp, raw_disp_vis, vis_mult);*/

	Mat filtered_disp_vis;
	//getDisparityVis(filtered_disp, filtered_disp_vis, vis_mult);






	//cv::ximgproc::computeBadPixelPercent(NULL,NULL,cv::Rect());

	Mat cropImg = disp;

	cropImage(disp, cropImg);

	cropImg.convertTo(disp8, CV_8U, 255 / (disparity*16.));

	
	imwrite(newImage, disp8);
	//display(disp8);

}

BaseStereoSGBM::BaseStereoSGBM()
{
}


BaseStereoSGBM::~BaseStereoSGBM()
{
}
