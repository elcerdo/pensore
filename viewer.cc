#include "viewer.h"

#include <QPainter>
#include <cmath>

static const double phi = (1.+sqrt(5))/2.;

Viewer::Viewer(QWidget* parent)
	: QWidget(parent)
{
}

void Viewer::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	QPainter painter(this);
	
	painter.translate(width()/2,height()/2);
}


