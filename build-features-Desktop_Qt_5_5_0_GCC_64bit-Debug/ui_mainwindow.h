/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoadImage;
    QAction *actionHarris;
    QAction *actionSaveImage;
    QAction *actionReset;
    QAction *actionCameraCapture;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QLabel *imageLabel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1011, 721);
        actionLoadImage = new QAction(MainWindow);
        actionLoadImage->setObjectName(QStringLiteral("actionLoadImage"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoadImage->setIcon(icon);
        actionHarris = new QAction(MainWindow);
        actionHarris->setObjectName(QStringLiteral("actionHarris"));
        actionHarris->setCheckable(true);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/harris_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHarris->setIcon(icon1);
        actionSaveImage = new QAction(MainWindow);
        actionSaveImage->setObjectName(QStringLiteral("actionSaveImage"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSaveImage->setIcon(icon2);
        actionReset = new QAction(MainWindow);
        actionReset->setObjectName(QStringLiteral("actionReset"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icons/reset.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionReset->setIcon(icon3);
        actionCameraCapture = new QAction(MainWindow);
        actionCameraCapture->setObjectName(QStringLiteral("actionCameraCapture"));
        actionCameraCapture->setCheckable(true);
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icons/camera.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCameraCapture->setIcon(icon4);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 991, 614));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        imageLabel = new QLabel(scrollAreaWidgetContents);
        imageLabel->setObjectName(QStringLiteral("imageLabel"));

        verticalLayout_2->addWidget(imageLabel);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1011, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        mainToolBar->addAction(actionCameraCapture);
        mainToolBar->addAction(actionHarris);
        mainToolBar->addAction(actionLoadImage);
        mainToolBar->addAction(actionSaveImage);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionLoadImage->setText(QApplication::translate("MainWindow", "LoadImage", 0));
#ifndef QT_NO_TOOLTIP
        actionLoadImage->setToolTip(QApplication::translate("MainWindow", "Load an image from file", 0));
#endif // QT_NO_TOOLTIP
        actionLoadImage->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        actionHarris->setText(QApplication::translate("MainWindow", "Harris Corner Detector", 0));
#ifndef QT_NO_TOOLTIP
        actionHarris->setToolTip(QApplication::translate("MainWindow", "Apply Harris Corner Detector", 0));
#endif // QT_NO_TOOLTIP
        actionHarris->setShortcut(QApplication::translate("MainWindow", "Ctrl+P", 0));
        actionSaveImage->setText(QApplication::translate("MainWindow", "SaveImage", 0));
#ifndef QT_NO_TOOLTIP
        actionSaveImage->setToolTip(QApplication::translate("MainWindow", "Save the image", 0));
#endif // QT_NO_TOOLTIP
        actionSaveImage->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0));
        actionReset->setText(QApplication::translate("MainWindow", "Reset", 0));
#ifndef QT_NO_TOOLTIP
        actionReset->setToolTip(QApplication::translate("MainWindow", "Undo filter applied ", 0));
#endif // QT_NO_TOOLTIP
        actionReset->setShortcut(QApplication::translate("MainWindow", "Ctrl+R", 0));
        actionCameraCapture->setText(QApplication::translate("MainWindow", "CameraCapture", 0));
#ifndef QT_NO_TOOLTIP
        actionCameraCapture->setToolTip(QApplication::translate("MainWindow", "Capture images from camera", 0));
#endif // QT_NO_TOOLTIP
        imageLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H