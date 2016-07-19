/*CPP FILE
---------------------------------------------------------------------------------------------------
--!@brief lookup_tables.cpp
---------------------------------------------------------------------------------------------------
--! DESCRIPTION:
--!
--! Gera as lookup tables dos color bar
--!
--!
--! DETAILS:
--!
--!- Project Name: lookup_tables
--!- Module Name: lookup_tables.cpp
--!- Tools: Qt Creator
--!- Author: Franz Wagner
--!- Company: LABORATORIO NACIONAL DE LUZ SINCROTRON - GRUPO DETECTORES
--!- Create Date: 25/02/2015
--!- Version: 1.0.0 (mar/2015)
---------------------------------------------------------------------------------------------------
-- LNLS - DET - 2015
---------------------------------------------------------------------------------------------------
*/
#include "lookup_tables.h"
#include "mainwindow.h"

Lookup_Tables::Lookup_Tables()
{
}

QVector<QRgb> Lookup_Tables::colorPalete64()
{
    QVector<QRgb> palete64;

    palete64.append(qRgb(0,0,0));
    palete64.append(qRgb(0,0,40));
    palete64.append(qRgb(0,0,60));
    palete64.append(qRgb(0,0,80));
    palete64.append(qRgb(0,0,100));
    palete64.append(qRgb(0,0,120));
    palete64.append(qRgb(0,0,140));
    palete64.append(qRgb(0,0,160));
    palete64.append(qRgb(0,0,180));
    palete64.append(qRgb(0,0,200));
    palete64.append(qRgb(0,0,220));
    palete64.append(qRgb(0,0,240));
    palete64.append(qRgb(0,0,255));

    palete64.append(qRgb(0,20,255));
    palete64.append(qRgb(0,40,255));
    palete64.append(qRgb(0,60,255));
    palete64.append(qRgb(0,80,255));
    palete64.append(qRgb(0,100,255));
    palete64.append(qRgb(0,120,255));
    palete64.append(qRgb(0,140,255));
    palete64.append(qRgb(0,160,255));
    palete64.append(qRgb(0,180,255));
    palete64.append(qRgb(0,200,255));
    palete64.append(qRgb(0,220,255));
    palete64.append(qRgb(0,240,255));
    palete64.append(qRgb(0,255,255));

    palete64.append(qRgb(0,255,240));
    palete64.append(qRgb(0,255,220));
    palete64.append(qRgb(0,255,200));
    palete64.append(qRgb(0,255,180));
    palete64.append(qRgb(0,255,160));
    palete64.append(qRgb(0,255,140));
    palete64.append(qRgb(0,255,120));
    palete64.append(qRgb(0,255,100));
    palete64.append(qRgb(0,255,80));
    palete64.append(qRgb(0,255,60));
    palete64.append(qRgb(0,255,40));
    palete64.append(qRgb(0,255,20));
    palete64.append(qRgb(0,255,0));

    palete64.append(qRgb(20,255,0));
    palete64.append(qRgb(40,255,0));
    palete64.append(qRgb(60,255,0));
    palete64.append(qRgb(80,255,0));
    palete64.append(qRgb(100,255,0));
    palete64.append(qRgb(120,255,0));
    palete64.append(qRgb(140,255,0));
    palete64.append(qRgb(160,255,0));
    palete64.append(qRgb(180,255,0));
    palete64.append(qRgb(200,255,0));
    palete64.append(qRgb(220,255,0));
    palete64.append(qRgb(240,255,0));
    palete64.append(qRgb(255,255,0));

    palete64.append(qRgb(255,240,0));
    palete64.append(qRgb(255,220,0));
    palete64.append(qRgb(255,200,0));
    palete64.append(qRgb(255,180,0));
    palete64.append(qRgb(255,160,0));
    palete64.append(qRgb(255,140,0));
    palete64.append(qRgb(255,120,0));
    palete64.append(qRgb(255,100,0));
    palete64.append(qRgb(255,80,0));
    palete64.append(qRgb(255,60,0));
    palete64.append(qRgb(255,40,0));
    palete64.append(qRgb(255,20,0));
    palete64.append(qRgb(255,0,0));

    return palete64;
}

QVector<QRgb> Lookup_Tables::colorPalete1280()
{
    QVector<QRgb> palete1280;

    for(int a=0;a<=255;a++)
    {
        palete1280.push_back(qRgb(0, 0, a));
    }
    for(int a=0;a<=255;a++)
    {
        palete1280.push_back(qRgb(0, a, 255));
    }
    for(int a=255;a>=0;a--)
    {
        palete1280.push_back(qRgb(0, 255, a));
    }
    for(int a=0;a<=255;a++)
    {
        palete1280.push_back(qRgb(a, 255, 0));
    }
    for(int a=255;a>=0;a--)
    {
        palete1280.push_back(qRgb(255, a, 0));
    }
    for(int a=0;a<=255;a++)
    {
        palete1280.push_back(qRgb(255, 0, a));
    }
    return palete1280;
}
