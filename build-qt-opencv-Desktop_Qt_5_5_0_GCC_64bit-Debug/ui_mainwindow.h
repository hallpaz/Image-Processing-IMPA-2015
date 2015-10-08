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
#include <QtWidgets/QRadioButton>
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
    QAction *actionProcessing;
    QAction *actionSaveImage;
    QAction *actionReset;
    QAction *actionCameraCapture;
    QAction *actionPyramid;
    QAction *actionGradientMagnitude;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QLabel *imageLabel;
    QWidget *widget;
    QRadioButton *scale_0;
    QRadioButton *scale_1;
    QRadioButton *scale_2;
    QRadioButton *scale_3;
    QLabel *label;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1024, 738);
        MainWindow->setMinimumSize(QSize(0, 0));
        actionLoadImage = new QAction(MainWindow);
        actionLoadImage->setObjectName(QStringLiteral("actionLoadImage"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoadImage->setIcon(icon);
        actionProcessing = new QAction(MainWindow);
        actionProcessing->setObjectName(QStringLiteral("actionProcessing"));
        actionProcessing->setCheckable(true);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/process.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionProcessing->setIcon(icon1);
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
        actionPyramid = new QAction(MainWindow);
        actionPyramid->setObjectName(QStringLiteral("actionPyramid"));
        actionPyramid->setCheckable(true);
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/icons/pyramid.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPyramid->setIcon(icon5);
        actionGradientMagnitude = new QAction(MainWindow);
        actionGradientMagnitude->setObjectName(QStringLiteral("actionGradientMagnitude"));
        actionGradientMagnitude->setCheckable(true);
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/icons/grad.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionGradientMagnitude->setIcon(icon6);
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
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1004, 605));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        imageLabel = new QLabel(scrollAreaWidgetContents);
        imageLabel->setObjectName(QStringLiteral("imageLabel"));

        verticalLayout_2->addWidget(imageLabel);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(829, 20));
        scale_0 = new QRadioButton(widget);
        scale_0->setObjectName(QStringLiteral("scale_0"));
        scale_0->setGeometry(QRect(150, 0, 51, 22));
        scale_1 = new QRadioButton(widget);
        scale_1->setObjectName(QStringLiteral("scale_1"));
        scale_1->setGeometry(QRect(200, 0, 41, 22));
        scale_2 = new QRadioButton(widget);
        scale_2->setObjectName(QStringLiteral("scale_2"));
        scale_2->setGeometry(QRect(240, 0, 41, 22));
        scale_3 = new QRadioButton(widget);
        scale_3->setObjectName(QStringLiteral("scale_3"));
        scale_3->setGeometry(QRect(280, 0, 41, 22));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 0, 121, 17));

        verticalLayout->addWidget(widget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        mainToolBar->addAction(actionCameraCapture);
        mainToolBar->addAction(actionPyramid);
        mainToolBar->addAction(actionProcessing);
        mainToolBar->addAction(actionGradientMagnitude);
        mainToolBar->addAction(actionLoadImage);
        mainToolBar->addAction(actionSaveImage);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Image Pyramids", 0));
        actionLoadImage->setText(QApplication::translate("MainWindow", "LoadImage", 0));
#ifndef QT_NO_TOOLTIP
        actionLoadImage->setToolTip(QApplication::translate("MainWindow", "Load an image from file", 0));
#endif // QT_NO_TOOLTIP
        actionLoadImage->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        actionProcessing->setText(QApplication::translate("MainWindow", "Processing", 0));
#ifndef QT_NO_TOOLTIP
        actionProcessing->setToolTip(QApplication::translate("MainWindow", "Apply a filter on image", 0));
#endif // QT_NO_TOOLTIP
        actionProcessing->setShortcut(QApplication::translate("MainWindow", "Ctrl+P", 0));
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
        actionPyramid->setText(QApplication::translate("MainWindow", "Pyramid", 0));
#ifndef QT_NO_TOOLTIP
        actionPyramid->setToolTip(QApplication::translate("MainWindow", "Show Image Pyramid", 0));
#endif // QT_NO_TOOLTIP
        actionGradientMagnitude->setText(QApplication::translate("MainWindow", "GradientMagnitude", 0));
#ifndef QT_NO_TOOLTIP
        actionGradientMagnitude->setToolTip(QApplication::translate("MainWindow", "Gradient Magnitude", 0));
#endif // QT_NO_TOOLTIP
        imageLabel->setText(QString());
        scale_0->setText(QApplication::translate("MainWindow", "0", 0));
        scale_1->setText(QApplication::translate("MainWindow", "1", 0));
        scale_2->setText(QApplication::translate("MainWindow", "2", 0));
        scale_3->setText(QApplication::translate("MainWindow", "3", 0));
        label->setText(QApplication::translate("MainWindow", "Current Scale", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
