#pragma once
#include <QImage>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Tools.h"
#include <algorithm>
#include <string>

using namespace std;
using namespace cv;


class KPImage {
	
private:
	string internalname;
	QImage q;

public:
	KPImage();
	KPImage(Mat& m);
	KPImage(QImage& data);
	KPImage(const string name);
	KPImage(int w, int h);
	KPImage(int w, int h, int format);

	QImage& getQ();
	Mat getM();
	void setName(const string n);
	string getName();
	int getWidth();
	int getHeight();
	int getNumChannels();
	int getBitDepth();
	
	bool saveToDisk(const string name);
};

