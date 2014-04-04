#ifndef TIMEREMULTHREADWORKER_H
#define TIMEREMULTHREADWORKER_H

#include <QObject>
#include <QTimer>

class QSerialPort;

class TimerEmulThreadWorker : public QObject
{
    Q_OBJECT
public:
    explicit TimerEmulThreadWorker(QObject *parent = 0);
    ~TimerEmulThreadWorker();

public Q_SLOTS:
    bool start(const QString &portName);
    void stop();

public Q_SLOTS:
    void onReadyRead();
    void onTimeoutWaitFullPacket();


signals:
    void textInform(QString info);

public slots:

private:
    bool m_isBusy;
    int m_currentState;
    QSerialPort *m_serialPort;
    QByteArray m_buffer;
    QTimer *m_timer;

};

#endif // TIMEREMULTHREADWORKER_H
