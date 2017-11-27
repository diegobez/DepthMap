#pragma once


#include <stdio.h>
#include <BaseStereo.h>


class StereoManager
{
private:

	//It doesnt work by now
	bool calibrateCamera(const std::vector<std::string>& imagelist, const std::string& path = "");

	BaseStereo*		baseStereo;

public:



	StereoManager();
	bool generateDepthMap(const Mat& imgL,const Mat& imgR,Mat& newImage,const int alg = BaseStereo::STEREO_SGBM,const bool is360=false,const int disparity=16*4,const int blockSize=21);

	~StereoManager();
};

