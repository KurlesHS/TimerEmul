#ifndef TIMEREMULTHREADWORKER_H
#define TIMEREMULTHREADWORKER_H

#include <QObject>

class TimerEmulThreadWorker : public QObject
{
    Q_OBJECT
public:
    explicit TimerEmulThreadWorker(QObject *parent = 0);

signals:

public slots:

private:
    bool m_isBusy;

};

#endif // TIMEREMULTHREADWORKER_H
