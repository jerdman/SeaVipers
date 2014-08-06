/********************************************************************************
** Form generated from reading UI file 'main_window.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_WINDOW_H
#define UI_MAIN_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_main_windowClass
{
public:
    QWidget *centralWidget;
    QPushButton *playPushButton;
    QPushButton *trackPushButton;
    QGraphicsView *cameraView;
    QGroupBox *groupBox;
    QLCDNumber *lcdTilt;
    QPushButton *connectPTUButton;
    QLCDNumber *lcdPan;
    QPushButton *homePushButton;
    QGroupBox *groupBox_2;
    QLCDNumber *lcdRange;
    QPushButton *connectRFButton;
    QPushButton *rangePushButton;
    QCheckBox *learningCheckBox;
    QGraphicsView *trackerView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *main_windowClass)
    {
        if (main_windowClass->objectName().isEmpty())
            main_windowClass->setObjectName(QStringLiteral("main_windowClass"));
        main_windowClass->resize(800, 600);
        centralWidget = new QWidget(main_windowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        playPushButton = new QPushButton(centralWidget);
        playPushButton->setObjectName(QStringLiteral("playPushButton"));
        playPushButton->setGeometry(QRect(10, 260, 75, 23));
        trackPushButton = new QPushButton(centralWidget);
        trackPushButton->setObjectName(QStringLiteral("trackPushButton"));
        trackPushButton->setGeometry(QRect(340, 260, 75, 23));
        cameraView = new QGraphicsView(centralWidget);
        cameraView->setObjectName(QStringLiteral("cameraView"));
        cameraView->setGeometry(QRect(10, 10, 320, 240));
        cameraView->viewport()->setProperty("cursor", QVariant(QCursor(Qt::CrossCursor)));
        cameraView->setFrameShape(QFrame::NoFrame);
        cameraView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        cameraView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        cameraView->setDragMode(QGraphicsView::NoDrag);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(670, 140, 120, 151));
        lcdTilt = new QLCDNumber(groupBox);
        lcdTilt->setObjectName(QStringLiteral("lcdTilt"));
        lcdTilt->setGeometry(QRect(20, 50, 81, 23));
        lcdTilt->setFrameShape(QFrame::Box);
        lcdTilt->setFrameShadow(QFrame::Plain);
        lcdTilt->setLineWidth(2);
        lcdTilt->setDigitCount(6);
        lcdTilt->setSegmentStyle(QLCDNumber::Flat);
        lcdTilt->setProperty("value", QVariant(0));
        connectPTUButton = new QPushButton(groupBox);
        connectPTUButton->setObjectName(QStringLiteral("connectPTUButton"));
        connectPTUButton->setGeometry(QRect(20, 80, 81, 23));
        lcdPan = new QLCDNumber(groupBox);
        lcdPan->setObjectName(QStringLiteral("lcdPan"));
        lcdPan->setGeometry(QRect(20, 20, 81, 23));
        lcdPan->setFrameShape(QFrame::Box);
        lcdPan->setFrameShadow(QFrame::Plain);
        lcdPan->setLineWidth(2);
        lcdPan->setDigitCount(6);
        lcdPan->setSegmentStyle(QLCDNumber::Flat);
        lcdPan->setProperty("value", QVariant(0));
        homePushButton = new QPushButton(groupBox);
        homePushButton->setObjectName(QStringLiteral("homePushButton"));
        homePushButton->setGeometry(QRect(20, 110, 81, 23));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(670, 10, 120, 121));
        lcdRange = new QLCDNumber(groupBox_2);
        lcdRange->setObjectName(QStringLiteral("lcdRange"));
        lcdRange->setGeometry(QRect(20, 20, 81, 23));
        lcdRange->setFrameShape(QFrame::Box);
        lcdRange->setFrameShadow(QFrame::Plain);
        lcdRange->setLineWidth(2);
        lcdRange->setDigitCount(6);
        lcdRange->setSegmentStyle(QLCDNumber::Flat);
        lcdRange->setProperty("value", QVariant(0));
        connectRFButton = new QPushButton(groupBox_2);
        connectRFButton->setObjectName(QStringLiteral("connectRFButton"));
        connectRFButton->setGeometry(QRect(20, 50, 81, 23));
        rangePushButton = new QPushButton(groupBox_2);
        rangePushButton->setObjectName(QStringLiteral("rangePushButton"));
        rangePushButton->setGeometry(QRect(20, 80, 81, 23));
        learningCheckBox = new QCheckBox(centralWidget);
        learningCheckBox->setObjectName(QStringLiteral("learningCheckBox"));
        learningCheckBox->setGeometry(QRect(420, 260, 70, 21));
        trackerView = new QGraphicsView(centralWidget);
        trackerView->setObjectName(QStringLiteral("trackerView"));
        trackerView->setGeometry(QRect(340, 10, 320, 240));
        trackerView->viewport()->setProperty("cursor", QVariant(QCursor(Qt::CrossCursor)));
        trackerView->setFrameShape(QFrame::NoFrame);
        trackerView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        trackerView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        trackerView->setDragMode(QGraphicsView::NoDrag);
        main_windowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(main_windowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        main_windowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(main_windowClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        main_windowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(main_windowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        main_windowClass->setStatusBar(statusBar);

        retranslateUi(main_windowClass);

        QMetaObject::connectSlotsByName(main_windowClass);
    } // setupUi

    void retranslateUi(QMainWindow *main_windowClass)
    {
        main_windowClass->setWindowTitle(QApplication::translate("main_windowClass", "TigerTracks", 0));
        playPushButton->setText(QApplication::translate("main_windowClass", "Connect", 0));
        trackPushButton->setText(QApplication::translate("main_windowClass", "Track", 0));
        groupBox->setTitle(QApplication::translate("main_windowClass", "Pan/Tilt Unit", 0));
        connectPTUButton->setText(QApplication::translate("main_windowClass", "Connect", 0));
        homePushButton->setText(QApplication::translate("main_windowClass", "Home", 0));
        groupBox_2->setTitle(QApplication::translate("main_windowClass", "Rangefinder", 0));
        connectRFButton->setText(QApplication::translate("main_windowClass", "Connect", 0));
        rangePushButton->setText(QApplication::translate("main_windowClass", "Range", 0));
        learningCheckBox->setText(QApplication::translate("main_windowClass", "Learning", 0));
    } // retranslateUi

};

namespace Ui {
    class main_windowClass: public Ui_main_windowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW_H
