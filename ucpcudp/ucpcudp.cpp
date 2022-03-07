#include "ucpcudp.h"
#include "ui_ucpcudp.h"

#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QString>

//#define IPserveur "192.168.1.150"
#define portServeur 26000

ucpcUDP::ucpcUDP(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ucpcUDP)
{
    ui->setupUi(this);
    qDebug() <<"Debut du programme"<<endl;
    MaSocket=new QUdpSocket(this);

    if (!MaSocket->bind(QHostAddress::Any, 26000))
    {
        qDebug("Impossible de créer le socket en écoute");
        exit(EXIT_FAILURE);
    }
    qDebug() <<"bind OK";

    if (!connect(MaSocket,SIGNAL(readyRead()),this,SLOT(on_Mess_a_lire())))
    {
        qDebug("Impossible de créer le slot");
        exit(EXIT_FAILURE);
    }
    qDebug() <<"Slot UDP ok";
}

ucpcUDP::~ucpcUDP()
{
    MaSocket->close();
    delete ui;
}

void ucpcUDP::on_Mess_a_lire()
{
    QHostAddress senderAddress;
    quint16 senderPort;
    QString msg;
     while (MaSocket->hasPendingDatagrams())
       {
         QByteArray datagram;
         datagram.resize(MaSocket->pendingDatagramSize());
         if (MaSocket->readDatagram(datagram.data(), datagram.size(), &senderAddress, &senderPort) == -1)
            {
             MaSocket->close();
             exit(EXIT_FAILURE);
            }
         msg = datagram.data();
         qDebug() << "Reception depuis : " << senderAddress.toString() << ':' << senderPort;
         qDebug() << "Message recu-> " << msg;
         ui->lblReception->setText(tr("Depuis -> %1:%2").arg(senderAddress.toString()).arg(senderPort));
         ui->lblEmission->setText(tr("Message recu -> \"%1\"").arg(msg));
     }
}

void ucpcUDP::on_pushButton_clicked()
{
 QByteArray datagram="2";
    if (MaSocket->writeDatagram(datagram, QHostAddress(IPserveur), portServeur) == -1)
       {
        qDebug("Émission du message modifié impossible");
        MaSocket->close();
        exit(EXIT_FAILURE);
       }
        qDebug() << "Emission du message : " << datagram.data();
}

void ucpcUDP::on_btn0_clicked()
{
    QByteArray datagram="0";
       if (MaSocket->writeDatagram(datagram, QHostAddress(IPserveur), portServeur) == -1)
          {
           qDebug("Émission du message modifié impossible");
           MaSocket->close();
           exit(EXIT_FAILURE);
          }
           qDebug() << "Emission du message : " << datagram.data();
}

void ucpcUDP::on_btn1_clicked()
{
    QByteArray datagram="1";
       if (MaSocket->writeDatagram(datagram, QHostAddress(IPserveur), portServeur) == -1)
          {
           qDebug("Émission du message modifié impossible");
           MaSocket->close();
           exit(EXIT_FAILURE);
          }
           qDebug() << "Emission du message : " << datagram.data();
}

void ucpcUDP::on_lineEdit_returnPressed()
{
    IPserveur=ui->lineEdit->text();
}
