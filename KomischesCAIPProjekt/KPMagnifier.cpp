#include "KPMagnifier.h"

KPMagnifier::KPMagnifier(QWidget* parent)
	: QWidget(parent), qgs(), current(nullptr)
{
	ui.setupUi(this);
	ui.graphicsView->setScene(&qgs);

	on_comboBox_currentIndexChanged(ui.comboBox->currentIndex());
}

KPMagnifier::~KPMagnifier()
{
	if (current) delete current;
}

void KPMagnifier::updateImage(KPImage* im, int x, int y) {
	if(current) delete current;
	int rw = round(this->getW() / 2 - 0.5);
	int rh = round(this->getH() / 2 - 0.5);
	int x0 = max(0, x - rw);
	int y0 = max(0, y - rh);
	int w = min(im->getWidth() - x0, this->getW());
	int h = min(im->getHeight() - y0, this->getH());

	current = ImProc::crop(im, x0, y0, w, h);

	qgs.clear();
	qgs.setSceneRect(current->getQ().rect());
	qgs.addPixmap(QPixmap::fromImage(current->getQ()));
	ui.graphicsView->fitInView(0, 0, current->getWidth(), current->getHeight(), Qt::KeepAspectRatio);
}

void KPMagnifier::resizeEvent(QResizeEvent* event) {
	QWidget::resizeEvent(event);
	if (current != nullptr) ui.graphicsView->fitInView(0, 0, current->getWidth(), current->getHeight(), Qt::KeepAspectRatio);
}

int KPMagnifier::getW() {
	switch (ui.comboBox->currentIndex()) {
	case FIVE:
		return 5;
	case TEN:
		return 10;
	case TWENTY:
		return 20;
	case ANSWER:
		return 42;
	case FIFTY:
		return 50;
	case HUNDRED:
		return 100;
	case CUSTOM:
		return ui.spinBox->value();
	}
	return 0;
}

int KPMagnifier::getH() {
	switch (ui.comboBox->currentIndex()) {
	case FIVE:
		return 5;
	case TEN:
		return 10;
	case TWENTY:
		return 20;
	case ANSWER:
		return 42;
	case FIFTY:
		return 50;
	case HUNDRED:
		return 100;
	case CUSTOM:
		return ui.spinBox_2->value();
	}
	return 0;
}

void KPMagnifier::on_pushButton_clicked() {
	this->hide();
}

void KPMagnifier::on_comboBox_currentIndexChanged(int n) {
	if (ui.comboBox->currentIndex() == CUSTOM) {
		ui.label_3->show();
		ui.label_4->show();
		ui.spinBox->show();
		ui.spinBox_2->show();
	} else {
		ui.label_3->hide();
		ui.label_4->hide();
		ui.spinBox->hide();
		ui.spinBox_2->hide();
	}
}
