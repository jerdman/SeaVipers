#pragma once
#include "qgraphicsview.h"
#include <QMouseEvent>

class SelectorOverlay : public QGraphicsView
{
	Q_OBJECT

private:
	QRect selection;

public:
	SelectorOverlay(QWidget *parent = 0);

	void mouseReleaseEvent(QMouseEvent *event);
	QRect getSelection(void){return selection;}
};

