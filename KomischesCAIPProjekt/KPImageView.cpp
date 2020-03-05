#include "KPImageView.h"

KPImageView::KPImageView(QWidget* parent)
	: QWidget(parent), currentImage(), kpgs(), currentImageID(-1) {
	ui.setupUi(this);
	ui.graphicsView->setScene(&kpgs);
	
}

KPImageView::~KPImageView() {
}

void KPImageView::setImage(KPImage* img, const int& ID) {
	this->currentImageID = ID;
	this->currentImage = img->getQ();
	kpgs.clear();
	kpgs.setSceneRect(currentImage.rect());
	kpgs.addPixmap(QPixmap::fromImage(currentImage));
	this->updateStats();
}

void KPImageView::fit(KPImage& img, const bool current = true) {
	if (current) {
		ui.graphicsView->fitInView(0, 0, currentImage.width(), currentImage.height(), Qt::KeepAspectRatio);
	} else {
		ui.graphicsView->fitInView(0, 0, img.getQ().width(), img.getQ().height(), Qt::KeepAspectRatio);
	}
}

void KPImageView::fitToCurrent() {
	ui.graphicsView->fitInView(0, 0, currentImage.width(), currentImage.height(), Qt::KeepAspectRatio);
}

const int KPImageView::getID() {
	return this->currentImageID;
}



void KPImageView::resizeEvent(QResizeEvent* event) {
	QWidget::resizeEvent(event);
	this->fitToCurrent();
}

void KPImageView::updateStats() {
	// TODO update fields in viewer
}

bool KPImageView::event(QEvent* e) {
	if (e->type() == QEvent::WindowActivate) {
		emit windowactivated(this->currentImageID);
	}
	return QWidget::event(e);
}