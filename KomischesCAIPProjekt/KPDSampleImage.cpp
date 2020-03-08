#include "KPDSampleImage.h"

KPDSampleImage::KPDSampleImage(string genname, bool needsdirection, bool needsinvert, bool needsspinner, bool needsslider, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	if (!needsdirection && !needsspinner && !needsinvert && !needsslider) {
		ui.groupBox_2->hide();
	} else {
		if (!needsdirection) {
			ui.checkBox->hide();
		}
		if (!needsinvert) {
			ui.checkBox_2->hide();
		}
		if (!needsspinner) {
			//ui.formLayout->hide();
			ui.seedLabel->hide();
			ui.seedSpinBox->hide();
		}
		if (!needsslider) {
			ui.label_2->hide();
			ui.horizontalSlider->hide();
		}
	}
	this->setWindowModality(Qt::WindowModality::WindowModal);
	this->setWindowTitle("Generate sample image");
	this->setGenType(genname);
	ui.seedSpinBox->setValue(Tools::GetRandomUint());

	connect(ui.pushOk, SIGNAL(clicked()), this, SLOT(accept()));
	connect(ui.pushCancel, SIGNAL(clicked()), this, SLOT(reject()));
}

KPDSampleImage::~KPDSampleImage()
{
}

const int KPDSampleImage::getHeight() {
	return ui.imageHeightPxSpinBox->value();
}

const int KPDSampleImage::getWidth() {
	return ui.imageWidthPxSpinBox->value();
}

const int KPDSampleImage::getSeed() {
	return ui.seedSpinBox->value();
}

const bool KPDSampleImage::getDirection() {
	return ui.checkBox->isChecked();
}

const bool KPDSampleImage::getInvert() {
	return ui.checkBox_2->isChecked();
}

const double KPDSampleImage::getZoom() {
	int v = ui.horizontalSlider->value();
	if (v == 0) return 1.0;
	if (v > 0) return v+1.0;
	if (v < 0) return 1 / (double)((-v)+1);
	return 0.0;
}

void KPDSampleImage::setGenType(const string a) {
	string t = string("Testimage: ") + a;
	ui.label->setText(QString(t.c_str()));
}
