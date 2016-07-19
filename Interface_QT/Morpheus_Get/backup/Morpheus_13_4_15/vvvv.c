    





uchar color_bar_row[960];
        int cont=0;
        for(int b=0;b<=63;b++)
        {
            for(int a=0;a<=14;a++)
            {
                color_bar_row[cont]=63-b;
                cont++;
            }
        }
        QImage image_color_bar(color_bar_row,15,60,QImage::Format_Indexed8);
        image_color_bar.setColorCount(64);
        QVector<QRgb> colortable;
        colortable=colorPalete64();
        image_color_bar.setColorTable(colortable);
        QPixmap pixmap_bar = QPixmap::fromImage(image_color_bar,Qt::ColorOnly);
        pixmap_bar = pixmap_bar.scaled(15,256);

        scene_table= new QGraphicsScene(this);
        ui->color_table_bar->setRenderHint(QPainter::Antialiasing);
        ui->color_table_bar->setScene(scene_table);
        pixview2 = scene_table->addPixmap(pixmap_bar);





















QStringList arguments_pserve;
    process_pserve = "/home/franz/altera/Interface/cgi_medipix/Interface_QT/port_server_ppm/pserve";
    //qDebug()<<Save_Dir.relativeFilePath(process_pserve);
    arguments_pserve<<Count_L<<NImage<<Save_Path;
    myProcess = new QProcess(this);
    myProcess->execute(process_pserve,arguments_pserve);
    QThread::sleep((Time.toFloat()*NImage.toInt()+0.4));

    Save_Dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    Save_Dir.setSorting(QDir::Time);
    QString image1;
    uchar oichar[131072];
    if(NImage.toInt()==1)
    {
        do
        {
            QFileInfoList list = Save_Dir.entryInfoList();
            QFileInfo fileinfo = list.at(0);
            //qDebug()<<QString("%1 %2").arg(fileinfo.fileName()).arg(fileinfo.size());
            image1 = fileinfo.fileName();
            //image1.remove();
        } while(image1.endsWith(".ppm",Qt::CaseSensitive)==false);

        ///qDebug()<<Save_Path+image1;

        (void)file.load(Save_Path+"1.ppm");

        //montando uma imagem
        //usando bytearray
//        QByteArray teste;
//        QFile filestr;
//        filestr.setFileName(Save_Path+"1.ppm");
//        filestr.open(QIODevice::ReadOnly);
//        teste=filestr.readAll();

//        teste.remove(0,14);
//        //qDebug()<<teste;
//        int cont=0;
//        for(int a=0;a<teste.size();a++)
//        {
//           if(teste.at(a)!=32)
//           {
//                if(teste.at(a)!=10)
//                {
//                 oichar[cont]=teste.at(a);
//                 //qDebug()<<oichar[cont]<<" "<<cont;
//                 cont++;
//                }
//           }
//        }
    }
    else
    {
        do
        {
            QFileInfoList list = Save_Dir.entryInfoList();
            QFileInfo fileinfo = list.at(0);
            //qDebug()<<QString("%1 %2").arg(fileinfo.fileName()).arg(fileinfo.size());
            image1 = fileinfo.fileName();
            //image1.remove();
        } while(image1.endsWith(".ppm",Qt::CaseSensitive)==false);

        ///qDebug()<<Save_Path+image1;

        (void)file.load(Save_Path+"1.ppm");
    }

//    QImage image(oichar,256,256, QImage::Format_Mono);
//    image.save(Save_Path+"sdf.ppm","ppm");
//    QStringList jaja = oi.split(QRegExp("\\s+"));
//    jaja.removeLast();

    //qDebug()<<jaja;
    //qDebug()<<jaja.size();


    scene= new QGraphicsScene(this);
    QPalette sample_palette;

    ui->Plot_Window->setScene(scene);
    ui->Plot_Window->setPalette(sample_palette);
    scene->setPalette(sample_palette);
    pixview = scene->addPixmap(file);
    //scene->addItem(&item);
