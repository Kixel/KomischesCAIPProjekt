#include "KomischesCAIPProjekt.h"

KomischesCAIPProjekt::KomischesCAIPProjekt(QWidget* parent)
	: QMainWindow(parent), activeM(-1), M(), V(), B(), viewmapper(this), buttonmapper(this), doBenchmark(true),
	  links(""), rechts("\u23f1\ufe0f") {
	ui.setupUi(this);
	connect(&viewmapper, SIGNAL(mapped(int)), this, SLOT(windowactivated(int)));
	cout << "viewmapper setup" << endl;
	connect(&buttonmapper, SIGNAL(mapped(int)), this, SLOT(selectorclicked(int)));
	cout << "buttonmapper setup" << endl;
	Tools::magnifiq = new KPMagnifier();
	ui.statusBar->addPermanentWidget(&links, 1);
	ui.statusBar->addPermanentWidget(ui.tempLabel, 0);
	ui.statusBar->addPermanentWidget(&rechts, 0);
	connect(ui.statusBar, SIGNAL(messageChanged(QString)), this, SLOT(showTimerTip(QString)));

}

void KomischesCAIPProjekt::changeImage(int ID, KPImage* im) {
	B[ID]->setImage(im);
	V[ID]->setImage(im, ID);
	V[ID]->fitToCurrent();
}

void KomischesCAIPProjekt::addImage(int ID, KPImage* im) {
	KPImageView* kpv = new KPImageView();
	KPImageSelector* kps = new KPImageSelector(ID, im);
	string tip(to_string(ID));
	tip += ": ";
	tip += im->getName();
	kps->setToolTip(QString(tip.c_str()));
	//ui.Selections.addWidget(kps);
	ui.TESTGRID->addWidget(kps);
	kpv->setImage(im, ID);
	//kpv->hide();
	kpv->fitToCurrent();
	//connect(kps, SIGNAL(clicked()), selectorclicked(kps));
	//connect(kpv, SIGNAL(windowactivated(int)), this, SLOT(windowactivated(kpv)));

	viewmapper.setMapping(kpv, kpv->getID());
	connect(kpv, SIGNAL(windowactivated(int)), this, SLOT(windowactivated(int)));

	buttonmapper.setMapping(kps, kps->getID());
	connect(kps, SIGNAL(leftclick(int)), this, SLOT(selectorclicked(int)));
	connect(kps, SIGNAL(rightclick(int)), this, SLOT(selectorRclicked(int)));
	//connect(kps, SIGNAL(middleclick(int)), this, SLOT(selectorMclicked(int)));
	connect(kps, SIGNAL(mouseHovering()), this, SLOT(selectorHovered()));


	connect(kpv, SIGNAL(closethis(int)), this, SLOT(inviewerclose(int)));

	V[ID] = kpv;
	B[ID] = kps;
	disenableItems();
	this->activeM = ID;
	changeActiveButton(ID);
}

void KomischesCAIPProjekt::removeImage(int ID) {
	cout << 1;
	V[ID]->close();
	cout << 2;
	delete V[ID];
	cout << 3;
	delete B[ID];
	cout << 4;
	V.erase(ID);
	cout << 5;
	B.erase(ID);
	cout << 6;
	M.deleteImage(ID);
	cout << 7;
	if(V.size() > 0) windowactivated(begin(V)->first);
	cout << 8;
	disenableItems();
	cout << 9;
}

void KomischesCAIPProjekt::disenableItems() {
	bool t = V.size() > 0;
	ui.actionSave_Active->setEnabled(t);
	ui.actionClose_Active->setEnabled(t);
	ui.actionClose_All_Images->setEnabled(t);
	ui.menuOperations->setEnabled(t);
	//ui.actionMagnifier->setEnabled(t);
}

void KomischesCAIPProjekt::changeActiveButton(int n) {
	vector<int> temp;
	temp.reserve(V.size());
	for (auto i = begin(V); i != end(V); ++i) {
		temp.push_back(i->first);
	}
	for (auto i = 0; i < temp.size(); i++) {
		B[temp[i]]->setActive(temp[i] == this->activeM);
	}
}

