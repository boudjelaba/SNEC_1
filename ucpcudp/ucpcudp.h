#ifndef UCPCUDP_H
#define UCPCUDP_H

#include <QMainWindow>
#include <QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class ucpcUDP; }
QT_END_NAMESPACE

class ucpcUDP : public QMainWindow
{
    Q_OBJECT

public:
    ucpcUDP(QWidget *parent = nullptr);
    ~ucpcUDP();

public slots:
    void on_Mess_a_lire();
    void on_pushButton_clicked();

private slots:
    void on_btn0_clicked();

    void on_btn1_clicked();

    void on_lineEdit_returnPressed();

private:
    Ui::ucpcUDP *ui;
    QUdpSocket  *MaSocket;
    QString IPserveur="192.168.1.150";

};
#endif // UCPCUDP_H
