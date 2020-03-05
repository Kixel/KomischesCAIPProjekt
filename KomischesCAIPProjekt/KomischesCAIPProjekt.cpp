#include "KomischesCAIPProjekt.h"

KomischesCAIPProjekt::KomischesCAIPProjekt(QWidget* parent)
	: QMainWindow(parent), activeM(-1), M(), V(), B(), viewmapper(this), buttonmapper(this) {
	ui.setupUi(this);
	connect(&viewmapper, SIGNAL(mapped(int)), this, SLOT(windowactivated(int)));
	cout << "viewmapper setup" << endl;
	connect(&buttonmapper, SIGNAL(mapped(int)), this, SLOT(selectorclicked(int)));
	cout << "buttonmapper setup" << endl;
}

void KomischesCAIPProjekt::changeImage(int ID, KPImage* im) {

}

void KomischesCAIPProjekt::addImage(int ID, KPImage* im) {
	KPImageView* kpv = new KPImageView();
	KPImageSelector* kps = new KPImageSelector(ID, im);
	//ui.Selections.addWidget(kps);
	ui.Test->addWidget(kps);
	kpv->setImage(im, ID);
	kpv->show();
	kpv->fitToCurrent();
	//connect(kps, SIGNAL(clicked()), selectorclicked(kps));
	//connect(kpv, SIGNAL(windowactivated(int)), this, SLOT(windowactivated(kpv)));

	viewmapper.setMapping(kpv, kpv->getID());
	connect(kpv, SIGNAL(windowactivated(int)), &viewmapper, SLOT(map()));

	buttonmapper.setMapping(kps, kps->getID());
	connect(kps, SIGNAL(clicked()), &buttonmapper, SLOT(map()));

	V[ID] = kpv;
	B[ID] = kps;
}

void KomischesCAIPProjekt::selectorclicked(int n) {
	cout << "Selector " << n << " clicked" << endl;
}

void KomischesCAIPProjekt::windowactivated(int view) {
	cout << "Window " << view << " activated" << endl;
}

void KomischesCAIPProjekt::on_actionOpen_triggered() {
	QString qs = QFileDialog::getOpenFileName(this, tr("Open File"), QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).last(), tr("Images (*.png *.jpg *.tif *.tiff *.jpeg *.bmp *.pbm *.pgm *.ppm *.sr *.ras *.dib)"));
	cout << qs.toStdString() << endl;
	this->activeM = M.loadImage(qs.toStdString());


	this->addImage(this->activeM, M.getImage(this->activeM));
	V[this->activeM]->show();
	V[this->activeM]->fitToCurrent();	
}

void KomischesCAIPProjekt::on_actionSave_Active_triggered() {
}

void KomischesCAIPProjekt::on_actionGray_Gradient_fast_triggered() {
}

void KomischesCAIPProjekt::on_actionGray_Gradient_slow_triggered() {
}

void KomischesCAIPProjekt::on_actionColor_Noise_triggered() {
}

void KomischesCAIPProjekt::on_actionGray_Noise_triggered() {
}

void KomischesCAIPProjekt::on_actionColor_Perlin_triggered() {
}

void KomischesCAIPProjekt::on_actionGray_Perlin_triggered() {
}

void KomischesCAIPProjekt::on_actionClose_Active_triggered() {
}

void KomischesCAIPProjekt::on_actionClose_All_Images_triggered() {
}

void KomischesCAIPProjekt::on_actionQuit_triggered() {
	QApplication::quit();
}

void KomischesCAIPProjekt::closeEvent(QCloseEvent* event) {
	on_actionQuit_triggered();
}

void KomischesCAIPProjekt::on_actionShow_Histogram_triggered() {
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

void KomischesCAIPProjekt::on_actionMagnifier_triggered() {
}