bool KomischesCAIPProjekt::notgray() {
	QMessageBox::StandardButton qb = QMessageBox::question(this, QString("Only grayscale supported!"), QString("Only grayscale images are supported for this operation. Do you want to convert the current image to grayscale and continue?"));
	if (qb == QMessageBox::StandardButton::Yes) {
		KPImage* r = ImProc::convert2Gray(M.getImage(activeM), nullptr);
		int nid = M.addImage(r, r->getName());
		this->activeM = nid;
		this->addImage(nid, r);
		changeActiveButton(this->activeM);
		return true;
	} else {
		return false;
	}
}

void KomischesCAIPProjekt::selectorclicked(int n) {
	cout << "Selector " << n << " clicked" << endl;
	this->activeM = n;
	changeActiveButton(n);
}

void KomischesCAIPProjekt::selectorMclicked(int n) {
	removeImage(n);
}

void KomischesCAIPProjekt::selectorRclicked(int n) {
	selectorclicked(n);
	if (!V[n]->isVisible()) V[n]->show();
	V[n]->activateWindow();
	V[n]->fitToCurrent();
}

void KomischesCAIPProjekt::selectorHovered() {
	links.setText("LClick: Activate, RClick: View");
}

void KomischesCAIPProjekt::showTimerTip(QString t) {
	QString a = QString(": ") + t;
	rechts.setText(a);
}

void KomischesCAIPProjekt::windowactivated(int view) {
	cout << "Window " << view << " activated" << endl;
	this->activeM = view;
	changeActiveButton(view);
}

void KomischesCAIPProjekt::on_actionOpen_triggered() {
	string a = string("Images (") + Tools::readableformats + string(")");
	cout << a << endl;
	QStringList qs = QFileDialog::getOpenFileNames(this, tr("Open File"), QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).last(), tr(a.c_str()));
	Tools::startBenchmark(doBenchmark);
	for (int i1 = 0; i1 < qs.size(); i1++) {

		cout << qs.at(i1).toStdString() << endl;
		this->activeM = M.loadImage(qs.at(i1).toStdString());


		this->addImage(this->activeM, M.getImage(this->activeM));
		//V[this->activeM]->show();
		V[this->activeM]->fitToCurrent();
	}
	Tools::endBenchmark(doBenchmark, ui.statusBar);
}

void KomischesCAIPProjekt::on_actionSave_Active_triggered() {
	if (M.isEmpty()) return;
	string a = string("Images (") + Tools::writeableformats + string(")");
	QString path = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).last();
	string oldpath = M.getImage(this->activeM)->getName();
	if (Tools::PathValid(oldpath)) path = QString(oldpath.c_str());
	QString qs = QFileDialog::getSaveFileName(this, tr("Save File"), path, tr(a.c_str()));
	Tools::startBenchmark(doBenchmark);
	M.getImage(this->activeM)->saveToDisk(qs.toStdString());
	Tools::endBenchmark(doBenchmark, ui.statusBar);
}

void KomischesCAIPProjekt::on_actionGray_Gradient_fast_triggered() {
	KPDSampleImage sam(string("Gray-Gradient fast"), true, true, false, false, this);
	if(sam.exec() == 1) {
		Tools::startBenchmark(doBenchmark);
		this->activeM = M.addImage(ImProc::create_Gradientfast(sam.getWidth(), sam.getHeight(), !sam.getDirection(), sam.getInvert()), "Gray-gradient fast");
		Tools::endBenchmark(doBenchmark, ui.statusBar);
		this->addImage(this->activeM, M.getImage(this->activeM));
		V[this->activeM]->show();
		V[this->activeM]->fitToCurrent();
	}
}

