#include "recognition.h"

cv::Mat sfml2opencv(const sf::Image& img)
{
	//get size from image
	cv::Size size(img.getSize().x, img.getSize().y);
	//create a mat on image memory
	cv::Mat mat(size, CV_8UC4, (void*)img.getPixelsPtr(), cv::Mat::AUTO_STEP);
	//make SFML RGBA to //OpenCV BGRA
	cv::cvtColor(mat, mat, cv::COLOR_RGBA2BGR);
	//clone mat to avoid memory editing on image memory
	return mat.clone();
}

cv::Mat GetThresholdedMat(const cv::Mat& mat) 
{
	int hueFrom = 30;
	int hueTo = 80;

	int saturationFrom = 150;
	int saturationTo = 255;

	int valueFrom = 190;
	int valueTo = 255;

	cv::Mat thresholded;
	cv::cvtColor(mat, thresholded, cv::COLOR_BGR2HSV);

	cv::inRange(
		thresholded,
		cv::Scalar(hueFrom, saturationFrom, valueFrom),
		cv::Scalar(hueTo, saturationTo, valueTo),
		thresholded
	);

	cv::erode(
		thresholded,
		thresholded,
		cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5))
	);

	cv::dilate(
		thresholded,
		thresholded,
		cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5))
	);

	cv::dilate(
		thresholded,
		thresholded,
		cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5))
	);

	cv::erode(
		thresholded,
		thresholded,
		cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5))
	);

	return thresholded;
}

sf::Image GetCountorsPic(const cv::Mat& thresholded
					   , cv::Mat& img
					   , std::vector<std::vector<cv::Point>>& contours)
{
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(
		thresholded,
		contours,
		hierarchy,
		cv::RETR_TREE,
		cv::CHAIN_APPROX_SIMPLE,
		cv::Point(0, 0)
	);

	int idx = 0;
	for (; idx >= 0; idx = hierarchy[idx][0])
	{
		cv::Scalar color(0, 0, 255);
		drawContours(img, contours, idx, color, 1, 8, hierarchy);
	}

	cv::cvtColor(img, img, cv::COLOR_BGR2RGBA);
	sf::Image image;
	image.create(img.cols, img.rows, img.ptr());

	return image;
}

float GetCentralPoint(const std::vector<std::vector<cv::Point>>& contours
					, const sf::Image& img)
{
	cv::Rect rect = cv::boundingRect(contours[0]);
	return static_cast<float>(rect.x + rect.width / 2) / static_cast<float>(img.getSize().x);
}

float DefineGreen(const sf::Image& img) {
	cv::Mat img_mat = sfml2opencv(img);
	cv::Mat thresholded = GetThresholdedMat(img_mat);

	std::vector<std::vector<cv::Point>> contours;

	sf::Image result = GetCountorsPic(thresholded, img_mat, contours);
	std::cout << "size = " << contours.size() << std::endl;

	if(contours.size() == 1)
	{
		float point = GetCentralPoint(contours, img);
	}
	else if (contours.size() == 0)
	{
		//������� ��� � �����
	} 
	else if (contours.size() > 1)
	{
		//����� ����� �� ���� �������� �� �����... throw exception?
	}


	return 0;
	
	
}