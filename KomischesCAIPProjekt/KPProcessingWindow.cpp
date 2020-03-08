#include "KPProcessingWindow.h"
#include <iostream>

KPProcessingWindow::KPProcessingWindow(KPImage* (*Func)(KPImage*, KPProcessingWindow*), KPImage* original, QWidget* parent, bool slowoperation)
	: QDialog(parent), Worker(Func), exitstate(-1), tablex(0), tabley(0)
{
	this->orig = original;
	this->preview = new KPImage(*this->orig);
	cout << preview->getWidth() << endl;
	this->left = new QGraphicsScene();
	this->right = new QGraphicsScene();
	ui.setupUi(this); 
	ui.qgv_original->setScene(left);
	ui.qgv_preview->setScene(right);
	left->clear();
	left->setSceneRect(orig->getQ().rect());
	left->addPixmap(QPixmap::fromImage(orig->getQ()));
	updatePreview();
	if (slowoperation) {
		connect(ui.buttonRefresh, SIGNAL(clicked()), this, SLOT(updatePreview()));
	} else {
		ui.buttonRefresh->hide();
		connect(ui.spinBox, SIGNAL(valueChanged(int)), this, SLOT(updatePreview()));
		connect(ui.spinBox_2, SIGNAL(valueChanged(int)), this, SLOT(updatePreview()));
		connect(ui.spinBox_3, SIGNAL(valueChanged(int)), this, SLOT(updatePreview()));
		connect(ui.spinBox_4, SIGNAL(valueChanged(int)), this, SLOT(updatePreview()));
		connect(ui.spinBox_5, SIGNAL(valueChanged(int)), this, SLOT(updatePreview()));
		connect(ui.doubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(updatePreview()));
		connect(ui.horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(updatePreview()));
		connect(ui.horizontalSlider_2, SIGNAL(valueChanged(int)), this, SLOT(updatePreview()));
		connect(ui.comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updatePreview()));

		connect(ui.comboBorder, SIGNAL(currentIndexChanged(int)), this, SLOT(updatePreview()));
		connect(ui.combo_shape, SIGNAL(currentIndexChanged(int)), this, SLOT(updatePreview()));
		connect(ui.spinnerBorder, SIGNAL(valueChanged(int)), this, SLOT(updatePreview()));


	}
	connect(ui.buttonOk, SIGNAL(clicked()), this, SLOT(finish()));
	connect(ui.buttonCancel, SIGNAL(clicked()), this, SLOT(abort()));
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
	//if (!this->isVisible()) return;
	if (preview) delete preview;
	preview = Worker(this->orig, this);
	cout << preview->getWidth();
	right->clear();
	right->setSceneRect(preview->getQ().rect());
	right->addPixmap(QPixmap::fromImage(preview->getQ()));
	this->fitToCurrent();
}

void KPProcessingWindow::setup(string title, bool needslabels, bool needsSpinner12, bool needsSpinner34, 
	bool needsDouble, bool needsSpinner5, bool needsSlider1, bool needsSlider2, bool needscombo, 
	bool needsmorph, bool needsborder, bool needsmatrix) {
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
		ui.label->hide();
	}
	if (!needsDouble) {
		ui.label_3->hide();
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
	if (!needscombo) {
		ui.w_comboBox->hide();
	}
	ui.spinnerBorder->hide();
	if (!needsmorph) {
		ui.w_morph->hide();
	} 
	if (needsborder) {
		ui.w_morph->show();
		ui.label_12->hide();
		ui.combo_shape->hide();
	}
	if (!needsmatrix) {
		ui.groupBox_3->hide();
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
	ui.label->setText(QString(L.c_str()));
	ui.spinBox_5->setRange(min, max);
	ui.spinBox_5->setValue(V);
}

void KPProcessingWindow::setupDouble(string L, double V, double min, double max) {
	ui.label_3->setText(QString(L.c_str()));
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

void KPProcessingWindow::setupTable(int x, int y, bool random) {
	tablex = x;
	tabley = y;
	table.reserve(y);
	QGridLayout* ql = new QGridLayout(ui.groupBox_3);
	for (int yy = 0; yy < y; yy++) {
		vector<QSpinBox*> td;
		td.reserve(x);
		for (int xx = 0; xx < x; xx++) {
			QSpinBox* nq = new QSpinBox();
			nq->setRange(-100, 100);
			if (random) {
				nq->setValue(rand()%200-100);
			} else {
				nq->setValue(0);
			}
			td.push_back(nq);
		}
		table.push_back(td);
	}
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

int KPProcessingWindow::getCombo() {
	return ui.comboBox->currentIndex();
}

int KPProcessingWindow::getIntAt(int x, int y) {
	if (x < 0 || x > tablex || y < 0 || y > tabley) return 0;
	return table[y][x]->value();
}

int KPProcessingWindow::getMatW() {
	return tablex;
}

int KPProcessingWindow::getMatH() {
	return tabley;
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

void KPProcessingWindow::show() {
	QDialog::show();
	this->updatePreview();
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

void KPProcessingWindow::on_horizontalSlider_valueChanged() {
	ui.lineEdit_3->setText(QString(to_string(ui.horizontalSlider->value()).c_str()));
}

void KPProcessingWindow::on_horizontalSlider_2_valueChanged() {
	ui.lineEdit_4->setText(QString(to_string(ui.horizontalSlider_2->value()).c_str()));
}

void KPProcessingWindow::closeEvent(QCloseEvent* event) {
	abort();
}

void KPProcessingWindow::on_comboBorder_currentIndexChanged(int i) {
	if (i > 0) {
		ui.spinnerBorder->hide();
	} else {
		ui.spinnerBorder->show();
	}
}

int KPProcessingWindow::getShape() {
	return ui.combo_shape->currentIndex();
}

int KPProcessingWindow::getBordertype() {
	return ui.comboBorder->currentIndex();
}

int KPProcessingWindow::getBordervalue() {
	return ui.spinnerBorder->value();
}
