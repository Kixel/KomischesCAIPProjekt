#include "KPDSampleImage.h"

KPDSampleImage::KPDSampleImage(bool needscheckbox, bool needsspinner, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	if (!needscheckbox && !needsspinner) {
		ui.groupBox_2->hide();
	} else {
		if (!needscheckbox) {
			ui.checkBox->hide();
		}
		if (!needsspinner) {
			ui.formLayout->hide();
		}
	}

}

KPDSampleImage::~KPDSampleImage()
{
}
