#include <QApplication>
#include "viewer.h"

int main(int argc,char * argv[])
{
    QApplication app(argc,argv);

    Viewer viewer;
    viewer.resize(600,600);
    viewer.showMaximized();

    return app.exec();
}

