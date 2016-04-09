#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myCom = new Posix_QextSerialPort("/dev/ttyUSB0",QextSerialBase::Polling);//定义串口对象，指名串口名和查询模式，使用polling
    myCom ->open(QIODevice::ReadWrite);     //以读写方式打开串口
    myCom->setBaudRate(BAUD115200);     //波特率设置，我们设置为115200

    myCom->setDataBits(DATA_8);     //数据位设置，我们设置为8位数据位

    myCom->setParity(PAR_NONE);     //奇偶校验设置，我们设置为无校验

    myCom->setStopBits(STOP_1);     //停止位设置，我们设置为1位停止位

    myCom->setFlowControl(FLOW_OFF);     //数据流控制设置，我们设置为无数据流控制

    myCom->setTimeout(200);   //延时设置，我们设置为延时200ms,如果设置为500ms的话，会造成程序无响应，原因未知
    readTimer = new QTimer(this);//设置读取计时器
    readTimer->start(100);//设置延时为100ms
    connect(readTimer,SIGNAL(timeout()),this,SLOT(readMyCom()));//信号和槽函数关联，当达到定时时间时，进行读串口操作

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readMyCom()
{
    QByteArray temp = myCom->readAll(); //读取串口缓冲区的所有数据给临时变量temp
    if(!temp.isEmpty())
    qDebug()<<temp;
    ui->showBrowser->insertPlainText(temp);//将串口的数据显示在窗口的文本浏览器中
}

void MainWindow::on_sendButton_clicked()
{
    myCom->write(ui->sendEdit->text().toAscii());//以ASCII码形式将数据写入串口,在Qt5中使用toLatin1
    //ui->showBrowser->insertPlainText(ui->sendEdit->text());
}
