#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtWidgets>
#include <QtNetwork>
#include <QTextStream>
#include <QtCore/qmath.h>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    nam = new QNetworkAccessManager(this);
    connect(nam,SIGNAL(finished(QNetworkReply*)),this,SLOT(finished(QNetworkReply*)));
    //connect(&teste1,SIGNAL(valuechanged(QDir)),&teste2,SLOT(setvalue(QDir)));

    ui->Plot_Window->setRenderHint(QPainter::Antialiasing);
    ui->Plot_Window->scale(1.0,1.0);

    setWindowTitle(tr("Morpheus"));
    resize(1000, 780);

    ui->tabWidget->setCurrentIndex(0);
    read_omr();

    Current_Dir = QDir::currentPath();
    Current_Path=Current_Dir.path();
    Save_Dir=Save_Dir;
    Save_Path=Current_Path;
    ui->Path_Input->setText(Save_Path);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setvalue(QDir value)
{
    emit valuechanged(value);
}

void MainWindow::finished(QNetworkReply *reply)
{
    QString buffer;
    QStringList list1;
    QStringList temp;

    if(reply->error() == QNetworkReply::NoError)
    {
        buffer=reply->readAll();
        if(buffer.size()>1)
        {
            ui->textBrowser->setText(buffer);
        }
        list1=buffer.split("!#", QString::SkipEmptyParts);

        if (list1.count()==20)
        {
            temp=list1.at(0).split("=");
            OP=temp.at(1);
            temp=list1.at(1).split("=");
            Read_Write=temp.at(1);
            temp=list1.at(2).split("=");
            Polarity=temp.at(1);
            temp=list1.at(4).split("=");
            Disc_CSM_SPM=temp.at(1);
            temp=list1.at(5).split("=");
            TP=temp.at(1);
            temp=list1.at(6).split("=");
            Count_L=temp.at(1);
            temp=list1.at(11).split("=");
            Equalization=temp.at(1);
            temp=list1.at(12).split("=");
            Colour_Mode=temp.at(1);
            temp=list1.at(13).split("=");
            Pixel_Mode=temp.at(1);
            temp=list1.at(15).split("=");
            Gain_Mode=temp.at(1);
            temp=list1.at(16).split("=");
            Time=temp.at(1);
            temp=list1.at(17).split("=");
            NImage=temp.at(1);
            temp=list1.at(18).split("=");
            Gap=temp.at(1);
            temp=list1.at(19).split("=");
            RCount=temp.at(1);

            ui->Aquire_Time_Input->setText(Time);
            ui->Gap_Input->setText(Gap);
            ui->NImages_Input->setText(NImage);
            ui->Read_Counter_Input->setCurrentIndex(RCount.toInt());
            ui->Polarity_Input->setCurrentIndex(Polarity.toInt());
            ui->Colour_Mode_Input->setCurrentIndex(Colour_Mode.toInt());
            ui->Read_Write_Input->setCurrentIndex(Read_Write.toInt());
            ui->Disc_CSM_SPM_Input->setCurrentIndex(Disc_CSM_SPM.toInt());
            ui->Count_L_Input->setCurrentIndex(Count_L.toInt());
            ui->Gain_Mode_Input->setCurrentIndex(Gain_Mode.toInt());
            ui->Pixel_Mode_Input->setCurrentIndex(Pixel_Mode.toInt());
        }
        else if(list1.count()==28)
        {
            temp=list1.at(1).split("=");
            th0=temp.at(1);
            temp=list1.at(2).split("=");
            th1=temp.at(1);
            temp=list1.at(3).split("=");
            th2=temp.at(1);
            temp=list1.at(4).split("=");
            th3=temp.at(1);
            temp=list1.at(5).split("=");
            th4=temp.at(1);
            temp=list1.at(6).split("=");
            th5=temp.at(1);
            temp=list1.at(7).split("=");
            th6=temp.at(1);
            temp=list1.at(8).split("=");
            th7=temp.at(1);
            temp=list1.at(9).split("=");
            preamp=temp.at(1);
            temp=list1.at(10).split("=");
            ikrum=temp.at(1);
            temp=list1.at(11).split("=");
            shaper=temp.at(1);
            temp=list1.at(12).split("=");
            disc=temp.at(1);
            temp=list1.at(13).split("=");
            discls=temp.at(1);
            temp=list1.at(14).split("=");
            shapertest=temp.at(1);
            temp=list1.at(15).split("=");
            dacdiscl=temp.at(1);
            temp=list1.at(16).split("=");
            dactest=temp.at(1);
            temp=list1.at(17).split("=");
            dacdisch=temp.at(1);
            temp=list1.at(18).split("=");
            delay=temp.at(1);
            temp=list1.at(19).split("=");
            tpbufferin=temp.at(1);
            temp=list1.at(20).split("=");
            tpbufferout=temp.at(1);
            temp=list1.at(21).split("=");
            rpz=temp.at(1);
            temp=list1.at(22).split("=");
            gnd=temp.at(1);
            temp=list1.at(23).split("=");
            tpref=temp.at(1);
            temp=list1.at(24).split("=");
            fbk=temp.at(1);
            temp=list1.at(25).split("=");
            cas=temp.at(1);
            temp=list1.at(26).split("=");
            tprefa=temp.at(1);
            temp=list1.at(27).split("=");
            tprefb=temp.at(1);

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
        else if(list1.count()==4)
        {
            temp=list1.at(0).split("=");
            Host_Ip=temp.at(1);
            temp=list1.at(1).split("=");
            Host_Net=temp.at(1);

            ui->HOSTIP_Input->setText(Host_Ip);
            ui->HOSTNETMASK_Input->setText(Host_Net);
        }
        else if(list1.count()==3)
        {
            temp=list1.at(0).split("=");
            Send_Ip=temp.at(1);
            temp=list1.at(1).split("=");
            Send_Port=temp.at(1);
            temp=list1.at(2).split("=");
            Send_Mac=temp.at(1);

            ui->SENDIP_Input->setText(Send_Ip);
            ui->SENDPORT_Input->setText(Send_Port);
            ui->SENDMAC_Input->setText(Send_Mac);
        }
    }
    else
    {
        ui->textBrowser->setText(reply->errorString());
    }
}

void MainWindow::read_omr()
{
    QString url = "http://10.0.27.67/cgi-bin/omr.cgi?read";
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::read_dac()
{
    QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?read";
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::read_host()
{
    QString url = "http://10.0.27.67/cgi-bin/host_setup.cgi?read";
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::read_send()
{
    QString url = "http://10.0.27.67/cgi-bin/tx_setup.cgi?read";
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_Start_Aquire_clicked()
{
    QString url = "http://10.0.27.67/cgi-bin/omr.cgi?opmode=0&write";
    nam->get(QNetworkRequest(QUrl(url)));
    start_pserve();
}

void MainWindow::start_pserve()
{
    QStringList arguments_pserve;
    process_pserve = Current_Path+"/pserve";
    arguments_pserve<<Count_L<<NImage<<Save_Path;
    myProcess = new QProcess(this);
    myProcess->start(process_pserve,arguments_pserve);
    myProcess->waitForStarted();
    //qDebug()<<"start "<<myProcess->state()<<"pid "<<myProcess->pid();
    if(Count_L.toInt()==0)
    {
        myProcess->waitForFinished((Time.toFloat()*1000)+500);
    }
    else if(Count_L.toInt()==1)
    {
        myProcess->waitForFinished((Time.toFloat()*1000)+1000);
    }
    else if(Count_L.toInt()==2)
    {
        myProcess->waitForFinished((Time.toFloat()*1000)+500);
    }
    else if(Count_L.toInt()==3)
    {
        myProcess->waitForFinished((Time.toFloat()*1000)+1500);
    }
    QByteArray text_response=myProcess->readAll();
    QString mystr(text_response);
    ui->textBrowser->setText(mystr);
    myProcess->kill();
    myProcess->close();

    Save_Dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    Save_Dir.setSorting(QDir::Time);

//    QString image1;

//    if(NImage.toInt()==1)
//    {
//            do
//            {
//                QFileInfoList list = Save_Dir.entryInfoList();
//                QFileInfo fileinfo = list.at(0);
//                //qDebug()<<QString("%1 %2").arg(fileinfo.fileName()).arg(fileinfo.size());
//                image1 = fileinfo.fileName();
//                QThread::msleep(1);
//            } while(image1.endsWith(".ppm",Qt::CaseSensitive)==false);
//    }
//    else
//    {
//        do
//            {
//                QFileInfoList list = Save_Dir.entryInfoList();
//                QFileInfo fileinfo = list.at(0);
//                image1 = fileinfo.fileName();
//                QThread::msleep(1);
//            } while(image1.endsWith(".ppm",Qt::CaseSensitive)==false);
//    }

    QPixmap pixmap;

    if(Count_L.toInt()==0) // 1 bit
    {
        QImage image(256,256,QImage::Format_Indexed8);
        image.load(Save_Path+"1.ppm","pbm");
        image.invertPixels();
        pixmap = QPixmap::fromImage(image,Qt::ColorOnly);
        //image.save(Save_Path+"sdf.pbm","pbm");
    }
    else if(Count_L.toInt()==1) // 12 bits
    {
        QImage image(256,256,QImage::Format_Indexed8);
        image.load(Save_Path+"1.ppm","pgm");
        QVector<QRgb> colortable;
        Lookup_Tables ctable;
        colortable=ctable.colorPalete256();
        image.setColorTable(colortable);
        qDebug()<<colortable.count();
        pixmap = QPixmap::fromImage(image,Qt::ColorOnly);
        //image.save(Save_Path+"sdf.ppm","ppm");
    }
    else if(Count_L.toInt()==2) // 6 bits
    {
        QImage image(256,256,QImage::Format_Indexed8);
        image.load(Save_Path+"1.ppm","pgm");
        QVector<QRgb> colortable;
        Lookup_Tables ctable;
        colortable=ctable.colorPalete64();
        image.setColorTable(colortable);
        pixmap = QPixmap::fromImage(image,Qt::ColorOnly);
        //image.save(Save_Path+"sdf.pgm","pgm");
    }
    else if(Count_L.toInt()==3) // 24 bits
    {
        QImage image(256,256,QImage::Format_RGB32);
        //montando uma imagem usando bytearray
        QByteArray teste;
        QFile filestr(Save_Path+"1.ppm");
        filestr.open(QIODevice::ReadOnly);
        teste=filestr.readAll();
        QString colorstr(teste);
        QStringList colors = colorstr.split(QRegExp("\\s+"));
        colors.removeLast();
        colors.removeFirst();
        colors.removeFirst();
        colors.removeFirst();
        colors.removeFirst();

        QVector<QRgb> colortable;
        Lookup_Tables ctable;
        colortable=ctable.colorPalete512();
        image.setColorTable(colortable);
        int cont=0;
        for(int a=0;a<=255;a++)
        {
            for(int b=0;b<=255;b++)
            {
                if(qCeil(colors.at(cont).toInt()/100)>=1280)
                {
                    image.setPixel(b,a, image.colorTable().at(1279));
                }
                else
                {
                    image.setPixel(b,a, image.colorTable().at(qCeil(colors.at(cont).toUInt()/100)));
                }
                cont++;
            }
        }
        pixmap = QPixmap::fromImage(image,Qt::ColorOnly);
    }

    scene= new QGraphicsScene(this);
    ui->Plot_Window->setScene(scene);
    pixview = scene->addPixmap(pixmap);
}

void MainWindow::on_Aquire_Time_Input_editingFinished()
{
    Time=ui->Aquire_Time_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/omr.cgi?opmode=7&aqtime=";
    url.append(ui->Aquire_Time_Input->text()+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_NImages_Input_editingFinished()
{
    NImage=ui->NImages_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/omr.cgi?opmode=7&aqcount=";
    url.append(ui->NImages_Input->text()+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_Gap_Input_editingFinished()
{
    Gap=ui->Gap_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/omr.cgi?opmode=7&aqgap=";
    url.append(ui->Gap_Input->text()+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_Read_Counter_Input_currentIndexChanged(int index)
{
    RCount.setNum(index);
    QString url = "http://10.0.27.67/cgi-bin/omr.cgi?opmode=7&readcount=";
    url.append(QString::number(index)+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_Colour_Mode_Input_currentIndexChanged(int index)
{
    Colour_Mode.setNum(index);
    QString url = "http://10.0.27.67/cgi-bin/omr.cgi?opmode=7&colourmode=";
    url.append(QString::number(index)+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_Read_Write_Input_currentIndexChanged(int index)
{
    Read_Write.setNum(index);
    QString url = "http://10.0.27.67/cgi-bin/omr.cgi?opmode=7&crw_srw=";
    url.append(QString::number(index)+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_Pixel_Mode_Input_currentIndexChanged(int index)
{
    Pixel_Mode.setNum(index);
    QString url = "http://10.0.27.67/cgi-bin/omr.cgi?opmode=7&csm_spm=";
    url.append(QString::number(index)+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_Disc_CSM_SPM_Input_currentIndexChanged(int index)
{
    Disc_CSM_SPM.setNum(index);
    QString url = "http://10.0.27.67/cgi-bin/omr.cgi?opmode=7&disc_csm_spm=";
    url.append(QString::number(index)+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_Count_L_Input_currentIndexChanged(int index)
{
    Count_L.setNum(index);
    QString url = "http://10.0.27.67/cgi-bin/omr.cgi?opmode=7&count_l=";
    url.append(QString::number(index)+"&write");
    nam->get(QNetworkRequest(QUrl(url)));


    if(Count_L.toInt()==0)
    {
        uchar color_bar_row[2];
        color_bar_row[0]=1;
        color_bar_row[1]=0;

        QImage image_color_bar(color_bar_row,1,2,QImage::Format_Mono);
        QPixmap pixmap_bar = QPixmap::fromImage(image_color_bar,Qt::AutoColor);
        pixmap_bar = pixmap_bar.scaled(15,256);

        scene_table= new QGraphicsScene(this);
        ui->color_table_bar->setRenderHint(QPainter::Antialiasing);
        ui->color_table_bar->setScene(scene_table);
        pixview2 = scene_table->addPixmap(pixmap_bar);
    }
    else if(Count_L.toInt()==1) // 12 bits
    {
        uchar color_bar_row[5120];
        int cont=0;
        for(int b=0;b<=255;b++)
        {
            for(int a=0;a<=14;a++)
            {
                color_bar_row[cont]=255-b;
                cont++;
            }
        }
        QImage image_color_bar(color_bar_row, 15, 240, QImage::Format_Indexed8);
        image_color_bar.setColorCount(256);
        QVector<QRgb> colortable;
        Lookup_Tables ctable;
        colortable=ctable.colorPalete256();
        image_color_bar.setColorTable(colortable);
        QPixmap pixmap_bar = QPixmap::fromImage(image_color_bar,Qt::ColorOnly);
        pixmap_bar = pixmap_bar.scaled(15,256);

        scene_table= new QGraphicsScene(this);
        ui->color_table_bar->setRenderHint(QPainter::Antialiasing);
        ui->color_table_bar->setScene(scene_table);
        pixview2 = scene_table->addPixmap(pixmap_bar);
    }
    else if(Count_L.toInt()==2) // 6 bits
    {
        int color_bar_row[64];
        for(int b=0;b<=63;b++)
        {
            color_bar_row[b]=63-b;
        }
        QImage image_color_bar(1,64,QImage::Format_RGB16);
        QVector<QRgb> colortable;
        Lookup_Tables ctable;
        colortable=ctable.colorPalete64();
        image_color_bar.setColorTable(colortable);
        for(int a=0;a<=63;a++)
        {
            image_color_bar.setPixel(0,a,colortable.at(color_bar_row[a]));
        }

        QPixmap pixmap_bar = QPixmap::fromImage(image_color_bar,Qt::ColorOnly);
        pixmap_bar = pixmap_bar.scaled(15,256);

        scene_table= new QGraphicsScene(this);
        ui->color_table_bar->setRenderHint(QPainter::Antialiasing);
        ui->color_table_bar->setScene(scene_table);
        pixview2 = scene_table->addPixmap(pixmap_bar);
    }
    else if(Count_L.toInt()==3) // 24 bits
    {
        QImage image_color_bar(1, 1280, QImage::Format_RGB32);
        image_color_bar.setColorCount(1280);
        QVector<QRgb> colortable;
        Lookup_Tables ctable;
        colortable=ctable.colorPalete512();
        image_color_bar.setColorTable(colortable);
        int color_bar_row[1280];
        for(int a=0;a<=1279;a++)
        {
            color_bar_row[a]=1279-a;
        }
        for(int a=0;a<=1279;a++)
        {
            image_color_bar.setPixel(0,a,colortable.at(color_bar_row[a]));
        }
        QPixmap pixmap_bar = QPixmap::fromImage(image_color_bar,Qt::ColorOnly);
        pixmap_bar = pixmap_bar.scaled(15,256);

        scene_table= new QGraphicsScene(this);
        ui->color_table_bar->setRenderHint(QPainter::Antialiasing);
        ui->color_table_bar->setScene(scene_table);
        pixview2 = scene_table->addPixmap(pixmap_bar);
    }
}

void MainWindow::on_Gain_Mode_Input_currentIndexChanged(int index)
{
    Gain_Mode.setNum(index);
    QString url = "http://10.0.27.67/cgi-bin/omr.cgi?opmode=7&gainmode=";
    url.append(QString::number(index)+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_Polarity_Input_currentIndexChanged(int index)
{
    Polarity.setNum(index);
    QString url = "http://10.0.27.67/cgi-bin/omr.cgi?opmode=7&pol=";
    url.append(QString::number(index)+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_TH0_Input_editingFinished()
{
    th0=ui->TH0_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&threshold_0=";
    url.append(ui->TH0_Input->text()+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_TH1_Input_editingFinished()
{
    th1=ui->TH1_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&threshold_1=";
    url.append(ui->TH1_Input->text()+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_TH2_Input_editingFinished()
{
    th2=ui->TH2_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&threshold_2=";
    url.append(ui->TH2_Input->text()+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_TH3_Input_editingFinished()
{
    th3=ui->TH3_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&threshold_3=";
    url.append(ui->TH3_Input->text()+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_TH4_Input_editingFinished()
{
    th4=ui->TH4_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&threshold_4=";
    url.append(ui->TH4_Input->text()+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_TH5_Input_editingFinished()
{
    th5=ui->TH5_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&threshold_5=";
    url.append(ui->TH5_Input->text()+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_TH6_Input_editingFinished()
{
    th6=ui->TH6_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&threshold_6=";
    url.append(ui->TH6_Input->text()+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_TH7_Input_editingFinished()
{
    th7=ui->TH7_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&threshold_7=";
    url.append(ui->TH7_Input->text()+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_IPREAMP_Input_editingFinished()
{
    preamp=ui->IPREAMP_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&preamp=";
    url.append(ui->IPREAMP_Input->text()+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_IKRUM_Input_editingFinished()
{
    ikrum=ui->IKRUM_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&ikrum=";
    url.append(ui->IKRUM_Input->text()+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_ISHAPER_Input_editingFinished()
{
    shaper=ui->ISHAPER_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&shaper=";
    url.append(ui->ISHAPER_Input->text()+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_IDISC_Input_editingFinished()
{
    disc=ui->IDISC_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&disc=";
    url.append(ui->IDISC_Input->text()+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_IDISCLS_Input_editingFinished()
{
    discls=ui->IDISCLS_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&discls=";
    url.append(ui->IDISCLS_Input->text()+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_ISHAPERTEST_Input_editingFinished()
{
    shapertest=ui->ISHAPERTEST_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&shaper_test=";
    url.append(ui->ISHAPERTEST_Input->text()+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_IDACDISCL_Input_editingFinished()
{
    dacdiscl=ui->IDACDISCL_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&dac_discl=";
    url.append(ui->IDACDISCL_Input->text()+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_IDAC_Test_Input_editingFinished()
{
    dactest=ui->IDAC_Test_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&dac_test=";
    url.append(ui->IDAC_Test_Input->text()+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_IDACDISCH_Input_editingFinished()
{
    dacdisch=ui->IDACDISCH_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&dac_disch=";
    url.append(ui->IDACDISCH_Input->text()+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_IDELAY_Input_editingFinished()
{
    delay=ui->IDELAY_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&delay=";
    url.append(ui->IDELAY_Input->text()+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_ITPBUFFERIN_Input_editingFinished()
{
    tpbufferin=ui->ITPBUFFERIN_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&tp_bufferin=";
    url.append(ui->ITPBUFFERIN_Input->text()+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_ITPBUFFEROUT_Input_editingFinished()
{
    tpbufferout=ui->ITPBUFFEROUT_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&tp_bufferout=";
    url.append(ui->ITPBUFFEROUT_Input->text()+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_VRPZ_Input_editingFinished()
{
    rpz=ui->VRPZ_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&rpz=";
    url.append(ui->VRPZ_Input->text()+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_VGND_Input_editingFinished()
{
    gnd=ui->VGND_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&gnd=";
    url.append(ui->VGND_Input->text()+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_VTPREF_Input_editingFinished()
{
    tpref=ui->VTPREF_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&tp_ref=";
    url.append(ui->VTPREF_Input->text()+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_VFBK_Input_editingFinished()
{
    fbk=ui->VFBK_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&fbk=";
    url.append(ui->VFBK_Input->text()+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_VCAS_Input_editingFinished()
{
    cas=ui->VCAS_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&cas=";
    url.append(ui->VCAS_Input->text()+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_VTPREFA_Input_editingFinished()
{
    tprefa=ui->VTPREFA_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&tp_refa=";
    url.append(ui->VTPREFA_Input->text()+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_VTPREFB_Input_editingFinished()
{
    tprefb=ui->VTPREFB_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&tp_refb=";
    url.append(ui->VTPREFB_Input->text()+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
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

        break;
        case 4:
                read_host();
                read_send();
        break;
        case 5:

        break;
        default:
        break;
    }
}

void MainWindow::on_Send_Eq_clicked()
{
    QString program = Current_Path+"/send_eq";
    QStringList arguments;

    myProcess = new QProcess(this);
    myProcess->start(program,arguments);
    myProcess->waitForStarted();
    //qDebug()<<"start "<<myProcess->state()<<"pid "<<myProcess->pid();
    myProcess->waitForFinished();
    myProcess->kill();
    myProcess->close();
    ui->textBrowser->setText("!#SUCCESS=Send Equalize!#");
    QThread::msleep(1);
}

void MainWindow::on_HOSTIP_Input_editingFinished()
{
    Host_Ip=ui->HOSTIP_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/host_setup.cgi?ip_address=";
    url.append(Host_Ip+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_HOSTNETMASK_Input_editingFinished()
{
    Host_Net=ui->HOSTNETMASK_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/host_setup.cgi?netmask=";
    url.append(Host_Net+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_SENDIP_Input_editingFinished()
{
    Send_Ip=ui->SENDIP_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/tx_setup.cgi?ip_tx_address=";
    url.append(Send_Ip+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_SENDPORT_Input_editingFinished()
{
    Send_Port=ui->SENDPORT_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/tx_setup.cgi?port=";
    url.append(Send_Port+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_SENDMAC_Input_editingFinished()
{
    Send_Mac=ui->SENDMAC_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/tx_setup.cgi?mac=";
    url.append(Send_Mac+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_Stop_Aquire_clicked()
{
    myProcess->close();
}

void MainWindow::on_Path_Input_editingFinished()
{
    QStringList list;
    QString temp_path;

    Save_Path=ui->Path_Input->text();
    list=Save_Path.split("/");
    list.removeFirst();
    for(int a=0;a<(list.count()-1);a++)
    {
        temp_path.append("/"+list.at(a));
        Image_Name = list.at(a+1);
    }
    Save_Dir = temp_path;
}
