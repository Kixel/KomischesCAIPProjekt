#include "ImProc.h"

//KPImage ImProc::gamma(KPImage& O, double gammavalue) {
//	/*double max = 255;
//	KPImage work = KPImage(O.getM().clone());
//	for (int i1 = 0; i1 < work.getM().rows; i1++) {
//		for (int i2 = 0; i2 < work.getM().cols; i2++) {
//			switch (work.getM().type()) {
//			case CV_8UC1:
//			{
//				unsigned char& c = work.getM().at<uchar>(i1, i2);
//				c = (uchar)((pow(((double)c / max), gammavalue)) * max);
//				break;
//			}
//			case CV_8UC3:
//			{
//				Vec3b& a = work.getM().at<Vec3b>(i1, i2);
//				for (int i3 = 0; i3 < 3; i3++) {
//					uchar& b = a.val[i3];
//					b = (uchar)(pow(((double)b / 255.0), gammavalue));
//				}
//				break;
//			}
//			case CV_8UC4:
//
//				break;
//			}
//		}
//	}
//	return work;*/
//	return KPImage();
//}

KPImage* ImProc::invert(KPImage* O) {
	return nullptr;
}

KPImage* ImProc::crop(KPImage* O, int startx, int starty, int endx, int endy) {
	return nullptr;
}

KPImage* ImProc::gamma(KPImage* O, double gammavalue) {
	return nullptr;
}

KPImage* ImProc::contrast(KPImage* O, int startg, int endg) {
	return nullptr;
}

KPImage* ImProc::binarise(KPImage* O, int thresh) {
	return nullptr;
}

KPImage* ImProc::binarise2(KPImage* O, int threshlower, int threshhigher) {
	return nullptr;
}

KPImage* ImProc::adaptthresh(KPImage* O, int range, double correctionvalue) {
	return nullptr;
}

KPImage* ImProc::filter(KPImage* O, Mat mask, int maskcenterx, int maskcentery, int outofbounds) {
	return nullptr;
}

vector<int> ImProc::grayhisto(KPImage* O) {
	return vector<int>();
}

KPImage* ImProc::convert2Gray(KPImage* O) {
	return nullptr;
}

KPImage* ImProc::rotate(KPImage* O, double angle) {
	return nullptr;
}

KPImage* ImProc::resize(KPImage* O, int w, int h, cv::InterpolationFlags) {
	return nullptr;
}

KPImage* ImProc::erode(KPImage* O, Mat structure) {
	return nullptr;
}

KPImage* ImProc::dilate(KPImage* O, Mat structure) {
	return nullptr;
}

KPImage* ImProc::open(KPImage* O, Mat structure) {
	return nullptr;
}

KPImage* ImProc::close(KPImage* O, Mat structure) {
	return nullptr;
}

KPImage* ImProc::create_Gradientfast(int w, int h, bool toptodown, bool invert) {
	KPImage* n = new KPImage(w, h, 24); //Format Grayscale8
	QImage& q = n->getQ();
	if (toptodown) {
		for (int i = 0; i < h; i++) {
			uchar* t = q.scanLine(i);
			uchar cur = (uchar)(((double)i / h) * 255);
			for (int j = 0; j < w; j++) {
				if (invert) {
					t[j] = 255 - cur;
				} else {
					t[j] = cur;
				}
			}
		}
	} else {
		vector<uchar> pre;
		pre.reserve(w);
		for (int i = 0; i < w; i++) {
			pre.push_back((uchar)(((double)i / w) * 255));
		}
		for (int i = 0; i < h; i++) {
			uchar* t = q.scanLine(i);
			for (int j = 0; j < w; j++) {
				if (invert) {
					t[j] = 255 - pre[j];
				} else {
					t[j] = pre[j];
				}
			}
		}
	}
	return n;
}

KPImage* ImProc::create_Gradientslow(int w, int h, bool toptodown, bool invert) {
	KPImage* n = new KPImage(w, h, 24); //Format Grayscale8
	QImage& q = n->getQ();
	if (toptodown) {
		for (int i = 0; i < h; i++) {
			uchar cur = (uchar)(((double)i / h) * 255);
			if (invert) cur = 255 - cur;
			QColor co(cur, cur, cur);
			for (int j = 0; j < w; j++) {
				q.setPixelColor(j, i, co);
			}
		}
	} else {
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				uchar cur = (uchar)(((double)j / w) * 255);
				if (invert) cur = 255 - cur;
				QColor co(cur, cur, cur);
				q.setPixelColor(j, i, co);
			}
		}
	}
	return n;
}

KPImage* ImProc::create_Colornoise(int w, int h) {
	KPImage* n = new KPImage(w, h, 13); //Format RGB888
	QImage& q = n->getQ();
	uchar* dat = q.bits();
	for (auto i = 0; i < q.sizeInBytes(); i++) {
		dat[i] = (uchar)(rand() % 256);
	}
	return n;
}

KPImage* ImProc::create_Graynoise(int w, int h) {
	KPImage* n = new KPImage(w, h, 24); //Format Grayscale_8
	QImage& q = n->getQ();
	uchar* dat = q.bits();
	for (auto i = 0; i < q.sizeInBytes(); i++) {
		dat[i] = (uchar)(rand() % 256);
	}
	return n;
}

KPImage* ImProc::create_Colorperlin(int w, int h, unsigned int seed) {
	KPImage* n = new KPImage(w, h, 13); //Format RGB888
	QImage& q = n->getQ();

	double rlayer = 0.1;
	double glayer = 0.5;
	double blayer = 0.9;

	PerlinNoise p(seed);


	for (int row = 0; row < h; row++) {
		//cout << "row " << row << endl;
		//uchar* line = q.scanLine(row);
		for (int col = 0; col < w; col++) {
			double x = (double)col / (double)(w-1);
			double y = (double)row / (double)(h-1);
			//if (row == h-1) {
			//	cout << "x" << x << "y" << y << endl;
			//}
			//*line = (uchar)255;
			//line++;
			uchar r = (uchar)floor(p.noise(x, y, rlayer) * 255);
			//*line = (uchar)floor(p.noise(x, y, rlayer)*255);
			//line++;
			uchar g = (uchar)floor(p.noise(x, y, glayer) * 255);
			//*line = (uchar)floor(p.noise(x, y, glayer)*255);
			//line++;
			uchar b = (uchar)floor(p.noise(x, y, blayer) * 255);
			//*line = (uchar)floor(p.noise(x, y, blayer)*255);
			//line++;
			q.setPixelColor(col, row, qRgb(r, g, b));
		}
	}
	return n;
}

KPImage* ImProc::create_Grayperlin(int w, int h, unsigned int seed) {
	KPImage* n = new KPImage(w, h, 24); //Format Grayscale8
	QImage& q = n->getQ();
	PerlinNoise p(seed);

	for (int i = 0; i < h; i++) {
		uchar* t = q.scanLine(i);
		for (int j = 0; j < w; j++) {
			t[j] = (uchar)floor(p.noise(j, i, 0.1) * 255);
		}
	}
	return n;
}
