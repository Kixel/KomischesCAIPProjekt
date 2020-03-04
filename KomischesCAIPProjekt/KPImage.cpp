#include "KPImage.h"

KPImage::KPImage() : im(1,1, CV_8UC3) 
{
	// TODO add constructors to KPImage
}

KPImage::KPImage(Mat m) : im(), internalname() {
	this->im = m;
}

KPImage::KPImage(QImage& data) : im(), internalname() {
	this->im = Mat(data.height(), data.width(), Tools::Type_Q2CV(data.format()), data.bits(), data.bytesPerLine());
}

KPImage::KPImage(const string name) : im(), internalname(name) {
	im = imread(name, 1);

}

KPImage::KPImage(int w, int h) : im(w, h, CV_8UC3), internalname() {

}




QImage& KPImage::getQ() {
	// TODO conversion to Qimage
	QImage* imgIn = new QImage((uchar*)im.data, im.cols, im.rows, im.step, QImage::Format(Tools::Type_CV2Q(im.type())));
	return *imgIn;
}

Mat& KPImage::getM() {
	return im;
}

void KPImage::setName(const string& n) {
	this->internalname = n;
}


bool KPImage::saveToDisk(const string name) {
	// TODO write save function
	return false;
}

