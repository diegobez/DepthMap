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
	IplImage* img1 = cvLoadImage("imgR.png");
	IplImage* img2 = cvLoadImage("imgL.png");

	IplImage *rimage = cvCreateImage(
		cvSize(img1->width, img1->height), IPL_DEPTH_8U, 1);
	cvCvtColor(img1, rimage, CV_RGB2GRAY);

	IplImage *limage = cvCreateImage(
		cvSize(img2->width, img2->height), IPL_DEPTH_8U, 1);
	cvCvtColor(img2, limage, CV_RGB2GRAY);

	cvNamedWindow("Right", CV_WINDOW_AUTOSIZE);
	cvShowImage("Right", rimage);

	cvNamedWindow("Left", CV_WINDOW_AUTOSIZE);
	cvShowImage("Left", limage);

	CvMat *matr = cvCreateMat(rimage->height, rimage->width, CV_8UC1);
	CvMat *matl = cvCreateMat(limage->height, limage->width, CV_8UC1);
	CvMat* disp = cvCreateMat(rimage->height, rimage->width, CV_16S);
	CvMat* vdisp = cvCreateMat(rimage->height, rimage->width, CV_16S);

	cvConvert(rimage, matr);
	cvConvert(limage, matl);

	CvStereoBMState *BMState = cvCreateStereoBMState();
	assert(BMState != 0);
	BMState->preFilterSize = 21;
	BMState->preFilterCap = 31;
	BMState->SADWindowSize = 21;
	BMState->minDisparity = 0;
	BMState->numberOfDisparities = 128;
	BMState->textureThreshold = 10;
	BMState->uniquenessRatio = 15;


	cvFindStereoCorrespondenceBM(matr, matl, disp, BMState);
	cvNormalize(disp, vdisp, 0, 255, CV_MINMAX);

	cvShowImage("depthmap", vdisp);
	cvWaitKey(0);
	return 0;
}