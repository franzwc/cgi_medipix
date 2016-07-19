#-------------------------------------------------
#
# Project created by QtCreator 2015-01-28T16:47:01
#
#-------------------------------------------------

QT       += core gui
QT       += network widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Morpheus
TEMPLATE = app


SOURCES += main.cpp\
           mainwindow.cpp \
           lookup_tables.cpp \
    qcustomplot.cpp


HEADERS  += mainwindow.h \
            lookup_tables.h \
    qcustomplot.h

FORMS    += mainwindow.ui
