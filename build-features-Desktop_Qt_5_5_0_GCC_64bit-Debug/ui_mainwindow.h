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
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
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
    QAction *actionCameraCapture;
    QAction *actionSift;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QLabel *imageLabel;
    QWidget *widget;
    QSlider *thresholdSlider;
    QLabel *threshold_label;
    QLabel *threshold_value;
    QDoubleSpinBox *apertureSpinBox;
    QDoubleSpinBox *blockSpinBox;
    QLabel *aperture_label;
    QLabel *block_size_label;
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
        actionCameraCapture = new QAction(MainWindow);
        actionCameraCapture->setObjectName(QStringLiteral("actionCameraCapture"));
        actionCameraCapture->setCheckable(true);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icons/camera.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCameraCapture->setIcon(icon3);
        actionSift = new QAction(MainWindow);
        actionSift->setObjectName(QStringLiteral("actionSift"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icons/sift.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSift->setIcon(icon4);
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
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 985, 568));
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
        widget->setMinimumSize(QSize(0, 30));
        thresholdSlider = new QSlider(widget);
        thresholdSlider->setObjectName(QStringLiteral("thresholdSlider"));
        thresholdSlider->setGeometry(QRect(140, 0, 341, 22));
        thresholdSlider->setMinimum(100);
        thresholdSlider->setMaximum(255);
        thresholdSlider->setOrientation(Qt::Horizontal);
        threshold_label = new QLabel(widget);
        threshold_label->setObjectName(QStringLiteral("threshold_label"));
        threshold_label->setGeometry(QRect(10, 0, 71, 16));
        threshold_value = new QLabel(widget);
        threshold_value->setObjectName(QStringLiteral("threshold_value"));
        threshold_value->setGeometry(QRect(90, 0, 41, 16));
        apertureSpinBox = new QDoubleSpinBox(widget);
        apertureSpinBox->setObjectName(QStringLiteral("apertureSpinBox"));
        apertureSpinBox->setGeometry(QRect(610, 0, 67, 24));
        apertureSpinBox->setDecimals(0);
        apertureSpinBox->setMinimum(1);
        apertureSpinBox->setMaximum(31);
        apertureSpinBox->setSingleStep(2);
        blockSpinBox = new QDoubleSpinBox(widget);
        blockSpinBox->setObjectName(QStringLiteral("blockSpinBox"));
        blockSpinBox->setGeometry(QRect(870, 0, 67, 24));
        blockSpinBox->setDecimals(0);
        aperture_label = new QLabel(widget);
        aperture_label->setObjectName(QStringLiteral("aperture_label"));
        aperture_label->setGeometry(QRect(500, 0, 101, 16));
        block_size_label = new QLabel(widget);
        block_size_label->setObjectName(QStringLiteral("block_size_label"));
        block_size_label->setGeometry(QRect(760, 10, 81, 16));

        verticalLayout->addWidget(widget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1011, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        mainToolBar->addAction(actionCameraCapture);
        mainToolBar->addAction(actionHarris);
        mainToolBar->addAction(actionSift);
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
        actionCameraCapture->setText(QApplication::translate("MainWindow", "CameraCapture", 0));
#ifndef QT_NO_TOOLTIP
        actionCameraCapture->setToolTip(QApplication::translate("MainWindow", "Capture images from camera", 0));
#endif // QT_NO_TOOLTIP
        actionSift->setText(QApplication::translate("MainWindow", "Sift", 0));
#ifndef QT_NO_TOOLTIP
        actionSift->setToolTip(QApplication::translate("MainWindow", "Apply Sift Detector", 0));
#endif // QT_NO_TOOLTIP
        imageLabel->setText(QString());
        threshold_label->setText(QApplication::translate("MainWindow", "Threshold:", 0));
        threshold_value->setText(QApplication::translate("MainWindow", "0", 0));
        aperture_label->setText(QApplication::translate("MainWindow", "Aperture Size:", 0));
        block_size_label->setText(QApplication::translate("MainWindow", "Block Size:", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
