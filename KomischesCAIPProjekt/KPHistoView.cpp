#include "KPHistoView.h"

KPHistoView::KPHistoView(KPImage orig, QWidget* parent)
	: QWidget(parent), currentImage(orig), histo(), qgs()
{
	ui.setupUi(this);
	if (currentImage.getQ().isGrayscale()) {
		histo.push_back(*ImProc::grayhisto(&currentImage));
	} else {
		histo = *ImProc::colorhisto(&currentImage);
	}
	ui.graphicsView->setScene(&qgs);
	qgs.clear();
	qgs.setSceneRect(currentImage.getQ().rect());
	qgs.addPixmap(QPixmap::fromImage(currentImage.getQ()));
	hw = new HistWidget(histo);
	QGridLayout* gl = new QGridLayout();
	gl->addWidget(hw, 0, 0);
	ui.groupBox_2->setLayout(gl);
	ui.graphicsView->fitInView(0, 0, currentImage.getQ().width(), currentImage.getQ().height(), Qt::KeepAspectRatio);
}

KPHistoView::~KPHistoView()
{
}

void KPHistoView::resizeEvent(QResizeEvent* event) {
	ui.graphicsView->fitInView(0, 0, currentImage.getQ().width(), currentImage.getQ().height(), Qt::KeepAspectRatio);
}

void KPHistoView::fit() {
	ui.graphicsView->fitInView(0, 0, currentImage.getQ().width(), currentImage.getQ().height(), Qt::KeepAspectRatio);
}

void KPHistoView::closeEvent(QCloseEvent* e) {
	this->hide();
}

void KPHistoView::on_pushButton_clicked() {
	this->hide();
	delete this;
}