#include "viewer.h"

#include <QPainter>
#include <QWheelEvent>
#include <cmath>
#include <QDebug>

static const qreal phi = (1.+sqrt(5))/2.;
static const qreal alpha = M_PI/5.;
static const qreal rad_to_deg = 180/M_PI;

Viewer::Viewer(QWidget* parent)
    : QWidget(parent), scale(200), translation_current(0,0), translation_start(0,0), display_edges(false), inner_radius(1), order(7)
{
}

static const QPen pen(QColor(33,43,61),.05);
//static const QColor kite_color(33,255,61);
static const QColor kite_color(Qt::white);
static const QColor dart_color(0,80,77);

void Viewer::drawHalfKite(QPainter& painter, unsigned int order) const
{
    if (order)
    {
        painter.save();
        painter.scale(1/phi,1/phi);
        painter.rotate(alpha*rad_to_deg);
        painter.translate(1,0);
        painter.scale(-1,-1);
        drawHalfDart(painter,order-1);
        painter.restore();

        painter.save();
        painter.scale(1/phi,1/phi);
        painter.rotate(alpha*rad_to_deg);
        painter.translate(1+phi,0);
        painter.rotate(alpha*rad_to_deg);
        painter.scale(-1,-1);
        drawKite(painter,order-1);
        painter.restore();

        return;
    }

    const QPointF points[] = {
        QPointF(0,0),
        QPointF(inner_radius*phi*cos(alpha),inner_radius*phi*sin(alpha)),
        QPointF(inner_radius*phi,0)
    };

    painter.setPen(kite_color);
    painter.setBrush(kite_color);
    painter.drawConvexPolygon(points,3);

    if (display_edges)
    {
        painter.setPen(pen);
        painter.drawPolyline(points,3);
    }
}

void Viewer::drawHalfDart(QPainter& painter, unsigned int order) const
{
    if (order)
    {
        painter.save();
        painter.scale(1/phi,1/phi);
        painter.translate(phi,0);
        painter.scale(-1,1);
        drawHalfKite(painter,order-1);
        painter.restore();

        painter.save();
        painter.scale(1/phi,1/phi);
        painter.rotate(2*alpha*rad_to_deg);
        painter.translate(1,0);
        painter.rotate(2*alpha*rad_to_deg);
        drawHalfDart(painter,order-1);
        painter.restore();

        return;
    }

    const QPointF points[] = {
        QPointF(0,0),
        QPointF(inner_radius*cos(3*alpha),inner_radius*sin(3*alpha)),
        QPointF(1,0)
    };

    painter.setPen(dart_color);
    painter.setBrush(dart_color);
    painter.drawConvexPolygon(points,3);

    if (display_edges)
    {
        painter.setPen(pen);
        painter.drawPolyline(points,3);
    }
}

void Viewer::drawKite(QPainter& painter, unsigned int order) const
{
    painter.save();
    drawHalfKite(painter,order);
    painter.scale(1,-1);
    drawHalfKite(painter,order);
    painter.restore();
}

void Viewer::drawDart(QPainter& painter, unsigned int order) const
{
    painter.save();
    drawHalfDart(painter,order);
    painter.scale(1,-1);
    drawHalfDart(painter,order);
    painter.restore();
}

void Viewer::toggleEdges()
{
    display_edges = !display_edges;
}

void Viewer::wheelEvent(QWheelEvent* event)
{
    scale *= pow(0.95,event->delta()/120);
    update();
}

void Viewer::keyPressEvent(QKeyEvent* event)
{
    if (event->text() == "d")
    {
        display_edges = !display_edges;
        event->accept();
        update();
        return;
    }

    if (event->text() == "o")
    {
        order ++;
        event->accept();
        update();
        return;
    }

    if (event->text() == "p")
    {
        order --;
        event->accept();
        update();
        return;
    }

    if (event->text() == "+")
    {
        inner_radius += .05;
        event->accept();
        update();
        return;
    }

    if (event->text() == "-")
    {
        inner_radius -= .05;
        event->accept();
        update();
        return;
    }
}

void Viewer::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.translate(width()/2,height()/2);
    painter.translate(translation_current);
    painter.scale(scale,scale);
    painter.rotate(alpha*rad_to_deg/2);

    for (int kk=0; kk<5; kk++)
    {
        painter.rotate(2*alpha*rad_to_deg);
        drawKite(painter,order);
    }
}


void Viewer::mousePressEvent(QMouseEvent* event)
{
    translation_start = event->posF();
}

void Viewer::mouseMoveEvent(QMouseEvent* event)
{
    translation_current += event->posF()-translation_start;
    translation_start = event->posF();
    update();
}

