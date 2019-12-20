#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <unistd.h>
#include <sys/wait.h>
#include "samson.h"

int qt_main(int argc, char *argv[]);

int main(int argc, char * argv[]) {
    pid_t   procId = 0;
    int     status = -1;
    bool    exitOk = false;

    qDebug() << "Hello, World!";

    while (!exitOk) {
        procId = start_process(qt_main, argc, argv);

        qDebug() << QString("From parent (Child pid = %1)!").arg(procId);

        waitpid(procId, &status, 0);

        if (WIFEXITED(status)) {
            qDebug() << QString("Child returned status %1").arg(WEXITSTATUS(status));
            exitOk = true;
        } else if (WIFSIGNALED(status)) {
            qDebug() << QString("Child exited with signal %1").arg(WTERMSIG(status));
            qDebug() << "RESTARTING!";
        }
    }

    return 0;
}

int qt_main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
