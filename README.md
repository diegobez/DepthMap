# Stereo Depth Map
This application basically calculates the depth mapping from a video stereo in top-bottom format.

It calculates frame by frame and make an output exit in video (also in stere top-bottom format).

The external libraries used were OpenCV 3.3.1 with ximgproc extra module (to make depth map from image) and ffmpeg to generate the output video.

### Prerequisites

If you want to modify it, just visual studio 2017

### Installing

You only have to clone or contrib this repository (it´s prepare to work with visual studio 2017 with compiled libraries in debug and release).

Important: to use the application in debug you must unzip this file DepthMap\x64\Debug\opencv_world331d.zip, it contains openCV dll (I couldn´t push it because of github max. 100 MB)

### What the project contains

This project contains 2 visual studio projets.

The folder structure is this:

-.vs : visual studio stuff.

-demo : demo to just make depth map video with no editing.

-ffmpeg : ffmpeg library.

-FilterDepthMap : project make in visual studio to make depth map from video with ffmpeg.

-include: opencv include folder.

-ipch : filter folder(?).

-lib : opencv lib folder (it conteins opencv libs in debug and release).

-resources : folder to keep image and video files.

-TestDepthMap : project make in visual studio to make depth map from 2 images (for testing).

-x64 : folder where is generated FilterDepthMap.dll from FilterDepthMap project (it is used by ffmeg and frei0r to generate DepthMap).

### Example of use to generate a Depth Map video

If you just want to use it, there are all prerapare in demo floder (don´t need anything else from repository).
Follow next steps to generate a depth map video.

1- Copy in folder resources/video the video (tested only in .mp4) you want to test.
Remember this video must be stereo and 360 with this demo.

2-Modify batch file (GenerateDepthMapVideo.bat) and edit it (right mouse button->edit)
This file use ffmpeg to call custom frei0r filter in each frame to generate the output video.

2.1- Modify your frei0r path to yours, it's very important to not change the absolute path structure (relative path doesn't work to me).


```
Set FREI0R_PATH=C://Users/Enrique/Documents/GitHub/DepthMap/demo/x64/Release

```

2.2- Modify input video name (change sherlock_4096.mp4 to your video copied in step 1).
You can also modify from the output video name to another (output2.mp4)

