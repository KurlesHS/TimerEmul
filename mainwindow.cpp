#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "timeremulthreadworker.h"

#include <QSerialPortInfo>

const static QString openString = QString("Open");
const static QString closeString = QString("Close");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_worker(nullptr),
    m_thread(nullptr)
{
    ui->setupUi(this);
    TimerEmulThreadWorker();
    ui->pushButtonOpenOrClose->setText(openString);
    initSerialPortComboBoxes();
}

MainWindow::~MainWindow()
{
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
}

void MainWindow::onOpenOrCloseButtonPushed()
{

}
