/*CPP FILE
---------------------------------------------------------------------------------------------------
--!@brief mainwindow.cpp
---------------------------------------------------------------------------------------------------
--! DESCRIPTION:
--!
--! Codigo fonte principal da ui
--!
--!
--! DETAILS:
--!
--!- Project Name: mainwindow
--!- Module Name: mainwindow.cpp
--!- Tools: Qt Creator
--!- Author: Franz Wagner
--!- Company: LABORATORIO NACIONAL DE LUZ SINCROTRON - GRUPO DETECTORES
--!- Create Date: 25/02/2015
--!- Version: 1.0.0 (mar/2015)
---------------------------------------------------------------------------------------------------
-- LNLS - DET - 2015
---------------------------------------------------------------------------------------------------
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"

// Image
QImage image1b(256,256,QImage::Format_Indexed8);
QImage image6b(256,256,QImage::Format_Indexed8);
QImage image12b(256,256,QImage::Format_RGB16);
QImage image24b(256,256,QImage::Format_RGB32);

/**************************************************************************************************
*   Construtor
**************************************************************************************************/
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    nam = new QNetworkAccessManager(this);
    connect(nam,SIGNAL(finished(QNetworkReply*)),this,SLOT(finished(QNetworkReply*)));
    setWindowTitle(tr("Morpheus"));
    resize(1290, 850);

    ui->tabWidget->setCurrentIndex(0);
    read_omr();

    Current_Dir = QDir::currentPath();
    Current_Path=Current_Dir.path();
    Save_Path=Current_Path;
    ui->Path_Input->setText(Save_Path);
    ui->Plot_Window->setMouseTracking(true);

    Scan_From=QString::number(200);
    Scan_To=QString::number(0);
    Scan_Step=QString::number(5);
    Scan_TH=QString::number(0);

    for(int a=0;a<=65535;a++)
    {
        Equalizacao_MASK.append("0");
        Equalizacao_TEST.append("0");
        Equalizacao_THH.append("0");
        Equalizacao_THH.append("0");
        Equalizacao_THL.append("0");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
/**************************************************************************************************
*   recebe resposta do socket http e printa no ui
**************************************************************************************************/
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
            QStringList teste;
            teste=buffer.split("!#");
            teste.removeLast();
            teste.removeFirst();
            QString receive_info;
            receive_info.append("Medipix Response :\n");
            for(int a=0;a<teste.size();a++)
            {
                receive_info.append(teste.at(a)+"\n");
            }
            ui->textBrowser->setText(receive_info);
        }
        list1=buffer.split("!#", QString::SkipEmptyParts);
        /**************************************************************************************************
        *   atualiza variaveis da omr e atualiza o ui
        **************************************************************************************************/
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
        /**************************************************************************************************
        *   atualiza variaveis das dacs e atualiza o ui
        **************************************************************************************************/
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
        /**************************************************************************************************
        *   atualiza variaveis do host e atualiza o ui
        **************************************************************************************************/
        else if(list1.count()==4)
        {
            temp=list1.at(0).split("=");
            Host_Ip=temp.at(1);
            temp=list1.at(1).split("=");
            Host_Net=temp.at(1);
            temp=list1.at(2).split("=");
            Host_Gate=temp.at(1);

            ui->HOSTIP_Input->setText(Host_Ip);
            ui->HOSTNETMASK_Input->setText(Host_Net);
            ui->HOSTGATEWAY_Input->setText(Host_Gate);
        }
        /**************************************************************************************************
        *   atualiza variaveis do send ip da imagem e atualiza o ui
        **************************************************************************************************/
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
    ui->textBrowser->setText("Acquiring....");
    start_pserve();
}
/**************************************************************************************************
*   open image
**************************************************************************************************/
void MainWindow::open_image()
{
    contagem=0;
    pixeis_lidos=0;
    float contagem_anterior;

    Save_Dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    Save_Dir.setSorting(QDir::Time);
    QFileInfoList list = Save_Dir.entryInfoList();
    QFileInfo fileinfo = list.at(0);
    QString Last_Arq = fileinfo.fileName();
    QRegExp valid("*.ppm");
    valid.setPatternSyntax(QRegExp::Wildcard);
    QString Curr_Open_Img(Save_Dir.path());
    if(valid.exactMatch(Last_Arq)==true)
    {
        Curr_Open_Img.append("/"+Last_Arq);
        if(Count_L.toInt()==0) // 1 bit
        {
            contagem=0;
            pixeis_lidos=0;
            if(image1b.load(Curr_Open_Img,"pbm")==true)
            {
                image1b.invertPixels();
                qDebug()<<image1b.size();
                for(int a=0;a<=255;a++)
                {
                    for(int b=0;b<=255;b++)
                    {
                        contagem=contagem+(1-image1b.pixelIndex(b,a));
                        pixeis_lidos=contagem;
                    }
                }
            }
            else
            {
                image1b.fill(Qt::black);
                ui->textBrowser->setText("Error Reading Image!!!");
            }
            pixmap = QPixmap::fromImage(image1b,Qt::ColorOnly);
        }
        else if(Count_L.toInt()==1) // 12 bits
        {
            contagem=0;
            pixeis_lidos=0;
            QByteArray teste;
            QFile filestr(Curr_Open_Img);
            if(filestr.open(QIODevice::ReadOnly)==true)
            {
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
                colortable=ctable.colorPalete1280();
                image12b.setColorTable(colortable);
                int cont=0;
                for(int a=0;a<=255;a++)
                {
                    for(int b=0;b<=255;b++)
                    {
                        contagem_anterior=contagem;
                        if(colors.at(cont).toInt()>=Max_Pixel_Value.toInt())
                        {
                            image12b.setPixel(b,a, image12b.colorTable().at(1279));
                        }
                        else
                        {
                            image12b.setPixel(b,a, image12b.colorTable().at(qCeil(colors.at(cont).toUInt()/3.201)));
                            contagem=contagem+colors.at(cont).toFloat();
                        }
                        cont++;
                        if(contagem_anterior!=contagem)
                        {
                            pixeis_lidos++;
                        }
                    }
                }
            }
            else
            {
                image12b.fill(Qt::black);
                ui->textBrowser->setText("Error Reading Image!!!");
            }
            pixmap = QPixmap::fromImage(image12b,Qt::ColorOnly);
        }
        else if(Count_L.toInt()==2) // 6 bits
        {
            contagem=0;
            pixeis_lidos=0;
            if(image6b.load(Curr_Open_Img,"pbm")==true)
            {
                QVector<QRgb> colortable;
                Lookup_Tables ctable;
                colortable=ctable.colorPalete64();
                image6b.setColorTable(colortable);
            }
            else
            {
                image6b.fill(Qt::black);
                ui->textBrowser->setText("Error Reading Image!!!");
            }

            for(int a=0;a<=255;a++)
            {
                for(int b=0;b<=255;b++)
                {
                    contagem_anterior=contagem;
                    if(image6b.pixelIndex(b,a)>=Max_Pixel_Value.toInt())
                    {
                        image6b.setPixel(b,a,63);
                    }
                    else
                    {
                        contagem=contagem+image6b.pixelIndex(b,a);
                    }
                    if(contagem_anterior!=contagem)
                    {
                        pixeis_lidos++;
                    }
                }
            }
            pixmap = QPixmap::fromImage(image6b,Qt::ColorOnly);
        }
        else if(Count_L.toInt()==3) // 24 bits
        {
            contagem=0;
            pixeis_lidos=0;
            QByteArray teste;
            QFile filestr(Curr_Open_Img);
            if(filestr.open(QIODevice::ReadOnly)==true)
            {
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
                colortable=ctable.colorPalete1280();
                image24b.setColorTable(colortable);
                int cont=0;
                for(int a=0;a<=255;a++)
                {
                   for(int b=0;b<=255;b++)
                   {
                       contagem_anterior=contagem;
                       if(colors.at(cont).toInt()>=Max_Pixel_Value.toInt())
                       {
                           image24b.setPixel(b,a, image24b.colorTable().at(1535));
                       }
                       else
                       {
                            image24b.setPixel(b,a, image24b.colorTable().at(qCeil(colors.at(cont).toUInt()/10923)));
                            contagem=contagem+colors.at(cont).toFloat();
                       }
                       cont++;
                       if(contagem_anterior!=contagem)
                       {
                           pixeis_lidos++;
                       }
                   }
                }
            }
            else
            {
                image24b.fill(Qt::black);
                ui->textBrowser->append("Error Reading Image!!!");
            }
            pixmap = QPixmap::fromImage(image24b,Qt::ColorOnly);
        }

        pixmap=pixmap.scaled(512,512);
        scene= new QGraphicsScene(this);
        scene->addPixmap(pixmap);
        ui->Plot_Window->setScene(scene);
        ui->textBrowser->append("Total Count = "+QString::number(contagem));
        ui->textBrowser->append("Pixel Read = "+QString::number(pixeis_lidos));
    }
    else
    {
        QImage temp(512,512,QImage::Format_RGB32);
        temp.fill(Qt::black);
        pixmap=QPixmap::fromImage(temp,Qt::ColorOnly);
        scene= new QGraphicsScene(this);
        scene->addPixmap(pixmap);
        ui->Plot_Window->setScene(scene);
        ui->textBrowser->setText("Error Reading Image!!!");
    }
}

