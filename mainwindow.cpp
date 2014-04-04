#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "timeremulthreadworker.h"

#include <QSerialPortInfo>
#include <QThread>

const static QString openString = QString("Open");
const static QString closeString = QString("Close");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_worker(nullptr),
    m_thread(nullptr)
{
    ui->setupUi(this);
    m_thread = new QThread();
    m_worker = new TimerEmulThreadWorker();
    m_worker->moveToThread(m_thread);
    m_thread->start();
    connect(m_worker, SIGNAL(textInform(QString)),
            this, SLOT(onLog(QString)), Qt::QueuedConnection);
    connect(ui->pushButtonOpenOrClose, SIGNAL(clicked()),
            this, SLOT(onOpenOrCloseButtonPushed()));
    ui->pushButtonOpenOrClose->setText(openString);
    initSerialPortComboBoxes();
}

MainWindow::~MainWindow()
{
    QMetaObject::invokeMethod(m_worker, "deleteLater", Qt::QueuedConnection);
    m_thread->quit();
    m_thread->wait();
    delete ui;
}

void MainWindow::initSerialPortComboBoxes()
{
    for (const QSerialPortInfo &serialInfo : QSerialPortInfo::availablePorts()) {
        ui->comboBoxPortName->addItem(serialInfo.portName());
    }

    for (const int &baudrate :QSerialPortInfo::standardBaudRates()) {
        ui->comboBoxSpeed->addItem(QString::number(baudrate));
    }
    ui->comboBoxPortName->setCurrentIndex(1);
    ui->comboBoxSpeed->setCurrentIndex(9);
}

void MainWindow::onOpenOrCloseButtonPushed()
{
    bool retVal;
    QMetaObject::invokeMethod(m_worker, "start", Qt::BlockingQueuedConnection, Q_RETURN_ARG(bool, retVal), Q_ARG(QString,ui->comboBoxPortName->currentText()));
}

void MainWindow::onLog(const QString &text)
{
    static int line = 0;
    ui->textEdit->append(QString("%0: %2").arg(line++).arg(text));
}
