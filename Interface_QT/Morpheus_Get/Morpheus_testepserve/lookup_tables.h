/*HEADER FILE
---------------------------------------------------------------------------------------------------
--!@brief lookup_tables.h
---------------------------------------------------------------------------------------------------
--! DESCRIPTION:
--!
--! Gera as lookup tables dos color bar
--!
--!
--! DETAILS:
--!
--!- Project Name: lookup_tables
--!- Module Name: lookup_tables.h
--!- Tools: Qt Creator
--!- Author: Franz Wagner
--!- Company: LABORATORIO NACIONAL DE LUZ SINCROTRON - GRUPO DETECTORES
--!- Create Date: 25/02/2015
--!- Version: 1.0.0 (mar/2015)
---------------------------------------------------------------------------------------------------
-- LNLS - DET - 2015
---------------------------------------------------------------------------------------------------
*/
#ifndef LOOKUP_TABLES_H
#define LOOKUP_TABLES_H
#include "mainwindow.h"
#include "lookup_tables.h"

class Lookup_Tables
{
public:
    Lookup_Tables();
    static QVector<QRgb> colorPalete64();
    static QVector<QRgb> colorPalete1280();

};

#endif // LOOKUP_TABLES_H
