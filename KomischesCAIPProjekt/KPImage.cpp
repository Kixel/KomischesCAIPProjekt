#include "KPImage.h"
#include <iostream>

KPImage::KPImage() : q(), internalname("Empty Image")
{
	// TODO add constructors to KPImage
}

KPImage::KPImage(Mat& m) : q(), internalname("Empty Image") {
	//this->im = m.clone();
	// TODO conversion from Mat
}

KPImage::KPImage(QImage& data) : q(data), internalname("") {
	//this->im = Mat(data.height(), data.width(), Tools::Type_Q2CV(data.format()), data.bits(), data.bytesPerLine());
}

KPImage::KPImage(const string name) : q(QString(name.c_str())), internalname(name) {
	
	/*string a(name);
	replace(a.begin(), a.end(), '/', '\\');
	a = "D:\magic.jpg";
	cout << a << endl;
	im = imread(a, 1);
	if (im.data == NULL) {
		cout << "data is null" << endl;
	}
	cout << "Image format " << im.type() << " size " << im.cols << " " << im.rows << " " << endl;*/
	
}

KPImage::KPImage(int w, int h) : q(w, h, QImage::Format_RGB888), internalname("") {

}

KPImage::KPImage(int w, int h, int format) : q(w, h, QImage::Format(format)), internalname("") {
}

QImage& KPImage::getQ() {
	// TODO conversion to Qimage
	return q;
}

Mat KPImage::getM() {
	return Mat();
}

void KPImage::setName(const string n) {
	this->internalname = n;
}

string KPImage::getName() {
	return this->internalname;
}

int KPImage::getWidth() {
	return q.width();
}

int KPImage::getHeight() {
	return q.height();
}

int KPImage::getNumChannels() {
	// TODO num channels from qimage
	return -1;
}

int KPImage::getBitDepth() {
	// TODO bit depth from qimage
	return q.depth();
}


bool KPImage::saveToDisk(const string name) {
	// TODO write save function
	cout << name << endl;
	return false;
}

