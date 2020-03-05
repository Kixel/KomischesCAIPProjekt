#include "KPGraphicsScene.h"


/*KPGraphicsScene::KPGraphicsScene(QObject *parent)
	: QGraphicsScene(parent)
{
}*/

KPGraphicsScene::~KPGraphicsScene()
{
}

void KPGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mevent) {
	int x = mevent->scenePos().x();
	int y = mevent->scenePos().y();

	emit mouseMoved(x, y);

}