void KomischesCAIPProjekt::on_actionGray_Gradient_slow_triggered() {
	KPDSampleImage sam(string("Gray-Gradient slow"), true, true, false, false, this);
	if (sam.exec() == 1) {
		Tools::startBenchmark(doBenchmark);
		this->activeM = M.addImage(ImProc::create_Gradientslow(sam.getWidth(), sam.getHeight(), !sam.getDirection(), sam.getInvert()), "Gray-gradient slow");
		Tools::endBenchmark(doBenchmark, ui.statusBar);
		this->addImage(this->activeM, M.getImage(this->activeM));
		V[this->activeM]->show();
		V[this->activeM]->fitToCurrent();
	}
}

void KomischesCAIPProjekt::on_actionColor_Noise_triggered() {
	KPDSampleImage sam(string("Colored noise"), false, false, false, false, this);
	if (sam.exec() == 1) {
		Tools::startBenchmark(doBenchmark);
		this->activeM = M.addImage(ImProc::create_Colornoise(sam.getWidth(), sam.getHeight()), "Colored noise");
		Tools::endBenchmark(doBenchmark, ui.statusBar);
		this->addImage(this->activeM, M.getImage(this->activeM));
		V[this->activeM]->show();
		V[this->activeM]->fitToCurrent();
	}
}

void KomischesCAIPProjekt::on_actionGray_Noise_triggered() {
	KPDSampleImage sam(string("Gray noise"), false, false, false, false, this);
	if (sam.exec() == 1) {
		Tools::startBenchmark(doBenchmark);
		this->activeM = M.addImage(ImProc::create_Graynoise(sam.getWidth(), sam.getHeight()), "Gray noise");
		Tools::endBenchmark(doBenchmark, ui.statusBar);
		this->addImage(this->activeM, M.getImage(this->activeM));
		V[this->activeM]->show();
		V[this->activeM]->fitToCurrent();
	}
}

void KomischesCAIPProjekt::on_actionColor_Perlin_triggered() {
	KPDSampleImage sam(string("Colored perlin noise"), false, false, true, true, this);
	if (sam.exec() == 1) {
		Tools::startBenchmark(doBenchmark);
		string n = string("Colored perlin noise, Seed: ") + to_string(sam.getSeed());
		this->activeM = M.addImage(ImProc::create_Colorperlin(sam.getWidth(), sam.getHeight(), sam.getSeed(), sam.getZoom()), n);
		Tools::endBenchmark(doBenchmark, ui.statusBar);
		this->addImage(this->activeM, M.getImage(this->activeM));
		V[this->activeM]->show();
		V[this->activeM]->fitToCurrent();
	}
}

void KomischesCAIPProjekt::on_actionGray_Perlin_triggered() {
	KPDSampleImage sam(string("Gray perlin noise"), false, false, true, true, this);
	if (sam.exec() == 1) {
		Tools::startBenchmark(doBenchmark);
		string n = string("Gray perlin noise, Seed: ") + to_string(sam.getSeed());
		this->activeM = M.addImage(ImProc::create_Grayperlin(sam.getWidth(), sam.getHeight(), sam.getSeed(), sam.getZoom()), n);
		Tools::endBenchmark(doBenchmark, ui.statusBar);
		this->addImage(this->activeM, M.getImage(this->activeM));
		V[this->activeM]->show();
		V[this->activeM]->fitToCurrent();
	}
}

void KomischesCAIPProjekt::on_actionClose_Active_triggered() {
	removeImage(activeM);
}

void KomischesCAIPProjekt::on_actionClose_All_Images_triggered() {
	vector<int> temp;
	temp.reserve(V.size());
	for (auto i = begin(V); i != end(V); ++i) {
		temp.push_back(i->first);
	}
	cout << "Removing " << temp.size() << " elements" << endl;
	for (auto i = 0; i < temp.size(); i++) {
		removeImage(temp[i]);
	}
}

void KomischesCAIPProjekt::on_actionQuit_triggered() {
	if (M.isEmpty()) {
		QApplication::quit();
	} else {
		QMessageBox::StandardButton a = QMessageBox::question(this, QString("Really exit?"), QString("Do you really want to exit the program? There are open images!"));
		if(a == QMessageBox::StandardButton::Yes) QApplication::quit();
	}
}

void KomischesCAIPProjekt::closeEvent(QCloseEvent* event) {
	on_actionQuit_triggered();
	event->ignore();
}

