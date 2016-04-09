#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "posix_qextserialport.h"
#include "qextserialbase.h"
#include <QDebug>

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
    Ui::MainWindow *ui;
    Posix_QextSerialPort *myCom;//串口
    QTimer *readTimer;//定时器
 private slots:
    void readMyCom();//读取串口
    void on_sendButton_clicked();//“发送数据”按钮槽函数
};

#endif // MAINWINDOW_H
