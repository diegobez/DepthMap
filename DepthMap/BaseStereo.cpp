#include "stdafx.h"
#include "BaseStereo.h"



void BaseStereo::rectifyImagesCameraNoCalibrated(std::string imgL, std::string imgR)
{

	Mat img1 = imread(imgL, IMREAD_GRAYSCALE);
	Mat img2 = imread(imgR, IMREAD_GRAYSCALE);

	std::vector<cv::KeyPoint> keypoints1;
	std::vector<cv::KeyPoint> keypoints2;
	cv::Mat descriptor1, descriptor2;

	Ptr<cv::ORB> orb = ORB::create();
	orb->detectAndCompute(img1, cv::Mat(), keypoints1, descriptor1);
	orb->detectAndCompute(img2, cv::Mat(), keypoints2, descriptor2);

	Mat out;
	drawKeypoints(img1, keypoints1, out);
	cv::imwrite("resources/images/keypoints1.png", out);//Testing image write
	drawKeypoints(img2, keypoints2, out);
	cv::imwrite("resources/images/keypoints2.png", out);//Testing image write

	BFMatcher matcher;
	std::vector<cv::DMatch> matches;
	matcher.match(descriptor1, descriptor2, matches);
	std::cout << "Number of matched points: " << matches.size() << std::endl;

	std::vector<int> pointIndexesLeft;
	std::vector<int> pointIndexesRight;
	for (std::vector<cv::DMatch>::const_iterator it = matches.begin(); it != matches.end(); ++it) {

		// Get the indexes of the selected matched keypoints
		pointIndexesLeft.push_back(it->queryIdx);
		pointIndexesRight.push_back(it->trainIdx);
	}

	// Convert keypoints into Point2f
	std::vector<cv::Point2f> selPointsLeft, selPointsRight;
	cv::KeyPoint::convert(keypoints1, selPointsLeft, pointIndexesLeft);
	cv::KeyPoint::convert(keypoints2, selPointsRight, pointIndexesRight);

	Mat image_matches;
	cv::drawMatches(img1, keypoints1, img2, keypoints2, matches, image_matches);
	cv::imwrite("resources/images/matches.png", image_matches);//Testing image write


	//std::vector<Point2f> outPutPoints;
	Mat f = findFundamentalMat(cv::Mat(selPointsLeft), cv::Mat(selPointsRight), CV_FM_RANSAC);
	cv::Mat H1(4, 4, img1.type());
	cv::Mat H2(4, 4, img2.type());

	cv::stereoRectifyUncalibrated(selPointsRight, selPointsLeft, f, img1.size(), H1, H2, 5);

	cv::Mat rectified1(img1.size(), img1.type());
	cv::warpPerspective(img1, rectified1, H1, img1.size());
	cv::imwrite("resources/images/rectified1.png", rectified1);//Testing image write

	cv::Mat rectified2(img2.size(), img2.type());
	cv::warpPerspective(img2, rectified2, H2, img2.size());
	cv::imwrite("resources/images/rectified2.png", rectified2);//Testing image write
}

void BaseStereo::display(Mat &img)
{
	namedWindow("left", CV_WINDOW_AUTOSIZE);
	imshow("left", img);
	printf("press any key to continue...\n");
	fflush(stdout);
	waitKey(0);
}

void BaseStereo::cropImage(Mat &img, Mat &cropImg)
{
	const int threshVal = 20;
	const float borderThresh = 0.05f; // 5%
	cv::Mat thresholded;
	cv::threshold(img, thresholded, threshVal, 255, cv::THRESH_BINARY);
	cv::morphologyEx(thresholded, thresholded, cv::MORPH_CLOSE,
		cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3)),
		cv::Point(-1, -1), 2, cv::BORDER_CONSTANT, cv::Scalar(0));

	cv::Point tl, br;

	for (int row = 0; row < thresholded.rows; row++)
	{
		if (cv::countNonZero(thresholded.row(row)) > borderThresh * thresholded.cols)
		{
			tl.y = row;
			break;
		}
	}

	for (int col = 0; col < thresholded.cols; col++)
	{
		if (cv::countNonZero(thresholded.col(col)) > borderThresh * thresholded.rows)
		{
			tl.x = col;
			break;
		}
	}

	for (int row = thresholded.rows - 1; row >= 0; row--)
	{
		if (cv::countNonZero(thresholded.row(row)) > borderThresh * thresholded.cols)
		{
			br.y = row;
			break;
		}
	}

	for (int col = thresholded.cols - 1; col >= 0; col--)
	{
		if (cv::countNonZero(thresholded.col(col)) > borderThresh * thresholded.rows)
		{
			br.x = col;
			break;
		}
	}

	cv::Rect roi(tl, br);
	cropImg = img(roi);
}

BaseStereo::BaseStereo()
{
}


BaseStereo::~BaseStereo()
{
}
