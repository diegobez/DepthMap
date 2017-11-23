#pragma once
#include "BaseStereo.h"
class BaseStereoSGBM :
	public BaseStereo
{
private:
	Ptr<StereoSGBM> sgbm;


public:

	virtual void compute(const std::string& imgL, const std::string& imgR, const std::string& newImage, const int alg, const bool is360, const int disparity, const int blockSize) override;

	BaseStereoSGBM();
	~BaseStereoSGBM();
};