void KomischesCAIPProjekt::on_actionShow_Histogram_triggered() {
	// TODO add histogramm function
}

void KomischesCAIPProjekt::on_actionInvert_triggered() {
	KPProcessingWindow* proc = new KPProcessingWindow(ImProc::invert, M.getImage(activeM), this);
	proc->setup("Invert image", false, false, false, false, false, false, false);
	proc->show();
	proc->fitToCurrent();
	connect(proc, SIGNAL(finished(KPProcessingWindow*)), this, SLOT(improcesserclose(KPProcessingWindow*)));
}

void KomischesCAIPProjekt::on_actionCrop_triggered() {
	KPProcessingWindow* proc = new KPProcessingWindow(ImProc::crop, M.getImage(activeM), this);
	proc->setup("Crop image", false, true, true, false, false, false, false);
	int w = M.getImage(activeM)->getWidth();
	int h = M.getImage(activeM)->getHeight();
	proc->setupSpinner12("First X-coordinate", 0, 0, w-1, "First Y-coordinate", 0, 0, h-1);
	proc->setupSpinner34("Second X-coordinate", w-1, 0, w-1, "Second Y-coordinate", h-1, 0, h-1);
	proc->show();
	proc->fitToCurrent();
	connect(proc, SIGNAL(finished(KPProcessingWindow*)), this, SLOT(improcesserclose(KPProcessingWindow*)));
}

void KomischesCAIPProjekt::on_actionResize_triggered() {
	KPProcessingWindow* proc = new KPProcessingWindow(ImProc::resize, M.getImage(activeM), this);
	proc->setup("Resize image", true, true, false, false, false, false, false);
	int w = M.getImage(activeM)->getWidth();
	int h = M.getImage(activeM)->getHeight();
	proc->setupLabels(to_string(w), to_string(h));
	proc->setupSpinner12("New width", w/2, 1, 32000, "New height", h/2, 1, 32000);

	proc->show();
	proc->fitToCurrent();
	connect(proc, SIGNAL(finished(KPProcessingWindow*)), this, SLOT(improcesserclose(KPProcessingWindow*)));
}

void KomischesCAIPProjekt::on_actionRotate_triggered() {
	KPProcessingWindow* proc = new KPProcessingWindow(ImProc::rotate, M.getImage(activeM), this, true);
	proc->setup("Rotate image", false, false, false, true, false, false, false);
	proc->setupDouble("Angle", 0, 0, 360);
	proc->show();
	proc->fitToCurrent();
	connect(proc, SIGNAL(finished(KPProcessingWindow*)), this, SLOT(improcesserclose(KPProcessingWindow*)));
}

void KomischesCAIPProjekt::on_actionConvert_to_Grayscale_triggered() {
	KPProcessingWindow* proc = new KPProcessingWindow(ImProc::convert2Gray, M.getImage(activeM), this);
	proc->setup("Convert to grayscale", false, false, false, false, false, false, false);
	proc->show();
	proc->fitToCurrent();
	connect(proc, SIGNAL(finished(KPProcessingWindow*)), this, SLOT(improcesserclose(KPProcessingWindow*)));
}

void KomischesCAIPProjekt::on_actionGammacorrection_triggered() {
	KPProcessingWindow* proc = new KPProcessingWindow(ImProc::gamma, M.getImage(activeM), this, true);
	proc->setup("Gamma correction", false, false, false, true, false, false, false);
	proc->setDoublePrecision(0.05);
	proc->setupDouble("Gamma", 1, 0, 100);
	proc->show();
	proc->fitToCurrent();
	connect(proc, SIGNAL(finished(KPProcessingWindow*)), this, SLOT(improcesserclose(KPProcessingWindow*)));

}

