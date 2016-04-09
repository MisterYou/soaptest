#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),http(this) ,
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&http, SIGNAL(responseReady()), SLOT(getResponse()));
    connect(ui->RequestStock, SIGNAL(clicked()), SLOT(submitRequest()));
    http.setAction("http://WebXml.com.cn/getStockInfoByCode/");// 设置SOAPACTION
    http.setHost("webxml.com.cn");// 设置HOST
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::submitRequest()
{

    if (ui->idline->text() == "") {
          QMessageBox::warning(this, tr("Missing Stock ID"),
              tr("Please Enter the Stock ID for query"));
          return;
      }
    QtSoapMessage request;
     request.setMethod(QtSoapQName("getStockInfoByCode", "http://WebXml.com.cn/"));// 设置方法和所在命名空
      request.addMethodArgument("theStockCode", "", ui->idline->text()); // 设置方法的参数
        http.submitRequest(request, "/WebServices/ChinaStockWebService.asmx"); //设置POST字段
        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));


}

void MainWindow::getResponse()
{
    int i;
    QApplication::restoreOverrideCursor();
    ui->stockResult->clear();
     const QtSoapMessage &resp = http.getResponse();
     if (resp.isFault()) {
             ui->stockResult->setText((resp.faultString().value().toString()));
             return;
         }
     const QtSoapType &res = resp.returnValue();
         if (!res.isValid()) {
             ui->stockResult->append("Invalid return value");
             return;
         }

         ui->stockResult->setText(res[0].toString());



}
