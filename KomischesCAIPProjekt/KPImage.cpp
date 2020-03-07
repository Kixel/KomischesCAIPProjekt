#include "KPImage.h"
#include <iostream>

KPImage::KPImage() : q(), internalname("")
{

}

KPImage::KPImage(Mat& m) : q(), internalname("") {
	this->setM(m);
}

KPImage::KPImage(QImage& data) : q(data), internalname("") {
}

KPImage::KPImage(const string name) : q(QString(name.c_str())), internalname(name) {
	if (q.isGrayscale()) {
		q = q.convertToFormat(QImage::Format_Grayscale8);
	} else {
		q = q.convertToFormat(QImage::Format_RGB888);
	}
}

KPImage::KPImage(int w, int h) : q(w, h, QImage::Format_RGB888), internalname("") {

}

KPImage::KPImage(int w, int h, int format) : q(w, h, QImage::Format(format)), internalname("") {
}

QImage& KPImage::getQ() {
	return q;
}

Mat KPImage::getM() {
	switch (q.format()) {
	case QImage::Format_RGB888:
	{
		QImage swapped = q.rgbSwapped();
		return Mat(Mat(swapped.height(), swapped.width(), CV_8UC3,
			const_cast<uchar*>(swapped.bits()), static_cast<size_t>(swapped.bytesPerLine())));
	}
	case QImage::Format_Grayscale8:
	{
		return Mat(Mat(q.height(), q.width(), CV_8UC1,
			const_cast<uchar*>(q.bits()), static_cast<size_t>(q.bytesPerLine())));
	}
	}
}

void KPImage::setM(Mat& m) {
	switch (m.type()) {
	case CV_8UC3:
	{
		//delete& q;
		q = QImage(m.data, m.cols, m.rows, static_cast<int>(m.step), QImage::Format_RGB888);
		q = q.rgbSwapped();
	}
	case CV_8UC1:
	{
		//delete &q;
		q = QImage(m.data, m.cols, m.rows, static_cast<int>(m.step), QImage::Format_Grayscale8);
	}
	}
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
	return q.save(QString(name.c_str()));
}

