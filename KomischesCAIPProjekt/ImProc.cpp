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


KPImage* ImProc::filter(KPImage* O, Mat mask, int maskcenterx, int maskcentery, int outofbounds) {
	return nullptr;
}

vector<int>* ImProc::grayhisto(KPImage* O) {
	vector<int>* out = new vector<int>(256, 0);
	for (int x = 0; x < O->getWidth(); x++) {
		for (int y = 0; y < O->getHeight(); y++) {
			out->at(qGray(O->getQ().pixel(x, y)))++;
		}
	}
	return out;
}

KPImage* ImProc::convert2Gray(KPImage* O, KPProcessingWindow* kpp) {
	KPImage* R = new KPImage();
	R->getQ() = O->getQ().convertToFormat(QImage::Format::Format_Grayscale8);
	R->setName(O->getName() + string(" gray"));
	return R;
}

KPImage* ImProc::rotate(KPImage* O, KPProcessingWindow* kpp) {
	
	//double angle = kpp->getDouble1();
	/*Mat src(O->getM());
	//cout << src.type() << endl;

	Point2f center((src.cols - 1) / 2.0, (src.rows - 1) / 2.0);
	cout << center.x << "|" << center.y << endl;
	Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);
	Rect2f bbox = cv::RotatedRect(cv::Point2f(), src.size(), angle).boundingRect2f();
	rot.at<double>(0, 2) += bbox.width / 2.0 - src.cols / 2.0;
	rot.at<double>(1, 2) += bbox.height / 2.0 - src.rows / 2.0;
	
	Mat* dst = new Mat(src.rows, src.cols, src.type());
	cout << dst->type() << endl;
	warpAffine(src, *dst, rot, bbox.size()); // one problem
	KPImage* R = new KPImage(dst);*/
	//R->setName(O->getName() + string(" rotated: ") + to_string(angle));*/
	//imshow("", *dst); 
	QTransform tm;
	tm.rotate(kpp->getDouble1());
	KPImage* R = new KPImage(O->getQ().transformed(tm));
	R->setName(O->getName() + string(" rotated: ") + to_string(kpp->getDouble1()));
	return R;
}

KPImage* ImProc::resize(KPImage* O, KPProcessingWindow* kpp) {
	KPImage* R = new KPImage(O->getQ().scaled(kpp->getInt1(), kpp->getInt2()));
	R->setName(O->getName() + string(" resized: ") + to_string(kpp->getInt1()) + string("x") + to_string(kpp->getInt2()));
	return R;
}

KPImage* ImProc::erode(KPImage* O, KPProcessingWindow* kpp) {
	Mat* out = new Mat();
	Mat in = O->getM();
	
	//needed elements:
	/*
	kernel:
		shape (int->combobox)
		Size (int/int->2spinner) exists
	iterations (int->spinner) exists
	bordertype (int->combobox)
	*/
	int shape = kpp->getShape();
	int size1 = kpp->getInt1();
	int size2 = kpp->getInt2();
	int iterations = kpp->getInt5();
	int bordert = kpp->getBordertype();
	int borderv = kpp->getBordervalue();
	morphologyEx(in, *out, MORPH_ERODE, getStructuringElement(shape, Size(size1, size2)), Point(-1, -1), iterations, bordert, borderv);
	KPImage* R = new KPImage(out);
	R->setName(O->getName() + string(" eroded"));
	return R;
}

KPImage* ImProc::dilate(KPImage* O, KPProcessingWindow* kpp) {
	Mat* out = new Mat();
	Mat in = O->getM();

	//needed elements:
	/*
	kernel:
		shape (int->combobox)
		Size (int/int->2spinner) exists
	iterations (int->spinner) exists
	bordertype (int->combobox)
	*/
	int shape = kpp->getShape();
	int size1 = kpp->getInt1();
	int size2 = kpp->getInt2();
	int iterations = kpp->getInt5();
	int bordert = kpp->getBordertype();
	int borderv = kpp->getBordervalue();
	morphologyEx(in, *out, MORPH_DILATE, getStructuringElement(shape, Size(size1, size2)), Point(-1, -1), iterations, bordert, borderv);
	KPImage* R = new KPImage(out);
	R->setName(O->getName() + string(" dilated"));
	return R;
}

