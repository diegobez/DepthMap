#pragma once
#include <iostream>
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
//#include "opencv2/core/utility.hpp"
using namespace cv;


class BaseStereo
{
private:
	//It doesnt work

protected:
	
	const void display(const Mat &img);
	void cropImage(const Mat &img, Mat &cropImg);
	void cropImageBySize(const Mat &img, Mat &cropImg,int width,int height);
	void addLeftBorder(Mat& img, int percent);
	void depthMapFiltering(const const Ptr<StereoMatcher> stereoMatcher, const Mat& LeftImg, const Mat& disparityMapLeft, const Mat& disparityMapRight, Mat& filteredDisparity);

public:
	static enum { STEREO_BM = 0, STEREO_SGBM = 1, STEREO_HH = 2, STEREO_3WAY = 3 } algorithm;
	BaseStereo();
	~BaseStereo();
	virtual void compute(const Mat& imgL, const Mat& imgR, Mat& newImage, const int alg, const bool is360, const int disparity, const int blockSize) = 0;
	

};

