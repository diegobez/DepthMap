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

	//Loading stereo images

	IplImage* img1 = cvLoadImage("resources/images/imgR.png");
	IplImage* img2 = cvLoadImage("resources/images/imgL.png");

	//Creating images with cv

	IplImage *rimage = cvCreateImage(
		cvSize(img1->width, img1->height), IPL_DEPTH_8U, 1);
	cvCvtColor(img1, rimage, CV_RGB2GRAY);

	IplImage *limage = cvCreateImage(
		cvSize(img2->width, img2->height), IPL_DEPTH_8U, 1);
	cvCvtColor(img2, limage, CV_RGB2GRAY);

	//Showing stereo images in different windows

	cvNamedWindow("Right", CV_WINDOW_AUTOSIZE);
	cvShowImage("Right", rimage);

	cvNamedWindow("Left", CV_WINDOW_AUTOSIZE);
	cvShowImage("Left", limage);


	//Create image matrix (rows,cols,type_depth)
	//It returns a matrix
	//CV_8UC1 = 8bits unsigned 1 channel
	//CV_16S = 	16bit signed

	CvMat *matr = cvCreateMat(rimage->height, rimage->width, CV_8UC1);
	CvMat *matl = cvCreateMat(limage->height, limage->width, CV_8UC1);

	//The output single - channel 16 - bit signed disparity map of the same size as input images
	CvMat* disp = cvCreateMat(rimage->height, rimage->width, CV_16S);  
	CvMat* vdisp = cvCreateMat(rimage->height, rimage->width, CV_16S);

	//ansign rimage and limage to matr and mat1 (new matrix) wich are 8bits unsigned

	cvConvert(rimage, matr);
	cvConvert(limage, matl);

	//CvStereoBMState is created (where is the method cvCreateStereoBMstate?)

	CvStereoBMState *BMState = cvCreateStereoBMState();

	assert(BMState != 0);

	//Adding features to CvStereoBMState

	BMState->preFilterSize = 21;
	BMState->preFilterCap = 31;
	BMState->SADWindowSize = 21;
	BMState->minDisparity = 0;
	BMState->numberOfDisparities = 128;
	BMState->textureThreshold = 10;
	BMState->uniquenessRatio = 15;

	//find stereo correspondence (leftImage,rightImage, ounput 17 bit signed disparity map, stereo correspondence)
	//mat and mat1 must be 8bits unsigned and disp must be 16bit signed
	
	cvFindStereoCorrespondenceBM(matr, matl, disp, BMState);

	//Normalize image and save it in vdisp
	cvNormalize(disp, vdisp, 0, 255, CV_MINMAX, CV_8U);

	//Showing depthmap image
	
	cvShowImage("Dethmap", vdisp);
	cvWaitKey(0);


	return 0;
}