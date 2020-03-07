#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_KomischesCAIPProjekt.h"
#include "ImageManager.h"
#include <iostream>
#include <QFileDialog>
#include <QStandardPaths>
#include "KPImageView.h"
#include "KPImageSelector.h"
#include <QSignalMapper>
#include "ImProc.h"
#include "KPDSampleImage.h"
#include <QMessageBox>
#include <QCloseEvent>
#include "KPProcessingWindow.h"


class KomischesCAIPProjekt : public QMainWindow
{
	Q_OBJECT

public:
	KomischesCAIPProjekt(QWidget *parent = Q_NULLPTR);

private:
	// Fields
	Ui::KomischesCAIPProjektClass ui;
	bool doBenchmark;
	ImageManager M;
	int activeM;
	map<int, KPImageView*> V;
	map<int, KPImageSelector*> B;

	QSignalMapper viewmapper, buttonmapper;

	// private functions
	void changeImage(int ID, KPImage* im);
	void addImage(int ID, KPImage* im);
	void removeImage(int ID);
	void disenableItems();

public slots:
	void windowactivated(int view);
	void selectorclicked(int n);

private slots:
	//Menu Bar
	//File Menu
	void on_actionOpen_triggered();
	void on_actionSave_Active_triggered();
		//TestImage Submenu
		void on_actionGray_Gradient_fast_triggered();
		void on_actionGray_Gradient_slow_triggered();
		void on_actionColor_Noise_triggered();
		void on_actionGray_Noise_triggered();
		void on_actionColor_Perlin_triggered();
		void on_actionGray_Perlin_triggered();
	void on_actionClose_Active_triggered();
	void on_actionClose_All_Images_triggered();
	void on_actionQuit_triggered();

	void closeEvent(QCloseEvent* event);

	//Operations Menu
	void on_actionShow_Histogram_triggered();
	void on_actionInvert_triggered();
	void on_actionCrop_triggered();
	void on_actionResize_triggered();
	void on_actionRotate_triggered();
	void on_actionConvert_to_Grayscale_triggered();
	void on_actionGammacorrection_triggered();
	void on_actionContrastcorrection_triggered();
	void on_actionBinarise_triggered();
	void on_actionBinarise_range_triggered();
	void on_actionAdaptive_Binarise_triggered();
		//Filter Submmenu
		void on_actionMean_triggered();
		void on_actionMedian_triggered();
		void on_actionGauss_triggered();
		void on_actionEdge_triggered();
		void on_actionRandom_triggered();
		void on_actionCustom_triggered();
		//Morphology
		void on_actionErode_triggered();
		void on_actionOpen_2_triggered();
		void on_actionDilate_triggered();
		void on_actionClose_triggered();

	
	//Extras Menu
	void on_actionBenchmark_triggered();
	void on_actionMagnifier_triggered();


	//Proxy
	void inviewerclose(int id);
	void improcesserclose(KPProcessingWindow* k);
};
