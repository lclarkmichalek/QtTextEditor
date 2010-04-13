#include "qttexteditor.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTTextEditor w;
    w.show();
    return a.exec();
}
