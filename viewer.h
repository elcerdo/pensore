#ifndef __VIEWER_H__
#define __VIEWER_H__

#include <QWidget>

class Viewer : public QWidget
{
  Q_OBJECT
  public:
    Viewer(QWidget* parent=NULL);
  public slot:
      void toggleEdges();
  protected:
    void keypressEvent(QKeyEvent* event);
    void paintEvent(QPaintEvent* event);
    void wheelEvent(QWheelEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    qreal scale;
    QPointF translation_current;
    QPointF translation_start;
    bool display_edges;
};

#endif

