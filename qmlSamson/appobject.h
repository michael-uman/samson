#ifndef APPOBJECT_H
#define APPOBJECT_H

#include <QObject>
#include "samson.h"

class appObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int crashCount READ crashCount WRITE setCrashCount NOTIFY crashCountChanged)

public:
    explicit appObject(QObject *parent = nullptr);

    Q_INVOKABLE void doSegfault();
    Q_INVOKABLE void doDivideByZero();
    Q_INVOKABLE void doAbort();

    int crashCount() {
        return get_crash_count();
    }

    void setCrashCount(int count) {
        Q_UNUSED(count)
    }

signals:
    void crashCountChanged();

private:
};

#endif // APPOBJECT_H
