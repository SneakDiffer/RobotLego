#include "walldrawer.h"
#include "ui_walldrawer.h"

Walldrawer::Walldrawer(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Walldrawer)
{
    ui->setupUi(this);
}

Walldrawer::~Walldrawer()
{
    delete ui;
}
