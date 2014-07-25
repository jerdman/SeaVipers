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
#include <QtWidgets/QGraphicsView>
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
    QGraphicsView *graphicsView;
    QLCDNumber *lcdRange;
    QPushButton *rangePushButton;
    QPushButton *connectRFButton;
    QPushButton *connectPTUButton;
    QPushButton *homePushButton;
    QLCDNumber *lcdPan;
    QLCDNumber *lcdTilt;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *main_windowClass)
    {
        if (main_windowClass->objectName().isEmpty())
            main_windowClass->setObjectName(QStringLiteral("main_windowClass"));
        main_windowClass->resize(792, 626);
        centralWidget = new QWidget(main_windowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        playPushButton = new QPushButton(centralWidget);
        playPushButton->setObjectName(QStringLiteral("playPushButton"));
        playPushButton->setGeometry(QRect(10, 540, 75, 23));
        trackPushButton = new QPushButton(centralWidget);
        trackPushButton->setObjectName(QStringLiteral("trackPushButton"));
        trackPushButton->setGeometry(QRect(100, 540, 75, 23));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(10, 10, 640, 480));
        graphicsView->viewport()->setProperty("cursor", QVariant(QCursor(Qt::CrossCursor)));
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setDragMode(QGraphicsView::NoDrag);
        lcdRange = new QLCDNumber(centralWidget);
        lcdRange->setObjectName(QStringLiteral("lcdRange"));
        lcdRange->setGeometry(QRect(660, 20, 71, 23));
        lcdRange->setFrameShape(QFrame::Box);
        lcdRange->setFrameShadow(QFrame::Plain);
        lcdRange->setLineWidth(2);
        lcdRange->setDigitCount(6);
        lcdRange->setSegmentStyle(QLCDNumber::Flat);
        lcdRange->setProperty("value", QVariant(0));
        rangePushButton = new QPushButton(centralWidget);
        rangePushButton->setObjectName(QStringLiteral("rangePushButton"));
        rangePushButton->setGeometry(QRect(660, 80, 75, 23));
        connectRFButton = new QPushButton(centralWidget);
        connectRFButton->setObjectName(QStringLiteral("connectRFButton"));
        connectRFButton->setGeometry(QRect(660, 50, 75, 23));
        connectPTUButton = new QPushButton(centralWidget);
        connectPTUButton->setObjectName(QStringLiteral("connectPTUButton"));
        connectPTUButton->setGeometry(QRect(660, 240, 75, 23));
        homePushButton = new QPushButton(centralWidget);
        homePushButton->setObjectName(QStringLiteral("homePushButton"));
        homePushButton->setGeometry(QRect(660, 270, 75, 23));
        lcdPan = new QLCDNumber(centralWidget);
        lcdPan->setObjectName(QStringLiteral("lcdPan"));
        lcdPan->setGeometry(QRect(660, 180, 71, 23));
        lcdPan->setFrameShape(QFrame::Box);
        lcdPan->setFrameShadow(QFrame::Plain);
        lcdPan->setLineWidth(2);
        lcdPan->setDigitCount(6);
        lcdPan->setSegmentStyle(QLCDNumber::Flat);
        lcdPan->setProperty("value", QVariant(0));
        lcdTilt = new QLCDNumber(centralWidget);
        lcdTilt->setObjectName(QStringLiteral("lcdTilt"));
        lcdTilt->setGeometry(QRect(660, 210, 71, 23));
        lcdTilt->setFrameShape(QFrame::Box);
        lcdTilt->setFrameShadow(QFrame::Plain);
        lcdTilt->setLineWidth(2);
        lcdTilt->setDigitCount(6);
        lcdTilt->setSegmentStyle(QLCDNumber::Flat);
        lcdTilt->setProperty("value", QVariant(0));
        main_windowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(main_windowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 792, 21));
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
        playPushButton->setText(QApplication::translate("main_windowClass", "Play", 0));
        trackPushButton->setText(QApplication::translate("main_windowClass", "Track", 0));
        rangePushButton->setText(QApplication::translate("main_windowClass", "Range", 0));
        connectRFButton->setText(QApplication::translate("main_windowClass", "Connect", 0));
        connectPTUButton->setText(QApplication::translate("main_windowClass", "Connect PTU", 0));
        homePushButton->setText(QApplication::translate("main_windowClass", "Home", 0));
    } // retranslateUi

};

namespace Ui {
    class main_windowClass: public Ui_main_windowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW_H
