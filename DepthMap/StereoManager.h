#pragma once
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core/utility.hpp"

#include <stdio.h>

using namespace cv;


class StereoManager
{
private:
	
	//Variables

	std::string		img1Name;
	std::string		img2Name;
	std::string		finalname;
	std::string		path;
	Mat				img1;
	Mat				img2;
	Mat				disp;
	Mat				disp8;
	int				numOfDisparities;
	int				SADWindowSize;

	int				alg;
	Ptr<StereoBM>		bm;
	Ptr<StereoSGBM>		sgbm;

	//Functions

	bool createBM();
	bool createSGBM();
	void display();

public:
	static enum { STEREO_BM = 0, STEREO_SGBM = 1, STEREO_HH = 2, STEREO_3WAY = 4 };
	StereoManager();
	StereoManager(std::string n_img1, std::string n_img2, std::string n_path, int n_numOfDisparities,int n_SADWindowSize,int n_alg);
	bool createStereoImage();
	~StereoManager();
};

