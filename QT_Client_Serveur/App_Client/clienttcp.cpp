#include "clienttcp.h"
#include "ui_clienttcp.h"

ClientTcp::ClientTcp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClientTcp)
{
    ui->setupUi(this);
}

ClientTcp::~ClientTcp()
{
    delete ui;
}