KPImage* ImProc::open(KPImage* O, KPProcessingWindow* kpp) {
	Mat* out = new Mat();
	Mat in = O->getM();

	//needed elements:
	/*
	kernel:
		shape (int->combobox)
		Size (int/int->2spinner) exists
	iterations (int->spinner) exists
	bordertype (int->combobox)
	*/
	int shape = kpp->getShape();
	int size1 = kpp->getInt1();
	int size2 = kpp->getInt2();
	int iterations = kpp->getInt5();
	int bordert = kpp->getBordertype();
	int borderv = kpp->getBordervalue();
	morphologyEx(in, *out, MORPH_OPEN, getStructuringElement(shape, Size(size1, size2)), Point(-1, -1), iterations, bordert, borderv);
	KPImage* R = new KPImage(out);
	R->setName(O->getName() + string(" opened"));
	return R;
}

KPImage* ImProc::close(KPImage* O, KPProcessingWindow* kpp) {
	Mat* out = new Mat();
	Mat in = O->getM();

	//needed elements:
	/*
	kernel:
		shape (int->combobox)
		Size (int/int->2spinner) exists
	iterations (int->spinner) exists
	bordertype (int->combobox)
	*/
	int shape = kpp->getShape();
	int size1 = kpp->getInt1();
	int size2 = kpp->getInt2();
	int iterations = kpp->getInt5();
	int bordert = kpp->getBordertype();
	int borderv = kpp->getBordervalue();
	morphologyEx(in, *out, MORPH_CLOSE, getStructuringElement(shape, Size(size1, size2)), Point(-1, -1), iterations, bordert, borderv);
	KPImage* R = new KPImage(out);
	R->setName(O->getName() + string(" closed"));
	return R;
}