/**************************************************************************************************
*   inicia o pserve para receber as imagens e plota na ui
**************************************************************************************************/
void MainWindow::start_pserve()
{
    contagem=0;
    pixeis_lidos=0;
    QProcess *myProcess = new QProcess;
    QStringList arguments_pserve;
    process_pserve = Current_Path+"/pserve";
    arguments_pserve<<Count_L<<NImage<<Save_Path;
    myProcess->start(process_pserve,arguments_pserve);
    myProcess->waitForStarted();
    float contagem_anterior;
    /**************************************************************************************************
    *   le uma imagem
    **************************************************************************************************/
    if(NImage.toInt()==1)
    {
        //open_image(1);
        if(Count_L.toInt()==0) // 1 bit
        {
            contagem=0;
            pixeis_lidos=0;
            myProcess->waitForFinished((Time.toFloat()*1000)+100);
            //QImage image(256,256,QImage::Format_Indexed8);
            if(image1b.load(Save_Path+"1.ppm","pbm")==true)
            {
                image1b.invertPixels();
                for(int a=0;a<=255;a++)
                {
                    for(int b=0;b<=255;b++)
                    {
                        contagem=contagem+(1-image1b.pixelIndex(b,a));
                        pixeis_lidos=contagem;
                    }
                }
            }
            else
            {
                image1b.fill(Qt::black);
                ui->textBrowser->append("Error Reading Image!!!");
            }
            pixmap = QPixmap::fromImage(image1b,Qt::ColorOnly);
        }
        else if(Count_L.toInt()==1) // 12 bits
        {
            contagem=0;
            pixeis_lidos=0;
            myProcess->waitForFinished((Time.toFloat()*1000)+1000);
            //QImage image(256,256,QImage::Format_RGB16);
            QByteArray teste;
            QFile filestr(Save_Path+"1.ppm");
            if(filestr.open(QIODevice::ReadOnly)==true)
            {
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
                colortable=ctable.colorPalete1280();
                image12b.setColorTable(colortable);
                int cont=0;
                for(int a=0;a<=255;a++)
                {
                    for(int b=0;b<=255;b++)
                    {
                        if(qCeil(colors.at(cont).toInt()/3.201)>=1280)
                        {
                            image12b.setPixel(b,a, image12b.colorTable().at(1279));
                        }
                        else
                        {
                            image12b.setPixel(b,a, image12b.colorTable().at(qCeil(colors.at(cont).toUInt()/3.201)));
                        }
                        contagem_anterior=contagem;
                        contagem=contagem+colors.at(cont).toFloat();
                        cont++;
                        if(contagem_anterior!=contagem)
                        {
                            pixeis_lidos++;
                        }
                    }
                }
            }
            else
            {
                image12b.fill(Qt::black);
                ui->textBrowser->append("Error Reading Image!!!");
            }
            pixmap = QPixmap::fromImage(image12b,Qt::ColorOnly);
        }
        else if(Count_L.toInt()==2) // 6 bits
        {
            contagem=0;
            pixeis_lidos=0;
            myProcess->waitForFinished((Time.toFloat()*1000)+500);
            //QImage image(256,256,QImage::Format_Indexed8);
            if(image6b.load(Save_Path+"1.ppm","pbm")==true)
            {
                QVector<QRgb> colortable;
                Lookup_Tables ctable;
                colortable=ctable.colorPalete64();
                image6b.setColorTable(colortable);
            }
            else
            {
                image6b.fill(Qt::black);
                ui->textBrowser->append("Error Reading Image!!!");
            }
            pixmap = QPixmap::fromImage(image6b,Qt::ColorOnly);

            for(int a=0;a<=255;a++)
            {
                for(int b=0;b<=255;b++)
                {
                    contagem_anterior=contagem;
                    contagem=contagem+image6b.pixelIndex(b,a);
                    if(contagem_anterior!=contagem)
                    {
                        pixeis_lidos++;
                    }
                }
            }
        }
        else if(Count_L.toInt()==3) // 24 bits
        {
            contagem=0;
            pixeis_lidos=0;
            myProcess->waitForFinished((Time.toFloat()*1000)+1500);
            //QImage image(256,256,QImage::Format_RGB32);
            QByteArray teste;
            QFile filestr(Save_Path+"1.ppm");
            if(filestr.open(QIODevice::ReadOnly)==true)
            {
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
                colortable=ctable.colorPalete1280();
                image24b.setColorTable(colortable);
                int cont=0;
                for(int a=0;a<=255;a++)
                {
                    for(int b=0;b<=255;b++)
                    {
                        if(qCeil(colors.at(cont).toInt()/10923)>=1536)
                        {
                            image24b.setPixel(b,a, image24b.colorTable().at(1535));
                        }
                        else
                        {
                            image24b.setPixel(b,a, image24b.colorTable().at(qCeil(colors.at(cont).toUInt()/10923)));
                        }
                        contagem_anterior=contagem;
                        contagem=contagem+colors.at(cont).toFloat();
                        cont++;
                        if(contagem_anterior!=contagem)
                        {
                            pixeis_lidos++;
                        }
                    }
                }
            }
            else
            {
                image24b.fill(Qt::black);
                ui->textBrowser->append("Error Reading Image!!!");
            }
            pixmap = QPixmap::fromImage(image24b,Qt::ColorOnly);
        }
        pixmap=pixmap.scaled(512,512);
        scene= new QGraphicsScene(this);
        scene->addPixmap(pixmap);
        ui->Plot_Window->setScene(scene);
        QByteArray text_response=myProcess->readAll();
        QString mystr(text_response);
        ui->textBrowser->setText(mystr);
        ui->textBrowser->append("Total Count = "+QString::number(contagem));
        ui->textBrowser->append("Pixel Read = "+QString::number(pixeis_lidos));
    }
    /**************************************************************************************************
    *   le +1 imagem
    **************************************************************************************************/
    else
    {
        QString lee(Image_Name);
        int cont =0;
        lee.append(QString::number(cont));
        for(int a=0;a<=(NImage.toInt()-1);a++)
        {
            if(Count_L.toInt()==0) // 1 bit
            {
                if(a==(NImage.toInt()-1))
                {
                    myProcess->waitForFinished(NImage.toInt()*((Gap.toInt()*1000)+(Time.toFloat()*1000)+300));
                }
                else if(a==0)
                {
                    QThread::msleep((Time.toFloat()*1000)+300);
                }
                else
                {
                    QThread::msleep((Gap.toInt()*1000)+(Time.toFloat()*1000)+300);
                }
                cont++;
                lee.replace(lee.size()-1,1,QString::number(cont));
                QImage image(256,256,QImage::Format_Indexed8);
                image.load(Save_Dir.absolutePath()+"/"+lee+".ppm","pbm");
                image.invertPixels();
                pixmap = QPixmap::fromImage(image,Qt::ColorOnly);
                pixmap=pixmap.scaled(512,512);
                scene= new QGraphicsScene(this);
                scene->addPixmap(pixmap);
                scene->update();
                ui->Plot_Window->setScene(scene);
                ui->Plot_Window->update();

                //ui->textBrowser->update();
                QCoreApplication::processEvents(QEventLoop::AllEvents);
                QByteArray text_response=myProcess->readAll();
                QString mystr(text_response);
                ui->textBrowser->append(mystr);
            }
            else if(Count_L.toInt()==1) // 12 bits
            {
                if(a==(NImage.toInt()-1))
                {
                    myProcess->waitForFinished(NImage.toInt()*((Gap.toInt()*1000)+(Time.toFloat()*1000)+1000));
                }
                else if(a==0)
                {
                    QThread::msleep((Time.toFloat()*1000)+1000);
                }
                else
                {
                    QThread::msleep((Gap.toInt()*1000)+(Time.toFloat()*1000)+1000);
                }
                QByteArray text_response=myProcess->readAll();
                QString mystr(text_response);
                ui->textBrowser->setText(mystr);
                cont++;
                lee.replace(lee.size()-1,1,QString::number(cont));
                QImage image(256,256,QImage::Format_RGB16);
                QByteArray teste;
                QFile filestr(Save_Dir.absolutePath()+"/"+lee+".ppm");
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
                colortable=ctable.colorPalete1280();
                image.setColorTable(colortable);
                int cont=0;
                for(int a=0;a<=255;a++)
                {
                    for(int b=0;b<=255;b++)
                    {
                        if(qCeil(colors.at(cont).toInt()/3.201)>=1280)
                        {
                            image.setPixel(b,a, image.colorTable().at(1279));
                        }
                        else
                        {
                            image.setPixel(b,a, image.colorTable().at(qCeil(colors.at(cont).toUInt()/3.201)));
                        }
                        cont++;
                    }
                }
                pixmap = QPixmap::fromImage(image,Qt::ColorOnly);
                pixmap=pixmap.scaled(512,512);
                scene= new QGraphicsScene(this);
                scene->addPixmap(pixmap);
                scene->update();
                ui->Plot_Window->setScene(scene);
                ui->Plot_Window->update();
                QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
            }
            else if(Count_L.toInt()==2) // 6 bits
            {
                if(a==(NImage.toInt()-1))
                {
                    myProcess->waitForFinished(NImage.toInt()*((Gap.toInt()*1000)+(Time.toFloat()*1000)+500));
                }
                else if(a==0)
                {
                    QThread::msleep((Time.toFloat()*1000)+500);
                }
                else
                {
                    QThread::msleep((Gap.toInt()*1000)+(Time.toFloat()*1000)+500);
                }
                QByteArray text_response=myProcess->readAll();
                QString mystr(text_response);
                ui->textBrowser->setText(mystr);
                cont++;
                //QFileInfoList list = Save_Dir.entryInfoList();
                //QFileInfo fileinfo = list.at(0);
                //image1 = fileinfo.fileName();
                lee.replace(lee.size()-1,1,QString::number(cont));
                //qDebug()<<Save_Dir.absolutePath()+"/"+lee+".ppm";
                QImage image(256,256,QImage::Format_Indexed8);
                image.load(Save_Dir.absolutePath()+"/"+lee+".ppm","pgm");
                QVector<QRgb> colortable;
                Lookup_Tables ctable;
                colortable=ctable.colorPalete64();
                image.setColorTable(colortable);
                pixmap=pixmap.scaled(512,512);
                pixmap = QPixmap::fromImage(image,Qt::ColorOnly);
                scene= new QGraphicsScene(this);
                scene->addPixmap(pixmap);
                scene->update();
                ui->Plot_Window->setScene(scene);
                ui->Plot_Window->update();
                QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
            }
            else if(Count_L.toInt()==3) // 24 bits
            {
                if(a==(NImage.toInt()-1))
                {
                    myProcess->waitForFinished(NImage.toInt()*((Gap.toInt()*1000)+(Time.toFloat()*1000)+1500));
                }
                else if(a==0)
                {
                    QThread::msleep((Time.toFloat()*1000)+1500);
                }
                else
                {
                    QThread::msleep((NImage.toInt()*1000)+(Time.toFloat()*1000)+1500);
                }
                QByteArray text_response=myProcess->readAll();
                QString mystr(text_response);
                ui->textBrowser->setText(mystr);
                cont++;
                lee.replace(lee.size()-1,1,QString::number(cont));
                QImage image(256,256,QImage::Format_RGB32);
                QByteArray teste;
                QFile filestr(Save_Dir.absolutePath()+"/"+lee+".ppm");
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
                colortable=ctable.colorPalete1280();
                image.setColorTable(colortable);
                int cont=0;
                for(int a=0;a<=255;a++)
                {
                    for(int b=0;b<=255;b++)
                    {
                        if(qCeil(colors.at(cont).toInt()/1000)>=1536)
                        {
                            image.setPixel(b,a, image.colorTable().at(1535));
                        }
                        else
                        {
                            image.setPixel(b,a, image.colorTable().at(qCeil(colors.at(cont).toUInt()/1000)));
                        }
                        cont++;
                    }
                }
                pixmap = QPixmap::fromImage(image,Qt::ColorOnly);
                pixmap=pixmap.scaled(512,512);
                scene= new QGraphicsScene(this);
                scene->addPixmap(pixmap);
                scene->update();
                ui->Plot_Window->setScene(scene);
                ui->Plot_Window->update();
                QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
            }
        }
    }
}

