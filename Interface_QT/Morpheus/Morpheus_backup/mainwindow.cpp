#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtWidgets>
#include <QtNetwork>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <QTextStream>
#include <QByteArray>
#include <QList>
#include <QString>
#include <QApplication>
#include <QGraphicsView>
#include <QThread>
#include <QProcess>

#define COMPORT 4000
#define DATAPORT 3000


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    conta_pacote=0;

    ui->setupUi(this);
    ui->Plot_Window->setRenderHint(QPainter::HighQualityAntialiasing);
    ui->Plot_Window->scale(1.5,1.5);

    Address_Transmit = QHostAddress("10.0.27.67");
    Address_Receive = QHostAddress("10.0.27.52");
    Address_Multicast = QHostAddress("224.0.0.1");

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(Address_Receive,COMPORT, QUdpSocket::ShareAddress);
    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(readPendingDatagrams()));

    udpSocketimagem = new QUdpSocket(this);
    udpSocketimagem->bind(Address_Multicast,DATAPORT, QUdpSocket::ShareAddress);
    udpSocketimagem->joinMulticastGroup(Address_Multicast);
    connect(udpSocketimagem,SIGNAL(readyRead()),this,SLOT(readPendingData()));

    setWindowTitle(tr("Morpheus"));
    resize(1240, 800);

    ui->tabWidget->setCurrentIndex(0);

    read_omr();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::read_omr()
{
    QByteArray datagram = "-readomr";
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
    QThread::sleep(1);
}

void MainWindow::read_dac()
{
    QByteArray datagram = "-readdac";
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
    QThread::sleep(1);
}

void MainWindow::read_network()
{
    QByteArray datagram = "-readnetwork";
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
    QThread::sleep(1);
}