void KomischesCAIPProjekt::on_actionContrastcorrection_triggered() {
	if (!M.getImage(this->activeM)->getQ().isGrayscale()) {
		if (!notgray()) return;
	}
	KPProcessingWindow* proc = new KPProcessingWindow(ImProc::contrast, M.getImage(activeM), this, true);
	proc->setup("Contrast correction", false, true, false, false, false, false, false);
	proc->setupSpinner12("Minimum grayvalue", 0, 0, 255, "Maximum grayvalue", 255, 0, 255);
	proc->show();
	proc->fitToCurrent();
	connect(proc, SIGNAL(finished(KPProcessingWindow*)), this, SLOT(improcesserclose(KPProcessingWindow*)));
}

void KomischesCAIPProjekt::on_actionBinarise_triggered() {
	if (!M.getImage(this->activeM)->getQ().isGrayscale()) {
		if (!notgray()) return;
	}
	KPProcessingWindow* proc = new KPProcessingWindow(ImProc::binarise, M.getImage(activeM), this);
	proc->setup("Binarise", false, false, false, false, false, true, false);
	int ot = ImProc::otsu(M.getImage(activeM));
	cout << "otsu" << ot << endl;
	proc->setupSlider1(string("Threshold (default:") + to_string(ot) + ")", ot);
	proc->show();
	proc->fitToCurrent();
	connect(proc, SIGNAL(finished(KPProcessingWindow*)), this, SLOT(improcesserclose(KPProcessingWindow*)));
}

void KomischesCAIPProjekt::on_actionBinarise_range_triggered() {
	if (!M.getImage(this->activeM)->getQ().isGrayscale()) {
		if (!notgray()) return;
	}
	KPProcessingWindow* proc = new KPProcessingWindow(ImProc::binarise2, M.getImage(activeM), this);
	proc->setup("Binarise with 2 thresholds", false, false, false, false, false, true, true);
	int ot = ImProc::otsu(M.getImage(activeM));
	proc->setupSlider1(string("Threshold (default:") + to_string(ot) + ")", ot);
	proc->setupSlider2(string("Threshold (default:255)"), 255);
	proc->show();
	proc->fitToCurrent();
	connect(proc, SIGNAL(finished(KPProcessingWindow*)), this, SLOT(improcesserclose(KPProcessingWindow*)));
}

void KomischesCAIPProjekt::on_actionAdaptive_Binarise_triggered() {
	if (!M.getImage(this->activeM)->getQ().isGrayscale()) {
		if (!notgray()) return;
	}
	KPProcessingWindow* proc = new KPProcessingWindow(ImProc::adaptthresh, M.getImage(activeM), this);
	proc->setup("Adaptive binarise", false, false, false, true, true, false, false, true);
	proc->setupDouble("Threshold modifier", 10, -10, 50);
	proc->setupSpinner5("Block radius", 7, 1, 251);
	proc->show();
	proc->fitToCurrent();
	connect(proc, SIGNAL(finished(KPProcessingWindow*)), this, SLOT(improcesserclose(KPProcessingWindow*)));
}

void KomischesCAIPProjekt::on_actionMean_triggered() {
	// TODO mean filter
}

void KomischesCAIPProjekt::on_actionMedian_triggered() {
	// TODO median filter
}

void KomischesCAIPProjekt::on_actionGauss_triggered() {
	// TODO gauss filter
}

void KomischesCAIPProjekt::on_actionEdge_triggered() {
	// TODO edge filter
}

void KomischesCAIPProjekt::on_actionRandom_triggered() {
	// TODO random filter
}

void KomischesCAIPProjekt::on_actionCustom_triggered() {
	// TODO custom filter
}

void KomischesCAIPProjekt::on_actionErode_triggered() {
	if (!M.getImage(this->activeM)->getQ().isGrayscale()) {
		if (!notgray()) return;
	}
	KPProcessingWindow* proc = new KPProcessingWindow(ImProc::erode, M.getImage(activeM), this);
	proc->setup("Erosion", false, true, false, false, true, false, false, false, true);
	proc->setupSpinner12("Structure element width", 3, 1, 75, "Structure element height", 3, 1, 75);
	proc->setupSpinner5("Iterations", 1, 1, 10);
	proc->show();
	proc->fitToCurrent();
	connect(proc, SIGNAL(finished(KPProcessingWindow*)), this, SLOT(improcesserclose(KPProcessingWindow*)));
}

