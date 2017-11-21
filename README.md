# Stereo Depth Map
This application calculates the depth mapping from 2 stereo images.
The only external library used was OpenCV 3.3.1 with ximgproc extra module

### Prerequisites

Visual studio 2017

### Installing

You only have to clone or contrib this repository (it´s prepare to work with visual studio 2017 with compiled libraries in debug and release).

Important: to use the application in debug you must unzip this file DepthMap\x64\Debug\opencv_world331d.zip, it contains openCV dll (I couldn´t push it because of github max. 100 MB)

### Example of use

To generate a depth map follow next steps (it's on DepthMap.cpp):

1 - Create a StereoManager object

```
StereoManager* SManager = new StereoManager();
```

2 - Inicialize strings from path and name of image

```
	std::string myPath = "resources/images/";
	std::string leftImg = "imgRealProjectL.png";
	std::string rightImg = "imgRealProjectR.png";
```

3 - Call "generateDepthMap" with the step 2 parameters, output image name and algorithm ( bm, sgbm, 3way or hh)

```
	int64 t = getTickCount();
	SManager->generateDepthMap(leftImg, rightImg, "STEREO_BM.png", BaseStereo::STEREO_BM, myPath);
	t = getTickCount() - t;
	printf("STEREO_BM: %fms\n", t * 1000 / getTickFrequency());
```

## Contributing

Pull requests are working on

## Authors

* **Enrique Moltó** - *Initial work* - [Enrique Moltó](https://github.com/emf31)

See also the list of who participated in this project.

## License

License is working on
