#include "animationsetwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AnimationSetWidget w;
    w.show();
    return a.exec();
}
