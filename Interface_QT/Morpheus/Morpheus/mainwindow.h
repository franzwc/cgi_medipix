#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHostAddress>
#include <QGraphicsScene>

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

    void readPendingDatagrams();

    void readPendingData();

    void read_omr();

    void read_dac();

    void read_network();

    void refresh_dacs_input();

    void plot_image_1bit(QList<char> *pixelmap_1bit);

    void on_Start_Aquire_clicked();

    void on_Aquire_Time_Input_editingFinished();

    void on_NImages_Input_editingFinished();

    void on_Gap_Input_editingFinished();

    void on_Read_Counter_Input_currentIndexChanged(int index);

    void on_Colour_Mode_Input_currentIndexChanged(int index);

    void on_Read_Write_Input_currentIndexChanged(int index);

    void on_Pixel_Mode_Input_currentIndexChanged(int index);

    void on_Disc_CSM_SPM_Input_currentIndexChanged(int index);

    void on_Output_Input_currentIndexChanged(int index);

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

    void on_ready_bar_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    QUdpSocket *udpSocket;
    QHostAddress Address_Transmit;
    QHostAddress Address_Receive;
    QHostAddress Address_Multicast;
    QUdpSocket *udpSocketimagem;
    QGraphicsScene *scene;
    QGraphicsLineItem *lineview;
    int conta_pacote;
    // Global Parameters
    QByteArray OP;
    QByteArray TP;
    QByteArray Equalization;
    QString Time;
    QString NImage;
    QString Gap;
    QString RCount;
    QString Colour_Mode;
    QString Read_Write;
    QString Pixel_Mode;
    QString Disc_CSM_SPM;
    QString PS;
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
    QString Send_Ip;
    QString Send_Port;
    QString Send_Mac;

    QByteArray data;
    QList<char> str;
};

#endif // MAINWINDOW_H
