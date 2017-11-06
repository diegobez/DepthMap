#include "stdafx.h"
#include <iostream>
#include <fstream>


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


#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif

using namespace cv;
using namespace std;


///////////////////////////////////////////////////////////////////////////////////
//                                                                               //
//                                                                               //
//                                                                               //
///////////////////////////////////////////////////////////////////////////////////
int main()
{
	


	//-- 1. Read the images
	Mat imgLeft = imread("resources/images/myLimage.png", IMREAD_GRAYSCALE);
	Mat imgRight = imread("resources/images/myRimage.png", IMREAD_GRAYSCALE);

	imshow("LeftImage", imgLeft);
	imshow("RightImage", imgRight);

	//-- And create the image in which we will save our disparities
	Mat imgDisparity16S = Mat(imgLeft.rows, imgLeft.cols, CV_16S);
	Mat imgDisparity8U = Mat(imgLeft.rows, imgLeft.cols, CV_8UC1);

	if (imgLeft.empty() || imgRight.empty())
	{
		std::cout << " --(!) Error reading images " << std::endl; return -1;
	}

	//-- 2. Call the constructor for StereoBM

	/*BMState->preFilterSize = 21;
	BMState->preFilterCap = 31;
	BMState->SADWindowSize = 21;
	BMState->minDisparity = 0;
	BMState->numberOfDisparities = 128;
	BMState->textureThreshold = 10;
	BMState->uniquenessRatio = 15;*/

	int ndisparities = 0;   /**< Range of disparity. Must be divisible by 16.  */
							/*The disparity range depends on the distance between
							the two cameras and the distance between the cameras and the object of interest. 
							Increase the DisparityRange when the cameras are far apart or the objects 
							are close to the cameras */

	int SADWindowSize = 21; /**< Size of the block window. Must be odd */

	Ptr<StereoBM> sbm = StereoBM::create(ndisparities, SADWindowSize);
	sbm->setPreFilterCap(31);
	sbm->setPreFilterSize(21);
	sbm->setTextureThreshold(10);
	sbm->setUniquenessRatio(15);

	//-- 3. Calculate the disparity image
	sbm->compute(imgLeft, imgRight, imgDisparity16S);

	//-- Check its extreme values
	double minVal; double maxVal;

	minMaxLoc(imgDisparity16S, &minVal, &maxVal);

	printf("Min disp: %f\n Max value: %f \n", minVal, maxVal);

	//-- 4. Display it as a CV_8UC1 image
	imgDisparity16S.convertTo(imgDisparity8U, CV_8UC1, 255 / (maxVal - minVal));
	namedWindow("Disparity", CV_WINDOW_AUTOSIZE);
	imshow("Disparity", imgDisparity8U);

	//-- 5. Save the image
	const std::string finalname ("NewImage");
	imwrite("resources/images/"+finalname+".png", imgDisparity16S);

	waitKey(0);

	return 0;
}