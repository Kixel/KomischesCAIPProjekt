#pragma once
#include <vector>
#include <opencv2/core/mat.hpp>

using namespace std;

class ImageManager
{
private:
	vector<cv::Mat> images;
	vector<string> filenames;

public:
	ImageManager();
	void addImage(cv::Mat im, string info);
	void loadImage(string filename);

	cv::Mat getImage(int n);
	cv::Mat getImage(string name);

	bool deleteImage(int n);
	bool deleteImage(string name);



};