void MainWindow::on_Start_Aquire_clicked()
{
    QByteArray datagram = "-acquire 1";
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::readPendingData()
{
    while (udpSocketimagem->hasPendingDatagrams()==true) {
        data.resize(udpSocketimagem->pendingDatagramSize());
        udpSocketimagem->readDatagram(data.data(), data.size());
        data.remove(0,4);
        data=data.toHex();
        for(int a=1;a<2050;a++)
        {
            if(a%2)
            {
                data.remove(0,1);
            }
            else
            {
                str.append(data.at(0));
                data.remove(0,1);
            }
        }
        conta_pacote++;
    }
    //for(int a=0;a<65536;a++)
    //{
    //    qDebug()<<conta_pacote;
    //}

    if(conta_pacote==65)
    {
        if(str.size()==66560)
        {
            plot_image_1bit(&str);
        }
        qDebug()<<endl<<str.size()<<endl;
        conta_pacote=0;
        str.clear();
    }
}

void MainWindow::readPendingDatagrams()
{
    QByteArray payload;
    QByteArray Type;
    QList<QByteArray> byte;

    while (udpSocket->hasPendingDatagrams()) {
        payload.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(payload.data(), payload.size());
    }
    qDebug()<<payload<<endl;

    if (QString::compare(payload.data(),"Invalid Option",Qt::CaseInsensitive)==0)
    {
        qDebug()<<"Invalid Option"<<endl;
    }
    else
    {
        byte=payload.split('+');
        byte.removeFirst();
        byte.removeLast();

        Type=byte.takeFirst();

        if(QString::compare(Type.data(),"OMR",Qt::CaseInsensitive)==0)
        {
            OP=byte.takeFirst();
            Read_Write=byte.takeFirst();
            Polarity=byte.takeFirst();
            PS=byte.takeFirst();
            Disc_CSM_SPM=byte.takeFirst();
            TP=byte.takeFirst();
            Count_L=byte.takeFirst();
            byte.removeFirst();
            byte.removeFirst();
            byte.removeFirst();
            byte.removeFirst();
            Equalization=byte.takeFirst();
            Colour_Mode=byte.takeFirst();
            Pixel_Mode=byte.takeFirst();
            byte.removeFirst();
            Gain_Mode=byte.takeFirst();
            byte.removeFirst();
            byte.removeFirst();
            byte.removeFirst();
            Time=byte.takeFirst();
            NImage=byte.takeFirst();
            Gap=byte.takeFirst();
            RCount=byte.takeFirst();

            ui->Aquire_Time_Input->setText(Time);
            ui->Gap_Input->setText(Gap);
            ui->NImages_Input->setText(NImage);
            ui->Read_Counter_Input->setCurrentIndex(RCount.toInt());
            ui->Polarity_Input->setCurrentIndex(Polarity.toInt());
            ui->Colour_Mode_Input->setCurrentIndex(Colour_Mode.toInt());
            ui->Read_Write_Input->setCurrentIndex(Read_Write.toInt());
            ui->Disc_CSM_SPM_Input->setCurrentIndex(Disc_CSM_SPM.toInt());
            ui->Output_Input->setCurrentIndex(PS.toInt());
            ui->Count_L_Input->setCurrentIndex(Count_L.toInt());
            ui->Gain_Mode_Input->setCurrentIndex(Gain_Mode.toInt());
            ui->Pixel_Mode_Input->setCurrentIndex(Pixel_Mode.toInt());
        }
        else if(QString::compare(Type.data(),"DAC",Qt::CaseInsensitive)==0)
        {
            th0=byte.takeFirst();
            th1=byte.takeFirst();
            th2=byte.takeFirst();
            th3=byte.takeFirst();
            th4=byte.takeFirst();
            th5=byte.takeFirst();
            th6=byte.takeFirst();
            th7=byte.takeFirst();
            preamp=byte.takeFirst();
            ikrum=byte.takeFirst();
            shaper=byte.takeFirst();
            disc=byte.takeFirst();
            discls=byte.takeFirst();
            shapertest=byte.takeFirst();
            dacdiscl=byte.takeFirst();
            dactest=byte.takeFirst();
            dacdisch=byte.takeFirst();
            delay=byte.takeFirst();
            tpbufferin=byte.takeFirst();
            tpbufferout=byte.takeFirst();
            rpz=byte.takeFirst();
            gnd=byte.takeFirst();
            tpref=byte.takeFirst();
            fbk=byte.takeFirst();
            cas=byte.takeFirst();
            tprefa=byte.takeFirst();
            tprefb=byte.takeFirst();

            ui->TH0_Input->setText(th0);
            ui->TH1_Input->setText(th1);
            ui->TH2_Input->setText(th2);
            ui->TH3_Input->setText(th3);
            ui->TH4_Input->setText(th4);
            ui->TH5_Input->setText(th5);
            ui->TH6_Input->setText(th6);
            ui->TH7_Input->setText(th7);
            ui->IPREAMP_Input->setText(preamp);
            ui->IKRUM_Input->setText(ikrum);
            ui->ISHAPER_Input->setText(shaper);
            ui->IDISC_Input->setText(disc);
            ui->IDISCLS_Input->setText(discls);
            ui->ISHAPERTEST_Input->setText(shapertest);
            ui->IDACDISCL_Input->setText(dacdiscl);
            ui->IDAC_Test_Input->setText(dactest);
            ui->IDACDISCH_Input->setText(dacdisch);
            ui->IDELAY_Input->setText(delay);
            ui->ITPBUFFERIN_Input->setText(tpbufferin);
            ui->ITPBUFFEROUT_Input->setText(tpbufferout);
            ui->VRPZ_Input->setText(rpz);
            ui->VGND_Input->setText(gnd);
            ui->VTPREF_Input->setText(tpref);
            ui->VFBK_Input->setText(fbk);
            ui->VCAS_Input->setText(cas);
            ui->VTPREFA_Input->setText(tprefa);
            ui->VTPREFB_Input->setText(tprefb);
        }
        else if(QString::compare(Type.data(),"SEND",Qt::CaseInsensitive)==0)
        {
            Send_Ip=byte.takeFirst();
            Send_Port=byte.takeFirst();
            Send_Mac=byte.takeFirst();
            byte.removeFirst();
            Host_Ip=byte.takeFirst();
            Host_Net=byte.takeFirst();

            ui->SENDIP_Input->setText(Send_Ip);
            ui->SENDPORT_Input->setText(Send_Port);
            ui->SENDMAC_Input->setText(Send_Mac);

            ui->HOSTIP_Input->setText(Host_Ip);
            ui->HOSTNETMASK_Input->setText(Host_Net);
        }
    }
}

void MainWindow::refresh_dacs_input()
{
    ui->TH0_Input->setText(th0);
}

void MainWindow::on_Aquire_Time_Input_editingFinished()
{
    Time=ui->Aquire_Time_Input->text();
    QByteArray datagram = "-time "+ Time.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_NImages_Input_editingFinished()
{
    NImage=ui->NImages_Input->text();
    QByteArray datagram = "-frames "+ NImage.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_Gap_Input_editingFinished()
{
    Gap=ui->Gap_Input->text();
    QByteArray datagram = "-gap "+ Gap.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_Read_Counter_Input_currentIndexChanged(int index)
{
    RCount.setNum(index);
    QByteArray datagram = "-readcounter "+ RCount.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_Colour_Mode_Input_currentIndexChanged(int index)
{
    Colour_Mode.setNum(index);
    QByteArray datagram = "-colormode "+ Colour_Mode.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_Read_Write_Input_currentIndexChanged(int index)
{
    Read_Write.setNum(index);
    QByteArray datagram = "-readwrite "+ Read_Write.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_Pixel_Mode_Input_currentIndexChanged(int index)
{
    Pixel_Mode.setNum(index);
    QByteArray datagram = "-summode "+ Pixel_Mode.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_Disc_CSM_SPM_Input_currentIndexChanged(int index)
{
    Disc_CSM_SPM.setNum(index);
    QByteArray datagram = "-discsel "+ Disc_CSM_SPM.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_Output_Input_currentIndexChanged(int index)
{
    PS.setNum(index);
    QByteArray datagram = "-readports "+ PS.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_Count_L_Input_currentIndexChanged(int index)
{
    Count_L.setNum(index);
    QByteArray datagram = "-ctrange "+ Count_L.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_Gain_Mode_Input_currentIndexChanged(int index)
{
    Gain_Mode.setNum(index);
    QByteArray datagram = "-gainmode "+ Gain_Mode.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_Polarity_Input_currentIndexChanged(int index)
{
    Polarity.setNum(index);
    QByteArray datagram = "-polarity "+ Polarity.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_TH0_Input_editingFinished()
{
    th0=ui->TH0_Input->text();
    QByteArray datagram = "-dacth0 "+ th0.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_TH1_Input_editingFinished()
{
    th1=ui->TH1_Input->text();
    QByteArray datagram = "-dacth1 "+ th1.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_TH2_Input_editingFinished()
{
    th2=ui->TH2_Input->text();
    QByteArray datagram = "-dacth2 "+ th2.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_TH3_Input_editingFinished()
{
    th3=ui->TH3_Input->text();
    QByteArray datagram = "-dacth3 "+ th3.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_TH4_Input_editingFinished()
{
    th4=ui->TH4_Input->text();
    QByteArray datagram = "-dacth4 "+ th4.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_TH5_Input_editingFinished()
{
    th5=ui->TH5_Input->text();
    QByteArray datagram = "-dacth5 "+ th5.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_TH6_Input_editingFinished()
{
    th6=ui->TH6_Input->text();
    QByteArray datagram = "-dacth6 "+ th6.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_TH7_Input_editingFinished()
{
    th7=ui->TH7_Input->text();
    QByteArray datagram = "-dacth7 "+ th7.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_IPREAMP_Input_editingFinished()
{
    preamp=ui->IPREAMP_Input->text();
    QByteArray datagram = "-preamp "+ preamp.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_IKRUM_Input_editingFinished()
{
    ikrum=ui->IKRUM_Input->text();
    QByteArray datagram = "-ikrum "+ ikrum.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_ISHAPER_Input_editingFinished()
{
    shaper=ui->ISHAPER_Input->text();
    QByteArray datagram = "-shaper "+ shaper.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_IDISC_Input_editingFinished()
{
    disc=ui->IDISC_Input->text();
    QByteArray datagram = "-disc "+ disc.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_IDISCLS_Input_editingFinished()
{
    discls=ui->IDISCLS_Input->text();
    QByteArray datagram = "-discls "+ discls.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_ISHAPERTEST_Input_editingFinished()
{
    shapertest=ui->ISHAPERTEST_Input->text();
    QByteArray datagram = "-shapertest "+ shapertest.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_IDACDISCL_Input_editingFinished()
{
    dacdiscl=ui->IDACDISCL_Input->text();
    QByteArray datagram = "-dacdiscl "+ dacdiscl.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_IDAC_Test_Input_editingFinished()
{
    dactest=ui->IDAC_Test_Input->text();
    QByteArray datagram = "-dactest "+ dactest.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_IDACDISCH_Input_editingFinished()
{
    dacdisch=ui->IDACDISCH_Input->text();
    QByteArray datagram = "-dacdisch "+ dacdisch.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_IDELAY_Input_editingFinished()
{
    delay=ui->IDELAY_Input->text();
    QByteArray datagram = "-delay "+ delay.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_ITPBUFFERIN_Input_editingFinished()
{
    tpbufferin=ui->ITPBUFFERIN_Input->text();
    QByteArray datagram = "-tpbuffin "+ tpbufferin.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_ITPBUFFEROUT_Input_editingFinished()
{
    tpbufferout=ui->ITPBUFFEROUT_Input->text();
    QByteArray datagram = "-tpbuffout "+ tpbufferout.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_VRPZ_Input_editingFinished()
{
    rpz=ui->VRPZ_Input->text();
    QByteArray datagram = "-rpz "+ rpz.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_VGND_Input_editingFinished()
{
    gnd=ui->VGND_Input->text();
    QByteArray datagram = "-gnd "+ gnd.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_VTPREF_Input_editingFinished()
{
    tpref=ui->VTPREF_Input->text();
    QByteArray datagram = "-tpref "+ tpref.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_VFBK_Input_editingFinished()
{
    fbk=ui->VFBK_Input->text();
    QByteArray datagram = "-fbk "+ fbk.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_VCAS_Input_editingFinished()
{
    cas=ui->VCAS_Input->text();
    QByteArray datagram = "-cas "+ cas.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_VTPREFA_Input_editingFinished()
{
    tprefa=ui->VTPREFA_Input->text();
    QByteArray datagram = "-tprefa "+ tprefa.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_VTPREFB_Input_editingFinished()
{
    tprefb=ui->VTPREFB_Input->text();
    QByteArray datagram = "-tprefb "+ tprefb.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    switch (index)
    {
        case 0:
                read_omr();
        break;
        case 1:
                read_dac();
        break;
        case 2:

        break;
        case 3:
                read_network();
        break;
        case 4:

        break;
        default:
        break;
    }
}

void MainWindow::plot_image_1bit(QList<char> *pixelmap_1bit)
{
    scene= new QGraphicsScene(this);
    ui->Plot_Window->setScene(scene);
    int linha,coluna;
    QPen blackpen(Qt::red);

    for (int bit=1;bit<65536;bit++)
    {
        if(bit==1)
        {
            linha=1;
            coluna=1;
        }
        else if(bit%256==0)
        {
            linha++;
            coluna=1;
        }
        else
        {
            coluna++;
        }
        //qDebug()<<"linha "<<linha<<"coluna "<<coluna;
        if(pixelmap_1bit->at(bit)=='1')
        {
            //qDebug()<<"bit "<<bit<<"pixel "<<pixelmap_1bit->at(bit);
            lineview = scene->addLine(linha,coluna,linha,coluna,blackpen);
        }
    }
}

void MainWindow::on_Send_Eq_clicked()
{
    QString program = "/home/franz/altera/www/send_eq";
    QStringList arguments;

    QProcess *myProcess = new QProcess(this);
    myProcess->execute(program,arguments);
    QThread::sleep(1);
    //qDebug()<<myProcess->state();//start
}

void MainWindow::on_HOSTIP_Input_editingFinished()
{
    Host_Ip=ui->HOSTIP_Input->text();
    QByteArray datagram = "-host_ip "+ Host_Ip.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_HOSTNETMASK_Input_editingFinished()
{
    Host_Net=ui->HOSTNETMASK_Input->text();
    QByteArray datagram = "-host_net "+ Host_Net.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_SENDIP_Input_editingFinished()
{
    Send_Ip=ui->SENDIP_Input->text();
    QByteArray datagram = "-send_ip "+ Send_Ip.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_SENDPORT_Input_editingFinished()
{
    Send_Port=ui->SENDPORT_Input->text();
    QByteArray datagram = "-send_port "+ Send_Port.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}

void MainWindow::on_SENDMAC_Input_editingFinished()
{
    Send_Mac=ui->SENDMAC_Input->text();
    QByteArray datagram = "-send_mac "+ Send_Mac.toUtf8();
    udpSocket->writeDatagram(datagram.data(),datagram.size(),Address_Transmit, COMPORT);
}
