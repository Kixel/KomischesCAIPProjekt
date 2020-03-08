#include "KPFilterPreDialog.h"

KPFilterPreDialog::KPFilterPreDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(reject()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(accept()));

}

KPFilterPreDialog::~KPFilterPreDialog()
{
}

int KPFilterPreDialog::getW() {
	return ui.spinBox->value();
}

int KPFilterPreDialog::getH() {
	return ui.spinBox_2->value();
}
