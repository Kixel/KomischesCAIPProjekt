#include "Tools.h"
#include <opencv2/core/core.hpp>

uint64_t Tools::benchstart = 0;
KPMagnifier* Tools::magnifiq = nullptr;

void Tools::updateMagnifier(KPImage* im, int x, int y) {
	if (!Tools::magnifiq->isVisible()) return;
	magnifiq->updateImage(im, x, y);
}

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

unsigned int Tools::GetRandomUint() {
	return rand() % 65536;
}

uint64_t Tools::systemtime() {
	using namespace std::chrono;
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void Tools::startBenchmark(bool doBenchmark) {
	if (!doBenchmark) return;
	Tools::benchstart = Tools::systemtime();
}

void Tools::endBenchmark(bool doBenchmark, QStatusBar* status) {
	if (!doBenchmark) return;
	uint64_t end = Tools::systemtime();
	uint64_t diff = end - Tools::benchstart;
	string a = to_string(diff) + string("ms");
	status->showMessage(QString(a.c_str()));
}

string Tools::readableformats = "*.bmp *.gif *.jpg *.jpeg *.png *.pbm *.pgm *.ppm *.xbm *.xpm";
string Tools::writeableformats = "*.bmp *.jpg *.jpeg *.png *.ppm *.xbm *.xpm";
