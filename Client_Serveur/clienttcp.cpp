#include "clienttcp.h"
#include "ui_clienttcp.h"

ClientTCP::ClientTCP(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClientTCP)
{
    ui->setupUi(this);
}

ClientTCP::~ClientTCP()
{
    delete ui;
}

