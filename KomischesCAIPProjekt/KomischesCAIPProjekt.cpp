#include "KomischesCAIPProjekt.h"

KomischesCAIPProjekt::KomischesCAIPProjekt(QWidget* parent)
	: QMainWindow(parent), activeM(-1), M() {
	ui.setupUi(this);
}

void KomischesCAIPProjekt::selectorclicked(int n) {
}

void KomischesCAIPProjekt::on_actionSave_Active_triggered() {
}

void KomischesCAIPProjekt::on_actionGray_Gradient_fast_triggered() {
}

void KomischesCAIPProjekt::on_actionGray_Gradient_slow_triggered() {
}

void KomischesCAIPProjekt::on_actionColor_Noise_triggered() {
}

void KomischesCAIPProjekt::on_actionGray_Noise_triggered() {
}

void KomischesCAIPProjekt::on_actionColor_Perlin_triggered() {
}

void KomischesCAIPProjekt::on_actionGray_Perlin_triggered() {
}

void KomischesCAIPProjekt::on_actionClose_All_Images_triggered() {
}

void KomischesCAIPProjekt::on_actionQuit_triggered() {
	QApplication::quit();
}

void KomischesCAIPProjekt::closeEvent(QCloseEvent* event) {
	on_actionQuit_triggered();
}

void KomischesCAIPProjekt::on_actionShow_Histogram_triggered() {
}

void KomischesCAIPProjekt::on_actionInvert_triggered() {
}

void KomischesCAIPProjekt::on_actionCrop_triggered() {
}

void KomischesCAIPProjekt::on_actionResize_triggered() {
}

void KomischesCAIPProjekt::on_actionRotate_triggered() {
}

void KomischesCAIPProjekt::on_actionConvert_to_Grayscale_triggered() {
}

void KomischesCAIPProjekt::on_actionGammacorrection_triggered() {
}

void KomischesCAIPProjekt::on_actionContrastcorrection_triggered() {
}

void KomischesCAIPProjekt::on_actionBinarise_triggered() {
}

void KomischesCAIPProjekt::on_actionMean_triggered() {
}

void KomischesCAIPProjekt::on_actionMedian_triggered() {
}

void KomischesCAIPProjekt::on_actionGauss_triggered() {
}

void KomischesCAIPProjekt::on_actionEdge_triggered() {
}

void KomischesCAIPProjekt::on_actionRandom_triggered() {
}

void KomischesCAIPProjekt::on_actionCustom_triggered() {
}

void KomischesCAIPProjekt::on_actionErode_triggered() {
}

void KomischesCAIPProjekt::on_actionOpen2_triggered() {
}

void KomischesCAIPProjekt::on_actionDilate_triggered() {
}

void KomischesCAIPProjekt::on_actionClose_triggered() {
}

void KomischesCAIPProjekt::on_actionMagnifier_triggered() {
}
