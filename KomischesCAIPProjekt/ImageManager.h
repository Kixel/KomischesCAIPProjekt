#pragma once
#include <vector>
#include <opencv2/core/mat.hpp>
#include <map>
#include "KPImage.h"

using namespace std;

class ImageManager
{
private:
	map<int, KPImage*> images;
	int keywalker;

public:
	ImageManager();
	void addImage(KPImage* im, string info);
	int loadImage(string filename);

	KPImage* getImage(int n);
	//cv::Mat getImage(string name);

	bool deleteImage(int n);
	//bool deleteImage(string name);

	bool iDExists(int n);


};

