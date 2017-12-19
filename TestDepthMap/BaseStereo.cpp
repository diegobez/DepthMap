#include "stdafx.h"
#include "BaseStereo.h"
#include "opencv2/calib3d.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/ximgproc/disparity_filter.hpp"

using namespace cv::ximgproc;

const void BaseStereo::display(const Mat &img)
{
	//Display a img with openCV

	namedWindow("Image", CV_WINDOW_AUTOSIZE);
	imshow("Image", img);
	printf("press any key to continue...\n");
	fflush(stdout);
	waitKey(0);
}

void BaseStereo::cropImage(const Mat &img, Mat &cropImg)
{
	//Deletes black borders of the image eith threshold

	//Inicialize variables and creating threshold to calculate cropped img

	const int threshVal = 20;
	const float borderThresh = 0.05f; // 5%
	cv::Mat thresholded;
	cv::threshold(img, thresholded, threshVal, 255, cv::THRESH_BINARY);
	cv::morphologyEx(thresholded, thresholded, cv::MORPH_CLOSE,
		cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3)),
		cv::Point(-1, -1), 2, cv::BORDER_CONSTANT, cv::Scalar(0));

	//Deleting black borders in 4 directions

	cv::Point tl, br;

	for (int row = 0; row < thresholded.rows; row++)
	{
		if (cv::countNonZero(thresholded.row(row)) > borderThresh * thresholded.cols)
		{
			tl.y = row;
			break;
		}
	}

	for (int col = 0; col < thresholded.cols; col++)
	{
		if (cv::countNonZero(thresholded.col(col)) > borderThresh * thresholded.rows)
		{
			tl.x = col;
			break;
		}
	}

	for (int row = thresholded.rows - 1; row >= 0; row--)
	{
		if (cv::countNonZero(thresholded.row(row)) > borderThresh * thresholded.cols)
		{
			br.y = row;
			break;
		}
	}

	for (int col = thresholded.cols - 1; col >= 0; col--)
	{
		if (cv::countNonZero(thresholded.col(col)) > borderThresh * thresholded.rows)
		{
			br.x = col;
			break;
		}
	}

	//Creating output img

	cv::Rect roi(tl, br);
	cropImg = img(roi);
}

void BaseStereo::cropImageBySize(const Mat &img, Mat &cropImg, int width, int height)
{
	//Generates a sub image from img with the original size of img starting on right

	Mat subImage(img, cv::Rect(img.cols-width,0,width,height));
	cropImg = subImage;
}

void BaseStereo::addLeftBorder(Mat & img, int percent)
{
	//Make a border with a percert of source image on the left
	//The border on the left is filled with right source image (Wrap)
	

	Mat img_large;
	int pix =(int) img.cols * percent / 100;
	copyMakeBorder(img, img_large, 0, 0, pix, 0, BORDER_WRAP, Scalar::all(0));
	img = img_large;

}

void BaseStereo::depthMapFiltering(const Ptr<StereoMatcher> stereoMatcher,const Mat & LeftImg, const Mat & disparityMapLeft, const Mat & disparityMapRight, Mat & filteredDisparity )
{
	Ptr<DisparityWLSFilter> wls_filter = createDisparityWLSFilter(stereoMatcher);
	double lambda = 8000.0;
	double sigma = 1.5;
	double vis_mult = 1.0;
	Mat filtered_disp;

	wls_filter->setLambda(lambda);
	wls_filter->setSigmaColor(sigma);
	wls_filter->filter(disparityMapLeft, LeftImg, filtered_disp, disparityMapRight);

	Mat filtered_disp_vis;
	getDisparityVis(filtered_disp, filteredDisparity, vis_mult);

	//Creating final output

	//filteredDisparity.convertTo(filteredDisparity, CV_8UC1);
}



BaseStereo::BaseStereo()
{
}


BaseStereo::~BaseStereo()
{
}
