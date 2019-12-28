#include <QDebug>
#include <QObject>
#include <stdlib.h>
#include "appobject.h"

appObject::appObject(QObject *parent) : QObject(parent)
{
    qDebug() << Q_FUNC_INFO;
}

void appObject::doSegfault()
{
    qDebug() << Q_FUNC_INFO;

    int * data = nullptr;

    *data = 0;
}

void appObject::doDivideByZero()
{
    qDebug() << Q_FUNC_INFO;
    int x = 10 / 0;
}

void appObject::doAbort()
{
    qDebug() << Q_FUNC_INFO;
    ::abort();
}
