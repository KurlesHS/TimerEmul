#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class TimerEmulThreadWorker;
class QThread;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void initSerialPortComboBoxes();

private Q_SLOTS:
    void onOpenOrCloseButtonPushed();

private:
    Ui::MainWindow *ui;
    TimerEmulThreadWorker *m_worker;
    QThread *m_thread;
};

#endif // MAINWINDOW_H
