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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *CNPEM;
    QLabel *LNLS;
    QTabWidget *tabWidget;
    QWidget *Aquire;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_1;
    QLabel *Aquire_Time;
    QLineEdit *Aquire_Time_Input;
    QLabel *Images;
    QLineEdit *NImages_Input;
    QLabel *Gap;
    QLineEdit *Gap_Input;
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout_2;
    QLabel *Read_Couter;
    QComboBox *Read_Counter_Input;
    QLabel *Polarity;
    QComboBox *Polarity_Input;
    QComboBox *Colour_Mode_Input;
    QLabel *ReadWrite;
    QComboBox *Read_Write_Input;
    QLabel *CSM_SPM;
    QComboBox *Disc_CSM_SPM_Input;
    QLabel *Output;
    QComboBox *Output_Input;
    QLabel *Image_Size;
    QComboBox *Count_L_Input;
    QLabel *Gain_mode;
    QComboBox *Gain_Mode_Input;
    QLabel *Pixel_Mode;
    QComboBox *Pixel_Mode_Input;
    QLabel *Colour_Mode;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_0;
    QPushButton *Start_Aquire;
    QPushButton *Stop_Aquire;
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
    QWidget *Equalization;
    QPushButton *Send_Eq;
    QWidget *Network_Setup;
    QWidget *layoutWidget_4;
    QGridLayout *gridLayout_5;
    QLineEdit *HOSTIP_Input;
    QLabel *Host;
    QLineEdit *SENDPORT_Input;
    QLabel *Send_IP;
    QLineEdit *SENDMAC_Input;
    QLabel *Host_IP;
    QLineEdit *SENDIP_Input;
    QLineEdit *HOSTNETMASK_Input;
    QLabel *Send_MAC;
    QLabel *Send_Port;
    QLabel *Server;
    QLabel *Host_Netmask;
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
    QProgressBar *ready_bar;
    QGraphicsView *Plot_Window;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1228, 800);
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
        MainWindow->setMouseTracking(true);
        MainWindow->setFocusPolicy(Qt::ClickFocus);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setTabShape(QTabWidget::Rounded);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CNPEM = new QLabel(centralWidget);
        CNPEM->setObjectName(QStringLiteral("CNPEM"));
        CNPEM->setGeometry(QRect(30, 20, 791, 131));
        CNPEM->setPixmap(QPixmap(QString::fromUtf8("../cnpem_black.png")));
        LNLS = new QLabel(centralWidget);
        LNLS->setObjectName(QStringLiteral("LNLS"));
        LNLS->setGeometry(QRect(550, 690, 51, 61));
        LNLS->setPixmap(QPixmap(QString::fromUtf8("../lnls.jpg")));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(590, 160, 621, 511));
        QFont font1;
        font1.setKerning(true);
        font1.setStyleStrategy(QFont::PreferAntialias);
        tabWidget->setFont(font1);
        tabWidget->setMouseTracking(true);
        tabWidget->setFocusPolicy(Qt::ClickFocus);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setElideMode(Qt::ElideNone);
        tabWidget->setUsesScrollButtons(false);
        Aquire = new QWidget();
        Aquire->setObjectName(QStringLiteral("Aquire"));
        layoutWidget = new QWidget(Aquire);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 30, 201, 134));
        gridLayout_1 = new QGridLayout(layoutWidget);
        gridLayout_1->setSpacing(6);
        gridLayout_1->setContentsMargins(11, 11, 11, 11);
        gridLayout_1->setObjectName(QStringLiteral("gridLayout_1"));
        gridLayout_1->setContentsMargins(0, 0, 0, 0);
        Aquire_Time = new QLabel(layoutWidget);
        Aquire_Time->setObjectName(QStringLiteral("Aquire_Time"));

        gridLayout_1->addWidget(Aquire_Time, 0, 0, 1, 1);

        Aquire_Time_Input = new QLineEdit(layoutWidget);
        Aquire_Time_Input->setObjectName(QStringLiteral("Aquire_Time_Input"));
        QPalette palette1;
        QBrush brush2(QColor(255, 0, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        QBrush brush3(QColor(159, 158, 158, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        Aquire_Time_Input->setPalette(palette1);
        Aquire_Time_Input->setMouseTracking(false);
        Aquire_Time_Input->setAcceptDrops(false);
        Aquire_Time_Input->setMaxLength(7);
        Aquire_Time_Input->setFrame(true);
        Aquire_Time_Input->setCursorMoveStyle(Qt::VisualMoveStyle);
        Aquire_Time_Input->setClearButtonEnabled(false);

        gridLayout_1->addWidget(Aquire_Time_Input, 0, 1, 1, 1);

        Images = new QLabel(layoutWidget);
        Images->setObjectName(QStringLiteral("Images"));

        gridLayout_1->addWidget(Images, 1, 0, 1, 1);

        NImages_Input = new QLineEdit(layoutWidget);
        NImages_Input->setObjectName(QStringLiteral("NImages_Input"));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        NImages_Input->setPalette(palette2);
        NImages_Input->setMouseTracking(false);
        NImages_Input->setAcceptDrops(false);
        NImages_Input->setMaxLength(3);

        gridLayout_1->addWidget(NImages_Input, 1, 1, 1, 1);

        Gap = new QLabel(layoutWidget);
        Gap->setObjectName(QStringLiteral("Gap"));

        gridLayout_1->addWidget(Gap, 2, 0, 1, 1);

        Gap_Input = new QLineEdit(layoutWidget);
        Gap_Input->setObjectName(QStringLiteral("Gap_Input"));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        Gap_Input->setPalette(palette3);
        Gap_Input->setMouseTracking(false);
        Gap_Input->setAcceptDrops(false);
        Gap_Input->setMaxLength(5);

        gridLayout_1->addWidget(Gap_Input, 2, 1, 1, 1);

        layoutWidget_2 = new QWidget(Aquire);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(30, 180, 561, 201));
        gridLayout_2 = new QGridLayout(layoutWidget_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        Read_Couter = new QLabel(layoutWidget_2);
        Read_Couter->setObjectName(QStringLiteral("Read_Couter"));

        gridLayout_2->addWidget(Read_Couter, 0, 0, 1, 1);

        Read_Counter_Input = new QComboBox(layoutWidget_2);
        Read_Counter_Input->setObjectName(QStringLiteral("Read_Counter_Input"));
        Read_Counter_Input->setFocusPolicy(Qt::ClickFocus);

        gridLayout_2->addWidget(Read_Counter_Input, 0, 1, 1, 1);

        Polarity = new QLabel(layoutWidget_2);
        Polarity->setObjectName(QStringLiteral("Polarity"));

        gridLayout_2->addWidget(Polarity, 0, 2, 1, 1);

        Polarity_Input = new QComboBox(layoutWidget_2);
        Polarity_Input->setObjectName(QStringLiteral("Polarity_Input"));
        Polarity_Input->setFocusPolicy(Qt::ClickFocus);

        gridLayout_2->addWidget(Polarity_Input, 0, 3, 1, 1);

        Colour_Mode_Input = new QComboBox(layoutWidget_2);
        Colour_Mode_Input->setObjectName(QStringLiteral("Colour_Mode_Input"));
        Colour_Mode_Input->setFocusPolicy(Qt::ClickFocus);

        gridLayout_2->addWidget(Colour_Mode_Input, 1, 1, 1, 1);

        ReadWrite = new QLabel(layoutWidget_2);
        ReadWrite->setObjectName(QStringLiteral("ReadWrite"));

        gridLayout_2->addWidget(ReadWrite, 1, 2, 1, 1);

        Read_Write_Input = new QComboBox(layoutWidget_2);
        Read_Write_Input->setObjectName(QStringLiteral("Read_Write_Input"));
        Read_Write_Input->setFocusPolicy(Qt::ClickFocus);

        gridLayout_2->addWidget(Read_Write_Input, 1, 3, 1, 1);

        CSM_SPM = new QLabel(layoutWidget_2);
        CSM_SPM->setObjectName(QStringLiteral("CSM_SPM"));

        gridLayout_2->addWidget(CSM_SPM, 2, 0, 1, 1);

        Disc_CSM_SPM_Input = new QComboBox(layoutWidget_2);
        Disc_CSM_SPM_Input->setObjectName(QStringLiteral("Disc_CSM_SPM_Input"));
        Disc_CSM_SPM_Input->setFocusPolicy(Qt::ClickFocus);

        gridLayout_2->addWidget(Disc_CSM_SPM_Input, 2, 1, 1, 1);

        Output = new QLabel(layoutWidget_2);
        Output->setObjectName(QStringLiteral("Output"));

        gridLayout_2->addWidget(Output, 2, 2, 1, 1);

        Output_Input = new QComboBox(layoutWidget_2);
        Output_Input->setObjectName(QStringLiteral("Output_Input"));
        Output_Input->setFocusPolicy(Qt::ClickFocus);

        gridLayout_2->addWidget(Output_Input, 2, 3, 1, 1);

        Image_Size = new QLabel(layoutWidget_2);
        Image_Size->setObjectName(QStringLiteral("Image_Size"));

        gridLayout_2->addWidget(Image_Size, 3, 0, 1, 1);

        Count_L_Input = new QComboBox(layoutWidget_2);
        Count_L_Input->setObjectName(QStringLiteral("Count_L_Input"));
        Count_L_Input->setFocusPolicy(Qt::ClickFocus);

        gridLayout_2->addWidget(Count_L_Input, 3, 1, 1, 1);

        Gain_mode = new QLabel(layoutWidget_2);
        Gain_mode->setObjectName(QStringLiteral("Gain_mode"));

        gridLayout_2->addWidget(Gain_mode, 3, 2, 1, 1);

        Gain_Mode_Input = new QComboBox(layoutWidget_2);
        Gain_Mode_Input->setObjectName(QStringLiteral("Gain_Mode_Input"));
        Gain_Mode_Input->setFocusPolicy(Qt::ClickFocus);

        gridLayout_2->addWidget(Gain_Mode_Input, 3, 3, 1, 1);

        Pixel_Mode = new QLabel(layoutWidget_2);
        Pixel_Mode->setObjectName(QStringLiteral("Pixel_Mode"));

        gridLayout_2->addWidget(Pixel_Mode, 4, 0, 1, 1);

        Pixel_Mode_Input = new QComboBox(layoutWidget_2);
        Pixel_Mode_Input->setObjectName(QStringLiteral("Pixel_Mode_Input"));
        Pixel_Mode_Input->setFocusPolicy(Qt::ClickFocus);

        gridLayout_2->addWidget(Pixel_Mode_Input, 4, 1, 1, 1);

        Colour_Mode = new QLabel(layoutWidget_2);
        Colour_Mode->setObjectName(QStringLiteral("Colour_Mode"));

        gridLayout_2->addWidget(Colour_Mode, 1, 0, 1, 1);

        layoutWidget1 = new QWidget(Aquire);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(320, 30, 87, 78));
        gridLayout_0 = new QGridLayout(layoutWidget1);
        gridLayout_0->setSpacing(6);
        gridLayout_0->setContentsMargins(11, 11, 11, 11);
        gridLayout_0->setObjectName(QStringLiteral("gridLayout_0"));
        gridLayout_0->setContentsMargins(0, 0, 0, 0);
        Start_Aquire = new QPushButton(layoutWidget1);
        Start_Aquire->setObjectName(QStringLiteral("Start_Aquire"));

        gridLayout_0->addWidget(Start_Aquire, 0, 0, 1, 1);

        Stop_Aquire = new QPushButton(layoutWidget1);
        Stop_Aquire->setObjectName(QStringLiteral("Stop_Aquire"));

        gridLayout_0->addWidget(Stop_Aquire, 1, 0, 1, 1);

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
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette4.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        TH1_Input->setPalette(palette4);
        TH1_Input->setMouseTracking(false);
        TH1_Input->setAcceptDrops(false);
        TH1_Input->setMaxLength(3);

        gridLayout_3->addWidget(TH1_Input, 1, 1, 1, 1);

        VGND_Input = new QLineEdit(layoutWidget_3);
        VGND_Input->setObjectName(QStringLiteral("VGND_Input"));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette5.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette5.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        VGND_Input->setPalette(palette5);
        VGND_Input->setMouseTracking(false);
        VGND_Input->setAcceptDrops(false);
        VGND_Input->setMaxLength(3);

        gridLayout_3->addWidget(VGND_Input, 1, 5, 1, 1);

        TH2_Input = new QLineEdit(layoutWidget_3);
        TH2_Input->setObjectName(QStringLiteral("TH2_Input"));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette6.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette6.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        TH2_Input->setPalette(palette6);
        TH2_Input->setMouseTracking(false);
        TH2_Input->setAcceptDrops(false);
        TH2_Input->setMaxLength(3);

        gridLayout_3->addWidget(TH2_Input, 2, 1, 1, 1);

        VTPREF_Input = new QLineEdit(layoutWidget_3);
        VTPREF_Input->setObjectName(QStringLiteral("VTPREF_Input"));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette7.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette7.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        VTPREF_Input->setPalette(palette7);
        VTPREF_Input->setMouseTracking(false);
        VTPREF_Input->setAcceptDrops(false);
        VTPREF_Input->setMaxLength(3);

        gridLayout_3->addWidget(VTPREF_Input, 2, 5, 1, 1);

        TH3_Input = new QLineEdit(layoutWidget_3);
        TH3_Input->setObjectName(QStringLiteral("TH3_Input"));
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette8.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette8.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        TH3_Input->setPalette(palette8);
        TH3_Input->setMouseTracking(false);
        TH3_Input->setAcceptDrops(false);
        TH3_Input->setMaxLength(3);

        gridLayout_3->addWidget(TH3_Input, 3, 1, 1, 1);

        VFBK_Input = new QLineEdit(layoutWidget_3);
        VFBK_Input->setObjectName(QStringLiteral("VFBK_Input"));
        QPalette palette9;
        palette9.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette9.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette9.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        VFBK_Input->setPalette(palette9);
        VFBK_Input->setMouseTracking(false);
        VFBK_Input->setAcceptDrops(false);
        VFBK_Input->setMaxLength(3);

        gridLayout_3->addWidget(VFBK_Input, 3, 5, 1, 1);

        TH4_Input = new QLineEdit(layoutWidget_3);
        TH4_Input->setObjectName(QStringLiteral("TH4_Input"));
        QPalette palette10;
        palette10.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette10.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette10.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        TH4_Input->setPalette(palette10);
        TH4_Input->setMouseTracking(false);
        TH4_Input->setAcceptDrops(false);
        TH4_Input->setMaxLength(3);

        gridLayout_3->addWidget(TH4_Input, 4, 1, 1, 1);

        VCAS_Input = new QLineEdit(layoutWidget_3);
        VCAS_Input->setObjectName(QStringLiteral("VCAS_Input"));
        QPalette palette11;
        palette11.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette11.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette11.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        VCAS_Input->setPalette(palette11);
        VCAS_Input->setMouseTracking(false);
        VCAS_Input->setAcceptDrops(false);
        VCAS_Input->setMaxLength(3);

        gridLayout_3->addWidget(VCAS_Input, 4, 5, 1, 1);

        TH5_Input = new QLineEdit(layoutWidget_3);
        TH5_Input->setObjectName(QStringLiteral("TH5_Input"));
        QPalette palette12;
        palette12.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette12.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette12.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        TH5_Input->setPalette(palette12);
        TH5_Input->setMouseTracking(false);
        TH5_Input->setAcceptDrops(false);
        TH5_Input->setMaxLength(3);

        gridLayout_3->addWidget(TH5_Input, 5, 1, 1, 1);

        VTPREFA_Input = new QLineEdit(layoutWidget_3);
        VTPREFA_Input->setObjectName(QStringLiteral("VTPREFA_Input"));
        QPalette palette13;
        palette13.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette13.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette13.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        VTPREFA_Input->setPalette(palette13);
        VTPREFA_Input->setMouseTracking(false);
        VTPREFA_Input->setAcceptDrops(false);
        VTPREFA_Input->setMaxLength(3);

        gridLayout_3->addWidget(VTPREFA_Input, 5, 5, 1, 1);

        TH6_Input = new QLineEdit(layoutWidget_3);
        TH6_Input->setObjectName(QStringLiteral("TH6_Input"));
        QPalette palette14;
        palette14.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette14.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette14.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        TH6_Input->setPalette(palette14);
        TH6_Input->setMouseTracking(false);
        TH6_Input->setAcceptDrops(false);
        TH6_Input->setMaxLength(3);

        gridLayout_3->addWidget(TH6_Input, 6, 1, 1, 1);

        VTPREFB_Input = new QLineEdit(layoutWidget_3);
        VTPREFB_Input->setObjectName(QStringLiteral("VTPREFB_Input"));
        QPalette palette15;
        palette15.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette15.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette15.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        VTPREFB_Input->setPalette(palette15);
        VTPREFB_Input->setMouseTracking(false);
        VTPREFB_Input->setAcceptDrops(false);
        VTPREFB_Input->setMaxLength(3);

        gridLayout_3->addWidget(VTPREFB_Input, 6, 5, 1, 1);

        TH7_Input = new QLineEdit(layoutWidget_3);
        TH7_Input->setObjectName(QStringLiteral("TH7_Input"));
        QPalette palette16;
        palette16.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette16.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette16.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        TH7_Input->setPalette(palette16);
        TH7_Input->setMouseTracking(false);
        TH7_Input->setAcceptDrops(false);
        TH7_Input->setMaxLength(3);

        gridLayout_3->addWidget(TH7_Input, 7, 1, 1, 1);

        Delay = new QLabel(layoutWidget_3);
        Delay->setObjectName(QStringLiteral("Delay"));

        gridLayout_3->addWidget(Delay, 7, 2, 1, 1);

        IDELAY_Input = new QLineEdit(layoutWidget_3);
        IDELAY_Input->setObjectName(QStringLiteral("IDELAY_Input"));
        QPalette palette17;
        palette17.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette17.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette17.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        IDELAY_Input->setPalette(palette17);
        IDELAY_Input->setMouseTracking(false);
        IDELAY_Input->setAcceptDrops(false);
        IDELAY_Input->setMaxLength(3);

        gridLayout_3->addWidget(IDELAY_Input, 7, 3, 1, 1);

        Tp_BufferIn = new QLabel(layoutWidget_3);
        Tp_BufferIn->setObjectName(QStringLiteral("Tp_BufferIn"));

        gridLayout_3->addWidget(Tp_BufferIn, 8, 2, 1, 1);

        ITPBUFFERIN_Input = new QLineEdit(layoutWidget_3);
        ITPBUFFERIN_Input->setObjectName(QStringLiteral("ITPBUFFERIN_Input"));
        QPalette palette18;
        palette18.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette18.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette18.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        ITPBUFFERIN_Input->setPalette(palette18);
        ITPBUFFERIN_Input->setMouseTracking(false);
        ITPBUFFERIN_Input->setAcceptDrops(false);
        ITPBUFFERIN_Input->setMaxLength(3);

        gridLayout_3->addWidget(ITPBUFFERIN_Input, 8, 3, 1, 1);

        Tp_BufferOut = new QLabel(layoutWidget_3);
        Tp_BufferOut->setObjectName(QStringLiteral("Tp_BufferOut"));

        gridLayout_3->addWidget(Tp_BufferOut, 9, 2, 1, 1);

        ITPBUFFEROUT_Input = new QLineEdit(layoutWidget_3);
        ITPBUFFEROUT_Input->setObjectName(QStringLiteral("ITPBUFFEROUT_Input"));
        QPalette palette19;
        palette19.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette19.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette19.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        ITPBUFFEROUT_Input->setPalette(palette19);
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
        QPalette palette20;
        palette20.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette20.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette20.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        TH0_Input->setPalette(palette20);
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
        QPalette palette21;
        palette21.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette21.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette21.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        VRPZ_Input->setPalette(palette21);
        VRPZ_Input->setMouseTracking(false);
        VRPZ_Input->setAcceptDrops(false);
        VRPZ_Input->setMaxLength(3);

        gridLayout_3->addWidget(VRPZ_Input, 0, 5, 1, 1);

        Preamp = new QLabel(layoutWidget_3);
        Preamp->setObjectName(QStringLiteral("Preamp"));

        gridLayout_3->addWidget(Preamp, 8, 0, 1, 1);

        IPREAMP_Input = new QLineEdit(layoutWidget_3);
        IPREAMP_Input->setObjectName(QStringLiteral("IPREAMP_Input"));
        QPalette palette22;
        palette22.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette22.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette22.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        IPREAMP_Input->setPalette(palette22);
        IPREAMP_Input->setMouseTracking(false);
        IPREAMP_Input->setAcceptDrops(false);
        IPREAMP_Input->setMaxLength(3);

        gridLayout_3->addWidget(IPREAMP_Input, 8, 1, 1, 1);

        Ikrum = new QLabel(layoutWidget_3);
        Ikrum->setObjectName(QStringLiteral("Ikrum"));

        gridLayout_3->addWidget(Ikrum, 9, 0, 1, 1);

        IKRUM_Input = new QLineEdit(layoutWidget_3);
        IKRUM_Input->setObjectName(QStringLiteral("IKRUM_Input"));
        QPalette palette23;
        palette23.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette23.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette23.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        IKRUM_Input->setPalette(palette23);
        IKRUM_Input->setMouseTracking(false);
        IKRUM_Input->setAcceptDrops(false);
        IKRUM_Input->setMaxLength(3);

        gridLayout_3->addWidget(IKRUM_Input, 9, 1, 1, 1);

        Shaper = new QLabel(layoutWidget_3);
        Shaper->setObjectName(QStringLiteral("Shaper"));

        gridLayout_3->addWidget(Shaper, 0, 2, 1, 1);

        ISHAPER_Input = new QLineEdit(layoutWidget_3);
        ISHAPER_Input->setObjectName(QStringLiteral("ISHAPER_Input"));
        QPalette palette24;
        palette24.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette24.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette24.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        ISHAPER_Input->setPalette(palette24);
        ISHAPER_Input->setMouseTracking(false);
        ISHAPER_Input->setAcceptDrops(false);
        ISHAPER_Input->setMaxLength(3);

        gridLayout_3->addWidget(ISHAPER_Input, 0, 3, 1, 1);

        Disc = new QLabel(layoutWidget_3);
        Disc->setObjectName(QStringLiteral("Disc"));

        gridLayout_3->addWidget(Disc, 1, 2, 1, 1);

        IDISC_Input = new QLineEdit(layoutWidget_3);
        IDISC_Input->setObjectName(QStringLiteral("IDISC_Input"));
        QPalette palette25;
        palette25.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette25.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette25.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        IDISC_Input->setPalette(palette25);
        IDISC_Input->setMouseTracking(false);
        IDISC_Input->setAcceptDrops(false);
        IDISC_Input->setMaxLength(3);

        gridLayout_3->addWidget(IDISC_Input, 1, 3, 1, 1);

        Disc_LS = new QLabel(layoutWidget_3);
        Disc_LS->setObjectName(QStringLiteral("Disc_LS"));

        gridLayout_3->addWidget(Disc_LS, 2, 2, 1, 1);

        IDISCLS_Input = new QLineEdit(layoutWidget_3);
        IDISCLS_Input->setObjectName(QStringLiteral("IDISCLS_Input"));
        QPalette palette26;
        palette26.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette26.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette26.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        IDISCLS_Input->setPalette(palette26);
        IDISCLS_Input->setMouseTracking(false);
        IDISCLS_Input->setAcceptDrops(false);
        IDISCLS_Input->setMaxLength(3);

        gridLayout_3->addWidget(IDISCLS_Input, 2, 3, 1, 1);

        Shaper_Test = new QLabel(layoutWidget_3);
        Shaper_Test->setObjectName(QStringLiteral("Shaper_Test"));

        gridLayout_3->addWidget(Shaper_Test, 3, 2, 1, 1);

        ISHAPERTEST_Input = new QLineEdit(layoutWidget_3);
        ISHAPERTEST_Input->setObjectName(QStringLiteral("ISHAPERTEST_Input"));
        QPalette palette27;
        palette27.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette27.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette27.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        ISHAPERTEST_Input->setPalette(palette27);
        ISHAPERTEST_Input->setMouseTracking(false);
        ISHAPERTEST_Input->setAcceptDrops(false);
        ISHAPERTEST_Input->setMaxLength(3);

        gridLayout_3->addWidget(ISHAPERTEST_Input, 3, 3, 1, 1);

        Dac_DiscL = new QLabel(layoutWidget_3);
        Dac_DiscL->setObjectName(QStringLiteral("Dac_DiscL"));

        gridLayout_3->addWidget(Dac_DiscL, 4, 2, 1, 1);

        IDACDISCL_Input = new QLineEdit(layoutWidget_3);
        IDACDISCL_Input->setObjectName(QStringLiteral("IDACDISCL_Input"));
        QPalette palette28;
        palette28.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette28.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette28.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        IDACDISCL_Input->setPalette(palette28);
        IDACDISCL_Input->setMouseTracking(false);
        IDACDISCL_Input->setAcceptDrops(false);
        IDACDISCL_Input->setMaxLength(3);

        gridLayout_3->addWidget(IDACDISCL_Input, 4, 3, 1, 1);

        Dac_Test = new QLabel(layoutWidget_3);
        Dac_Test->setObjectName(QStringLiteral("Dac_Test"));

        gridLayout_3->addWidget(Dac_Test, 5, 2, 1, 1);

        IDAC_Test_Input = new QLineEdit(layoutWidget_3);
        IDAC_Test_Input->setObjectName(QStringLiteral("IDAC_Test_Input"));
        QPalette palette29;
        palette29.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette29.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette29.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        IDAC_Test_Input->setPalette(palette29);
        IDAC_Test_Input->setMouseTracking(false);
        IDAC_Test_Input->setAcceptDrops(false);
        IDAC_Test_Input->setMaxLength(3);

        gridLayout_3->addWidget(IDAC_Test_Input, 5, 3, 1, 1);

        Dac_DiscH = new QLabel(layoutWidget_3);
        Dac_DiscH->setObjectName(QStringLiteral("Dac_DiscH"));

        gridLayout_3->addWidget(Dac_DiscH, 6, 2, 1, 1);

        IDACDISCH_Input = new QLineEdit(layoutWidget_3);
        IDACDISCH_Input->setObjectName(QStringLiteral("IDACDISCH_Input"));
        QPalette palette30;
        palette30.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette30.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette30.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        IDACDISCH_Input->setPalette(palette30);
        IDACDISCH_Input->setMouseTracking(false);
        IDACDISCH_Input->setAcceptDrops(false);
        IDACDISCH_Input->setMaxLength(3);

        gridLayout_3->addWidget(IDACDISCH_Input, 6, 3, 1, 1);

        tabWidget->addTab(Dac_Adjust, QString());
        Equalization = new QWidget();
        Equalization->setObjectName(QStringLiteral("Equalization"));
        Send_Eq = new QPushButton(Equalization);
        Send_Eq->setObjectName(QStringLiteral("Send_Eq"));
        Send_Eq->setGeometry(QRect(70, 70, 96, 31));
        tabWidget->addTab(Equalization, QString());
        Network_Setup = new QWidget();
        Network_Setup->setObjectName(QStringLiteral("Network_Setup"));
        layoutWidget_4 = new QWidget(Network_Setup);
        layoutWidget_4->setObjectName(QStringLiteral("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(50, 30, 281, 263));
        gridLayout_5 = new QGridLayout(layoutWidget_4);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        HOSTIP_Input = new QLineEdit(layoutWidget_4);
        HOSTIP_Input->setObjectName(QStringLiteral("HOSTIP_Input"));
        QPalette palette31;
        palette31.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette31.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette31.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        HOSTIP_Input->setPalette(palette31);
        HOSTIP_Input->setMouseTracking(false);
        HOSTIP_Input->setAcceptDrops(false);
        HOSTIP_Input->setMaxLength(15);

        gridLayout_5->addWidget(HOSTIP_Input, 1, 2, 1, 1);

        Host = new QLabel(layoutWidget_4);
        Host->setObjectName(QStringLiteral("Host"));
        QPalette palette32;
        QBrush brush4(QColor(0, 0, 0, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette32.setBrush(QPalette::Active, QPalette::Text, brush4);
        palette32.setBrush(QPalette::Inactive, QPalette::Text, brush4);
        palette32.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        Host->setPalette(palette32);
        QFont font2;
        font2.setBold(true);
        font2.setWeight(75);
        Host->setFont(font2);

        gridLayout_5->addWidget(Host, 0, 0, 1, 1);

        SENDPORT_Input = new QLineEdit(layoutWidget_4);
        SENDPORT_Input->setObjectName(QStringLiteral("SENDPORT_Input"));
        QPalette palette33;
        palette33.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette33.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette33.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        SENDPORT_Input->setPalette(palette33);
        SENDPORT_Input->setMouseTracking(false);
        SENDPORT_Input->setAcceptDrops(false);
        SENDPORT_Input->setMaxLength(5);

        gridLayout_5->addWidget(SENDPORT_Input, 6, 2, 1, 1);

        Send_IP = new QLabel(layoutWidget_4);
        Send_IP->setObjectName(QStringLiteral("Send_IP"));

        gridLayout_5->addWidget(Send_IP, 5, 0, 1, 1);

        SENDMAC_Input = new QLineEdit(layoutWidget_4);
        SENDMAC_Input->setObjectName(QStringLiteral("SENDMAC_Input"));
        QPalette palette34;
        palette34.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette34.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette34.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        SENDMAC_Input->setPalette(palette34);
        SENDMAC_Input->setMouseTracking(false);
        SENDMAC_Input->setAcceptDrops(false);
        SENDMAC_Input->setMaxLength(17);

        gridLayout_5->addWidget(SENDMAC_Input, 7, 2, 1, 1);

        Host_IP = new QLabel(layoutWidget_4);
        Host_IP->setObjectName(QStringLiteral("Host_IP"));

        gridLayout_5->addWidget(Host_IP, 1, 0, 1, 1);

        SENDIP_Input = new QLineEdit(layoutWidget_4);
        SENDIP_Input->setObjectName(QStringLiteral("SENDIP_Input"));
        QPalette palette35;
        palette35.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette35.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette35.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        SENDIP_Input->setPalette(palette35);
        SENDIP_Input->setMouseTracking(false);
        SENDIP_Input->setAcceptDrops(false);
        SENDIP_Input->setMaxLength(15);

        gridLayout_5->addWidget(SENDIP_Input, 5, 2, 1, 1);

        HOSTNETMASK_Input = new QLineEdit(layoutWidget_4);
        HOSTNETMASK_Input->setObjectName(QStringLiteral("HOSTNETMASK_Input"));
        QPalette palette36;
        palette36.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette36.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette36.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        HOSTNETMASK_Input->setPalette(palette36);
        HOSTNETMASK_Input->setMouseTracking(false);
        HOSTNETMASK_Input->setAcceptDrops(false);
        HOSTNETMASK_Input->setMaxLength(15);

        gridLayout_5->addWidget(HOSTNETMASK_Input, 2, 2, 1, 1);

        Send_MAC = new QLabel(layoutWidget_4);
        Send_MAC->setObjectName(QStringLiteral("Send_MAC"));

        gridLayout_5->addWidget(Send_MAC, 7, 0, 1, 1);

        Send_Port = new QLabel(layoutWidget_4);
        Send_Port->setObjectName(QStringLiteral("Send_Port"));

        gridLayout_5->addWidget(Send_Port, 6, 0, 1, 1);

        Server = new QLabel(layoutWidget_4);
        Server->setObjectName(QStringLiteral("Server"));
        Server->setFont(font2);

        gridLayout_5->addWidget(Server, 4, 0, 1, 1);

        Host_Netmask = new QLabel(layoutWidget_4);
        Host_Netmask->setObjectName(QStringLiteral("Host_Netmask"));

        gridLayout_5->addWidget(Host_Netmask, 2, 0, 1, 1);

        tabWidget->addTab(Network_Setup, QString());
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
        ready_bar = new QProgressBar(centralWidget);
        ready_bar->setObjectName(QStringLiteral("ready_bar"));
        ready_bar->setGeometry(QRect(1120, 165, 81, 23));
        ready_bar->setValue(0);
        ready_bar->setTextVisible(false);
        ready_bar->setOrientation(Qt::Horizontal);
        ready_bar->setInvertedAppearance(false);
        Plot_Window = new QGraphicsView(centralWidget);
        Plot_Window->setObjectName(QStringLiteral("Plot_Window"));
        Plot_Window->setGeometry(QRect(30, 160, 512, 512));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1228, 33));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Morpheus", 0));
        CNPEM->setText(QString());
        LNLS->setText(QString());
        Aquire_Time->setText(QApplication::translate("MainWindow", "Aquire Time", 0));
        Images->setText(QApplication::translate("MainWindow", "Images", 0));
        NImages_Input->setText(QString());
        Gap->setText(QApplication::translate("MainWindow", "Gap", 0));
        Gap_Input->setText(QString());
        Read_Couter->setText(QApplication::translate("MainWindow", "Read Counter", 0));
        Read_Counter_Input->clear();
        Read_Counter_Input->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Counter L", 0)
         << QApplication::translate("MainWindow", "Counter H", 0)
         << QApplication::translate("MainWindow", "Both", 0)
        );
        Polarity->setText(QApplication::translate("MainWindow", "Polarity", 0));
        Polarity_Input->clear();
        Polarity_Input->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Eletrons", 0)
         << QApplication::translate("MainWindow", "Holes", 0)
        );
        Colour_Mode_Input->clear();
        Colour_Mode_Input->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Fine Pith Mode", 0)
         << QApplication::translate("MainWindow", "Spectroscopic Mode", 0)
        );
        ReadWrite->setText(QApplication::translate("MainWindow", "Read / Write", 0));
        Read_Write_Input->clear();
        Read_Write_Input->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Sequencial", 0)
         << QApplication::translate("MainWindow", "Continous", 0)
        );
        CSM_SPM->setText(QApplication::translate("MainWindow", "Disc CSM SPM", 0));
        Disc_CSM_SPM_Input->clear();
        Disc_CSM_SPM_Input->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Disc L", 0)
         << QApplication::translate("MainWindow", "Disc H", 0)
        );
        Output->setText(QApplication::translate("MainWindow", "Output", 0));
        Output_Input->clear();
        Output_Input->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Dout[0]", 0)
         << QApplication::translate("MainWindow", "Dout[0..3]", 0)
         << QApplication::translate("MainWindow", "Dout[0..1]", 0)
         << QApplication::translate("MainWindow", "Dout[0..7]", 0)
        );
        Image_Size->setText(QApplication::translate("MainWindow", "Image Size", 0));
        Count_L_Input->clear();
        Count_L_Input->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "2 x 1 Bit", 0)
         << QApplication::translate("MainWindow", "2 x 12 Bits", 0)
         << QApplication::translate("MainWindow", "2 x 6 Bits", 0)
         << QApplication::translate("MainWindow", "1 x 24 Bits", 0)
        );
        Gain_mode->setText(QApplication::translate("MainWindow", "Gain Mode", 0));
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
        Start_Aquire->setText(QApplication::translate("MainWindow", "Start", 0));
        Stop_Aquire->setText(QApplication::translate("MainWindow", "Stop", 0));
        tabWidget->setTabText(tabWidget->indexOf(Aquire), QApplication::translate("MainWindow", "Aquire", 0));
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
        Send_Eq->setText(QApplication::translate("MainWindow", "Send Eq", 0));
        tabWidget->setTabText(tabWidget->indexOf(Equalization), QApplication::translate("MainWindow", "Equalization", 0));
        Host->setText(QApplication::translate("MainWindow", "Host", 0));
        Send_IP->setText(QApplication::translate("MainWindow", "Send IP", 0));
        Host_IP->setText(QApplication::translate("MainWindow", "Host IP", 0));
        Send_MAC->setText(QApplication::translate("MainWindow", "Send MAC", 0));
        Send_Port->setText(QApplication::translate("MainWindow", "Send Port", 0));
        Server->setText(QApplication::translate("MainWindow", "Server", 0));
        Host_Netmask->setText(QApplication::translate("MainWindow", "Host Netmask", 0));
        tabWidget->setTabText(tabWidget->indexOf(Network_Setup), QApplication::translate("MainWindow", "Network Setup", 0));
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
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
