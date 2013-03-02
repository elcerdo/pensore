#include "viewer.h"

#include <QPainter>
#include <cmath>

static const qreal phi = (1.+sqrt(5))/2.;
static const qreal alpha = M_PI/5.;
static const qreal rad_to_deg = 180/M_PI;

Viewer::Viewer(QWidget* parent)
	: QWidget(parent), scale(100)
{
}

static const QPen pen(Qt::yellow,.05);
static const QColor kite_color(Qt::red);
static const QColor dart_color(Qt::blue);

void drawHalfKite(QPainter& painter, unsigned int order)
{
	static const QPointF points[] = {
		QPointF(0,0),
		QPointF(phi*cos(alpha),phi*sin(alpha)),
		QPointF(phi,0)
	};

	painter.setPen(kite_color);
	painter.setBrush(kite_color);
	painter.drawConvexPolygon(points,3);

	painter.setPen(pen);
	painter.drawPolyline(points,3);
}

void drawHalfDart(QPainter& painter, unsigned int order)
{
	static const QPointF points[] = {
		QPointF(0,0),
		QPointF(cos(3*alpha),sin(3*alpha)),
		QPointF(1,0)
	};

	painter.setPen(dart_color);
	painter.setBrush(dart_color);
	painter.drawConvexPolygon(points,3);

	painter.setPen(pen);
	painter.drawPolyline(points,3);
}

void drawKite(QPainter& painter, unsigned int order)
{
	painter.save();
	drawHalfKite(painter,order);
	painter.scale(1,-1);
	drawHalfKite(painter,order);
	painter.restore();
}

void drawDart(QPainter& painter, unsigned int order)
{
	painter.save();
	drawHalfDart(painter,order);
	painter.scale(1,-1);
	drawHalfDart(painter,order);
	painter.restore();
}

void Viewer::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	
	painter.translate(width()/2,height()/2);
	painter.scale(scale,scale);

	for (int kk=0; kk<5; kk++)
	{
		painter.save();
		painter.rotate(2*kk*alpha*rad_to_deg);
		drawKite(painter,1);
		painter.translate(phi,0);
		drawDart(painter,1);
		painter.restore();
	}
}


