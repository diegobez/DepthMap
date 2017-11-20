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
	void rectifyImagesCameraNoCalibrated(const std::string& imgL, const std::string& imgR);

protected:
	
	const void display(const Mat &img);
	void cropImage(const Mat &img, Mat &cropImg);

public:
	static enum { STEREO_BM = 0, STEREO_SGBM = 1, STEREO_HH = 2, STEREO_3WAY = 3 } algorithm;
	BaseStereo();
	~BaseStereo();
	virtual void compute(const std::string& imgL, const std::string& imgR, const std::string& newImage, const int alg, const int disparity, const int blockSize) = 0;
	

};

