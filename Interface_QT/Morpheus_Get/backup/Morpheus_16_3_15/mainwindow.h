/*HEADER FILE
---------------------------------------------------------------------------------------------------
--!@brief mainwindow.h
---------------------------------------------------------------------------------------------------
--! DESCRIPTION:
--!
--! Codigo fonte principal da ui
--!
--!
--! DETAILS:
--!
--!- Project Name: mainwindow
--!- Module Name: mainwindow.h
--!- Tools: Qt Creator
--!- Author: Franz Wagner
--!- Company: LABORATORIO NACIONAL DE LUZ SINCROTRON - GRUPO DETECTORES
--!- Create Date: 25/02/2015
--!- Version: 1.0.0 (mar/2015)
---------------------------------------------------------------------------------------------------
-- LNLS - DET - 2015
---------------------------------------------------------------------------------------------------
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtNetwork>
#include "lookup_tables.h"

class QUdpSocket;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void open_image();

    void start_pserve();

    void finished(QNetworkReply *reply);

    void read_omr();

    void read_dac();

    void read_host();

    void read_send();

    void on_Start_Aquire_clicked();

    void on_Aquire_Time_Input_editingFinished();

    void on_NImages_Input_editingFinished();

    void on_Gap_Input_editingFinished();

    void on_Read_Counter_Input_currentIndexChanged(int index);

    void on_Colour_Mode_Input_currentIndexChanged(int index);

    void on_Read_Write_Input_currentIndexChanged(int index);

    void on_Pixel_Mode_Input_currentIndexChanged(int index);

    void on_Disc_CSM_SPM_Input_currentIndexChanged(int index);

    void on_Count_L_Input_currentIndexChanged(int index);

    void on_Gain_Mode_Input_currentIndexChanged(int index);

    void on_Polarity_Input_currentIndexChanged(int index);

    void on_TH0_Input_editingFinished();

    void on_TH1_Input_editingFinished();

    void on_TH2_Input_editingFinished();

    void on_TH3_Input_editingFinished();

    void on_TH4_Input_editingFinished();

    void on_TH5_Input_editingFinished();

    void on_TH6_Input_editingFinished();

    void on_TH7_Input_editingFinished();

    void on_IPREAMP_Input_editingFinished();

    void on_IKRUM_Input_editingFinished();

    void on_ISHAPER_Input_editingFinished();

    void on_IDISC_Input_editingFinished();

    void on_IDISCLS_Input_editingFinished();

    void on_ISHAPERTEST_Input_editingFinished();

    void on_IDACDISCL_Input_editingFinished();

    void on_IDELAY_Input_editingFinished();

    void on_IDAC_Test_Input_editingFinished();

    void on_IDACDISCH_Input_editingFinished();

    void on_ITPBUFFERIN_Input_editingFinished();

    void on_ITPBUFFEROUT_Input_editingFinished();

    void on_VRPZ_Input_editingFinished();

    void on_VGND_Input_editingFinished();

    void on_VTPREF_Input_editingFinished();

    void on_VFBK_Input_editingFinished();

    void on_VCAS_Input_editingFinished();

    void on_VTPREFA_Input_editingFinished();

    void on_VTPREFB_Input_editingFinished();

    void on_tabWidget_tabBarClicked(int index);

    void on_Send_Eq_clicked();

    void on_HOSTIP_Input_editingFinished();

    void on_HOSTNETMASK_Input_editingFinished();

    void on_SENDIP_Input_editingFinished();

    void on_SENDPORT_Input_editingFinished();

    void on_SENDMAC_Input_editingFinished();

    void on_Stop_Aquire_clicked();

    void on_Path_Input_editingFinished();

    void on_Max_Level_Input_textChanged(const QString &arg1);

    void on_Max_Level_button_clicked();

    void on_HOSTGATEWAY_Input_editingFinished();

    void on_Read_THL_clicked();

    void on_Read_THH_clicked();

    void on_Read_Mask_clicked();

    void on_Read_Test_clicked();

    void on_Start_Scan_Button_clicked();

protected:

    void mouseMoveEvent(QMouseEvent *event);

    void mousePressEvent(QMouseEvent *event);

signals:

public:

    Ui::MainWindow *ui;
    // Http Server
    QNetworkAccessManager *nam;
    // Graphic Scene
    QGraphicsScene *scene;
    QPixmap pixmap;
    // Color Table
    QGraphicsScene *scene_table;
    // Process
    QString process_pserve;
    // Save Path
    QDir Current_Dir;
    QDir Save_Dir;
    QString Current_Path;
    QString Save_Path;
    QString Image_Name;
    // Global Parameters
    QString OP;
    QString TP;
    QString Equalization;
    QString Time;
    QString NImage;
    QString Gap;
    QString RCount;
    QString Colour_Mode;
    QString Read_Write;
    QString Pixel_Mode;
    QString Disc_CSM_SPM;
    QString Count_L;
    QString Gain_Mode;
    QString Polarity;
    // Dacs
    QString th0;
    QString th1;
    QString th2;
    QString th3;
    QString th4;
    QString th5;
    QString th6;
    QString th7;
    QString preamp;
    QString ikrum;
    QString shaper;
    QString disc;
    QString discls;
    QString shapertest;
    QString dacdiscl;
    QString dactest;
    QString dacdisch;
    QString delay;
    QString tpbufferin;
    QString tpbufferout;
    QString rpz;
    QString gnd;
    QString tpref;
    QString fbk;
    QString cas;
    QString tprefa;
    QString tprefb;
    // IP
    QString Host_Ip;
    QString Host_Net;
    QString Host_Gate;
    QString Send_Ip;
    QString Send_Port;
    QString Send_Mac;
    // Decode
    unsigned int LFSR6bits[64];
    unsigned int LFSR12bits[4096];
    // Contagem
    float contagem;
    int pixeis_lidos;
    QString Max_Pixel_Value;
    // Equalizacao
    QStringList Equalizacao_THH;
    QStringList Equalizacao_THL;
    QStringList Equalizacao_MASK;
    QStringList Equalizacao_TEST;
    // Scan Parameters
    QString Scan_From;
    QString Scan_To;
    QString Scan_Step;
    QString Scan_Time;
};


#endif // MAINWINDOW_H
