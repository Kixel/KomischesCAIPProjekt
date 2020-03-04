#pragma once

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

//#include <qgraphicssceneevent.h>

//Code zum großteil direkt aus der Musterlösung übernommen
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
