#pragma once
#include "qgraphicsview.h"
#include <QMouseEvent>

class SelectorOverlay : public QGraphicsView
{
	Q_OBJECT

private:
	QRect selection;

signals:
	void selectionReady(const QRect &rect);

public:
	SelectorOverlay(QWidget *parent = 0);

	void mouseReleaseEvent(QMouseEvent *event);
};

