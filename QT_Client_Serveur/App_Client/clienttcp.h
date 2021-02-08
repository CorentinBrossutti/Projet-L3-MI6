#ifndef CLIENTTCP_H
#define CLIENTTCP_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ClientTcp; }
QT_END_NAMESPACE

class ClientTcp : public QMainWindow
{
    Q_OBJECT

public:
    ClientTcp(QWidget *parent = nullptr);
    ~ClientTcp();

private:
    Ui::ClientTcp *ui;
};
#endif // CLIENTTCP_H
