        
    QByteArray teste;
    uint pixelvalue[65536];


    //montando uma imagem usando bytearray
            //QByteArray teste;
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
            //valor de todos pixeis na lista como string
            teste.clear();
            //passa de string pra bytearray
            for(int a=0;a<colors.size();a++)
            {
                teste.append(colors.at(a).toLatin1());
                pixelvalue[a]=colors.at(a).toInt();
            }
//            //qDebug()<<teste;
