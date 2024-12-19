#include "foldwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FoldWindow w;
    w.show();
    return a.exec();
}
