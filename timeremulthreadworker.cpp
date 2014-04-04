#include "timeremulthreadworker.h"
#include <QSerialPort>
// в этом режиме шлём телеметрию, ожидаем команды на изменение положения машинок
// и команд на запись / чтение настроек прошивки
static const int telemetryMode = 0x00;

// принимаем новые данные для алгоритма с андроида
static const int receiveAlgDataMode = 0x01;

// посылаем данные для алгоритма на андроид
static const int sentAlgDataMode = 0x02;

TimerEmulThreadWorker::TimerEmulThreadWorker(QObject *parent) :
    QObject(parent),
    m_isBusy(false),
    m_serialPort(nullptr),
    m_timer(new QTimer(this))
{
    /*
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimeoutWaitFullPacket()));
    m_timer->setInterval(10);
    */
}

TimerEmulThreadWorker::~TimerEmulThreadWorker()
{
    stop();
    delete m_timer;
}

bool TimerEmulThreadWorker::start(const QString &portName)
{
    m_currentState = telemetryMode;
    if (!m_serialPort) {
        m_serialPort = new QSerialPort(portName);
        connect(m_serialPort, SIGNAL(readyRead()),
                this, SLOT(onReadyRead()));
        if (!m_serialPort->open(QIODevice::ReadWrite)) {
            emit textInform("error open port");
            stop();
            return false;
        }
        m_serialPort->setBaudRate(QSerialPort::Baud38400);
        m_serialPort->setDataBits(QSerialPort::Data8);
        m_serialPort->setFlowControl(QSerialPort::NoFlowControl);
        m_serialPort->setStopBits(QSerialPort::OneStop);
        emit textInform("port open success");
        return true;

    }
    emit textInform("error open port");
    return false;

}

void TimerEmulThreadWorker::stop()
{
    if (m_serialPort) {
        delete m_serialPort;
        m_serialPort = nullptr;
    }
}

void TimerEmulThreadWorker::onReadyRead()
{
    m_timer->stop();
    auto serialPort = qobject_cast<QSerialPort*>(sender());
    if (!serialPort)
        return;
    m_buffer.append(serialPort->readAll());

    QString inhex = QString::fromLatin1(m_buffer.toHex());
    QString inHexFinal;
    for (int i = 0; i < inhex.length()/ 2; ++i) {
        inHexFinal.append("0x").append(inhex.mid(i * 2, 2)).append(" ");
    }
    emit textInform(inHexFinal);
    if (m_currentState == telemetryMode) {
        if (m_buffer.length() == 0x11) {
            m_serialPort->write("READY");
            m_currentState = sentAlgDataMode;
            m_buffer.clear();
        }
    } else if (m_currentState == sentAlgDataMode) {
        if (m_buffer.length() == 0x22) {
            m_serialPort->write("GOOD ");
            m_buffer.clear();
        }
    }



}

void TimerEmulThreadWorker::onTimeoutWaitFullPacket()
{
    m_timer->stop();

}