void KomischesCAIPProjekt::on_actionOpen_2_triggered() {
	if (!M.getImage(this->activeM)->getQ().isGrayscale()) {
		if (!notgray()) return;
	}
	KPProcessingWindow* proc = new KPProcessingWindow(ImProc::open, M.getImage(activeM), this);
	proc->setup("Opening", false, true, false, false, true, false, false, false, true);
	proc->setupSpinner12("Structure element width", 3, 1, 75, "Structure element height", 3, 1, 75);
	proc->setupSpinner5("Iterations", 1, 1, 10);
	proc->show();
	proc->fitToCurrent();
	connect(proc, SIGNAL(finished(KPProcessingWindow*)), this, SLOT(improcesserclose(KPProcessingWindow*)));
}

void KomischesCAIPProjekt::on_actionDilate_triggered() {
	if (!M.getImage(this->activeM)->getQ().isGrayscale()) {
		if (!notgray()) return;
	}
	KPProcessingWindow* proc = new KPProcessingWindow(ImProc::dilate, M.getImage(activeM), this);
	proc->setup("Dilation", false, true, false, false, true, false, false, false, true);
	proc->setupSpinner12("Structure element width", 3, 1, 75, "Structure element height", 3, 1, 75);
	proc->setupSpinner5("Iterations", 1, 1, 10);
	proc->show();
	proc->fitToCurrent();
	connect(proc, SIGNAL(finished(KPProcessingWindow*)), this, SLOT(improcesserclose(KPProcessingWindow*)));
}

void KomischesCAIPProjekt::on_actionClose_triggered() {
	if (!M.getImage(this->activeM)->getQ().isGrayscale()) {
		if (!notgray()) return;
	}
	KPProcessingWindow* proc = new KPProcessingWindow(ImProc::close, M.getImage(activeM), this);
	proc->setup("Closing", false, true, false, false, true, false, false, false, true);
	proc->setupSpinner12("Structure element width", 3, 1, 75, "Structure element height", 3, 1, 75);
	proc->setupSpinner5("Iterations", 1, 1, 10);
	proc->show();
	proc->fitToCurrent();
	connect(proc, SIGNAL(finished(KPProcessingWindow*)), this, SLOT(improcesserclose(KPProcessingWindow*)));
}

void KomischesCAIPProjekt::on_actionGradient_triggered() {
	if (!M.getImage(this->activeM)->getQ().isGrayscale()) {
		if (!notgray()) return;
	}
	KPProcessingWindow* proc = new KPProcessingWindow(ImProc::morphgradient, M.getImage(activeM), this);
	proc->setup("Gradient", false, true, false, false, true, false, false, false, true);
	proc->setupSpinner12("Structure element width", 3, 1, 75, "Structure element height", 3, 1, 75);
	proc->setupSpinner5("Iterations", 1, 1, 10);
	proc->show();
	proc->fitToCurrent();
	connect(proc, SIGNAL(finished(KPProcessingWindow*)), this, SLOT(improcesserclose(KPProcessingWindow*)));
}

void KomischesCAIPProjekt::on_actionBenchmark_triggered() {
	this->doBenchmark = ui.actionBenchmark->isChecked();
}

void KomischesCAIPProjekt::on_actionMagnifier_triggered() {
	Tools::magnifiq->show();
}

void KomischesCAIPProjekt::inviewerclose(int id) {
	removeImage(id);
}

void KomischesCAIPProjekt::improcesserclose(KPProcessingWindow* k) {
	cout << "Call received!" << endl;
	k->hide();
	if (k->getState() > 0) {
		Tools::startBenchmark(doBenchmark);
		KPImage* r = k->getResult();
		Tools::endBenchmark(doBenchmark, ui.statusBar);
		if (k->copyToNew()) {
			int nid = M.addImage(r, r->getName());
			this->activeM = nid;
			this->addImage(nid, r);
		} else {
			M.replaceImage(this->activeM, r);
			this->changeImage(this->activeM, r);
		}
	}
	delete k;
}
