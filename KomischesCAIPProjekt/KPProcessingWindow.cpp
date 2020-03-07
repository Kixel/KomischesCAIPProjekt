#include "KPProcessingWindow.h"
#include <iostream>

KPProcessingWindow::KPProcessingWindow(KPImage* (*Func)(KPImage*, KPProcessingWindow*), KPImage* original, QWidget* parent)
	: QDialog(parent), Worker(Func), exitstate(-1)
{
	cout << 1;
	this->orig = original;
	cout << 2;
	this->preview = new KPImage(*this->orig);
	this->left = new QGraphicsScene();
	this->right = new QGraphicsScene();
	cout << 3;
	ui.setupUi(this); 
	cout << 4;
	ui.qgv_original->setScene(left);
	cout << 5;
	ui.qgv_preview->setScene(right);
	cout << 6;

	left->clear();
	cout << 1;
	left->setSceneRect(orig->getQ().rect());
	cout << 2;
	left->addPixmap(QPixmap::fromImage(orig->getQ()));
	cout << 7;
	this->updatePreview();
	cout << 8;
	connect(ui.spinBox, SIGNAL(valueChanged(int)), this, SLOT(updatePreview()));
	connect(ui.spinBox_2, SIGNAL(valueChanged(int)), this, SLOT(updatePreview()));
	connect(ui.spinBox_3, SIGNAL(valueChanged(int)), this, SLOT(updatePreview()));
	connect(ui.spinBox_4, SIGNAL(valueChanged(int)), this, SLOT(updatePreview()));
	connect(ui.spinBox_5, SIGNAL(valueChanged(int)), this, SLOT(updatePreview()));
	connect(ui.doubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(updatePreview()));
	connect(ui.horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(updatePreview()));
	connect(ui.horizontalSlider_2, SIGNAL(valueChanged(int)), this, SLOT(updatePreview()));
	cout << 9;
	connect(ui.buttonOk, SIGNAL(clicked()), this, SLOT(finish()));
	connect(ui.buttonCancel, SIGNAL(clicked()), this, SLOT(abort()));
	cout << 10;
	this->setModal(true);
	this->setWindowModality(Qt::WindowModality::ApplicationModal);
}

KPProcessingWindow::~KPProcessingWindow() {
	delete left;
	delete right;
	delete preview;
}

void KPProcessingWindow::fitToCurrent() {
	ui.qgv_original->fitInView(0, 0, orig->getQ().width(), orig->getQ().height(), Qt::KeepAspectRatio);
	ui.qgv_preview->fitInView(0, 0, preview->getQ().width(), preview->getQ().height(), Qt::KeepAspectRatio);
}


void KPProcessingWindow::updatePreview() {
	delete preview;
	preview = Worker(this->orig, this);

	right->clear();
	right->setSceneRect(preview->getQ().rect());
	right->addPixmap(QPixmap::fromImage(preview->getQ()));
	this->fitToCurrent();
}

void KPProcessingWindow::setup(string title, bool needslabels, bool needsSpinner12, bool needsSpinner34, bool needsDouble, bool needsSpinner5, bool needsSlider1, bool needsSlider2) {
	ui.labelTitle->setText(QString(title.c_str()));
	if (!needslabels) {
		ui.w_info12->hide();
	}
	if (!needsSpinner12) {
		ui.w_spinner12->hide();
	}
	if (!needsSpinner34) {
		ui.w_spinner34->hide();
	}
	if (!needsSpinner5) {
		ui.spinBox_5->hide();
		ui.label_3->hide();
	}
	if (!needsDouble) {
		ui.label->hide();
		ui.doubleSpinBox->hide();
	}
	if (!needsSpinner5 && !needsDouble) {
		ui.w_doublebox1->hide();
	}
	if (!needsSlider1) {
		ui.w_slider1->hide();
	}
	if (!needsSlider2) {
		ui.w_slider2->hide();
	}
}

