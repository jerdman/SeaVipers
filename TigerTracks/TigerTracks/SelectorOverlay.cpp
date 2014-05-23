#include "SelectorOverlay.h"


SelectorOverlay::SelectorOverlay(QWidget *parent): QGraphicsView(parent)
{
	setDragMode(RubberBandDrag);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void SelectorOverlay::mouseReleaseEvent(QMouseEvent *event){
	selection = rubberBandRect();
	QGraphicsView::mouseReleaseEvent(event);
	emit selectionReady(selection);
}
