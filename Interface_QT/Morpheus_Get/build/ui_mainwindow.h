/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *CNPEM;
    QLabel *LNLS;
    QTabWidget *tabWidget;
    QWidget *Aquire;
    QLineEdit *Path_Input;
    QLabel *Path;
    QPushButton *Start_Aquire;
    QPushButton *Stop_Aquire;
    QLabel *Read_Couter;
    QComboBox *Read_Counter_Input;
    QComboBox *Count_L_Input;
    QComboBox *Gain_Mode_Input;
    QLabel *Pixel_Mode;
    QComboBox *Pixel_Mode_Input;
    QLabel *Colour_Mode;
    QLabel *CSM_SPM;
    QComboBox *Disc_CSM_SPM_Input;
    QLabel *Image_Size;
    QLabel *Polarity;
    QComboBox *Polarity_Input;
    QComboBox *Colour_Mode_Input;
    QLabel *Gain_mode;
    QLabel *ReadWrite;
    QComboBox *Read_Write_Input;
    QLineEdit *Gap_Input;
    QLineEdit *Aquire_Time_Input;
    QLabel *Images;
    QLineEdit *NImages_Input;
    QLabel *Gap;
    QLabel *Aquire_Time;
    QLabel *Max_Level;
    QLineEdit *Max_Level_Input;
    QPushButton *Max_Level_button;
    QWidget *Dac_Adjust;
    QWidget *layoutWidget_3;
    QGridLayout *gridLayout_3;
    QLineEdit *TH1_Input;
    QLineEdit *VGND_Input;
    QLineEdit *TH2_Input;
    QLineEdit *VTPREF_Input;
    QLineEdit *TH3_Input;
    QLineEdit *VFBK_Input;
    QLineEdit *TH4_Input;
    QLineEdit *VCAS_Input;
    QLineEdit *TH5_Input;
    QLineEdit *VTPREFA_Input;
    QLineEdit *TH6_Input;
    QLineEdit *VTPREFB_Input;
    QLineEdit *TH7_Input;
    QLabel *Delay;
    QLineEdit *IDELAY_Input;
    QLabel *Tp_BufferIn;
    QLineEdit *ITPBUFFERIN_Input;
    QLabel *Tp_BufferOut;
    QLineEdit *ITPBUFFEROUT_Input;
    QLabel *TH0;
    QLabel *TH1;
    QLabel *TH2;
    QLabel *TH3;
    QLabel *TH4;
    QLabel *TH5;
    QLabel *TH6;
    QLabel *TH7;
    QLineEdit *TH0_Input;
    QLabel *Rpz;
    QLabel *Gnd;
    QLabel *Tp_Ref;
    QLabel *Fbk;
    QLabel *Cas;
    QLabel *Tp_RefA;
    QLabel *Tp_RefB;
    QLineEdit *VRPZ_Input;
    QLabel *Preamp;
    QLineEdit *IPREAMP_Input;
    QLabel *Ikrum;
    QLineEdit *IKRUM_Input;
    QLabel *Shaper;
    QLineEdit *ISHAPER_Input;
    QLabel *Disc;
    QLineEdit *IDISC_Input;
    QLabel *Disc_LS;
    QLineEdit *IDISCLS_Input;
    QLabel *Shaper_Test;
    QLineEdit *ISHAPERTEST_Input;
    QLabel *Dac_DiscL;
    QLineEdit *IDACDISCL_Input;
    QLabel *Dac_Test;
    QLineEdit *IDAC_Test_Input;
    QLabel *Dac_DiscH;
    QLineEdit *IDACDISCH_Input;
    QWidget *tab;
    QLabel *Scan_From;
    QLineEdit *Scan_From_Input;
    QLabel *Scan_To;
    QLineEdit *Scan_To_Input;
    QPushButton *Start_Scan_Button;
    QLineEdit *Scan_Step_Input;
    QLabel *Scan_Step;
    QLabel *Scan_Time;
    QLineEdit *Scan_Time_Input;
    QCustomPlot *custom_Plot;
    QPushButton *y_minus;
    QPushButton *y_plus;
    QPushButton *x_plus;
    QPushButton *x_minus;
    QLabel *TH_Level;
    QLabel *TH_Level_Input;
    QComboBox *Scan_TH;
    QPushButton *Stop_Scan_Button;
    QWidget *Equalization;
    QPushButton *Send_Eq;
    QPushButton *Test_Bit_Disable;
    QPushButton *Write_Eq;
    QLabel *Test_Bit;
    QPushButton *Test_Bit_Enable;
    QLabel *Set_THL;
    QPushButton *Set_THL_All;
    QLineEdit *THL_Input;
    QLabel *Set_THL_3;
    QLineEdit *THH_Input;
    QPushButton *Set_THH_All;
    QPushButton *Enable_All_Test;
    QWidget *Network_Setup;
    QLineEdit *SENDIP_Input;
    QLabel *Send_MAC;
    QLabel *Send_Port;
    QLabel *Server;
    QLabel *Host_Netmask;
    QLineEdit *HOSTIP_Input;
    QLabel *Host;
    QLineEdit *SENDPORT_Input;
    QLabel *Send_IP;
    QLineEdit *SENDMAC_Input;
    QLabel *Host_IP;
    QLineEdit *HOSTNETMASK_Input;
    QLineEdit *HOSTGATEWAY_Input;
    QLabel *Host_Netmask_2;
    QWidget *Test_Pulse;
    QCheckBox *Enable_TP;
    QLineEdit *TP_Pulse_Period_Input;
    QLineEdit *TP_NPulses_Input;
    QLineEdit *TP_Pulse_Spacing_Input;
    QLabel *Pulse_Period;
    QLabel *NPulses;
    QLabel *Pulse_Period_2;
    QLabel *Pulse_Period_3;
    QLabel *Pulse_Period_4;
    QLabel *Pulse_Period_5;
    QPushButton *Read_CTPR;
    QPushButton *CTPR_Enable;
    QPushButton *CTPR_Disable;
    QLabel *label_2;
    QWidget *About;
    QWidget *layoutWidget_5;
    QGridLayout *gridLayout_6;
    QLabel *Equipment_Information;
    QGridLayout *gridLayout_4;
    QLabel *label_48;
    QLabel *Hard_Version;
    QLabel *label_46;
    QLabel *Model;
    QLabel *Sof_Version;
    QLabel *MC10;
    QLabel *Firm_Version;
    QLabel *label_47;
    QLabel *label;
    QGraphicsView *color_table_bar;
    QTextBrowser *textBrowser;
    QLabel *MaxV_Tab;
    QLabel *MidV_Tab;
    QLabel *X;
    QLabel *Y;
    QLabel *Value;
    QLabel *Value_input;
    QLabel *X_Value;
    QLabel *Y_Value;
    QTabWidget *Tab_Preview;
    QWidget *tab_2;
    QGraphicsView *Plot_Window;
    QWidget *tab_3;
    QGraphicsView *Plot_Window_2;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1294, 850);
        MainWindow->setMinimumSize(QSize(1280, 850));
        MainWindow->setSizeIncrement(QSize(0, 0));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(26, 26, 26, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        MainWindow->setPalette(palette);
        QFont font;
        font.setFamily(QStringLiteral("Purisa"));
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        MainWindow->setFont(font);
        MainWindow->setMouseTracking(false);
        MainWindow->setFocusPolicy(Qt::ClickFocus);
        MainWindow->setContextMenuPolicy(Qt::ActionsContextMenu);
        QIcon icon;
        icon.addFile(QStringLiteral("../icone.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setTabShape(QTabWidget::Rounded);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CNPEM = new QLabel(centralWidget);
        CNPEM->setObjectName(QStringLiteral("CNPEM"));
        CNPEM->setEnabled(true);
        CNPEM->setGeometry(QRect(30, 10, 791, 131));
        CNPEM->setPixmap(QPixmap(QString::fromUtf8("../cnpem_black.png")));
        LNLS = new QLabel(centralWidget);
        LNLS->setObjectName(QStringLiteral("LNLS"));
        LNLS->setGeometry(QRect(620, 750, 51, 61));
        LNLS->setPixmap(QPixmap(QString::fromUtf8("../lnls.jpg")));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(640, 210, 620, 510));
        QFont font1;
        font1.setKerning(true);
        font1.setStyleStrategy(QFont::PreferAntialias);
        tabWidget->setFont(font1);
        tabWidget->setMouseTracking(false);
        tabWidget->setFocusPolicy(Qt::ClickFocus);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setElideMode(Qt::ElideNone);
        tabWidget->setUsesScrollButtons(false);
        Aquire = new QWidget();
        Aquire->setObjectName(QStringLiteral("Aquire"));
        Path_Input = new QLineEdit(Aquire);
        Path_Input->setObjectName(QStringLiteral("Path_Input"));
        Path_Input->setGeometry(QRect(340, 122, 241, 31));
        QPalette palette1;
        QBrush brush2(QColor(255, 0, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        QBrush brush3(QColor(159, 158, 158, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        Path_Input->setPalette(palette1);
        Path = new QLabel(Aquire);
        Path->setObjectName(QStringLiteral("Path"));
        Path->setGeometry(QRect(250, 125, 91, 21));
        Start_Aquire = new QPushButton(Aquire);
        Start_Aquire->setObjectName(QStringLiteral("Start_Aquire"));
        Start_Aquire->setGeometry(QRect(200, 180, 85, 35));
        Stop_Aquire = new QPushButton(Aquire);
        Stop_Aquire->setObjectName(QStringLiteral("Stop_Aquire"));
        Stop_Aquire->setGeometry(QRect(335, 180, 85, 35));
        Read_Couter = new QLabel(Aquire);
        Read_Couter->setObjectName(QStringLiteral("Read_Couter"));
        Read_Couter->setGeometry(QRect(21, 250, 122, 25));
        Read_Counter_Input = new QComboBox(Aquire);
        Read_Counter_Input->setObjectName(QStringLiteral("Read_Counter_Input"));
        Read_Counter_Input->setGeometry(QRect(149, 241, 150, 35));
        Read_Counter_Input->setFocusPolicy(Qt::ClickFocus);
        Count_L_Input = new QComboBox(Aquire);
        Count_L_Input->setObjectName(QStringLiteral("Count_L_Input"));
        Count_L_Input->setGeometry(QRect(149, 364, 150, 35));
        Count_L_Input->setFocusPolicy(Qt::ClickFocus);
        Gain_Mode_Input = new QComboBox(Aquire);
        Gain_Mode_Input->setObjectName(QStringLiteral("Gain_Mode_Input"));
        Gain_Mode_Input->setGeometry(QRect(450, 364, 150, 35));
        Gain_Mode_Input->setFocusPolicy(Qt::ClickFocus);
        Pixel_Mode = new QLabel(Aquire);
        Pixel_Mode->setObjectName(QStringLiteral("Pixel_Mode"));
        Pixel_Mode->setGeometry(QRect(320, 330, 94, 25));
        Pixel_Mode_Input = new QComboBox(Aquire);
        Pixel_Mode_Input->setObjectName(QStringLiteral("Pixel_Mode_Input"));
        Pixel_Mode_Input->setGeometry(QRect(450, 323, 150, 35));
        Pixel_Mode_Input->setFocusPolicy(Qt::ClickFocus);
        Colour_Mode = new QLabel(Aquire);
        Colour_Mode->setObjectName(QStringLiteral("Colour_Mode"));
        Colour_Mode->setGeometry(QRect(21, 290, 111, 25));
        CSM_SPM = new QLabel(Aquire);
        CSM_SPM->setObjectName(QStringLiteral("CSM_SPM"));
        CSM_SPM->setGeometry(QRect(21, 330, 121, 25));
        Disc_CSM_SPM_Input = new QComboBox(Aquire);
        Disc_CSM_SPM_Input->setObjectName(QStringLiteral("Disc_CSM_SPM_Input"));
        Disc_CSM_SPM_Input->setGeometry(QRect(149, 323, 150, 35));
        Disc_CSM_SPM_Input->setFocusPolicy(Qt::ClickFocus);
        Image_Size = new QLabel(Aquire);
        Image_Size->setObjectName(QStringLiteral("Image_Size"));
        Image_Size->setGeometry(QRect(21, 370, 99, 25));
        Polarity = new QLabel(Aquire);
        Polarity->setObjectName(QStringLiteral("Polarity"));
        Polarity->setGeometry(QRect(320, 250, 66, 25));
        Polarity_Input = new QComboBox(Aquire);
        Polarity_Input->setObjectName(QStringLiteral("Polarity_Input"));
        Polarity_Input->setGeometry(QRect(450, 241, 150, 35));
        Polarity_Input->setFocusPolicy(Qt::ClickFocus);
        Colour_Mode_Input = new QComboBox(Aquire);
        Colour_Mode_Input->setObjectName(QStringLiteral("Colour_Mode_Input"));
        Colour_Mode_Input->setGeometry(QRect(149, 282, 150, 35));
        Colour_Mode_Input->setFocusPolicy(Qt::ClickFocus);
        Gain_mode = new QLabel(Aquire);
        Gain_mode->setObjectName(QStringLiteral("Gain_mode"));
        Gain_mode->setGeometry(QRect(320, 370, 90, 25));
        ReadWrite = new QLabel(Aquire);
        ReadWrite->setObjectName(QStringLiteral("ReadWrite"));
        ReadWrite->setGeometry(QRect(320, 290, 120, 25));
        Read_Write_Input = new QComboBox(Aquire);
        Read_Write_Input->setObjectName(QStringLiteral("Read_Write_Input"));
        Read_Write_Input->setGeometry(QRect(450, 282, 150, 35));
        Read_Write_Input->setFocusPolicy(Qt::ClickFocus);
        Gap_Input = new QLineEdit(Aquire);
        Gap_Input->setObjectName(QStringLiteral("Gap_Input"));
        Gap_Input->setGeometry(QRect(110, 122, 84, 35));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        Gap_Input->setPalette(palette2);
        Gap_Input->setMouseTracking(false);
        Gap_Input->setAcceptDrops(false);
        Gap_Input->setMaxLength(5);
        Aquire_Time_Input = new QLineEdit(Aquire);
        Aquire_Time_Input->setObjectName(QStringLiteral("Aquire_Time_Input"));
        Aquire_Time_Input->setGeometry(QRect(110, 34, 84, 35));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        Aquire_Time_Input->setPalette(palette3);
        Aquire_Time_Input->setMouseTracking(false);
        Aquire_Time_Input->setAcceptDrops(false);
        Aquire_Time_Input->setMaxLength(10);
        Aquire_Time_Input->setFrame(true);
        Aquire_Time_Input->setCursorMoveStyle(Qt::VisualMoveStyle);
        Aquire_Time_Input->setClearButtonEnabled(false);
        Images = new QLabel(Aquire);
        Images->setObjectName(QStringLiteral("Images"));
        Images->setGeometry(QRect(31, 85, 64, 25));
        NImages_Input = new QLineEdit(Aquire);
        NImages_Input->setObjectName(QStringLiteral("NImages_Input"));
        NImages_Input->setGeometry(QRect(110, 78, 84, 35));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette4.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        NImages_Input->setPalette(palette4);
        NImages_Input->setMouseTracking(false);
        NImages_Input->setAcceptDrops(false);
        NImages_Input->setMaxLength(3);
        Gap = new QLabel(Aquire);
        Gap->setObjectName(QStringLiteral("Gap"));
        Gap->setGeometry(QRect(31, 125, 32, 25));
        Aquire_Time = new QLabel(Aquire);
        Aquire_Time->setObjectName(QStringLiteral("Aquire_Time"));
        Aquire_Time->setGeometry(QRect(31, 40, 109, 25));
        Max_Level = new QLabel(Aquire);
        Max_Level->setObjectName(QStringLiteral("Max_Level"));
        Max_Level->setGeometry(QRect(310, 40, 91, 21));
        Max_Level_Input = new QLineEdit(Aquire);
        Max_Level_Input->setObjectName(QStringLiteral("Max_Level_Input"));
        Max_Level_Input->setGeometry(QRect(410, 34, 111, 35));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette5.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette5.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        Max_Level_Input->setPalette(palette5);
        Max_Level_Input->setLayoutDirection(Qt::RightToLeft);
        Max_Level_Input->setClearButtonEnabled(false);
        Max_Level_button = new QPushButton(Aquire);
        Max_Level_button->setObjectName(QStringLiteral("Max_Level_button"));
        Max_Level_button->setGeometry(QRect(530, 34, 51, 35));
        tabWidget->addTab(Aquire, QString());
        Dac_Adjust = new QWidget();
        Dac_Adjust->setObjectName(QStringLiteral("Dac_Adjust"));
        layoutWidget_3 = new QWidget(Dac_Adjust);
        layoutWidget_3->setObjectName(QStringLiteral("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(30, 30, 501, 406));
        gridLayout_3 = new QGridLayout(layoutWidget_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        TH1_Input = new QLineEdit(layoutWidget_3);
        TH1_Input->setObjectName(QStringLiteral("TH1_Input"));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette6.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette6.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        TH1_Input->setPalette(palette6);
        TH1_Input->setMouseTracking(false);
        TH1_Input->setAcceptDrops(false);
        TH1_Input->setMaxLength(3);

        gridLayout_3->addWidget(TH1_Input, 1, 1, 1, 1);

        VGND_Input = new QLineEdit(layoutWidget_3);
        VGND_Input->setObjectName(QStringLiteral("VGND_Input"));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette7.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette7.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        VGND_Input->setPalette(palette7);
        VGND_Input->setMouseTracking(false);
        VGND_Input->setAcceptDrops(false);
        VGND_Input->setMaxLength(3);

        gridLayout_3->addWidget(VGND_Input, 1, 5, 1, 1);

        TH2_Input = new QLineEdit(layoutWidget_3);
        TH2_Input->setObjectName(QStringLiteral("TH2_Input"));
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette8.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette8.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        TH2_Input->setPalette(palette8);
        TH2_Input->setMouseTracking(false);
        TH2_Input->setAcceptDrops(false);
        TH2_Input->setMaxLength(3);

        gridLayout_3->addWidget(TH2_Input, 2, 1, 1, 1);

        VTPREF_Input = new QLineEdit(layoutWidget_3);
        VTPREF_Input->setObjectName(QStringLiteral("VTPREF_Input"));
        QPalette palette9;
        palette9.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette9.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette9.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        VTPREF_Input->setPalette(palette9);
        VTPREF_Input->setMouseTracking(false);
        VTPREF_Input->setAcceptDrops(false);
        VTPREF_Input->setMaxLength(3);

        gridLayout_3->addWidget(VTPREF_Input, 2, 5, 1, 1);

        TH3_Input = new QLineEdit(layoutWidget_3);
        TH3_Input->setObjectName(QStringLiteral("TH3_Input"));
        QPalette palette10;
        palette10.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette10.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette10.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        TH3_Input->setPalette(palette10);
        TH3_Input->setMouseTracking(false);
        TH3_Input->setAcceptDrops(false);
        TH3_Input->setMaxLength(3);

        gridLayout_3->addWidget(TH3_Input, 3, 1, 1, 1);

        VFBK_Input = new QLineEdit(layoutWidget_3);
        VFBK_Input->setObjectName(QStringLiteral("VFBK_Input"));
        QPalette palette11;
        palette11.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette11.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette11.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        VFBK_Input->setPalette(palette11);
        VFBK_Input->setMouseTracking(false);
        VFBK_Input->setAcceptDrops(false);
        VFBK_Input->setMaxLength(3);

        gridLayout_3->addWidget(VFBK_Input, 3, 5, 1, 1);

        TH4_Input = new QLineEdit(layoutWidget_3);
        TH4_Input->setObjectName(QStringLiteral("TH4_Input"));
        QPalette palette12;
        palette12.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette12.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette12.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        TH4_Input->setPalette(palette12);
        TH4_Input->setMouseTracking(false);
        TH4_Input->setAcceptDrops(false);
        TH4_Input->setMaxLength(3);

        gridLayout_3->addWidget(TH4_Input, 4, 1, 1, 1);

        VCAS_Input = new QLineEdit(layoutWidget_3);
        VCAS_Input->setObjectName(QStringLiteral("VCAS_Input"));
        QPalette palette13;
        palette13.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette13.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette13.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        VCAS_Input->setPalette(palette13);
        VCAS_Input->setMouseTracking(false);
        VCAS_Input->setAcceptDrops(false);
        VCAS_Input->setMaxLength(3);

        gridLayout_3->addWidget(VCAS_Input, 4, 5, 1, 1);

        TH5_Input = new QLineEdit(layoutWidget_3);
        TH5_Input->setObjectName(QStringLiteral("TH5_Input"));
        QPalette palette14;
        palette14.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette14.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette14.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        TH5_Input->setPalette(palette14);
        TH5_Input->setMouseTracking(false);
        TH5_Input->setAcceptDrops(false);
        TH5_Input->setMaxLength(3);

        gridLayout_3->addWidget(TH5_Input, 5, 1, 1, 1);

        VTPREFA_Input = new QLineEdit(layoutWidget_3);
        VTPREFA_Input->setObjectName(QStringLiteral("VTPREFA_Input"));
        QPalette palette15;
        palette15.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette15.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette15.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        VTPREFA_Input->setPalette(palette15);
        VTPREFA_Input->setMouseTracking(false);
        VTPREFA_Input->setAcceptDrops(false);
        VTPREFA_Input->setMaxLength(3);

        gridLayout_3->addWidget(VTPREFA_Input, 5, 5, 1, 1);

        TH6_Input = new QLineEdit(layoutWidget_3);
        TH6_Input->setObjectName(QStringLiteral("TH6_Input"));
        QPalette palette16;
        palette16.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette16.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette16.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        TH6_Input->setPalette(palette16);
        TH6_Input->setMouseTracking(false);
        TH6_Input->setAcceptDrops(false);
        TH6_Input->setMaxLength(3);

        gridLayout_3->addWidget(TH6_Input, 6, 1, 1, 1);

        VTPREFB_Input = new QLineEdit(layoutWidget_3);
        VTPREFB_Input->setObjectName(QStringLiteral("VTPREFB_Input"));
        QPalette palette17;
        palette17.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette17.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette17.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        VTPREFB_Input->setPalette(palette17);
        VTPREFB_Input->setMouseTracking(false);
        VTPREFB_Input->setAcceptDrops(false);
        VTPREFB_Input->setMaxLength(3);

        gridLayout_3->addWidget(VTPREFB_Input, 6, 5, 1, 1);

        TH7_Input = new QLineEdit(layoutWidget_3);
        TH7_Input->setObjectName(QStringLiteral("TH7_Input"));
        QPalette palette18;
        palette18.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette18.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette18.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        TH7_Input->setPalette(palette18);
        TH7_Input->setMouseTracking(false);
        TH7_Input->setAcceptDrops(false);
        TH7_Input->setMaxLength(3);

        gridLayout_3->addWidget(TH7_Input, 7, 1, 1, 1);

        Delay = new QLabel(layoutWidget_3);
        Delay->setObjectName(QStringLiteral("Delay"));

        gridLayout_3->addWidget(Delay, 7, 2, 1, 1);

        IDELAY_Input = new QLineEdit(layoutWidget_3);
        IDELAY_Input->setObjectName(QStringLiteral("IDELAY_Input"));
        QPalette palette19;
        palette19.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette19.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette19.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        IDELAY_Input->setPalette(palette19);
        IDELAY_Input->setMouseTracking(false);
        IDELAY_Input->setAcceptDrops(false);
        IDELAY_Input->setMaxLength(3);

        gridLayout_3->addWidget(IDELAY_Input, 7, 3, 1, 1);

        Tp_BufferIn = new QLabel(layoutWidget_3);
        Tp_BufferIn->setObjectName(QStringLiteral("Tp_BufferIn"));

        gridLayout_3->addWidget(Tp_BufferIn, 8, 2, 1, 1);

        ITPBUFFERIN_Input = new QLineEdit(layoutWidget_3);
        ITPBUFFERIN_Input->setObjectName(QStringLiteral("ITPBUFFERIN_Input"));
        QPalette palette20;
        palette20.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette20.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette20.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        ITPBUFFERIN_Input->setPalette(palette20);
        ITPBUFFERIN_Input->setMouseTracking(false);
        ITPBUFFERIN_Input->setAcceptDrops(false);
        ITPBUFFERIN_Input->setMaxLength(3);

        gridLayout_3->addWidget(ITPBUFFERIN_Input, 8, 3, 1, 1);

        Tp_BufferOut = new QLabel(layoutWidget_3);
        Tp_BufferOut->setObjectName(QStringLiteral("Tp_BufferOut"));

        gridLayout_3->addWidget(Tp_BufferOut, 9, 2, 1, 1);

        ITPBUFFEROUT_Input = new QLineEdit(layoutWidget_3);
        ITPBUFFEROUT_Input->setObjectName(QStringLiteral("ITPBUFFEROUT_Input"));
        QPalette palette21;
        palette21.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette21.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette21.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        ITPBUFFEROUT_Input->setPalette(palette21);
        ITPBUFFEROUT_Input->setMouseTracking(false);
        ITPBUFFEROUT_Input->setAcceptDrops(false);
        ITPBUFFEROUT_Input->setMaxLength(3);

        gridLayout_3->addWidget(ITPBUFFEROUT_Input, 9, 3, 1, 1);

        TH0 = new QLabel(layoutWidget_3);
        TH0->setObjectName(QStringLiteral("TH0"));

        gridLayout_3->addWidget(TH0, 0, 0, 1, 1);

        TH1 = new QLabel(layoutWidget_3);
        TH1->setObjectName(QStringLiteral("TH1"));

        gridLayout_3->addWidget(TH1, 1, 0, 1, 1);

        TH2 = new QLabel(layoutWidget_3);
        TH2->setObjectName(QStringLiteral("TH2"));

        gridLayout_3->addWidget(TH2, 2, 0, 1, 1);

        TH3 = new QLabel(layoutWidget_3);
        TH3->setObjectName(QStringLiteral("TH3"));

        gridLayout_3->addWidget(TH3, 3, 0, 1, 1);

        TH4 = new QLabel(layoutWidget_3);
        TH4->setObjectName(QStringLiteral("TH4"));

        gridLayout_3->addWidget(TH4, 4, 0, 1, 1);

        TH5 = new QLabel(layoutWidget_3);
        TH5->setObjectName(QStringLiteral("TH5"));

        gridLayout_3->addWidget(TH5, 5, 0, 1, 1);

        TH6 = new QLabel(layoutWidget_3);
        TH6->setObjectName(QStringLiteral("TH6"));

        gridLayout_3->addWidget(TH6, 6, 0, 1, 1);

        TH7 = new QLabel(layoutWidget_3);
        TH7->setObjectName(QStringLiteral("TH7"));

        gridLayout_3->addWidget(TH7, 7, 0, 1, 1);

        TH0_Input = new QLineEdit(layoutWidget_3);
        TH0_Input->setObjectName(QStringLiteral("TH0_Input"));
        QPalette palette22;
        palette22.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette22.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette22.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        TH0_Input->setPalette(palette22);
        TH0_Input->setMouseTracking(false);
        TH0_Input->setAcceptDrops(false);
        TH0_Input->setMaxLength(3);

        gridLayout_3->addWidget(TH0_Input, 0, 1, 1, 1);

        Rpz = new QLabel(layoutWidget_3);
        Rpz->setObjectName(QStringLiteral("Rpz"));

        gridLayout_3->addWidget(Rpz, 0, 4, 1, 1);

        Gnd = new QLabel(layoutWidget_3);
        Gnd->setObjectName(QStringLiteral("Gnd"));

        gridLayout_3->addWidget(Gnd, 1, 4, 1, 1);

        Tp_Ref = new QLabel(layoutWidget_3);
        Tp_Ref->setObjectName(QStringLiteral("Tp_Ref"));

        gridLayout_3->addWidget(Tp_Ref, 2, 4, 1, 1);

        Fbk = new QLabel(layoutWidget_3);
        Fbk->setObjectName(QStringLiteral("Fbk"));

        gridLayout_3->addWidget(Fbk, 3, 4, 1, 1);

        Cas = new QLabel(layoutWidget_3);
        Cas->setObjectName(QStringLiteral("Cas"));

        gridLayout_3->addWidget(Cas, 4, 4, 1, 1);

        Tp_RefA = new QLabel(layoutWidget_3);
        Tp_RefA->setObjectName(QStringLiteral("Tp_RefA"));

        gridLayout_3->addWidget(Tp_RefA, 5, 4, 1, 1);

        Tp_RefB = new QLabel(layoutWidget_3);
        Tp_RefB->setObjectName(QStringLiteral("Tp_RefB"));

        gridLayout_3->addWidget(Tp_RefB, 6, 4, 1, 1);

        VRPZ_Input = new QLineEdit(layoutWidget_3);
        VRPZ_Input->setObjectName(QStringLiteral("VRPZ_Input"));
        QPalette palette23;
        palette23.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette23.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette23.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        VRPZ_Input->setPalette(palette23);
        VRPZ_Input->setMouseTracking(false);
        VRPZ_Input->setAcceptDrops(false);
        VRPZ_Input->setMaxLength(3);

        gridLayout_3->addWidget(VRPZ_Input, 0, 5, 1, 1);

        Preamp = new QLabel(layoutWidget_3);
        Preamp->setObjectName(QStringLiteral("Preamp"));

        gridLayout_3->addWidget(Preamp, 8, 0, 1, 1);

        IPREAMP_Input = new QLineEdit(layoutWidget_3);
        IPREAMP_Input->setObjectName(QStringLiteral("IPREAMP_Input"));
        QPalette palette24;
        palette24.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette24.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette24.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        IPREAMP_Input->setPalette(palette24);
        IPREAMP_Input->setMouseTracking(false);
        IPREAMP_Input->setAcceptDrops(false);
        IPREAMP_Input->setMaxLength(3);

        gridLayout_3->addWidget(IPREAMP_Input, 8, 1, 1, 1);

        Ikrum = new QLabel(layoutWidget_3);
        Ikrum->setObjectName(QStringLiteral("Ikrum"));

        gridLayout_3->addWidget(Ikrum, 9, 0, 1, 1);

        IKRUM_Input = new QLineEdit(layoutWidget_3);
        IKRUM_Input->setObjectName(QStringLiteral("IKRUM_Input"));
        QPalette palette25;
        palette25.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette25.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette25.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        IKRUM_Input->setPalette(palette25);
        IKRUM_Input->setMouseTracking(false);
        IKRUM_Input->setAcceptDrops(false);
        IKRUM_Input->setMaxLength(3);

        gridLayout_3->addWidget(IKRUM_Input, 9, 1, 1, 1);

        Shaper = new QLabel(layoutWidget_3);
        Shaper->setObjectName(QStringLiteral("Shaper"));

        gridLayout_3->addWidget(Shaper, 0, 2, 1, 1);

        ISHAPER_Input = new QLineEdit(layoutWidget_3);
        ISHAPER_Input->setObjectName(QStringLiteral("ISHAPER_Input"));
        QPalette palette26;
        palette26.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette26.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette26.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        ISHAPER_Input->setPalette(palette26);
        ISHAPER_Input->setMouseTracking(false);
        ISHAPER_Input->setAcceptDrops(false);
        ISHAPER_Input->setMaxLength(3);

        gridLayout_3->addWidget(ISHAPER_Input, 0, 3, 1, 1);

        Disc = new QLabel(layoutWidget_3);
        Disc->setObjectName(QStringLiteral("Disc"));

        gridLayout_3->addWidget(Disc, 1, 2, 1, 1);

        IDISC_Input = new QLineEdit(layoutWidget_3);
        IDISC_Input->setObjectName(QStringLiteral("IDISC_Input"));
        QPalette palette27;
        palette27.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette27.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette27.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        IDISC_Input->setPalette(palette27);
        IDISC_Input->setMouseTracking(false);
        IDISC_Input->setAcceptDrops(false);
        IDISC_Input->setMaxLength(3);

        gridLayout_3->addWidget(IDISC_Input, 1, 3, 1, 1);

        Disc_LS = new QLabel(layoutWidget_3);
        Disc_LS->setObjectName(QStringLiteral("Disc_LS"));

        gridLayout_3->addWidget(Disc_LS, 2, 2, 1, 1);

        IDISCLS_Input = new QLineEdit(layoutWidget_3);
        IDISCLS_Input->setObjectName(QStringLiteral("IDISCLS_Input"));
        QPalette palette28;
        palette28.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette28.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette28.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        IDISCLS_Input->setPalette(palette28);
        IDISCLS_Input->setMouseTracking(false);
        IDISCLS_Input->setAcceptDrops(false);
        IDISCLS_Input->setMaxLength(3);

        gridLayout_3->addWidget(IDISCLS_Input, 2, 3, 1, 1);

        Shaper_Test = new QLabel(layoutWidget_3);
        Shaper_Test->setObjectName(QStringLiteral("Shaper_Test"));

        gridLayout_3->addWidget(Shaper_Test, 3, 2, 1, 1);

        ISHAPERTEST_Input = new QLineEdit(layoutWidget_3);
        ISHAPERTEST_Input->setObjectName(QStringLiteral("ISHAPERTEST_Input"));
        QPalette palette29;
        palette29.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette29.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette29.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        ISHAPERTEST_Input->setPalette(palette29);
        ISHAPERTEST_Input->setMouseTracking(false);
        ISHAPERTEST_Input->setAcceptDrops(false);
        ISHAPERTEST_Input->setMaxLength(3);

        gridLayout_3->addWidget(ISHAPERTEST_Input, 3, 3, 1, 1);

        Dac_DiscL = new QLabel(layoutWidget_3);
        Dac_DiscL->setObjectName(QStringLiteral("Dac_DiscL"));

        gridLayout_3->addWidget(Dac_DiscL, 4, 2, 1, 1);

        IDACDISCL_Input = new QLineEdit(layoutWidget_3);
        IDACDISCL_Input->setObjectName(QStringLiteral("IDACDISCL_Input"));
        QPalette palette30;
        palette30.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette30.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette30.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        IDACDISCL_Input->setPalette(palette30);
        IDACDISCL_Input->setMouseTracking(false);
        IDACDISCL_Input->setAcceptDrops(false);
        IDACDISCL_Input->setMaxLength(3);

        gridLayout_3->addWidget(IDACDISCL_Input, 4, 3, 1, 1);

        Dac_Test = new QLabel(layoutWidget_3);
        Dac_Test->setObjectName(QStringLiteral("Dac_Test"));

        gridLayout_3->addWidget(Dac_Test, 5, 2, 1, 1);

        IDAC_Test_Input = new QLineEdit(layoutWidget_3);
        IDAC_Test_Input->setObjectName(QStringLiteral("IDAC_Test_Input"));
        QPalette palette31;
        palette31.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette31.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette31.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        IDAC_Test_Input->setPalette(palette31);
        IDAC_Test_Input->setMouseTracking(false);
        IDAC_Test_Input->setAcceptDrops(false);
        IDAC_Test_Input->setMaxLength(3);

        gridLayout_3->addWidget(IDAC_Test_Input, 5, 3, 1, 1);

        Dac_DiscH = new QLabel(layoutWidget_3);
        Dac_DiscH->setObjectName(QStringLiteral("Dac_DiscH"));

        gridLayout_3->addWidget(Dac_DiscH, 6, 2, 1, 1);

        IDACDISCH_Input = new QLineEdit(layoutWidget_3);
        IDACDISCH_Input->setObjectName(QStringLiteral("IDACDISCH_Input"));
        QPalette palette32;
        palette32.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette32.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette32.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        IDACDISCH_Input->setPalette(palette32);
        IDACDISCH_Input->setMouseTracking(false);
        IDACDISCH_Input->setAcceptDrops(false);
        IDACDISCH_Input->setMaxLength(3);

        gridLayout_3->addWidget(IDACDISCH_Input, 6, 3, 1, 1);

        tabWidget->addTab(Dac_Adjust, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        Scan_From = new QLabel(tab);
        Scan_From->setObjectName(QStringLiteral("Scan_From"));
        Scan_From->setGeometry(QRect(40, 350, 100, 20));
        Scan_From_Input = new QLineEdit(tab);
        Scan_From_Input->setObjectName(QStringLiteral("Scan_From_Input"));
        Scan_From_Input->setGeometry(QRect(140, 340, 50, 30));
        QPalette palette33;
        palette33.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette33.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette33.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        Scan_From_Input->setPalette(palette33);
        Scan_To = new QLabel(tab);
        Scan_To->setObjectName(QStringLiteral("Scan_To"));
        Scan_To->setGeometry(QRect(200, 350, 31, 21));
        Scan_To_Input = new QLineEdit(tab);
        Scan_To_Input->setObjectName(QStringLiteral("Scan_To_Input"));
        Scan_To_Input->setGeometry(QRect(240, 340, 50, 30));
        QPalette palette34;
        palette34.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette34.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette34.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        Scan_To_Input->setPalette(palette34);
        Start_Scan_Button = new QPushButton(tab);
        Start_Scan_Button->setObjectName(QStringLiteral("Start_Scan_Button"));
        Start_Scan_Button->setGeometry(QRect(50, 410, 110, 30));
        Scan_Step_Input = new QLineEdit(tab);
        Scan_Step_Input->setObjectName(QStringLiteral("Scan_Step_Input"));
        Scan_Step_Input->setGeometry(QRect(350, 340, 50, 30));
        QPalette palette35;
        palette35.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette35.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette35.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        Scan_Step_Input->setPalette(palette35);
        Scan_Step = new QLabel(tab);
        Scan_Step->setObjectName(QStringLiteral("Scan_Step"));
        Scan_Step->setGeometry(QRect(300, 350, 41, 21));
        Scan_Time = new QLabel(tab);
        Scan_Time->setObjectName(QStringLiteral("Scan_Time"));
        Scan_Time->setGeometry(QRect(410, 350, 41, 21));
        Scan_Time_Input = new QLineEdit(tab);
        Scan_Time_Input->setObjectName(QStringLiteral("Scan_Time_Input"));
        Scan_Time_Input->setGeometry(QRect(460, 340, 50, 30));
        QPalette palette36;
        palette36.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette36.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette36.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        Scan_Time_Input->setPalette(palette36);
        custom_Plot = new QCustomPlot(tab);
        custom_Plot->setObjectName(QStringLiteral("custom_Plot"));
        custom_Plot->setGeometry(QRect(20, 20, 571, 271));
        y_minus = new QPushButton(tab);
        y_minus->setObjectName(QStringLiteral("y_minus"));
        y_minus->setGeometry(QRect(80, 300, 41, 31));
        y_plus = new QPushButton(tab);
        y_plus->setObjectName(QStringLiteral("y_plus"));
        y_plus->setGeometry(QRect(30, 300, 41, 31));
        x_plus = new QPushButton(tab);
        x_plus->setObjectName(QStringLiteral("x_plus"));
        x_plus->setGeometry(QRect(140, 300, 41, 31));
        x_minus = new QPushButton(tab);
        x_minus->setObjectName(QStringLiteral("x_minus"));
        x_minus->setGeometry(QRect(190, 300, 41, 31));
        TH_Level = new QLabel(tab);
        TH_Level->setObjectName(QStringLiteral("TH_Level"));
        TH_Level->setGeometry(QRect(360, 305, 141, 21));
        TH_Level_Input = new QLabel(tab);
        TH_Level_Input->setObjectName(QStringLiteral("TH_Level_Input"));
        TH_Level_Input->setGeometry(QRect(510, 305, 66, 21));
        QPalette palette37;
        palette37.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette37.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette37.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette37.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette37.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette37.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        TH_Level_Input->setPalette(palette37);
        Scan_TH = new QComboBox(tab);
        Scan_TH->setObjectName(QStringLiteral("Scan_TH"));
        Scan_TH->setGeometry(QRect(290, 410, 61, 30));
        Scan_TH->setFocusPolicy(Qt::ClickFocus);
        Stop_Scan_Button = new QPushButton(tab);
        Stop_Scan_Button->setObjectName(QStringLiteral("Stop_Scan_Button"));
        Stop_Scan_Button->setGeometry(QRect(180, 410, 90, 30));
        tabWidget->addTab(tab, QString());
        Equalization = new QWidget();
        Equalization->setObjectName(QStringLiteral("Equalization"));
        Send_Eq = new QPushButton(Equalization);
        Send_Eq->setObjectName(QStringLiteral("Send_Eq"));
        Send_Eq->setGeometry(QRect(30, 80, 96, 31));
        Test_Bit_Disable = new QPushButton(Equalization);
        Test_Bit_Disable->setObjectName(QStringLiteral("Test_Bit_Disable"));
        Test_Bit_Disable->setGeometry(QRect(260, 180, 96, 31));
        Write_Eq = new QPushButton(Equalization);
        Write_Eq->setObjectName(QStringLiteral("Write_Eq"));
        Write_Eq->setGeometry(QRect(30, 130, 96, 31));
        Test_Bit = new QLabel(Equalization);
        Test_Bit->setObjectName(QStringLiteral("Test_Bit"));
        Test_Bit->setGeometry(QRect(260, 40, 91, 21));
        Test_Bit_Enable = new QPushButton(Equalization);
        Test_Bit_Enable->setObjectName(QStringLiteral("Test_Bit_Enable"));
        Test_Bit_Enable->setGeometry(QRect(260, 80, 96, 31));
        Set_THL = new QLabel(Equalization);
        Set_THL->setObjectName(QStringLiteral("Set_THL"));
        Set_THL->setGeometry(QRect(370, 40, 91, 21));
        Set_THL_All = new QPushButton(Equalization);
        Set_THL_All->setObjectName(QStringLiteral("Set_THL_All"));
        Set_THL_All->setGeometry(QRect(370, 130, 96, 31));
        THL_Input = new QLineEdit(Equalization);
        THL_Input->setObjectName(QStringLiteral("THL_Input"));
        THL_Input->setGeometry(QRect(370, 80, 96, 31));
        QPalette palette38;
        palette38.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette38.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette38.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        THL_Input->setPalette(palette38);
        THL_Input->setMouseTracking(false);
        THL_Input->setAcceptDrops(false);
        THL_Input->setMaxLength(3);
        Set_THL_3 = new QLabel(Equalization);
        Set_THL_3->setObjectName(QStringLiteral("Set_THL_3"));
        Set_THL_3->setGeometry(QRect(480, 40, 91, 21));
        THH_Input = new QLineEdit(Equalization);
        THH_Input->setObjectName(QStringLiteral("THH_Input"));
        THH_Input->setGeometry(QRect(480, 80, 96, 31));
        QPalette palette39;
        palette39.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette39.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette39.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        THH_Input->setPalette(palette39);
        THH_Input->setMouseTracking(false);
        THH_Input->setAcceptDrops(false);
        THH_Input->setMaxLength(3);
        Set_THH_All = new QPushButton(Equalization);
        Set_THH_All->setObjectName(QStringLiteral("Set_THH_All"));
        Set_THH_All->setGeometry(QRect(480, 130, 96, 31));
        Enable_All_Test = new QPushButton(Equalization);
        Enable_All_Test->setObjectName(QStringLiteral("Enable_All_Test"));
        Enable_All_Test->setGeometry(QRect(260, 130, 96, 31));
        tabWidget->addTab(Equalization, QString());
        Network_Setup = new QWidget();
        Network_Setup->setObjectName(QStringLiteral("Network_Setup"));
        SENDIP_Input = new QLineEdit(Network_Setup);
        SENDIP_Input->setObjectName(QStringLiteral("SENDIP_Input"));
        SENDIP_Input->setGeometry(QRect(177, 236, 153, 35));
        QPalette palette40;
        palette40.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette40.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette40.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        SENDIP_Input->setPalette(palette40);
        SENDIP_Input->setMouseTracking(false);
        SENDIP_Input->setAcceptDrops(false);
        SENDIP_Input->setMaxLength(15);
        Send_MAC = new QLabel(Network_Setup);
        Send_MAC->setObjectName(QStringLiteral("Send_MAC"));
        Send_MAC->setGeometry(QRect(51, 326, 87, 25));
        Send_Port = new QLabel(Network_Setup);
        Send_Port->setObjectName(QStringLiteral("Send_Port"));
        Send_Port->setGeometry(QRect(51, 286, 92, 25));
        Server = new QLabel(Network_Setup);
        Server->setObjectName(QStringLiteral("Server"));
        Server->setGeometry(QRect(51, 210, 58, 25));
        QFont font2;
        font2.setBold(true);
        font2.setWeight(75);
        Server->setFont(font2);
        Host_Netmask = new QLabel(Network_Setup);
        Host_Netmask->setObjectName(QStringLiteral("Host_Netmask"));
        Host_Netmask->setGeometry(QRect(51, 110, 120, 25));
        HOSTIP_Input = new QLineEdit(Network_Setup);
        HOSTIP_Input->setObjectName(QStringLiteral("HOSTIP_Input"));
        HOSTIP_Input->setGeometry(QRect(177, 60, 153, 35));
        QPalette palette41;
        palette41.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette41.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette41.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        HOSTIP_Input->setPalette(palette41);
        HOSTIP_Input->setMouseTracking(false);
        HOSTIP_Input->setAcceptDrops(false);
        HOSTIP_Input->setMaxLength(15);
        Host = new QLabel(Network_Setup);
        Host->setObjectName(QStringLiteral("Host"));
        Host->setGeometry(QRect(51, 31, 41, 25));
        QPalette palette42;
        QBrush brush4(QColor(0, 0, 0, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette42.setBrush(QPalette::Active, QPalette::Text, brush4);
        palette42.setBrush(QPalette::Inactive, QPalette::Text, brush4);
        palette42.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        Host->setPalette(palette42);
        Host->setFont(font2);
        SENDPORT_Input = new QLineEdit(Network_Setup);
        SENDPORT_Input->setObjectName(QStringLiteral("SENDPORT_Input"));
        SENDPORT_Input->setGeometry(QRect(177, 276, 153, 35));
        QPalette palette43;
        palette43.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette43.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette43.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        SENDPORT_Input->setPalette(palette43);
        SENDPORT_Input->setMouseTracking(false);
        SENDPORT_Input->setAcceptDrops(false);
        SENDPORT_Input->setMaxLength(5);
        Send_IP = new QLabel(Network_Setup);
        Send_IP->setObjectName(QStringLiteral("Send_IP"));
        Send_IP->setGeometry(QRect(51, 246, 73, 25));
        SENDMAC_Input = new QLineEdit(Network_Setup);
        SENDMAC_Input->setObjectName(QStringLiteral("SENDMAC_Input"));
        SENDMAC_Input->setGeometry(QRect(177, 316, 153, 35));
        QPalette palette44;
        palette44.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette44.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette44.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        SENDMAC_Input->setPalette(palette44);
        SENDMAC_Input->setMouseTracking(false);
        SENDMAC_Input->setAcceptDrops(false);
        SENDMAC_Input->setMaxLength(17);
        Host_IP = new QLabel(Network_Setup);
        Host_IP->setObjectName(QStringLiteral("Host_IP"));
        Host_IP->setGeometry(QRect(51, 70, 70, 25));
        HOSTNETMASK_Input = new QLineEdit(Network_Setup);
        HOSTNETMASK_Input->setObjectName(QStringLiteral("HOSTNETMASK_Input"));
        HOSTNETMASK_Input->setGeometry(QRect(177, 100, 153, 35));
        QPalette palette45;
        palette45.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette45.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette45.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        HOSTNETMASK_Input->setPalette(palette45);
        HOSTNETMASK_Input->setMouseTracking(false);
        HOSTNETMASK_Input->setAcceptDrops(false);
        HOSTNETMASK_Input->setMaxLength(15);
        HOSTGATEWAY_Input = new QLineEdit(Network_Setup);
        HOSTGATEWAY_Input->setObjectName(QStringLiteral("HOSTGATEWAY_Input"));
        HOSTGATEWAY_Input->setGeometry(QRect(177, 140, 153, 35));
        QPalette palette46;
        palette46.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette46.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette46.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        HOSTGATEWAY_Input->setPalette(palette46);
        HOSTGATEWAY_Input->setMouseTracking(false);
        HOSTGATEWAY_Input->setAcceptDrops(false);
        HOSTGATEWAY_Input->setMaxLength(15);
        Host_Netmask_2 = new QLabel(Network_Setup);
        Host_Netmask_2->setObjectName(QStringLiteral("Host_Netmask_2"));
        Host_Netmask_2->setGeometry(QRect(50, 150, 120, 25));
        tabWidget->addTab(Network_Setup, QString());
        Test_Pulse = new QWidget();
        Test_Pulse->setObjectName(QStringLiteral("Test_Pulse"));
        Enable_TP = new QCheckBox(Test_Pulse);
        Enable_TP->setObjectName(QStringLiteral("Enable_TP"));
        Enable_TP->setGeometry(QRect(50, 40, 191, 26));
        TP_Pulse_Period_Input = new QLineEdit(Test_Pulse);
        TP_Pulse_Period_Input->setObjectName(QStringLiteral("TP_Pulse_Period_Input"));
        TP_Pulse_Period_Input->setGeometry(QRect(150, 90, 84, 35));
        QPalette palette47;
        palette47.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette47.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette47.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        TP_Pulse_Period_Input->setPalette(palette47);
        TP_Pulse_Period_Input->setMouseTracking(false);
        TP_Pulse_Period_Input->setAcceptDrops(false);
        TP_Pulse_Period_Input->setMaxLength(5);
        TP_NPulses_Input = new QLineEdit(Test_Pulse);
        TP_NPulses_Input->setObjectName(QStringLiteral("TP_NPulses_Input"));
        TP_NPulses_Input->setGeometry(QRect(150, 140, 84, 35));
        QPalette palette48;
        palette48.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette48.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette48.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        TP_NPulses_Input->setPalette(palette48);
        TP_NPulses_Input->setMouseTracking(false);
        TP_NPulses_Input->setAcceptDrops(false);
        TP_NPulses_Input->setMaxLength(5);
        TP_Pulse_Spacing_Input = new QLineEdit(Test_Pulse);
        TP_Pulse_Spacing_Input->setObjectName(QStringLiteral("TP_Pulse_Spacing_Input"));
        TP_Pulse_Spacing_Input->setGeometry(QRect(150, 190, 84, 35));
        QPalette palette49;
        palette49.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette49.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette49.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        TP_Pulse_Spacing_Input->setPalette(palette49);
        TP_Pulse_Spacing_Input->setMouseTracking(false);
        TP_Pulse_Spacing_Input->setAcceptDrops(false);
        TP_Pulse_Spacing_Input->setMaxLength(5);
        Pulse_Period = new QLabel(Test_Pulse);
        Pulse_Period->setObjectName(QStringLiteral("Pulse_Period"));
        Pulse_Period->setGeometry(QRect(30, 100, 111, 21));
        NPulses = new QLabel(Test_Pulse);
        NPulses->setObjectName(QStringLiteral("NPulses"));
        NPulses->setGeometry(QRect(30, 150, 111, 21));
        Pulse_Period_2 = new QLabel(Test_Pulse);
        Pulse_Period_2->setObjectName(QStringLiteral("Pulse_Period_2"));
        Pulse_Period_2->setGeometry(QRect(30, 200, 111, 21));
        Pulse_Period_3 = new QLabel(Test_Pulse);
        Pulse_Period_3->setObjectName(QStringLiteral("Pulse_Period_3"));
        Pulse_Period_3->setGeometry(QRect(240, 100, 111, 21));
        Pulse_Period_4 = new QLabel(Test_Pulse);
        Pulse_Period_4->setObjectName(QStringLiteral("Pulse_Period_4"));
        Pulse_Period_4->setGeometry(QRect(240, 150, 111, 21));
        Pulse_Period_5 = new QLabel(Test_Pulse);
        Pulse_Period_5->setObjectName(QStringLiteral("Pulse_Period_5"));
        Pulse_Period_5->setGeometry(QRect(240, 200, 111, 21));
        Read_CTPR = new QPushButton(Test_Pulse);
        Read_CTPR->setObjectName(QStringLiteral("Read_CTPR"));
        Read_CTPR->setGeometry(QRect(380, 190, 96, 31));
        CTPR_Enable = new QPushButton(Test_Pulse);
        CTPR_Enable->setObjectName(QStringLiteral("CTPR_Enable"));
        CTPR_Enable->setGeometry(QRect(380, 90, 96, 31));
        CTPR_Disable = new QPushButton(Test_Pulse);
        CTPR_Disable->setObjectName(QStringLiteral("CTPR_Disable"));
        CTPR_Disable->setGeometry(QRect(380, 140, 96, 31));
        label_2 = new QLabel(Test_Pulse);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(390, 50, 66, 21));
        tabWidget->addTab(Test_Pulse, QString());
        About = new QWidget();
        About->setObjectName(QStringLiteral("About"));
        layoutWidget_5 = new QWidget(About);
        layoutWidget_5->setObjectName(QStringLiteral("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(40, 30, 221, 153));
        gridLayout_6 = new QGridLayout(layoutWidget_5);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        Equipment_Information = new QLabel(layoutWidget_5);
        Equipment_Information->setObjectName(QStringLiteral("Equipment_Information"));
        Equipment_Information->setFont(font2);

        gridLayout_6->addWidget(Equipment_Information, 0, 0, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        label_48 = new QLabel(layoutWidget_5);
        label_48->setObjectName(QStringLiteral("label_48"));

        gridLayout_4->addWidget(label_48, 3, 1, 1, 1);

        Hard_Version = new QLabel(layoutWidget_5);
        Hard_Version->setObjectName(QStringLiteral("Hard_Version"));

        gridLayout_4->addWidget(Hard_Version, 1, 0, 1, 1);

        label_46 = new QLabel(layoutWidget_5);
        label_46->setObjectName(QStringLiteral("label_46"));

        gridLayout_4->addWidget(label_46, 1, 1, 1, 1);

        Model = new QLabel(layoutWidget_5);
        Model->setObjectName(QStringLiteral("Model"));

        gridLayout_4->addWidget(Model, 0, 0, 1, 1);

        Sof_Version = new QLabel(layoutWidget_5);
        Sof_Version->setObjectName(QStringLiteral("Sof_Version"));

        gridLayout_4->addWidget(Sof_Version, 3, 0, 1, 1);

        MC10 = new QLabel(layoutWidget_5);
        MC10->setObjectName(QStringLiteral("MC10"));

        gridLayout_4->addWidget(MC10, 0, 1, 1, 1);

        Firm_Version = new QLabel(layoutWidget_5);
        Firm_Version->setObjectName(QStringLiteral("Firm_Version"));

        gridLayout_4->addWidget(Firm_Version, 2, 0, 1, 1);

        label_47 = new QLabel(layoutWidget_5);
        label_47->setObjectName(QStringLiteral("label_47"));

        gridLayout_4->addWidget(label_47, 2, 1, 1, 1);


        gridLayout_6->addLayout(gridLayout_4, 1, 0, 1, 1);

        tabWidget->addTab(About, QString());
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 170, 71, 21));
        color_table_bar = new QGraphicsView(centralWidget);
        color_table_bar->setObjectName(QStringLiteral("color_table_bar"));
        color_table_bar->setGeometry(QRect(550, 200, 17, 514));
        color_table_bar->setFocusPolicy(Qt::NoFocus);
        color_table_bar->setContextMenuPolicy(Qt::NoContextMenu);
        color_table_bar->setAcceptDrops(false);
        color_table_bar->setAutoFillBackground(true);
        color_table_bar->setInteractive(false);
        color_table_bar->setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing|QPainter::SmoothPixmapTransform|QPainter::TextAntialiasing);
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(850, 10, 411, 190));
        QPalette palette50;
        QBrush brush5(QColor(0, 255, 1, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette50.setBrush(QPalette::Active, QPalette::Text, brush5);
        palette50.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette50.setBrush(QPalette::Inactive, QPalette::Text, brush5);
        palette50.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette50.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        palette50.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        textBrowser->setPalette(palette50);
        textBrowser->setAcceptDrops(false);
        textBrowser->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        textBrowser->setAutoFormatting(QTextEdit::AutoNone);
        textBrowser->setTabChangesFocus(false);
        MaxV_Tab = new QLabel(centralWidget);
        MaxV_Tab->setObjectName(QStringLiteral("MaxV_Tab"));
        MaxV_Tab->setGeometry(QRect(570, 190, 61, 21));
        QPalette palette51;
        QBrush brush6(QColor(0, 255, 0, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette51.setBrush(QPalette::Active, QPalette::WindowText, brush6);
        palette51.setBrush(QPalette::Active, QPalette::Text, brush6);
        palette51.setBrush(QPalette::Active, QPalette::ButtonText, brush6);
        palette51.setBrush(QPalette::Inactive, QPalette::WindowText, brush6);
        palette51.setBrush(QPalette::Inactive, QPalette::Text, brush6);
        palette51.setBrush(QPalette::Inactive, QPalette::ButtonText, brush6);
        palette51.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette51.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        palette51.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        MaxV_Tab->setPalette(palette51);
        MidV_Tab = new QLabel(centralWidget);
        MidV_Tab->setObjectName(QStringLiteral("MidV_Tab"));
        MidV_Tab->setGeometry(QRect(570, 440, 61, 21));
        QPalette palette52;
        palette52.setBrush(QPalette::Active, QPalette::WindowText, brush6);
        palette52.setBrush(QPalette::Active, QPalette::Text, brush6);
        palette52.setBrush(QPalette::Active, QPalette::ButtonText, brush6);
        palette52.setBrush(QPalette::Inactive, QPalette::WindowText, brush6);
        palette52.setBrush(QPalette::Inactive, QPalette::Text, brush6);
        palette52.setBrush(QPalette::Inactive, QPalette::ButtonText, brush6);
        palette52.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette52.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        palette52.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        MidV_Tab->setPalette(palette52);
        X = new QLabel(centralWidget);
        X->setObjectName(QStringLiteral("X"));
        X->setGeometry(QRect(30, 730, 21, 21));
        QPalette palette53;
        QBrush brush7(QColor(76, 76, 76, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette53.setBrush(QPalette::Active, QPalette::WindowText, brush7);
        palette53.setBrush(QPalette::Inactive, QPalette::WindowText, brush7);
        palette53.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        X->setPalette(palette53);
        Y = new QLabel(centralWidget);
        Y->setObjectName(QStringLiteral("Y"));
        Y->setGeometry(QRect(100, 730, 21, 21));
        QPalette palette54;
        palette54.setBrush(QPalette::Active, QPalette::WindowText, brush7);
        palette54.setBrush(QPalette::Inactive, QPalette::WindowText, brush7);
        palette54.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        Y->setPalette(palette54);
        Value = new QLabel(centralWidget);
        Value->setObjectName(QStringLiteral("Value"));
        Value->setGeometry(QRect(170, 730, 61, 21));
        QPalette palette55;
        palette55.setBrush(QPalette::Active, QPalette::WindowText, brush7);
        QBrush brush8(QColor(60, 60, 60, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette55.setBrush(QPalette::Active, QPalette::Text, brush8);
        palette55.setBrush(QPalette::Inactive, QPalette::WindowText, brush7);
        palette55.setBrush(QPalette::Inactive, QPalette::Text, brush8);
        palette55.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette55.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        Value->setPalette(palette55);
        Value_input = new QLabel(centralWidget);
        Value_input->setObjectName(QStringLiteral("Value_input"));
        Value_input->setGeometry(QRect(230, 730, 111, 21));
        QPalette palette56;
        palette56.setBrush(QPalette::Active, QPalette::WindowText, brush6);
        palette56.setBrush(QPalette::Active, QPalette::Text, brush5);
        palette56.setBrush(QPalette::Inactive, QPalette::WindowText, brush6);
        palette56.setBrush(QPalette::Inactive, QPalette::Text, brush5);
        palette56.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette56.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        Value_input->setPalette(palette56);
        X_Value = new QLabel(centralWidget);
        X_Value->setObjectName(QStringLiteral("X_Value"));
        X_Value->setGeometry(QRect(50, 730, 41, 21));
        QPalette palette57;
        palette57.setBrush(QPalette::Active, QPalette::WindowText, brush6);
        palette57.setBrush(QPalette::Active, QPalette::Text, brush6);
        palette57.setBrush(QPalette::Inactive, QPalette::WindowText, brush6);
        palette57.setBrush(QPalette::Inactive, QPalette::Text, brush6);
        palette57.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette57.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        X_Value->setPalette(palette57);
        Y_Value = new QLabel(centralWidget);
        Y_Value->setObjectName(QStringLiteral("Y_Value"));
        Y_Value->setGeometry(QRect(120, 730, 41, 21));
        QPalette palette58;
        palette58.setBrush(QPalette::Active, QPalette::WindowText, brush6);
        palette58.setBrush(QPalette::Inactive, QPalette::WindowText, brush6);
        palette58.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        Y_Value->setPalette(palette58);
        Tab_Preview = new QTabWidget(centralWidget);
        Tab_Preview->setObjectName(QStringLiteral("Tab_Preview"));
        Tab_Preview->setGeometry(QRect(20, 160, 519, 556));
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        Plot_Window = new QGraphicsView(tab_2);
        Plot_Window->setObjectName(QStringLiteral("Plot_Window"));
        Plot_Window->setGeometry(QRect(0, 0, 514, 514));
        Plot_Window->setMouseTracking(true);
        Plot_Window->setFocusPolicy(Qt::ClickFocus);
        Plot_Window->setContextMenuPolicy(Qt::DefaultContextMenu);
        Plot_Window->setAcceptDrops(false);
        Plot_Window->setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing|QPainter::SmoothPixmapTransform);
        Plot_Window->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        Plot_Window->setResizeAnchor(QGraphicsView::AnchorUnderMouse);
        Plot_Window->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
        Tab_Preview->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        Plot_Window_2 = new QGraphicsView(tab_3);
        Plot_Window_2->setObjectName(QStringLiteral("Plot_Window_2"));
        Plot_Window_2->setGeometry(QRect(0, 0, 514, 514));
        Plot_Window_2->setMouseTracking(true);
        Plot_Window_2->setFocusPolicy(Qt::ClickFocus);
        Plot_Window_2->setContextMenuPolicy(Qt::DefaultContextMenu);
        Plot_Window_2->setAcceptDrops(false);
        Plot_Window_2->setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing|QPainter::SmoothPixmapTransform);
        Plot_Window_2->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        Plot_Window_2->setResizeAnchor(QGraphicsView::AnchorUnderMouse);
        Plot_Window_2->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
        Tab_Preview->addTab(tab_3, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1294, 33));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);
        Tab_Preview->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Morpheus", 0));
        CNPEM->setText(QString());
        LNLS->setText(QString());
        Path->setText(QApplication::translate("MainWindow", "Save Path", 0));
        Start_Aquire->setText(QApplication::translate("MainWindow", "Start", 0));
        Stop_Aquire->setText(QApplication::translate("MainWindow", "Stop", 0));
        Read_Couter->setText(QApplication::translate("MainWindow", "Read Counter", 0));
        Read_Counter_Input->clear();
        Read_Counter_Input->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Counter L", 0)
         << QApplication::translate("MainWindow", "Counter H", 0)
         << QApplication::translate("MainWindow", "Both", 0)
        );
        Count_L_Input->clear();
        Count_L_Input->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "2 x 1 Bit", 0)
         << QApplication::translate("MainWindow", "2 x 12 Bits", 0)
         << QApplication::translate("MainWindow", "2 x 6 Bits", 0)
         << QApplication::translate("MainWindow", "1 x 24 Bits", 0)
        );
        Gain_Mode_Input->clear();
        Gain_Mode_Input->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "SHGM", 0)
         << QApplication::translate("MainWindow", "LGM", 0)
         << QApplication::translate("MainWindow", "HGM", 0)
         << QApplication::translate("MainWindow", "SLGM", 0)
        );
        Pixel_Mode->setText(QApplication::translate("MainWindow", "Pixel Mode", 0));
        Pixel_Mode_Input->clear();
        Pixel_Mode_Input->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Single Pixel", 0)
         << QApplication::translate("MainWindow", "Charge Summing", 0)
        );
        Colour_Mode->setText(QApplication::translate("MainWindow", "Colour Mode", 0));
        CSM_SPM->setText(QApplication::translate("MainWindow", "Disc CSM SPM", 0));
        Disc_CSM_SPM_Input->clear();
        Disc_CSM_SPM_Input->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Disc L", 0)
         << QApplication::translate("MainWindow", "Disc H", 0)
        );
        Image_Size->setText(QApplication::translate("MainWindow", "Image Size", 0));
        Polarity->setText(QApplication::translate("MainWindow", "Polarity", 0));
        Polarity_Input->clear();
        Polarity_Input->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Eletrons", 0)
         << QApplication::translate("MainWindow", "Holes", 0)
        );
        Colour_Mode_Input->clear();
        Colour_Mode_Input->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Fine Pith", 0)
         << QApplication::translate("MainWindow", "Spectroscopic", 0)
        );
        Gain_mode->setText(QApplication::translate("MainWindow", "Gain Mode", 0));
        ReadWrite->setText(QApplication::translate("MainWindow", "Read / Write", 0));
        Read_Write_Input->clear();
        Read_Write_Input->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Sequencial", 0)
         << QApplication::translate("MainWindow", "Continous", 0)
        );
        Gap_Input->setText(QString());
        Images->setText(QApplication::translate("MainWindow", "Images", 0));
        NImages_Input->setText(QString());
        Gap->setText(QApplication::translate("MainWindow", "Gap", 0));
        Aquire_Time->setText(QApplication::translate("MainWindow", "Time", 0));
        Max_Level->setText(QApplication::translate("MainWindow", "Max Level", 0));
        Max_Level_button->setText(QApplication::translate("MainWindow", "Max", 0));
        tabWidget->setTabText(tabWidget->indexOf(Aquire), QApplication::translate("MainWindow", "Acquire", 0));
        Delay->setText(QApplication::translate("MainWindow", "I_Delay", 0));
        Tp_BufferIn->setText(QApplication::translate("MainWindow", "I_TP_BufferIn", 0));
        Tp_BufferOut->setText(QApplication::translate("MainWindow", "I_TP_BufferOut", 0));
        TH0->setText(QApplication::translate("MainWindow", "Threshold 0", 0));
        TH1->setText(QApplication::translate("MainWindow", "Threshold 1", 0));
        TH2->setText(QApplication::translate("MainWindow", "Threshold 2", 0));
        TH3->setText(QApplication::translate("MainWindow", "Threshold 3", 0));
        TH4->setText(QApplication::translate("MainWindow", "Threshold 4", 0));
        TH5->setText(QApplication::translate("MainWindow", "Threshold 5", 0));
        TH6->setText(QApplication::translate("MainWindow", "Threshold 6", 0));
        TH7->setText(QApplication::translate("MainWindow", "Threshold 7", 0));
        Rpz->setText(QApplication::translate("MainWindow", "V_Rpz", 0));
        Gnd->setText(QApplication::translate("MainWindow", "V_Gnd", 0));
        Tp_Ref->setText(QApplication::translate("MainWindow", "V_Tp_Ref", 0));
        Fbk->setText(QApplication::translate("MainWindow", "V_Fbk", 0));
        Cas->setText(QApplication::translate("MainWindow", "V_Cas", 0));
        Tp_RefA->setText(QApplication::translate("MainWindow", "V_Tp_refA", 0));
        Tp_RefB->setText(QApplication::translate("MainWindow", "V_Tp_refB", 0));
        VRPZ_Input->setText(QString());
        Preamp->setText(QApplication::translate("MainWindow", "I_Preamp", 0));
        Ikrum->setText(QApplication::translate("MainWindow", "I_Ikrum", 0));
        Shaper->setText(QApplication::translate("MainWindow", "I_Shaper", 0));
        Disc->setText(QApplication::translate("MainWindow", "I_Disc", 0));
        Disc_LS->setText(QApplication::translate("MainWindow", "I_Disc_LS", 0));
        Shaper_Test->setText(QApplication::translate("MainWindow", "I_Shaper_Test", 0));
        Dac_DiscL->setText(QApplication::translate("MainWindow", "I_DAC_DiscL", 0));
        Dac_Test->setText(QApplication::translate("MainWindow", "I_DAC_Test", 0));
        Dac_DiscH->setText(QApplication::translate("MainWindow", "I_DAC_DiscH", 0));
        tabWidget->setTabText(tabWidget->indexOf(Dac_Adjust), QApplication::translate("MainWindow", "Dac Adjust", 0));
        Scan_From->setText(QApplication::translate("MainWindow", "Scan From", 0));
        Scan_To->setText(QApplication::translate("MainWindow", "To", 0));
        Start_Scan_Button->setText(QApplication::translate("MainWindow", "Start Scan", 0));
        Scan_Step->setText(QApplication::translate("MainWindow", "Step", 0));
        Scan_Time->setText(QApplication::translate("MainWindow", "Time", 0));
        Scan_Time_Input->setText(QString());
        y_minus->setText(QApplication::translate("MainWindow", "y-", 0));
        y_plus->setText(QApplication::translate("MainWindow", "y+", 0));
        x_plus->setText(QApplication::translate("MainWindow", "x+", 0));
        x_minus->setText(QApplication::translate("MainWindow", "x-", 0));
        TH_Level->setText(QApplication::translate("MainWindow", "Scanning Level", 0));
        TH_Level_Input->setText(QString());
        Scan_TH->clear();
        Scan_TH->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "TH0", 0)
         << QApplication::translate("MainWindow", "TH1", 0)
        );
        Stop_Scan_Button->setText(QApplication::translate("MainWindow", "Stop", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Scan", 0));
        Send_Eq->setText(QApplication::translate("MainWindow", "Send Eq", 0));
        Test_Bit_Disable->setText(QApplication::translate("MainWindow", "Disable All", 0));
        Write_Eq->setText(QApplication::translate("MainWindow", "Write Eq", 0));
        Test_Bit->setText(QApplication::translate("MainWindow", "Set Test", 0));
        Test_Bit_Enable->setText(QApplication::translate("MainWindow", "Enable 2x2", 0));
        Set_THL->setText(QApplication::translate("MainWindow", "Set THL", 0));
        Set_THL_All->setText(QApplication::translate("MainWindow", "Set ALL", 0));
        THL_Input->setText(QString());
        Set_THL_3->setText(QApplication::translate("MainWindow", "Set THH", 0));
        THH_Input->setText(QString());
        Set_THH_All->setText(QApplication::translate("MainWindow", "Set ALL", 0));
        Enable_All_Test->setText(QApplication::translate("MainWindow", "Enable All", 0));
        tabWidget->setTabText(tabWidget->indexOf(Equalization), QApplication::translate("MainWindow", "Equalization", 0));
        Send_MAC->setText(QApplication::translate("MainWindow", "Send MAC", 0));
        Send_Port->setText(QApplication::translate("MainWindow", "Send Port", 0));
        Server->setText(QApplication::translate("MainWindow", "Server", 0));
        Host_Netmask->setText(QApplication::translate("MainWindow", "Host Netmask", 0));
        Host->setText(QApplication::translate("MainWindow", "Host", 0));
        Send_IP->setText(QApplication::translate("MainWindow", "Send IP", 0));
        Host_IP->setText(QApplication::translate("MainWindow", "Host IP", 0));
        Host_Netmask_2->setText(QApplication::translate("MainWindow", "Host Gateway", 0));
        tabWidget->setTabText(tabWidget->indexOf(Network_Setup), QApplication::translate("MainWindow", "Network", 0));
        Enable_TP->setText(QApplication::translate("MainWindow", "Enable Test Pulse", 0));
        TP_Pulse_Period_Input->setText(QString());
        TP_NPulses_Input->setText(QString());
        TP_Pulse_Spacing_Input->setText(QString());
        Pulse_Period->setText(QApplication::translate("MainWindow", "Pulse Period", 0));
        NPulses->setText(QApplication::translate("MainWindow", "N Pulses", 0));
        Pulse_Period_2->setText(QApplication::translate("MainWindow", "Spacing", 0));
        Pulse_Period_3->setText(QApplication::translate("MainWindow", "0~236 uS", 0));
        Pulse_Period_4->setText(QApplication::translate("MainWindow", "0~8192", 0));
        Pulse_Period_5->setText(QApplication::translate("MainWindow", "2 ou 4", 0));
        Read_CTPR->setText(QApplication::translate("MainWindow", "Read", 0));
        CTPR_Enable->setText(QApplication::translate("MainWindow", "Enable", 0));
        CTPR_Disable->setText(QApplication::translate("MainWindow", "Disable", 0));
        label_2->setText(QApplication::translate("MainWindow", "CTPR", 0));
        tabWidget->setTabText(tabWidget->indexOf(Test_Pulse), QApplication::translate("MainWindow", "TP", 0));
        Equipment_Information->setText(QApplication::translate("MainWindow", "Equipment Information", 0));
        label_48->setText(QApplication::translate("MainWindow", "1.0", 0));
        Hard_Version->setText(QApplication::translate("MainWindow", "Hardware Version", 0));
        label_46->setText(QApplication::translate("MainWindow", "1.0", 0));
        Model->setText(QApplication::translate("MainWindow", "Model", 0));
        Sof_Version->setText(QApplication::translate("MainWindow", "Software Version", 0));
        MC10->setText(QApplication::translate("MainWindow", "MC 1.0", 0));
        Firm_Version->setText(QApplication::translate("MainWindow", "Firmware Version", 0));
        label_47->setText(QApplication::translate("MainWindow", "1.0", 0));
        tabWidget->setTabText(tabWidget->indexOf(About), QApplication::translate("MainWindow", "About", 0));
        label->setText(QApplication::translate("MainWindow", "Preview", 0));
        MaxV_Tab->setText(QString());
        MidV_Tab->setText(QString());
        X->setText(QApplication::translate("MainWindow", "X=", 0));
        Y->setText(QApplication::translate("MainWindow", "Y=", 0));
        Value->setText(QApplication::translate("MainWindow", "Value=", 0));
        Value_input->setText(QString());
        X_Value->setText(QString());
        Y_Value->setText(QString());
        Tab_Preview->setTabText(Tab_Preview->indexOf(tab_2), QApplication::translate("MainWindow", "Preview", 0));
        Tab_Preview->setTabText(Tab_Preview->indexOf(tab_3), QApplication::translate("MainWindow", "Counter H", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
