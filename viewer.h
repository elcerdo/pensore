#ifndef __VIEWER_H__
#define __VIEWER_H__

#include <QWidget>

class Viewer : public QWidget
{
    Q_OBJECT
    public:
        Viewer(QWidget* parent=NULL);
        void toggleEdges();
    protected:
        void keyPressEvent(QKeyEvent* event);
        void paintEvent(QPaintEvent* event);
        void wheelEvent(QWheelEvent* event);
        void mousePressEvent(QMouseEvent* event);
        void mouseMoveEvent(QMouseEvent* event);
        qreal scale;
        QPointF translation_current;
        QPointF translation_start;
        bool display_edges;
        qreal inner_radius;
    protected:
        void drawHalfKite(QPainter& painter, unsigned int order) const;
        void drawHalfDart(QPainter& painter, unsigned int order) const;
        void drawKite(QPainter& painter, unsigned int order) const;
        void drawDart(QPainter& painter, unsigned int order) const;
};

#endif

