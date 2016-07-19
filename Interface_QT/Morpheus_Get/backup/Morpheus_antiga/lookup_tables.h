#ifndef LOOKUP_TABLES_H
#define LOOKUP_TABLES_H
#include "mainwindow.h"
#include "lookup_tables.h"

class Lookup_Tables
{
public:
    Lookup_Tables();
    static QVector<QRgb> colorPalete64();
    static QVector<QRgb> colorPalete256();
    static QVector<QRgb> colorPalete512();
};

#endif // LOOKUP_TABLES_H
