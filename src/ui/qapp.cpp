#include "qapp.h"
#include "ui_qapp.h"

QApp::QApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QApp)
{
    ui->setupUi(this);
}

QApp::~QApp()
{
    delete ui;
}
