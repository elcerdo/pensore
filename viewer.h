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
		qreal scale;
};

#endif

