#include "timeremulthreadworker.h"

// в этом режиме шлём телеметрию, ожидаем команды на изменение положения машинок
// и команд на запись / чтение настроек прошивки
static const int telemetryMode = 0x00;

// принимаем новые данные для алгоритма с андроида
static const int receiveAlgDataMode = 0x01;

// посылаем данные для алгоритма на андроид
static const int sentAlgDataMode = 0x02;

TimerEmulThreadWorker::TimerEmulThreadWorker(QObject *parent) :
    QObject(parent),
    m_isBusy(false)
{

}
