#include "viewer.h"

#include <QPainter>
#include <cmath>

static const qreal phi = (1.+sqrt(5))/2.;
static const qreal alpha = M_PI/5.;

Viewer::Viewer(QWidget* parent)
	: QWidget(parent), scale(100)
{
}

static const QPen pen(Qt::yellow,.05);
static const QBrush kite_brush(Qt::red);
static const QBrush dart_brush(Qt::blue);

void drawKiteUp(QPainter& painter)
{
	static const QPointF points[] = {
		QPointF(0,0),
		QPointF(phi*cos(alpha),phi*sin(alpha)),
		QPointF(phi,0)
	};

	painter.setPen(Qt::NoPen);
	painter.setBrush(kite_brush);
	painter.drawConvexPolygon(points,3);

	painter.setPen(pen);
	painter.drawPolyline(points,3);
}

void drawKiteDown(QPainter& painter)
{
	static const QPointF points[] = {
		QPointF(0,0),
		QPointF(phi*cos(alpha),-phi*sin(alpha)),
		QPointF(phi,0)
	};

	painter.setPen(Qt::NoPen);
	painter.setBrush(kite_brush);
	painter.drawConvexPolygon(points,3);

	painter.setPen(pen);
	painter.drawPolyline(points,3);
}

void drawDartUp(QPainter& painter)
{
	static const QPointF points[] = {
		QPointF(0,0),
		QPointF(cos(3*alpha),sin(3*alpha)),
		QPointF(1,0)
	};

	painter.setPen(Qt::NoPen);
	painter.setBrush(dart_brush);
	painter.drawConvexPolygon(points,3);

	painter.setPen(pen);
	painter.drawPolyline(points,3);
}

void drawDartDown(QPainter& painter)
{
	static const QPointF points[] = {
		QPointF(0,0),
		QPointF(1*cos(3*alpha),-sin(3*alpha)),
		QPointF(1,0)
	};

	painter.setPen(Qt::NoPen);
	painter.setBrush(dart_brush);
	painter.drawConvexPolygon(points,3);

	painter.setPen(pen);
	painter.drawPolyline(points,3);
}


void Viewer::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	
	painter.translate(width()/2,height()/2);
	painter.scale(scale,scale);

	drawKiteUp(painter);
	drawKiteDown(painter);
	painter.translate(phi,0);
	drawDartUp(painter);
	drawDartDown(painter);
}


