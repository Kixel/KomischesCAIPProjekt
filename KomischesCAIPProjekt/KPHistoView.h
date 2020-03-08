#pragma once

#include <QWidget>
#include "ui_KPHistoView.h"
#include "KPImage.h"
#include <vector>
#include "ImProc.h"
#include "HistWidget.h"

class KPHistoView : public QWidget
{
	Q_OBJECT

public:
	KPHistoView(KPImage orig, QWidget *parent = Q_NULLPTR);
	~KPHistoView();

	void resizeEvent(QResizeEvent* event);
	void fit();

	void closeEvent(QCloseEvent* e);
private:
	Ui::KPHistoView ui;
	KPImage currentImage;
	vector<vector<int>> histo;
	HistWidget* hw;
	QGraphicsScene qgs;

private slots:
	void on_pushButton_clicked();
};