/**************************************************************************************************
*   omr validacao e send
**************************************************************************************************/
void MainWindow::on_Aquire_Time_Input_editingFinished()
{
    Time=ui->Aquire_Time_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/omr.cgi?opmode=7&aqtime=";
    url.append(Time+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_NImages_Input_editingFinished()
{
    QRegExp validation("\\d*");
    if (validation.exactMatch(ui->NImages_Input->text()))
    {
        NImage=ui->NImages_Input->text();
        QString url = "http://10.0.27.67/cgi-bin/omr.cgi?opmode=7&aqcount=";
        url.append(NImage+"&write");
        nam->get(QNetworkRequest(QUrl(url)));
    }
    else
    {
        ui->textBrowser->setText("Invalid Value Dude!!!<br/>from 1 to 100 please!!!");
        ui->NImages_Input->setText(NImage);
    }
}

void MainWindow::on_Gap_Input_editingFinished()
{
    Gap=ui->Gap_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/omr.cgi?opmode=7&aqgap=";
    url.append(Gap+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_Read_Counter_Input_currentIndexChanged(int index)
{
    RCount.setNum(index);
    QString url = "http://10.0.27.67/cgi-bin/omr.cgi?opmode=7&readcount=";
    url.append(RCount+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_Colour_Mode_Input_currentIndexChanged(int index)
{
    Colour_Mode.setNum(index);
    QString url = "http://10.0.27.67/cgi-bin/omr.cgi?opmode=7&colourmode=";
    url.append(Colour_Mode+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_Read_Write_Input_currentIndexChanged(int index)
{
    Read_Write.setNum(index);
    QString url = "http://10.0.27.67/cgi-bin/omr.cgi?opmode=7&crw_srw=";
    url.append(Read_Write+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_Pixel_Mode_Input_currentIndexChanged(int index)
{
    Pixel_Mode.setNum(index);
    QString url = "http://10.0.27.67/cgi-bin/omr.cgi?opmode=7&csm_spm=";
    url.append(Pixel_Mode+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_Disc_CSM_SPM_Input_currentIndexChanged(int index)
{
    Disc_CSM_SPM.setNum(index);
    QString url = "http://10.0.27.67/cgi-bin/omr.cgi?opmode=7&disc_csm_spm=";
    url.append(Disc_CSM_SPM+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}
/**************************************************************************************************
*   atualiza o numero de bits de leitura e plota o color bar correspondente na ui
**************************************************************************************************/
void MainWindow::on_Count_L_Input_currentIndexChanged(int index)
{
    Count_L.setNum(index);
    QString url = "http://10.0.27.67/cgi-bin/omr.cgi?opmode=7&count_l=";
    url.append(Count_L+"&write");
    nam->get(QNetworkRequest(QUrl(url)));

    QPixmap pixmap_bar;

    if(Count_L.toInt()==0)
    {
        Max_Pixel_Value=QString::number(1);
        ui->Max_Level_Input->setText(Max_Pixel_Value);
        QImage image_color_bar(1,2,QImage::Format_Mono);
        image_color_bar.invertPixels();
        pixmap_bar = QPixmap::fromImage(image_color_bar,Qt::ColorOnly);
        ui->MaxV_Tab->setText(QString::number(1));
        ui->MidV_Tab->setText(QString::number(0));
    }
    else if(Count_L.toInt()==1) // 12 bits
    {
        Max_Pixel_Value=QString::number(4095);
        ui->Max_Level_Input->setText(Max_Pixel_Value);
        QImage image_color_bar(1, 1280, QImage::Format_RGB32);
        image_color_bar.setColorCount(1280);
        QVector<QRgb> colortable;
        Lookup_Tables ctable;
        colortable=ctable.colorPalete1280();
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
        pixmap_bar = QPixmap::fromImage(image_color_bar,Qt::ColorOnly);

        ui->MaxV_Tab->setText(QString::number(qFloor(colortable.size()*2.667)-1));
        ui->MidV_Tab->setText(QString::number(qFloor((colortable.size()/2)*2.667)-1));
    }
    else if(Count_L.toInt()==2) // 6 bits
    {
        Max_Pixel_Value=QString::number(63);
        ui->Max_Level_Input->setText(Max_Pixel_Value);
        QImage image_color_bar(1,64,QImage::Format_RGB16);
        QVector<QRgb> colortable;
        Lookup_Tables ctable;
        colortable=ctable.colorPalete64();
        image_color_bar.setColorTable(colortable);
        int color_bar_row[64];
        for(int b=0;b<=63;b++)
        {
            color_bar_row[b]=63-b;
        }
        for(int a=0;a<=63;a++)
        {
            image_color_bar.setPixel(0,a,colortable.at(color_bar_row[a]));
        }
        pixmap_bar = QPixmap::fromImage(image_color_bar,Qt::ColorOnly);
        ui->MaxV_Tab->setText(QString::number(colortable.size()-2));
        ui->MidV_Tab->setText(QString::number((colortable.size()/2)-1));
    }
    else if(Count_L.toInt()==3) // 24 bits
    {
        Max_Pixel_Value=QString::number(16777215);
        ui->Max_Level_Input->setText(Max_Pixel_Value);
        QImage image_color_bar(1, 1536, QImage::Format_RGB32);
        image_color_bar.setColorCount(1536);
        QVector<QRgb> colortable;
        Lookup_Tables ctable;
        colortable=ctable.colorPalete1280();
        image_color_bar.setColorTable(colortable);
        int color_bar_row[1536];
        for(int a=0;a<=1535;a++)
        {
            color_bar_row[a]=1535-a;
        }
        for(int a=0;a<=1535;a++)
        {
            image_color_bar.setPixel(0,a,colortable.at(color_bar_row[a]));
        }
        pixmap_bar = QPixmap::fromImage(image_color_bar,Qt::ColorOnly);

        ui->MaxV_Tab->setText(QString::number(qFloor(colortable.size()*10922.667)-1));
        ui->MidV_Tab->setText(QString::number(qFloor((colortable.size()/2)*10922.667)-1));
    }
    pixmap_bar = pixmap_bar.scaled(15,512);
    scene_table= new QGraphicsScene(this);
    ui->color_table_bar->setRenderHint(QPainter::Antialiasing);
    scene_table->addPixmap(pixmap_bar);
    ui->color_table_bar->setScene(scene_table);
}

void MainWindow::on_Gain_Mode_Input_currentIndexChanged(int index)
{
    Gain_Mode.setNum(index);
    QString url = "http://10.0.27.67/cgi-bin/omr.cgi?opmode=7&gainmode=";
    url.append(Gain_Mode+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_Polarity_Input_currentIndexChanged(int index)
{
    Polarity.setNum(index);
    QString url = "http://10.0.27.67/cgi-bin/omr.cgi?opmode=7&pol=";
    url.append(Polarity+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
}
/**************************************************************************************************
*   dacs validacao e send
**************************************************************************************************/
void MainWindow::on_TH0_Input_editingFinished()
{
    QRegExp validation("\\d*");
    if (validation.exactMatch(ui->TH0_Input->text()))
    {
        th0=ui->TH0_Input->text().rightJustified(3,'0');
        QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&threshold_0=";
        url.append(th0+"&write");
        nam->get(QNetworkRequest(QUrl(url)));
    }
    else
    {
        ui->textBrowser->setText("Invalid Value Dude!!!<br/>from 0 to 511 please!!!");
        ui->TH0_Input->setText(th0);
    }
}

void MainWindow::on_TH1_Input_editingFinished()
{
    QRegExp validation("\\d*");
    if (validation.exactMatch(ui->TH1_Input->text()))
    {
        th1=ui->TH1_Input->text().rightJustified(3,'0');
        QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&threshold_1=";
        url.append(th1+"&write");
        nam->get(QNetworkRequest(QUrl(url)));
    }
    else
    {
        ui->textBrowser->setText("Invalid Value Dude!!!<br/>from 0 to 511 please!!!");
        ui->TH1_Input->setText(th1);
    }
}

void MainWindow::on_TH2_Input_editingFinished()
{
    QRegExp validation("\\d*");
    if (validation.exactMatch(ui->TH2_Input->text()))
    {
        th2=ui->TH2_Input->text().rightJustified(3,'0');
        QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&threshold_2=";
        url.append(th2+"&write");
        nam->get(QNetworkRequest(QUrl(url)));
    }
    else
    {
        ui->textBrowser->setText("Invalid Value Dude!!!<br/>from 0 to 511 please!!!");
        ui->TH2_Input->setText(th2);
    }
}

void MainWindow::on_TH3_Input_editingFinished()
{
    QRegExp validation("\\d*");
    if (validation.exactMatch(ui->TH3_Input->text()))
    {
        th3=ui->TH3_Input->text().rightJustified(3,'0');
        QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&threshold_3=";
        url.append(th3+"&write");
        nam->get(QNetworkRequest(QUrl(url)));
    }
    else
    {
        ui->textBrowser->setText("Invalid Value Dude!!!<br/>from 0 to 511 please!!!");
        ui->TH3_Input->setText(th3);
    }
}

void MainWindow::on_TH4_Input_editingFinished()
{
    QRegExp validation("\\d*");
    if (validation.exactMatch(ui->TH4_Input->text()))
    {
        th4=ui->TH4_Input->text().rightJustified(3,'0');
        QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&threshold_4=";
        url.append(th4+"&write");
        nam->get(QNetworkRequest(QUrl(url)));
    }
    else
    {
        ui->textBrowser->setText("Invalid Value Dude!!!<br/>from 0 to 511 please!!!");
        ui->TH4_Input->setText(th4);
    }
}

void MainWindow::on_TH5_Input_editingFinished()
{
    QRegExp validation("\\d*");
    if (validation.exactMatch(ui->TH5_Input->text()))
    {
    th5=ui->TH5_Input->text().rightJustified(3,'0');
    QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&threshold_5=";
    url.append(th5+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
    }
    else
    {
        ui->textBrowser->setText("Invalid Value Dude!!!<br/>from 0 to 511 please!!!");
        ui->TH5_Input->setText(th5);
    }
}

void MainWindow::on_TH6_Input_editingFinished()
{
    QRegExp validation("\\d*");
    if (validation.exactMatch(ui->TH6_Input->text()))
    {
    th6=ui->TH6_Input->text().rightJustified(3,'0');
    QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&threshold_6=";
    url.append(th6+"&write");
    nam->get(QNetworkRequest(QUrl(url)));
    }
    else
    {
        ui->textBrowser->setText("Invalid Value Dude<br/>from 0 to 511 please!!!!!!");
        ui->TH6_Input->setText(th6);
    }
}

void MainWindow::on_TH7_Input_editingFinished()
{
    QRegExp validation("\\d*");
    if (validation.exactMatch(ui->TH7_Input->text()))
    {
        th7=ui->TH7_Input->text().rightJustified(3,'0');
        QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&threshold_7=";
        url.append(th7+"&write");
        nam->get(QNetworkRequest(QUrl(url)));
    }
    else
    {
        ui->textBrowser->setText("Invalid Value Dude!!!<br/>from 0 to 511 please!!!");
        ui->TH7_Input->setText(th7);
    }
}

void MainWindow::on_IPREAMP_Input_editingFinished()
{
    QRegExp validation("\\d*");
    if (validation.exactMatch(ui->IPREAMP_Input->text()))
    {
        preamp=ui->IPREAMP_Input->text().rightJustified(3,'0');
        QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&preamp=";
        url.append(preamp+"&write");
        nam->get(QNetworkRequest(QUrl(url)));
    }
    else
    {
        ui->textBrowser->setText("Invalid Value Dude!!!<br/>from 0 to 255 please!!!");
        ui->IPREAMP_Input->setText(preamp);
    }
}

void MainWindow::on_IKRUM_Input_editingFinished()
{
    QRegExp validation("\\d*");
    if (validation.exactMatch(ui->IKRUM_Input->text()))
    {
        ikrum=ui->IKRUM_Input->text().rightJustified(3,'0');
        QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&ikrum=";
        url.append(ikrum+"&write");
        nam->get(QNetworkRequest(QUrl(url)));
    }
    else
    {
        ui->textBrowser->setText("Invalid Value Dude!!!<br/>from 0 to 255 please!!!");
        ui->IKRUM_Input->setText(ikrum);
    }
}

void MainWindow::on_ISHAPER_Input_editingFinished()
{
    QRegExp validation("\\d*");
    if (validation.exactMatch(ui->ISHAPER_Input->text()))
    {
        shaper=ui->ISHAPER_Input->text().rightJustified(3,'0');
        QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&shaper=";
        url.append(shaper+"&write");
        nam->get(QNetworkRequest(QUrl(url)));
    }
    else
    {
        ui->textBrowser->setText("Invalid Value Dude!!!<br/>from 0 to 255 please!!!");
        ui->ISHAPER_Input->setText(shaper);
    }
}

void MainWindow::on_IDISC_Input_editingFinished()
{
    QRegExp validation("\\d*");
    if (validation.exactMatch(ui->IDISC_Input->text()))
    {
        disc=ui->IDISC_Input->text().rightJustified(3,'0');
        QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&disc=";
        url.append(disc+"&write");
        nam->get(QNetworkRequest(QUrl(url)));
    }
    else
    {
        ui->textBrowser->setText("Invalid Value Dude!!!<br/>from 0 to 255 please!!!");
        ui->IDISC_Input->setText(disc);
    }
}

void MainWindow::on_IDISCLS_Input_editingFinished()
{
    QRegExp validation("\\d*");
    if (validation.exactMatch(ui->IDISCLS_Input->text()))
    {
        discls=ui->IDISCLS_Input->text().rightJustified(3,'0');
        QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&discls=";
        url.append(discls+"&write");
        nam->get(QNetworkRequest(QUrl(url)));
    }
    else
    {
        ui->textBrowser->setText("Invalid Value Dude!!!<br/>from 0 to 255 please!!!");
        ui->IDISCLS_Input->setText(discls);
    }
}

void MainWindow::on_ISHAPERTEST_Input_editingFinished()
{
    QRegExp validation("\\d*");
    if (validation.exactMatch(ui->ISHAPERTEST_Input->text()))
    {
        shapertest=ui->ISHAPERTEST_Input->text().rightJustified(3,'0');
        QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&shaper_test=";
        url.append(shapertest+"&write");
        nam->get(QNetworkRequest(QUrl(url)));
    }
    else
    {
        ui->textBrowser->setText("Invalid Value Dude!!!<br/>from 0 to 255 please!!!");
        ui->ISHAPERTEST_Input->setText(shapertest);
    }
}

void MainWindow::on_IDACDISCL_Input_editingFinished()
{
    QRegExp validation("\\d*");
    if (validation.exactMatch(ui->IDACDISCL_Input->text()))
    {
        dacdiscl=ui->IDACDISCL_Input->text().rightJustified(3,'0');
        QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&dac_discl=";
        url.append(dacdiscl+"&write");
        nam->get(QNetworkRequest(QUrl(url)));
    }
    else
    {
        ui->textBrowser->setText("Invalid Value Dude!!!<br/>from 0 to 255 please!!!");
        ui->IDACDISCL_Input->setText(dacdiscl);
    }
}

void MainWindow::on_IDAC_Test_Input_editingFinished()
{
    QRegExp validation("\\d*");
    if (validation.exactMatch(ui->IDAC_Test_Input->text()))
    {
        dactest=ui->IDAC_Test_Input->text().rightJustified(3,'0');
        QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&dac_test=";
        url.append(dactest+"&write");
        nam->get(QNetworkRequest(QUrl(url)));
    }
    else
    {
        ui->textBrowser->setText("Invalid Value Dude!!!<br/>from 0 to 255 please!!!");
        ui->IDAC_Test_Input->setText(dactest);
    }
}

void MainWindow::on_IDACDISCH_Input_editingFinished()
{
    QRegExp validation("\\d*");
    if (validation.exactMatch(ui->IDACDISCH_Input->text()))
    {
        dacdisch=ui->IDACDISCH_Input->text().rightJustified(3,'0');
        QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&dac_disch=";
        url.append(dacdisch+"&write");
        nam->get(QNetworkRequest(QUrl(url)));
    }
    else
    {
        ui->textBrowser->setText("Invalid Value Dude!!!<br/>from 0 to 255 please!!!");
        ui->IDACDISCH_Input->setText(dacdisch);
    }
}

void MainWindow::on_IDELAY_Input_editingFinished()
{
    QRegExp validation("\\d*");
    if (validation.exactMatch(ui->IDELAY_Input->text()))
    {
        delay=ui->IDELAY_Input->text().rightJustified(3,'0');
        QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&delay=";
        url.append(delay+"&write");
        nam->get(QNetworkRequest(QUrl(url)));
    }
    else
    {
        ui->textBrowser->setText("Invalid Value Dude!!!<br/>from 0 to 255 please!!!");
        ui->IDELAY_Input->setText(delay);
    }
}

void MainWindow::on_ITPBUFFERIN_Input_editingFinished()
{
    QRegExp validation("\\d*");
    if (validation.exactMatch(ui->ITPBUFFEROUT_Input->text()))
    {
        tpbufferin=ui->ITPBUFFERIN_Input->text().rightJustified(3,'0');
        QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&tp_bufferin=";
        url.append(tpbufferin+"&write");
        nam->get(QNetworkRequest(QUrl(url)));
    }
    else
    {
        ui->textBrowser->setText("Invalid Value Dude!!!<br/>from 0 to 255 please!!!");
        ui->ITPBUFFERIN_Input->setText(tpbufferin);
    }
}

void MainWindow::on_ITPBUFFEROUT_Input_editingFinished()
{
    QRegExp validation("\\d*");
    if (validation.exactMatch(ui->ITPBUFFEROUT_Input->text()))
    {
        tpbufferout=ui->ITPBUFFEROUT_Input->text().rightJustified(3,'0');
        QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&tp_bufferout=";
        url.append(tpbufferout+"&write");
        nam->get(QNetworkRequest(QUrl(url)));
    }
    else
    {
        ui->textBrowser->setText("Invalid Value Dude!!!<br/>from 0 to 255 please!!!");
        ui->ITPBUFFEROUT_Input->setText(tpbufferout);
    }
}

void MainWindow::on_VRPZ_Input_editingFinished()
{
    QRegExp validation("\\d*");
    if (validation.exactMatch(ui->VRPZ_Input->text()))
    {
        rpz=ui->VRPZ_Input->text().rightJustified(3,'0');
        QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&rpz=";
        url.append(rpz+"&write");
        nam->get(QNetworkRequest(QUrl(url)));
    }
    else
    {
        ui->textBrowser->setText("Invalid Value Dude!!!<br/>from 0 to 255 please!!!");
        ui->VRPZ_Input->setText(rpz);
    }
}

void MainWindow::on_VGND_Input_editingFinished()
{
    QRegExp validation("\\d*");
    if (validation.exactMatch(ui->VGND_Input->text()))
    {
        gnd=ui->VGND_Input->text().rightJustified(3,'0');
        QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&gnd=";
        url.append(gnd+"&write");
        nam->get(QNetworkRequest(QUrl(url)));
    }
    else
    {
        ui->textBrowser->setText("Invalid Value Dude!!!<br/>from 0 to 255 please!!!");
        ui->VGND_Input->setText(gnd);
    }
}

void MainWindow::on_VTPREF_Input_editingFinished()
{
    QRegExp validation("\\d*");
    if (validation.exactMatch(ui->VTPREF_Input->text()))
    {
        tpref=ui->VTPREF_Input->text().rightJustified(3,'0');
        QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&tp_ref=";
        url.append(tpref+"&write");
        nam->get(QNetworkRequest(QUrl(url)));
    }
    else
    {
        ui->textBrowser->setText("Invalid Value Dude!!!<br/>from 0 to 255 please!!!");
        ui->VTPREF_Input->setText(tpref);
    }
}

void MainWindow::on_VFBK_Input_editingFinished()
{
    QRegExp validation("\\d*");
    if (validation.exactMatch(ui->VFBK_Input->text()))
    {
        fbk=ui->VFBK_Input->text().rightJustified(3,'0');
        QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&fbk=";
        url.append(fbk+"&write");
        nam->get(QNetworkRequest(QUrl(url)));
    }
    else
    {
        ui->textBrowser->setText("Invalid Value Dude!!!<br/>from 0 to 255 please!!!");
        ui->VFBK_Input->setText(fbk);
    }
}

void MainWindow::on_VCAS_Input_editingFinished()
{
    QRegExp validation("\\d*");
    if (validation.exactMatch(ui->VCAS_Input->text()))
    {
        cas=ui->VCAS_Input->text().rightJustified(3,'0');
        QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&cas=";
        url.append(cas+"&write");
        nam->get(QNetworkRequest(QUrl(url)));
    }
    else
    {
        ui->textBrowser->setText("Invalid Value Dude!!!<br/>from 0 to 255 please!!!");
        ui->VCAS_Input->setText(cas);
    }
}

void MainWindow::on_VTPREFA_Input_editingFinished()
{
    QRegExp validation("\\d*");
    if (validation.exactMatch(ui->VTPREFA_Input->text()))
    {
        tprefa=ui->VTPREFA_Input->text().rightJustified(3,'0');
        QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&tp_refa=";
        url.append(tprefa+"&write");
        nam->get(QNetworkRequest(QUrl(url)));
    }
    else
    {
        ui->textBrowser->setText("Invalid Value Dude!!!<br/>from 0 to 511 please!!!");
        ui->VTPREFA_Input->setText(tprefa);
    }
}

void MainWindow::on_VTPREFB_Input_editingFinished()
{
    QRegExp validation("\\d*");
    if (validation.exactMatch(ui->VTPREFB_Input->text()))
    {
        tprefb=ui->VTPREFB_Input->text().rightJustified(3,'0');
        QString url = "http://10.0.27.67/cgi-bin/dacs.cgi?&tp_refb=";
        url.append(tprefb+"&write");
        nam->get(QNetworkRequest(QUrl(url)));
    }
    else
    {
        ui->textBrowser->setText("Invalid Value Dude!!!<br/>from 0 to 511 please!!!");
        ui->VTPREFB_Input->setText(tprefb);
    }
}
/**************************************************************************************************
*
**************************************************************************************************/
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
                ui->Scan_From_Input->setText(Scan_From);
                ui->Scan_To_Input->setText(Scan_To);
                ui->Scan_Step_Input->setText(Scan_Step);
                ui->Scan_Time_Input->setText(Time);
                ui->Scan_TH->setCurrentIndex(Scan_TH.toInt());
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
    QProcess *myProcess;
    myProcess = new QProcess(this);
    myProcess->start(program,arguments);
    myProcess->waitForStarted();
    myProcess->waitForFinished();
    myProcess->kill();
    myProcess->close();
    ui->textBrowser->setText("!#SUCCESS=Send Equalize!#");
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

void MainWindow::on_HOSTGATEWAY_Input_editingFinished()
{
    Host_Gate=ui->HOSTGATEWAY_Input->text();
    QString url = "http://10.0.27.67/cgi-bin/host_setup.cgi?gateway=";
    url.append(Host_Gate+"&write");
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
    //myProcess->close();
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
    Save_Dir.setPath(temp_path);
}

void MainWindow::on_Max_Level_Input_textChanged(const QString &arg1)
{
    Max_Pixel_Value=arg1;
    open_image();
}

void MainWindow::on_Max_Level_button_clicked()
{
    if(Count_L.toInt()==0) // 1 bit
    {
        Max_Pixel_Value=QString::number(1);
        ui->Max_Level_Input->setText(Max_Pixel_Value);
        open_image();
    }
    else if(Count_L.toInt()==2) // 6 bits
    {
        Max_Pixel_Value=QString::number(63);
        ui->Max_Level_Input->setText(Max_Pixel_Value);
        open_image();
    }
    else if (Count_L.toInt()==1) // 12 bits
    {
        Max_Pixel_Value=QString::number(4095);
        ui->Max_Level_Input->setText(Max_Pixel_Value);
        open_image();
    }
    else if (Count_L.toInt()==3) // 24 bits
    {
        Max_Pixel_Value=QString::number(16777215);
        ui->Max_Level_Input->setText(Max_Pixel_Value);
        open_image();
    }
}

void MainWindow::on_Read_THL_clicked()
{
    QStringList Threshold;
    QString THString;
    QFile File("/home/franz/altera/Interface/cgi_medipix/Interface_QT/Morpheus_Get/build/Equalize/ThAdjustmentL");
    File.open(QIODevice::ReadOnly);
    THString=File.readAll();
    Threshold=THString.split(QRegExp("\\s+"));
    Threshold.removeLast();
    QImage temp(256,256,QImage::Format_Indexed8);
    QVector<QRgb> colortable;
    Lookup_Tables ctable;
    colortable=ctable.colorPalete64();
    temp.setColorTable(colortable);
    int cont=0;
    for(int a=0;a<=255;a++)
    {
        for(int b=0;b<=255;b++)
        {
            temp.setPixel(b,a,Threshold.at(cont).toInt());
            cont++;
        }
    }
    Equalizacao_THH=Threshold;
    pixmap=QPixmap::fromImage(temp,Qt::ColorOnly);
    pixmap=pixmap.scaled(512,512);
    scene= new QGraphicsScene(this);
    scene->addPixmap(pixmap);
    ui->Plot_Window->setScene(scene);

    QProcess *myProcess;
    myProcess = new QProcess(this);
    myProcess->start(Current_Path+"/read");
    myProcess->waitForStarted();
    myProcess->waitForFinished();
    myProcess->close();
    ui->textBrowser->setText("!#SUCCESS=Read Equalize!#");
}

void MainWindow::on_Read_THH_clicked()
{
    QStringList Threshold;
    QString THString;
    QFile File("/home/franz/altera/Interface/cgi_medipix/Interface_QT/Morpheus_Get/build/Equalize/ThAdjustmentH");
    File.open(QIODevice::ReadOnly);
    THString=File.readAll();
    Threshold=THString.split(QRegExp("\\s+"));
    Threshold.removeLast();
    QImage temp(256,256,QImage::Format_Indexed8);
    QVector<QRgb> colortable;
    Lookup_Tables ctable;
    colortable=ctable.colorPalete64();
    temp.setColorTable(colortable);

    int cont=0;
    for(int a=0;a<=255;a++)
    {
        for(int b=0;b<=255;b++)
        {
            temp.setPixel(b,a,Threshold.at(cont).toInt());
            cont++;
        }
    }
    Equalizacao_THL=Threshold;

    pixmap=QPixmap::fromImage(temp,Qt::ColorOnly);
    pixmap=pixmap.scaled(512,512);
    scene= new QGraphicsScene(this);
    scene->addPixmap(pixmap);
    ui->Plot_Window->setScene(scene);

    QProcess *myProcess;
    myProcess = new QProcess(this);
    myProcess->start(Current_Path+"/read");
    myProcess->waitForStarted();
    myProcess->waitForFinished();
    myProcess->close();
    ui->textBrowser->setText("!#SUCCESS=Read Equalize!#");
}

void MainWindow::on_Read_Mask_clicked()
{
    QStringList Mask;
    QString THString;
    QFile File("/home/franz/altera/Interface/cgi_medipix/Interface_QT/Morpheus_Get/build/Equalize/maskbit");
    File.open(QIODevice::ReadOnly);
    THString=File.readAll();
    Mask=THString.split(QRegExp("\\s+"));
    Mask.removeLast();
    QImage temp(256,256,QImage::Format_Mono);

    int cont=0;
    for(int a=0;a<=255;a++)
    {
        for(int b=0;b<=255;b++)
        {
            temp.setPixel(b,a,Mask.at(cont).toInt());
            cont++;
        }
    }

    Equalizacao_MASK=Mask;
    pixmap=QPixmap::fromImage(temp,Qt::ColorOnly);
    pixmap=pixmap.scaled(512,512);
    scene= new QGraphicsScene(this);
    scene->addPixmap(pixmap);
    ui->Plot_Window->setScene(scene);

    QProcess *myProcess;
    myProcess = new QProcess(this);
    myProcess->start(Current_Path+"/read");
    myProcess->waitForStarted();
    myProcess->waitForFinished();
    myProcess->close();
    ui->textBrowser->setText("!#SUCCESS=Read Mask!#");
}

void MainWindow::on_Read_Test_clicked()
{
    QStringList Test;
    QString THString;
    QFile File("/home/franz/altera/Interface/cgi_medipix/Interface_QT/Morpheus_Get/build/Equalize/testbit");
    File.open(QIODevice::ReadOnly);
    THString=File.readAll();
    Test=THString.split(QRegExp("\\s+"));
    Test.removeLast();
    QImage temp(256,256,QImage::Format_Mono);

    int cont=0;
    for(int a=0;a<=255;a++)
    {
        for(int b=0;b<=255;b++)
        {
            temp.setPixel(b,a,Test.at(cont).toInt());
            cont++;
        }
    }

    Equalizacao_TEST=Test;
    pixmap=QPixmap::fromImage(temp,Qt::ColorOnly);
    pixmap=pixmap.scaled(512,512);
    scene= new QGraphicsScene(this);
    scene->addPixmap(pixmap);
    ui->Plot_Window->setScene(scene);

    QProcess *myProcess;
    myProcess = new QProcess(this);
    myProcess->start(Current_Path+"/read");
    myProcess->waitForStarted();
    myProcess->waitForFinished();
    myProcess->close();
    ui->textBrowser->setText("!#SUCCESS=Read Test bit!#");
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug()<<event->pos();
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(ui->tabWidget->currentIndex()<=2)
    {
        //qDebug()<<event->pos();
        QPoint  local_pt = ui->Plot_Window->mapFromGlobal(event->globalPos());
        QPointF img_coord_pt = ui->Plot_Window->mapToScene(local_pt);

        int x =qFloor((img_coord_pt.x()-1)/2);
        int y =qFloor((img_coord_pt.y()-1)/2);
        if(x>=1 && x<=255)
        {
            if(y>=1 && y<=255)
            {
                ui->X_Value->setText(QString::number(x));
                ui->Y_Value->setText(QString::number(y));

                if(Count_L.toInt()==1)
                {
                    QVector<QRgb> colortable;
                    Lookup_Tables ctable;
                    colortable=ctable.colorPalete1280();
                    for(int a=0;a<1536;a++)
                    {
                        if(image12b.pixel(x,y)==colortable.at(a))
                        {
                            ui->Value_input->setText(QString::number(qCeil(colortable.indexOf(image12b.pixel(x,y))*3.201)));
                        }
                    }
                }
                else if(Count_L.toInt()==2)
                {
                    QVector<QRgb> colortable;
                    Lookup_Tables ctable;
                    colortable=ctable.colorPalete64();
                    for(int a=0;a<=63;a++)
                    {
                        ui->Value_input->setText(QString::number(image6b.pixelIndex(x,y)));
                    }
                }
            }
        }
    }
    if(ui->tabWidget->currentIndex()==3)
    {
        QPoint  local_pt = ui->Plot_Window->mapFromGlobal(event->globalPos());
        QPointF img_coord_pt = ui->Plot_Window->mapToScene(local_pt);

        int x =qFloor((img_coord_pt.x()-1)/2);
        int y =qFloor((img_coord_pt.y()-1)/2);
        if(x>=1 && x<=255)
        {
            if(y>=1 && y<=255)
            {
                ui->X_Value->setText(QString::number(x));
                ui->Y_Value->setText(QString::number(y));
            }
        }
    }
}

void MainWindow::on_Start_Scan_Button_clicked()
{
    scan = Scan_From.toInt();
    contagem=0;
    dcont=0;
    dcont_ant=0;
    ui->custom_Plot->clearGraphs();
    ui->custom_Plot->legend->setVisible(true);
    ui->custom_Plot->legend->setFont(QFont("Helvetica",9));
    ui->custom_Plot->addGraph();// soma
    ui->custom_Plot->graph(0)->setPen(QPen(Qt::blue));
    ui->custom_Plot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    ui->custom_Plot->graph(0)->setAntialiasedFill(false);
    ui->custom_Plot->graph(0)->setName("Integral");

    ui->custom_Plot->addGraph(); // blue dot
    ui->custom_Plot->graph(1)->setPen(QPen(Qt::blue));
    ui->custom_Plot->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->custom_Plot->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);

    ui->custom_Plot->addGraph(); // diferencial
    ui->custom_Plot->graph(2)->setPen(QPen(Qt::red));
    ui->custom_Plot->graph(2)->setBrush(QBrush(QColor(255, 0, 0, 20)));
    ui->custom_Plot->graph(2)->setAntialiasedFill(false);
    ui->custom_Plot->graph(2)->setName("Diferencial");

    ui->custom_Plot->addGraph(); // diferential dot
    ui->custom_Plot->graph(3)->setPen(QPen(Qt::red));
    ui->custom_Plot->graph(3)->setLineStyle(QCPGraph::lsNone);
    ui->custom_Plot->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);

    //ui->custom_Plot->xAxis->setAutoTickStep(false);
    ui->custom_Plot->xAxis->setTickStep(5);
    ui->custom_Plot->legend->removeAt(1);
    ui->custom_Plot->legend->removeAt(3);
    //ui->custom_Plot->axisRect()->setupFullAxesBox();

    ui->custom_Plot->xAxis->setLabel("Threshold");
    ui->custom_Plot->yAxis->setLabel("Count");
    ui->custom_Plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    //ui->custom_Plot->xAxis->setRange(0, Scan_From.toInt(), Qt::AlignLeft);

    Scan_From=ui->Scan_From_Input->text();
    Scan_To=ui->Scan_To_Input->text();
    Scan_Step=ui->Scan_Step_Input->text();
    Time=ui->Scan_Time_Input->text();

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer.start(0); // Interval 0 means to refresh as fast as possible
}

void MainWindow::realtimeDataSlot()
{
    if(scan>=0)
    {
        QVector<double> x(512), y(512);
        QVector<double> dy(512);
        QVector<double> ddy(512);
        double contagem_anterior;

        int wait_time;
        double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
        static double lastPointKey = 0;
        if(Time.toFloat()>=1)
        {
            wait_time=qFloor(Time.toFloat());
        }
        else
        {
            wait_time=1;;
        }

        if (key-lastPointKey > wait_time+2) // de 3 em 3 segundos
        {
            ui->TH_Level_Input->setText(QString::number(scan));
            QString url;
            if(Scan_TH.toInt()==0)
            {
                url = "http://10.0.27.67/cgi-bin/dacs.cgi?&threshold_0=";
            }
            else
            {
                url = "http://10.0.27.67/cgi-bin/dacs.cgi?&threshold_1=";
            }
            url.append(QString::number(scan)+"&write");
            nam->get(QNetworkRequest(QUrl(url)));
            QThread::msleep(50);

            url = "http://10.0.27.67/cgi-bin/omr.cgi?opmode=0&aqtime=";
            url.append(Time+"&write");
            nam->get(QNetworkRequest(QUrl(url)));
            QString scan_name("Scan");
            QProcess *myProcess = new QProcess;
            QStringList arguments_pserve;
            process_pserve = Current_Path+"/pserve";
            arguments_pserve<<Count_L<<"1"<<Current_Path+"/scan/"+scan_name+QString::number(scan);
            myProcess->start(process_pserve,arguments_pserve);
            myProcess->waitForStarted();
            bool a = myProcess->waitForFinished(2500);
            //qDebug()<<a <<scan;
            if(a==false)
            {
                scan+=Scan_Step.toInt();
            }
            else
            {
                QThread::msleep(50);
                QByteArray stream;
                QFile filestr(Current_Path+"/scan/"+scan_name+QString::number(scan)+"1.ppm");
                if(filestr.open(QIODevice::ReadOnly)==true)
                {
                    stream=filestr.readAll();
                    QString colorstr(stream);
                    QStringList colors = colorstr.split(QRegExp("\\s+"));
                    colors.removeLast();
                    colors.removeFirst();
                    colors.removeFirst();
                    colors.removeFirst();
                    colors.removeFirst();
                    QVector<QRgb> colortable;
                    Lookup_Tables ctable;

                    if(Count_L.toInt()==1) // 12 bits
                    {
                        colortable=ctable.colorPalete1280();
                        image12b.setColorTable(colortable);
                        contagem_anterior=contagem;
                        int cont=0;
                        for(int a=0;a<=255;a++)
                        {
                            for(int b=0;b<=255;b++)
                            {
                                if(qCeil(colors.at(cont).toInt()/3.201)>=1280)
                                {
                                    image12b.setPixel(b,a, image12b.colorTable().at(1279));
                                }
                                else
                                {
                                    image12b.setPixel(b,a, image12b.colorTable().at(qCeil(colors.at(cont).toUInt()/3.201)));
                                }
                                contagem=contagem+colors.at(cont).toFloat();
                                cont++;
                            }
                        }
                        pixmap = QPixmap::fromImage(image12b,Qt::ColorOnly);
                    }
                    else if(Count_L.toInt()==3) // 24 bits
                    {
                        colortable=ctable.colorPalete1280();
                        image24b.setColorTable(colortable);
                        contagem_anterior=contagem;
                        int cont=0;
                        for(int a=0;a<=255;a++)
                        {
                            for(int b=0;b<=255;b++)
                            {
                                if(qCeil(colors.at(cont).toInt()/1000)>=1536)
                                {
                                   image24b.setPixel(b,a, image24b.colorTable().at(1535));
                                }
                                else
                                {
                                    image24b.setPixel(b,a, image24b.colorTable().at(qCeil(colors.at(cont).toUInt()/1000)));
                                }

                                contagem=contagem+colors.at(cont).toFloat();
                                cont++;
                            }
                        }
                        pixmap = QPixmap::fromImage(image24b,Qt::ColorOnly);
                    }
                }
                dcont_ant=dcont;
                dcont=(contagem-contagem_anterior);

                y[scan]=contagem;
                dy[scan]=dcont;
                ddy[scan]=-(dcont_ant-dcont);

                xtotal= scan;
                x[scan] = scan;

                pixmap=pixmap.scaled(512,512);
                scene= new QGraphicsScene(this);
                scene->addPixmap(pixmap);
                scene->update();
                pixmap.save(Current_Path+"/scan/"+scan_name+QString::number(scan)+".tiff",0,100);
                ui->Plot_Window->setScene(scene);
                ui->Plot_Window->update();
                QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);

                // add data to line
                ui->custom_Plot->graph(0)->addData(x, dy);
                // add data to dot
                ui->custom_Plot->graph(1)->clearData();
                ui->custom_Plot->graph(1)->addData(x, dy);
                // add diff
                ui->custom_Plot->graph(2)->addData(x, ddy);
                // add diff dot
                ui->custom_Plot->graph(3)->clearData();
                ui->custom_Plot->graph(3)->addData(x, ddy);
                // rescale value (vertical) axis to fit the current data:
                ui->custom_Plot->graph(0)->rescaleValueAxis(true);
                lastPointKey = key;
                // make key axis range scroll with the data (at a constant range size of 5):
                ui->custom_Plot->xAxis->setRange(scan-5, Scan_From.toInt(), Qt::AlignLeft);
                ui->custom_Plot->replot();
                }
            scan=scan-Scan_Step.toInt();
        }
    }
}

void MainWindow::on_y_minus_clicked()
{
    ytotal-=50;
    ui->custom_Plot->yAxis->setRange(0,ytotal);
    ui->custom_Plot->replot();
}

void MainWindow::on_y_plus_clicked()
{
    ytotal+=50;
    ui->custom_Plot->yAxis->setRange(0,ytotal);
    ui->custom_Plot->replot();
}

void MainWindow::on_x_plus_clicked()
{
     xtotal+=5;
     ui->custom_Plot->xAxis->setRange(Scan_From.toInt()/2,xtotal);
     ui->custom_Plot->replot();

}

void MainWindow::on_x_minus_clicked()
{
     xtotal-=5;
     ui->custom_Plot->xAxis->setRange(Scan_From.toInt()/2,xtotal);
     ui->custom_Plot->replot();
}

void MainWindow::on_Scan_From_Input_editingFinished()
{
    Scan_From=ui->Scan_From_Input->text();
    scan=Scan_From.toInt();
}



void MainWindow::on_Scan_TH_currentIndexChanged(int index)
{
    Scan_TH=QString::number(index);
}

void MainWindow::on_Stop_Scan_Button_clicked()
{
    dataTimer.stop();
}