2.3- To render full time video you must delete from ffmpeg instruction "-t 5" (it's there for testing, it makes ffmpeg renderize only 5 secodns)

```
"ffmpeg\bin\ffmpeg.exe" -y -t 5 -i resources\video\sherlock_4096.mp4 -filter_complex "[0:v]format=pix_fmts=bgra,frei0r=filter_name=FilterDepthMap:filter_params=1|1" -pix_fmt yuv420p -c:v libx264 out2.mp4
```

```
"ffmpeg\bin\ffmpeg.exe" -y -i resources\video\INPUT_VIDEO.mp4 -filter_complex "[0:v]format=pix_fmts=bgra,frei0r=filter_name=FilterDepthMap:filter_params=1|1" -pix_fmt yuv420p -c:v libx264 OUTPUT_VIDEO.mp4
```

3- When you all these steps you can run bat file with double click and generate your own depth map video

### Frei0r video filter

To make the depth map video it was necesary to make a filter to use it with ffmpeg. This filter was created with frei0r.

This filter is in "FilterDepthMap.cpp" from FilterDepthMap project.

The important things in this file are made in f0r_update, this function is called in each frame.

1-First of all read the frames images (bottom and top images from frame).

```
int width = inst->width;
int height = inst->height;
uint32_t* inframe1 = inframe;
uint32_t* inframe2 = &(inframe[width*height/2]);
```
2-After that, it convert uint32_t imgs in Opencv variable (Mat) in 4 chanres for reading (BGRA).

```
//Initial image in 4 channels for reading

Mat cvSrc1(height / 2, width, CV_8UC4, inframe1);
Mat cvSrc2(height / 2, width, CV_8UC4, inframe2);
```
3-To create Depth Map image I need to transfrom 4 channel image in 1 channel (gray scale).
I also create flipped images to right dispacement.

```
//2- Turning them from bgr to gray (1 channel)

cvtColor(cvSrc1, imgLGray, CV_BGR2GRAY);
cvtColor(cvSrc2, imgRGray, CV_BGR2GRAY);
flip(imgLGray,imgLGrayFlip,1);
flip(imgRGray,imgRGrayFlip, 1);
```
4-Generating 2 depht map. To make this I create a stereoManager from this project and their values:

Values:

-Left Image.

-Right Image.

-Output Image (reference).

-Type of Algorithm (3WAY algorithm goes quite well).

-Is360video (true if is 360 to use the right border of image to complete left part of image).

```
//3- Generating depthmap img with 1 channel imgs

StereoManager* sm = new StereoManager();
sm->generateDepthMap(imgLGray, imgRGray, NewImgGrayL, BaseStereo::STEREO_3WAY, true);
sm->generateDepthMap(imgRGrayFlip, imgLGrayFlip, NewImgGrayRFlip, BaseStereo::STEREO_3WAY, true);
flip(NewImgGrayRFlip, NewImgGrayR, 1);
```

5- Converting output image in 4 channels (same size output and input) and copying it into output
```
//4-Copying output img with 4 channels in output

cvtColor(NewImgGrayL, NewImgL, CV_GRAY2BGRA);
cvtColor(NewImgGrayR, NewImgR, CV_GRAY2BGRA);

//The final size should be in (width * height * 4) bytes 
//but the output is 1 image and input 2 so the output is half of initial size

memcpy(outframe, NewImgL.data, (width * height * 4)/2);
memcpy(&(outframe[width*height / 2]), NewImgR.data, (width * height * 4) / 2);
```

### Example of use to generate a Depth Map image for testing

First of all, you must open DepthMap.sln with visual studio.

Then, open DepthMap.cpp from TestDepthMap project.

This is an example how to use the aplication to generate a depth map image :

1- Create a StereoManager object

```
StereoManager* SManager = new StereoManager();
```

2- Inicialize strings from path and name of image, also flag to indicate if img is 360 or not.

```
std::string myPath = "resources/images/";
std::string leftImg = "imgRealProjectL.png";
std::string rightImg = "imgRealProjectR.png";
bool isImg360		 = true;
```

3- Generate Opencv variables:
-Left and right image in gray scale
-Left and right image in gray scale flipped to right displacement
-Output variables

```
Mat Limg = imread(myPath+leftImg, IMREAD_GRAYSCALE);
Mat Rimg = imread(myPath+rightImg, IMREAD_GRAYSCALE);
Mat LimgFlip, RimgFlip;
cv::flip(Limg, LimgFlip, 1);
cv::flip(Rimg, RimgFlip, 1);
Mat OutBM, OutSGBM, Out3W, OutHH;
Mat Out3WF, Out3W2;

```

3- Call "generateDepthMap" with the step 2 parameters, output image name and algorithm ( bm, sgbm, 3way or hh)
Also call it flipped to generate the other stero image

```
t = getTickCount();
SManager->generateDepthMap(Limg, Rimg, Out3W, BaseStereo::STEREO_3WAY, isImg360);
SManager->generateDepthMap(RimgFlip, LimgFlip, Out3WF, BaseStereo::STEREO_3WAY, isImg360);
cv::flip(Out3WF, Out3W2, 1);
```
4- Write into folder path the new images

```
imwrite(myPath + "STEREO_3WAYL.png", Out3W);
imwrite(myPath + "STEREO_3WAYRwFlip.png", Out3W2);

```

## Inputs of image testing
Stereo Images

![Left Image](https://github.com/diegobez/DepthMap/blob/master/resources/images/imgRealProjectL.png)

![Right Image](https://github.com/diegobez/DepthMap/blob/master/resources/images/imgRealProjectR.png)

## Output of image testing
Output Image (3Way algorithm)

![Output Left](https://github.com/diegobez/DepthMap/blob/master/resources/images/STEREO_3WAYR.png)

![Output Right](https://github.com/diegobez/DepthMap/blob/master/resources/images/STEREO_3WAYRwFlip.png)


## Authors

* **Enrique Moltó** - *Initial work* - [Enrique Moltó](https://github.com/emf31)

See also the list of who participated in this project.

## License

Free licence
