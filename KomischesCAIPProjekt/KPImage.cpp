#include "KPImage.h"
#include <iostream>

KPImage::KPImage() : q(), internalname("")
{

}

KPImage::KPImage(Mat* m) : q(), internalname("") {
	this->setM(m);
	if (q.isGrayscale()) {
		q = q.convertToFormat(QImage::Format_Grayscale8);
	} else if (q.format() != 1) {
		q = q.convertToFormat(QImage::Format_RGB888);
	}
}

KPImage::KPImage(QImage& data) : q(data), internalname("") {
	if (q.isGrayscale()) {
		q = q.convertToFormat(QImage::Format_Grayscale8);
	} else if (q.format() != 1) {
		q = q.convertToFormat(QImage::Format_RGB888);
	}
}

KPImage::KPImage(const string name) : q(QString(name.c_str())), internalname(name) {
	cout << "read fomrat is " << q.format() << endl;
	if (q.isGrayscale()) {
		q = q.convertToFormat(QImage::Format_Grayscale8);
	} else if(q.format() != 1) {
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
		QImage swapped = q.rgbSwapped().convertToFormat(QImage::Format_Grayscale8);
		return Mat(Mat(swapped.height(), swapped.width(), CV_8UC1,
			const_cast<uchar*>(swapped.bits()), static_cast<size_t>(swapped.bytesPerLine()))).clone();
	}
	case QImage::Format_Grayscale8:
	{
		return Mat(Mat(q.height(), q.width(), CV_8UC1,
			const_cast<uchar*>(q.bits()), static_cast<size_t>(q.bytesPerLine()))).clone();
	}
	case QImage::Format_Mono:
	{
		QImage g = q.convertToFormat(QImage::Format_Grayscale8);
		return Mat(Mat(g.height(), g.width(), CV_8UC1,
			const_cast<uchar*>(g.bits()), static_cast<size_t>(g.bytesPerLine()))).clone();
	}

	}
}

void KPImage::setM(Mat* m) {
	switch (m->type()) {
	case CV_8UC3:
	{
		Mat t;
		cvtColor(*m, t, CV_BGR2GRAY);
		//cvtColor(*m, t, CV_BGR2RGB);
		//q = QImage(m->data, m->cols, m->rows, static_cast<int>(m->step), QImage::Format_RGB888).rgbSwapped();
		q = QImage(t.data, t.cols, t.rows, static_cast<int>(t.step), QImage::Format_RGB888);
		
		//cout << m->cols << endl;

		/*q = QImage(m->cols, m->rows, QImage::Format_RGB888);
		for (int y = 0; y < q.height(); y++) {
			for (int x = 0; x < q.width(); x++) {
				Vec3b r = m->at<Vec3b>(Point(y, x));
				Vec3b g = m->at<Vec3b>(Point(y, x+1));
				Vec3b b = m->at<Vec3b>(Point(y, x+2));


				q.setPixel(x, y, qRgb(r[2], g[1], b[0]));
			}
		}*/

	}
	case CV_8UC1:
	{
		q = QImage(m->data, m->cols, m->rows, static_cast<int>(m->step), QImage::Format_Grayscale8);
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
	switch (q.format()) {
	case 1:
	case 24:
	case 28:
		return 1;
	case 13:
	case 29:
		return 3;
	default:
		return 4;
	}
	return -1;
}

int KPImage::getBitDepth() {
	// TODO bit depth from qimage
	return q.depth()/this->getNumChannels();
}


bool KPImage::saveToDisk(const string name) {
	// TODO write save function
	cout << name << endl;
	return q.save(QString(name.c_str()));
}

