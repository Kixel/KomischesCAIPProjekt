#include "KPDSampleImage.h"

KPDSampleImage::KPDSampleImage(bool needsdirection, bool needsinvert, bool needsspinner, string genname,  QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	if (!needsdirection && !needsspinner && !needsinvert) {
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

void KPDSampleImage::setGenType(const string a) {
	string t = string("Testimage: ") + a;
	ui.label->setText(QString(t.c_str()));
}
