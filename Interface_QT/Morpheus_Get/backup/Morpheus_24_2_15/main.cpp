/*MAIN FILE
---------------------------------------------------------------------------------------------------
--!@brief main.cpp
---------------------------------------------------------------------------------------------------
--! DESCRIPTION:
--!
--! Codigo fonte principal da ui
--!
--!
--! DETAILS:
--!
--!- Project Name: main
--!- Module Name: main.cpp
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
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
