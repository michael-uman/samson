#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <unistd.h>
#include <sys/wait.h>
#include "../samson.h"

int qt_main(int argc, char *argv[]);

int main(int argc, char * argv[]) {
    return keep_alive(qt_main, argc, argv);
}

int qt_main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
