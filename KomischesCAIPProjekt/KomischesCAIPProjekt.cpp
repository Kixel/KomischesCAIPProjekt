#include "KomischesCAIPProjekt.h"

KomischesCAIPProjekt::KomischesCAIPProjekt(QWidget* parent)
	: QMainWindow(parent), activeM(-1), M(), V(), B(), viewmapper(this), buttonmapper(this), doBenchmark(true) {
	ui.setupUi(this);
	connect(&viewmapper, SIGNAL(mapped(int)), this, SLOT(windowactivated(int)));
	cout << "viewmapper setup" << endl;
	connect(&buttonmapper, SIGNAL(mapped(int)), this, SLOT(selectorclicked(int)));
	cout << "buttonmapper setup" << endl;
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
	connect(kpv, SIGNAL(windowactivated(int)), &viewmapper, SLOT(map()));

	buttonmapper.setMapping(kps, kps->getID());
	connect(kps, SIGNAL(clicked()), &buttonmapper, SLOT(map()));

	connect(kpv, SIGNAL(closethis(int)), this, SLOT(inviewerclose(int)));

	V[ID] = kpv;
	B[ID] = kps;
	disenableItems();
}

void KomischesCAIPProjekt::removeImage(int ID) {
	V[ID]->close();
	delete V[ID];
	delete B[ID];
	V.erase(ID);
	B.erase(ID);
	if(V.size() > 0) windowactivated(begin(V)->first);
	disenableItems();
}

void KomischesCAIPProjekt::disenableItems() {
	bool t = V.size() > 0;
	ui.actionSave_Active->setEnabled(t);
	ui.actionClose_Active->setEnabled(t);
	ui.actionClose_All_Images->setEnabled(t);
	ui.menuOperations->setEnabled(t);
	ui.actionMagnifier->setEnabled(t);
}

void KomischesCAIPProjekt::selectorclicked(int n) {
	cout << "Selector " << n << " clicked" << endl;
	this->activeM = n;
	if (!V[n]->isVisible()) V[n]->show();
	V[n]->activateWindow();
	V[n]->fitToCurrent();
}

void KomischesCAIPProjekt::windowactivated(int view) {
	cout << "Window " << view << " activated" << endl;
	this->activeM = view;
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
	KPDSampleImage sam(true, true, false, string("Gray-Gradient fast"), this);
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
	KPDSampleImage sam(true, true, false, string("Gray-Gradient slow"), this);
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
	KPDSampleImage sam(false, false, false, string("Colored noise"), this);
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
	KPDSampleImage sam(false, false, false, string("Gray noise"), this);
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
	KPDSampleImage sam(false, false, true, string("Colored perlin noise"), this);
	if (sam.exec() == 1) {
		Tools::startBenchmark(doBenchmark);
		string n = string("Colored perlin noise, Seed: ") + to_string(sam.getSeed());
		this->activeM = M.addImage(ImProc::create_Colorperlin(sam.getWidth(), sam.getHeight(), sam.getSeed()), n);
		Tools::endBenchmark(doBenchmark, ui.statusBar);
		this->addImage(this->activeM, M.getImage(this->activeM));
		V[this->activeM]->show();
		V[this->activeM]->fitToCurrent();
	}
}

void KomischesCAIPProjekt::on_actionGray_Perlin_triggered() {
	KPDSampleImage sam(false, false, true, string("Gray perlin noise"), this);
	if (sam.exec() == 1) {
		Tools::startBenchmark(doBenchmark);
		string n = string("Gray perlin noise, Seed: ") + to_string(sam.getSeed());
		this->activeM = M.addImage(ImProc::create_Grayperlin(sam.getWidth(), sam.getHeight(), sam.getSeed()), n);
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
		QMessageBox::StandardButton a = QMessageBox::question(this, QString("Really exit?"), QString("Do you really want to exit the program?"));
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
}

void KomischesCAIPProjekt::on_actionCrop_triggered() {
}

void KomischesCAIPProjekt::on_actionResize_triggered() {
}

void KomischesCAIPProjekt::on_actionRotate_triggered() {
}

void KomischesCAIPProjekt::on_actionConvert_to_Grayscale_triggered() {
}

void KomischesCAIPProjekt::on_actionGammacorrection_triggered() {
}

void KomischesCAIPProjekt::on_actionContrastcorrection_triggered() {
}

void KomischesCAIPProjekt::on_actionBinarise_triggered() {
}

void KomischesCAIPProjekt::on_actionMean_triggered() {
}

void KomischesCAIPProjekt::on_actionMedian_triggered() {
}

void KomischesCAIPProjekt::on_actionGauss_triggered() {
}

void KomischesCAIPProjekt::on_actionEdge_triggered() {
}

void KomischesCAIPProjekt::on_actionRandom_triggered() {
}

void KomischesCAIPProjekt::on_actionCustom_triggered() {
}

void KomischesCAIPProjekt::on_actionErode_triggered() {
}

void KomischesCAIPProjekt::on_actionOpen_2_triggered() {
}

void KomischesCAIPProjekt::on_actionDilate_triggered() {
}

void KomischesCAIPProjekt::on_actionClose_triggered() {
}

void KomischesCAIPProjekt::on_actionBenchmark_triggered() {
	this->doBenchmark = ui.actionBenchmark->isChecked();
}

void KomischesCAIPProjekt::on_actionMagnifier_triggered() {
}

void KomischesCAIPProjekt::inviewerclose(int id) {
	removeImage(id);
}