void KPProcessingWindow::setupLabels(string leftW, string rightH) {
	ui.lineEdit->setText(QString(leftW.c_str()));
	ui.lineEdit_2->setText(QString(rightH.c_str()));
}

void KPProcessingWindow::setupSpinner12(string leftL, int leftV, int leftmin, int leftmax, string rightL, int rightV, int rightmin, int rightmax) {
	ui.label_6->setText(QString(leftL.c_str()));
	ui.label_7->setText(QString(rightL.c_str()));
	ui.spinBox->setRange(leftmin, leftmax);
	ui.spinBox->setValue(leftV);
	ui.spinBox_2->setRange(rightmin, rightmax);
	ui.spinBox_2->setValue(rightV);
}

void KPProcessingWindow::setupSpinner34(string leftL, int leftV, int leftmin, int leftmax, string rightL, int rightV, int rightmin, int rightmax) {
	ui.label_8->setText(QString(leftL.c_str()));
	ui.label_9->setText(QString(rightL.c_str()));
	ui.spinBox_3->setRange(leftmin, leftmax);
	ui.spinBox_3->setValue(leftV);
	ui.spinBox_4->setRange(rightmin, rightmax);
	ui.spinBox_4->setValue(rightV);
}

void KPProcessingWindow::setupSpinner5(string L, int V, int min, int max) {
	ui.label_3->setText(QString(L.c_str()));
	ui.spinBox_5->setRange(min, max);
	ui.spinBox_5->setValue(V);
}

void KPProcessingWindow::setupDouble(string L, double V, double min, double max) {
	ui.label->setText(QString(L.c_str()));
	ui.doubleSpinBox->setRange(min, max);
	ui.doubleSpinBox->setValue(V);
}

void KPProcessingWindow::setupSlider1(string T, int V) {
	//string t = string("Threshold (default: ") + T + string(")");
	ui.label_2->setText(QString(T.c_str()));
	ui.horizontalSlider->setValue(V);
}

void KPProcessingWindow::setupSlider2(string T, int V) {
	//string t = string("Threshold (default: ") + T + string(")");
	ui.label_10->setText(QString(T.c_str()));
	ui.horizontalSlider_2->setValue(V);
}

void KPProcessingWindow::setDoublePrecision(double a) {
	ui.doubleSpinBox->setSingleStep(a);
}

int KPProcessingWindow::getInt1() {
	return ui.spinBox->value();
}

int KPProcessingWindow::getInt2() {
	return ui.spinBox_2->value();
}

int KPProcessingWindow::getInt3() {
	return ui.spinBox_3->value();
}

int KPProcessingWindow::getInt4() {
	return ui.spinBox_4->value();
}

int KPProcessingWindow::getInt5() {
	return ui.spinBox_5->value();
}

double KPProcessingWindow::getDouble1() {
	return ui.doubleSpinBox->value();
}

int KPProcessingWindow::getSlider1() {
	return ui.horizontalSlider->value();
}

int KPProcessingWindow::getSlider2() {
	return ui.horizontalSlider_2->value();
}

void KPProcessingWindow::resizeEvent(QResizeEvent* event) {
	QWidget::resizeEvent(event);
	this->fitToCurrent();
}

int KPProcessingWindow::getState() {
	return this->exitstate;
}

KPImage* KPProcessingWindow::getResult() {
	return Worker(this->orig, this);
}

KPImage* KPProcessingWindow::getSource() {
	return orig;
}

bool KPProcessingWindow::copyToNew() {
	return ui.copyToNew->isChecked();
}

void KPProcessingWindow::abort() {
	cout << "abort" << endl;
	this->exitstate = 0;
	emit finished(this);
}

void KPProcessingWindow::finish() {
	cout << "ok!" << endl;
	this->exitstate = 1;
	emit finished(this);
}

void KPProcessingWindow::closeEvent(QCloseEvent* event) {
	abort();
}
