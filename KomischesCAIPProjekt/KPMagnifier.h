#pragma once

#include <QWidget>
#include "ui_KPMagnifier.h"
#include "KPImage.h"
#include <QGraphicsScene>
#include "ImProc.h"

class KPMagnifier : public QWidget {
	Q_OBJECT

public:
	KPMagnifier(QWidget* parent = Q_NULLPTR);
	~KPMagnifier();

	void updateImage(KPImage* im, int x, int y);

	void resizeEvent(QResizeEvent* event);


private:
	Ui::KPMagnifier ui;
	QGraphicsScene qgs;
	KPImage* current;

	int getW();
	int getH();

	enum SnapSize {FIVE, TEN, TWENTY, ANSWER, FIFTY, HUNDRED, CUSTOM};
private slots:

	void on_comboBox_currentIndexChanged(int n);
	void on_pushButton_clicked();
};
