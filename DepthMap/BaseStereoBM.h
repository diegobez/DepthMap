#pragma once
#include <BaseStereo.h>




class BaseStereoBM :
	public BaseStereo
{
private:
	Ptr<StereoBM> bm;

public:
	virtual void compute(std::string imgL, std::string imgR, std::string newImage, int alg, int disparity, int blockSize) override;
	BaseStereoBM();
	~BaseStereoBM();
};