//    if(Count_L.toInt()==0)
//    {

//    }
//    else
//    {
//        pixview = scene->addPixmap(QPixmap::fromImage(image));
//    }




QVector<QRgb> MainWindow::colorPalete64()
{
    QVector<QRgb> palete64;
    palete64.push_back(qRgb(0,     0,   0));
    palete64.push_back(qRgb(85,   85,  85));
    palete64.push_back(qRgb(170, 170, 170));

    palete64.push_back(qRgb(0,     0,  85));
    palete64.push_back(qRgb(0,     0, 170));
    palete64.push_back(qRgb(0,     0, 255));
    palete64.push_back(qRgb(0,    85,   0));
    palete64.push_back(qRgb(0,    85,  85));
    palete64.push_back(qRgb(0,    85, 170));
    palete64.push_back(qRgb(0,    85, 255));
    palete64.push_back(qRgb(0,   170,   0));
    palete64.push_back(qRgb(0,   170,  85));
    palete64.push_back(qRgb(0,   170, 170));
    palete64.push_back(qRgb(0,   170, 255));
    palete64.push_back(qRgb(0,   255,   0));
    palete64.push_back(qRgb(0,   255,  85));
    palete64.push_back(qRgb(0,   255, 170));
    palete64.push_back(qRgb(0,   255, 255));

    palete64.push_back(qRgb(85,    0,   0));
    palete64.push_back(qRgb(85,    0,  85));
    palete64.push_back(qRgb(85,    0, 170));
    palete64.push_back(qRgb(85,    0, 255));
    palete64.push_back(qRgb(85,   85,   0));
    palete64.push_back(qRgb(85,   85, 170));
    palete64.push_back(qRgb(85,   85, 255));
    palete64.push_back(qRgb(85,  170,   0));
    palete64.push_back(qRgb(85,  170,  85));
    palete64.push_back(qRgb(85,  170, 170));
    palete64.push_back(qRgb(85,  170, 255));
    palete64.push_back(qRgb(85,  255,   0));
    palete64.push_back(qRgb(85,  255,  85));
    palete64.push_back(qRgb(85,  255, 170));
    palete64.push_back(qRgb(85,  255, 255));

    palete64.push_back(qRgb(170,   0,   0));
    palete64.push_back(qRgb(170,   0,  85));
    palete64.push_back(qRgb(170,   0, 170));
    palete64.push_back(qRgb(170,   0, 255));
    palete64.push_back(qRgb(170,  85,   0));
    palete64.push_back(qRgb(170,  85,  85));
    palete64.push_back(qRgb(170,  85, 170));
    palete64.push_back(qRgb(170,  85, 255));
    palete64.push_back(qRgb(170, 170,   0));
    palete64.push_back(qRgb(170, 170,  85));
    palete64.push_back(qRgb(170, 170, 255));
    palete64.push_back(qRgb(170, 255,   0));
    palete64.push_back(qRgb(170, 255,  85));
    palete64.push_back(qRgb(170, 255, 170));
    palete64.push_back(qRgb(170, 255, 255));

    palete64.push_back(qRgb(255,   0,   0));
    palete64.push_back(qRgb(255,   0,  85));
    palete64.push_back(qRgb(255,   0, 170));
    palete64.push_back(qRgb(255,   0, 255));
    palete64.push_back(qRgb(255,  85,   0));
    palete64.push_back(qRgb(255,  85,  85));
    palete64.push_back(qRgb(255,  85, 170));
    palete64.push_back(qRgb(255,  85, 255));
    palete64.push_back(qRgb(255, 170,   0));
    palete64.push_back(qRgb(255, 170,  85));
    palete64.push_back(qRgb(255, 170, 170));
    palete64.push_back(qRgb(255, 170, 255));
    palete64.push_back(qRgb(255, 255,   0));
    palete64.push_back(qRgb(255, 255,  85));
    palete64.push_back(qRgb(255, 255, 170));
    palete64.push_back(qRgb(255, 255, 255));

    return palete64;
}
