/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *readButton;
    QPushButton *surfaceRenderButton;
    QPushButton *resetButton;
    QTextBrowser *textBrowser;
    QPushButton *threshouldButton;
    QScrollBar *horizontalScrollBar;
    QPushButton *volumeRenderButton;
    QLabel *label;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QVTKWidget *qvtkWidget_Volume_2;
    QScrollBar *verticalScrollBar;
    QHBoxLayout *horizontalLayout_2;
    QVTKWidget *qvtkWidget_Volume_3;
    QScrollBar *verticalScrollBar_2;
    QHBoxLayout *horizontalLayout_3;
    QVTKWidget *qvtkWidget_Volume_4;
    QScrollBar *verticalScrollBar_3;
    QPushButton *contourSegmentButton;
    QTextBrowser *textBrowser_2;
    QLabel *label_2;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_4;
    QVTKWidget *qvtkWidget_Volume_6;
    QVTKWidget *qvtkWidget_Volume;
    QPushButton *denoiseButton;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;
    QTextEdit *textEdit_3;
    QTextEdit *textEdit_4;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1160, 719);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        readButton = new QPushButton(centralWidget);
        readButton->setObjectName(QString::fromUtf8("readButton"));
        readButton->setGeometry(QRect(10, 460, 81, 51));
        surfaceRenderButton = new QPushButton(centralWidget);
        surfaceRenderButton->setObjectName(QString::fromUtf8("surfaceRenderButton"));
        surfaceRenderButton->setGeometry(QRect(260, 580, 75, 23));
        resetButton = new QPushButton(centralWidget);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));
        resetButton->setGeometry(QRect(100, 460, 81, 51));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(370, 470, 381, 191));
        threshouldButton = new QPushButton(centralWidget);
        threshouldButton->setObjectName(QString::fromUtf8("threshouldButton"));
        threshouldButton->setGeometry(QRect(190, 460, 81, 51));
        horizontalScrollBar = new QScrollBar(centralWidget);
        horizontalScrollBar->setObjectName(QString::fromUtf8("horizontalScrollBar"));
        horizontalScrollBar->setGeometry(QRect(90, 530, 160, 21));
        horizontalScrollBar->setPageStep(5);
        horizontalScrollBar->setValue(0);
        horizontalScrollBar->setOrientation(Qt::Horizontal);
        volumeRenderButton = new QPushButton(centralWidget);
        volumeRenderButton->setObjectName(QString::fromUtf8("volumeRenderButton"));
        volumeRenderButton->setGeometry(QRect(150, 580, 75, 23));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 570, 71, 41));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(770, 0, 370, 677));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        qvtkWidget_Volume_2 = new QVTKWidget(layoutWidget);
        qvtkWidget_Volume_2->setObjectName(QString::fromUtf8("qvtkWidget_Volume_2"));
        qvtkWidget_Volume_2->setEnabled(true);
        qvtkWidget_Volume_2->setMinimumSize(QSize(343, 219));

        horizontalLayout->addWidget(qvtkWidget_Volume_2);

        verticalScrollBar = new QScrollBar(layoutWidget);
        verticalScrollBar->setObjectName(QString::fromUtf8("verticalScrollBar"));
        verticalScrollBar->setMaximum(511);
        verticalScrollBar->setOrientation(Qt::Vertical);

        horizontalLayout->addWidget(verticalScrollBar);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        qvtkWidget_Volume_3 = new QVTKWidget(layoutWidget);
        qvtkWidget_Volume_3->setObjectName(QString::fromUtf8("qvtkWidget_Volume_3"));
        qvtkWidget_Volume_3->setMinimumSize(QSize(343, 219));

        horizontalLayout_2->addWidget(qvtkWidget_Volume_3);

        verticalScrollBar_2 = new QScrollBar(layoutWidget);
        verticalScrollBar_2->setObjectName(QString::fromUtf8("verticalScrollBar_2"));
        verticalScrollBar_2->setMaximum(511);
        verticalScrollBar_2->setOrientation(Qt::Vertical);

        horizontalLayout_2->addWidget(verticalScrollBar_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        qvtkWidget_Volume_4 = new QVTKWidget(layoutWidget);
        qvtkWidget_Volume_4->setObjectName(QString::fromUtf8("qvtkWidget_Volume_4"));
        qvtkWidget_Volume_4->setMinimumSize(QSize(343, 219));

        horizontalLayout_3->addWidget(qvtkWidget_Volume_4);

        verticalScrollBar_3 = new QScrollBar(layoutWidget);
        verticalScrollBar_3->setObjectName(QString::fromUtf8("verticalScrollBar_3"));
        verticalScrollBar_3->setMaximum(200);
        verticalScrollBar_3->setOrientation(Qt::Vertical);

        horizontalLayout_3->addWidget(verticalScrollBar_3);


        verticalLayout->addLayout(horizontalLayout_3);

        contourSegmentButton = new QPushButton(centralWidget);
        contourSegmentButton->setObjectName(QString::fromUtf8("contourSegmentButton"));
        contourSegmentButton->setGeometry(QRect(280, 460, 81, 51));
        textBrowser_2 = new QTextBrowser(centralWidget);
        textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));
        textBrowser_2->setGeometry(QRect(270, 520, 61, 31));
        textBrowser_2->setAcceptRichText(true);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 530, 54, 12));
        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 13, 708, 402));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        qvtkWidget_Volume_6 = new QVTKWidget(layoutWidget1);
        qvtkWidget_Volume_6->setObjectName(QString::fromUtf8("qvtkWidget_Volume_6"));
        qvtkWidget_Volume_6->setMinimumSize(QSize(350, 400));

        horizontalLayout_4->addWidget(qvtkWidget_Volume_6);

        qvtkWidget_Volume = new QVTKWidget(layoutWidget1);
        qvtkWidget_Volume->setObjectName(QString::fromUtf8("qvtkWidget_Volume"));
        qvtkWidget_Volume->setMinimumSize(QSize(350, 400));

        horizontalLayout_4->addWidget(qvtkWidget_Volume);

        denoiseButton = new QPushButton(centralWidget);
        denoiseButton->setObjectName(QString::fromUtf8("denoiseButton"));
        denoiseButton->setGeometry(QRect(380, 430, 81, 31));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(480, 430, 41, 31));
        textEdit_2 = new QTextEdit(centralWidget);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        textEdit_2->setGeometry(QRect(530, 430, 41, 31));
        textEdit_3 = new QTextEdit(centralWidget);
        textEdit_3->setObjectName(QString::fromUtf8("textEdit_3"));
        textEdit_3->setGeometry(QRect(600, 430, 41, 31));
        textEdit_4 = new QTextEdit(centralWidget);
        textEdit_4->setObjectName(QString::fromUtf8("textEdit_4"));
        textEdit_4->setGeometry(QRect(650, 430, 41, 31));
        MainWindow->setCentralWidget(centralWidget);
        layoutWidget->raise();
        readButton->raise();
        surfaceRenderButton->raise();
        resetButton->raise();
        layoutWidget->raise();
        textBrowser->raise();
        threshouldButton->raise();
        horizontalScrollBar->raise();
        volumeRenderButton->raise();
        label->raise();
        contourSegmentButton->raise();
        textBrowser_2->raise();
        label_2->raise();
        denoiseButton->raise();
        textEdit->raise();
        textEdit_2->raise();
        textEdit_3->raise();
        textEdit_4->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1160, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "CT\344\270\212\347\252\246\351\242\235\345\210\206\345\211\262", nullptr));
        readButton->setText(QCoreApplication::translate("MainWindow", "\350\257\273\345\217\226\346\225\260\346\215\256", nullptr));
        surfaceRenderButton->setText(QCoreApplication::translate("MainWindow", "\351\235\242\347\273\230\345\210\266", nullptr));
        resetButton->setText(QCoreApplication::translate("MainWindow", "\351\207\215\347\275\256", nullptr));
        threshouldButton->setText(QCoreApplication::translate("MainWindow", "\351\230\210\345\200\274\345\210\206\345\211\262", nullptr));
        volumeRenderButton->setText(QCoreApplication::translate("MainWindow", "\344\275\223\347\273\230\345\210\266", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\344\270\211\347\273\264\351\207\215\345\273\272", nullptr));
        contourSegmentButton->setText(QCoreApplication::translate("MainWindow", "\345\210\206\345\211\262\344\270\212\347\252\246\351\242\235", nullptr));
        textBrowser_2->setDocumentTitle(QString());
        textBrowser_2->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">-512</p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\345\210\206\345\211\262\351\230\210\345\200\274", nullptr));
        denoiseButton->setText(QCoreApplication::translate("MainWindow", "\345\216\273\345\231\252", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
