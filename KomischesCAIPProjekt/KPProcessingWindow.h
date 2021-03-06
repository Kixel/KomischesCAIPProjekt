#pragma once

#include <QWidget>
#include "ui_KPProcessingWindow.h"
#include "KPImage.h"
#include <QGraphicsScene>
#include <QPixMap>
#include <QDialog>


class KPProcessingWindow : public QDialog
{
	Q_OBJECT

public:
	KPProcessingWindow(KPImage*(*Func)(KPImage*, KPProcessingWindow*), KPImage* original, QWidget *parent = Q_NULLPTR, bool slowoperation = false);

	~KPProcessingWindow();

	void fitToCurrent();

	void setup(string title, bool needslabels = false, bool needsSpinner12 = false, bool needsSpinner34 = false,
		bool needsDouble = false, bool needsSpinner5 = false, bool needsSlider1 = false,
		bool needsSlider2 = false, bool needscombo = false, bool needsmorph = false, 
		bool needsborder = false, bool needsmatrix = false);
	void setupLabels(string leftW, string rightH);
	void setupSpinner12(string leftL, int leftV, int leftmin, int leftmax,
		string rightL, int rightV, int rightmin, int rightmax);
	void setupSpinner34(string leftL, int leftV, int leftmin, int leftmax,
		string rightL, int rightV, int rightmin, int rightmax);
	void setupSpinner5(string L, int V, int min, int max);
	void setupDouble(string L, double V, double min, double max);
	void setupSlider1(string T, int V);
	void setupSlider2(string T, int V);
	void setDoublePrecision(double a);
	void setupTable(int x, int y, bool random);

	int getInt1();
	int getInt2();
	int getInt3();
	int getInt4();
	int getInt5();
	double getDouble1();
	int getSlider1();
	int getSlider2();
	int getCombo();
	int getIntAt(int x, int y);

	int getMatW();
	int getMatH();

	int getShape();
	int getBordertype();
	int getBordervalue();

	void resizeEvent(QResizeEvent* event);
	int getState();

	KPImage* getResult();
	KPImage* getSource();

	bool copyToNew();
	void show();
	
private slots:
	void updatePreview();
	void abort();
	void finish();

	void on_horizontalSlider_valueChanged();
	void on_horizontalSlider_2_valueChanged();

	void on_comboBorder_currentIndexChanged(int i);


private:
	Ui::KPProcessingWindow ui;
	KPImage* preview;
	KPImage* orig;
	QGraphicsScene* left,* right;
	KPImage* (*Worker)(KPImage*, KPProcessingWindow*);

	int exitstate;
	int tablex, tabley;
	vector<vector<QSpinBox*>> table;
	void closeEvent(QCloseEvent* event);

signals:
	void finished(KPProcessingWindow* kp);


};


/*
	Invert: none
	Crop: minx (int)=0, miny (int)=0, maxx (int)=size, maxy(int)=size -> 4 spinbox
	Resize: NewWidth (int)=original, NewHeight (int)=original, oldheight+oldwidth (text) -> 2 spinbox, 2 inputs
	Rotate: angle (double)=0 -> 1 doublespinbox
	Convert to grayscale: none
	gamma: gammavalue (double)=1 -> 1 doublespinbox
	contrast: mingray (int)=0, maxgray (int)=255 -> 2 spinbox
	binarise: grayvalue (int) -> 1 slider (auto to otsu!)
	bin2: grayvalue (int), grayvalue (int) -> 2 slider (otsu and 255)
	adapt: correctionvalue (double), range (int)  -> 1 doublebox, 1 spinbox



	spinbox 4 -> crop, resize, contrast
	inputs 2 -> resize
	doublespinbox 1 -> rotate, gamma
	slider 1 k -> binarise


*/