KPImage* ImProc::morphgradient(KPImage* O, KPProcessingWindow* kpp) {
	Mat* out = new Mat();
	Mat in = O->getM();

	//needed elements:
	/*
	kernel:
		shape (int->combobox)
		Size (int/int->2spinner) exists
	iterations (int->spinner) exists
	bordertype (int->combobox)
	*/
	int shape = kpp->getShape();
	int size1 = kpp->getInt1();
	int size2 = kpp->getInt2();
	int iterations = kpp->getInt5();
	int bordert = kpp->getBordertype();
	int borderv = kpp->getBordervalue();
	morphologyEx(in, *out, MORPH_GRADIENT, getStructuringElement(shape, Size(size1, size2)), Point(-1, -1), iterations, bordert, borderv);
	KPImage* R = new KPImage(out);
	R->setName(O->getName() + string(" gradient"));
	return R;
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

KPImage* ImProc::create_Colorperlin(int w, int h, unsigned int seed, double zoomfactor) {
	KPImage* n = new KPImage(w, h, 13); //Format RGB888
	QImage& q = n->getQ();

	PerlinNoise p(seed);

	for (int row = 0; row < h; row++) {
		for (int col = 0; col < w; col++) {
			double x = ((double)col / (double)(w - 1)) / zoomfactor;
			double y = ((double)row / (double)(h - 1)) / zoomfactor;
			uchar r = (uchar)floor(p.noise(x, y, 0.5) * 255);
			uchar g = (uchar)floor(p.noise(x, 0.5, y) * 255);
			uchar b = (uchar)floor(p.noise(0.5, x, y) * 255);
			q.setPixelColor(col, row, qRgb(r, g, b));
		}
	}
	return n;
}

KPImage* ImProc::create_Grayperlin(int w, int h, unsigned int seed, double zoomfactor) {
	KPImage* n = new KPImage(w, h, 24); //Format Grayscale8
	QImage& q = n->getQ();
	PerlinNoise p(seed);

	for (int i = 0; i < h; i++) {
		uchar* t = q.scanLine(i);
		for (int j = 0; j < w; j++) {
			double x = ((double)j / (double)(w - 1)) / zoomfactor;
			double y = ((double)i / (double)(h - 1)) / zoomfactor;
			t[j] = (uchar)floor(p.noise(x, y, 0.1) * 255);
		}
	}
	return n;
}

int ImProc::otsu(KPImage* im) {
	// TODO otsu
	long int totalpixels = im->getWidth() * im->getHeight();
	vector<int> histogramI = *ImProc::grayhisto(im);
	//Making mean tables
	int K = histogramI.size();
	double n0 = 0, s0 = 0;
	vector<double> my0, my1;
	for (int i = 0; i < K; i++) {
		my0.push_back(0.0);
		my1.push_back(0.0);
	}
	for (int q = 0; q < K - 1; q++) {
		n0 += histogramI[q];
		s0 += q * histogramI[q];
		if (n0 > 0) { 
			my0[q] = s0 / n0; 
		} else {
			my0[q] = -1;
		}
	}
	double N = n0;
	double n1 = 0;
	double s1 = 0;
	my1[K - 1] = 0;
	for (int q = K - 2; q >= 0; q--) {
		n1 += histogramI[q + 1];
		s1 += (q + 1) * histogramI[q + 1];
		if (n1 > 0) {
			my1[q] = s1 / n1;
		} else {
			my1[q] = -1;
		}
	}
	//Generating otsu
	double o2bmax = 0;
	double qmax = -1;
	n0 = 0;
	double MN = N;
	for (int q = 0; q <= K - 2; q++) {
		n0 += histogramI[q];
		n1 = MN - n0;
		if ((n0 > 0) && (n1 > 0)) {
			double o2b = (1 / pow(MN, 2)) * n0 * n1 * pow((my0[q] - my1[q]), 2);
			if (o2b > o2bmax) {
				o2bmax = o2b;
				qmax = q;
			}
		}
	}
	cout << "qmax" << qmax << endl;
	return qmax;
}

KPImage* ImProc::invert(KPImage* O, KPProcessingWindow* kpp) {
	KPImage* R = new KPImage(*O);
	R->getQ().invertPixels();
	R->setName(O->getName() + string(" inverted"));
	return R;
}

KPImage* ImProc::crop(KPImage* O, KPProcessingWindow* kpp) {
	KPImage* R = new KPImage(*O);
	int wi = abs(kpp->getInt3() - kpp->getInt1());
	int hi = abs(kpp->getInt4() - kpp->getInt2());
	int x = min(kpp->getInt3(), kpp->getInt1());
	int y = min(kpp->getInt4(), kpp->getInt2());
	R->getQ() = R->getQ().copy(x, y, wi, hi);
	R->setName(O->getName() + string(" cropped"));
	return R;
}

KPImage* ImProc::gamma(KPImage* O, KPProcessingWindow* kpp) {
	vector<int> precalc(256, 0);
	for (int i = 0; i < 256; i++) {
		precalc[i] = pow((double)i / 255.0, kpp->getDouble1()) * 255.0;
	}


	KPImage* R = new KPImage(*O);
	for (int row = 0; row < O->getHeight(); row++) {
		for (int col = 0; col < O->getWidth(); col++) {
			QColor qc;
			if (O->getQ().format() == QImage::Format_RGB888) {
				int nvr = precalc[O->getQ().pixelColor(col, row).red()];
				int nvg = precalc[O->getQ().pixelColor(col, row).green()];
				int nvb = precalc[O->getQ().pixelColor(col, row).blue()];
				qc = QColor(nvr, nvg, nvb);
				//cout << qc.value() << endl;
			} else if (O->getQ().format() == QImage::Format_Grayscale8) {
				int nvr = precalc[qGray(O->getQ().pixelColor(col, row).rgb())];
				qc = QColor(nvr, nvr, nvr);
			} else if (O->getQ().format() == QImage::Format_Mono) return R;
			R->getQ().setPixelColor(col, row, qc);
		}
	}
	R->setName(O->getName() + string(" gamma: ") + to_string(kpp->getDouble1()));
	return R;
}

KPImage* ImProc::contrast(KPImage* O, KPProcessingWindow* kpp) {
	vector<int> precalc(256, 0);
	//precalc.reserve(256);
	double minv = 255;
	double maxv = 0;
	for (int i = 0; i < O->getHeight(); i++) {
		for (int j = 0; j < O->getWidth(); j++) {
			int g = qGray(O->getQ().pixelColor(j, i).rgb());
			if (g < minv) minv = g;
			if (g > maxv) maxv = g;
		}
	}
	double nmax = max(kpp->getInt1(), kpp->getInt2());
	double nmin = min(kpp->getInt1(), kpp->getInt2());
	for (int i = 0; i < 256; i++) {
		precalc[i] = nmin + (i - minv) * ((nmax-nmin) / (maxv - minv));
		//cout << precalc[i] << endl;
	}


	KPImage* R = new KPImage(*O);
	for (int row = 0; row < O->getHeight(); row++) {
		for (int col = 0; col < O->getWidth(); col++) {
			QColor qc;
			if (O->getQ().format() == QImage::Format_Grayscale8) {
				int nvr = precalc[qGray(O->getQ().pixelColor(col, row).rgb())];
				qc = QColor(nvr, nvr, nvr);
			} else return R;
			R->getQ().setPixelColor(col, row, qc);
		}
	}
	R->setName(O->getName() + string(" contrast: ") + to_string(nmin) + string("->") + to_string(nmax));
	return R;
}

KPImage* ImProc::binarise(KPImage* O, KPProcessingWindow* kpp) {
	KPImage* R = new KPImage(O->getWidth(), O->getHeight(), 1); // Format mono
	for (int row = 0; row < O->getHeight(); row++) {
		uchar* t = O->getQ().scanLine(row);
		//bool* r = R->getQ().scanLine(row);
		for (int col = 0; col < O->getWidth(); col++) {
			R->getQ().setPixel(col, row, t[col] > kpp->getSlider1());
		}
	}
	R->setName(O->getName() + string(" binarised: ") + to_string(kpp->getSlider1()));
	return R;
}

KPImage* ImProc::binarise2(KPImage* O, KPProcessingWindow* kpp) {
	KPImage* R = new KPImage(O->getWidth(), O->getHeight(), 1); // Format mono
	int lower = min(kpp->getSlider1(), kpp->getSlider2());
	int higher = max(kpp->getSlider1(), kpp->getSlider2());
	for (int row = 0; row < O->getHeight(); row++) {
		uchar* t = O->getQ().scanLine(row);
		//bool* r = R->getQ().scanLine(row);
		for (int col = 0; col < O->getWidth(); col++) {
			R->getQ().setPixel(col, row, (t[col] > lower && t[col] < higher));
		}
	}
	R->setName(O->getName() + string(" binarised: ") + to_string(lower) + string("<n<") + to_string(higher));
	return R;
}

KPImage* ImProc::adaptthresh(KPImage* O, KPProcessingWindow* kpp) {
	int masksi = (kpp->getInt5())*2+1;
	Mat* out = new Mat();
	Mat in = O->getM();
	double constan = kpp->getDouble1();
	int meth = kpp->getCombo();

	adaptiveThreshold(in, *out, 255.0, meth, THRESH_BINARY, masksi, constan);

	//adaptiveThreshold(in, *out, 255, method, THRESH_BINARY, masksize, constant);
	KPImage* R = new KPImage(out);
	R->setName(O->getName() + string(" adaptive binarised"));
	return R;
}
