#pragma once


#include <stdio.h>
#include <BaseStereo.h>


class StereoManager
{
private:

	BaseStereo*		baseStereo;

public:
	StereoManager();
	bool generateDepthMap(std::string imgL, std::string imgR, std::string newImage, int alg = BaseStereo::STEREO_SGBM,  std::string path="", int disparity=16*4, int blockSize=21);


	~StereoManager();
};

