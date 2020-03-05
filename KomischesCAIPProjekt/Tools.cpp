#include "Tools.h"
#include <qimage.h>
#include <opencv2/core/core.hpp>

int Tools::Type_Q2CV(int t) {
	switch (t) {
	case QImage::Format_Indexed8: return 0;
	case QImage::Format_ARGB32: return 24;
	case QImage::Format_RGB888: return 16;
	}
	return 24;
}

int Tools::Type_CV2Q(int t) {
	switch (t) {
	case 0: return QImage::Format_Indexed8;
	case 16: return QImage::Format_RGB888;
	case 24: return QImage::Format_ARGB32;
	}
	return QImage::Format_ARGB32;
}

bool Tools::PathValid(string p) {
	ifstream infi(p.c_str());
	return infi.good();
}

string Tools::readableformats = "*.bmp *.gif *.jpg *.jpeg *.png *.pbm *.pgm *.ppm *.xbm *.xpm";
string Tools::writeableformats = "*.bmp *.jpg *.jpeg *.png *.ppm *.xbm *.xpm";
