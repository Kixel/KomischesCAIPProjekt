#pragma once

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

//#include <qgraphicssceneevent.h>

//Code zum gro�teil direkt aus der Musterl�sung �bernommen
class KPGraphicsScene : public QGraphicsScene
{
	Q_OBJECT

public:
	//KPGraphicsScene(QObject *parent);
	~KPGraphicsScene();

signals:
	void mouseMoved(int x, int y);

public slots:
	void mouseMoveEvent(QGraphicsSceneMouseEvent *mevent);
};
