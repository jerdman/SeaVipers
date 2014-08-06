#include "SelectorOverlay.h"


SelectorOverlay::SelectorOverlay(QWidget *parent): QGraphicsView(parent)
{
	setDragMode(RubberBandDrag);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setFrameShape(QFrame::NoFrame);
	setCursor(QCursor(Qt::CursorShape::CrossCursor));
}

void SelectorOverlay::mouseReleaseEvent(QMouseEvent *event){
	selection = rubberBandRect();
	QGraphicsView::mouseReleaseEvent(event);
}
