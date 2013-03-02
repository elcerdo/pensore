#ifndef __VIEWER_H__
#define __VIEWER_H__

#include <QWidget>

class Viewer : public QWidget
{
	Q_OBJECT
	public:
		Viewer(QWidget* parent=NULL);
	protected:
		void paintEvent(QPaintEvent* event);
		void wheelEvent(QWheelEvent* event);
		void mousePressEvent(QMouseEvent* event);
		void mouseMoveEvent(QMouseEvent* event);
		qreal scale;
		QPointF translation_current;
		QPointF translation_start;
};

#endif

