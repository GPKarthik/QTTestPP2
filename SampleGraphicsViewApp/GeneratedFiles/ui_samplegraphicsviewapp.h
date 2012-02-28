/********************************************************************************
** Form generated from reading UI file 'samplegraphicsviewapp.ui'
**
** Created: Tue Feb 28 13:49:30 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAMPLEGRAPHICSVIEWAPP_H
#define UI_SAMPLEGRAPHICSVIEWAPP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>
#include <customgraphicsview.h>

QT_BEGIN_NAMESPACE

class Ui_SampleGraphicsViewAppClass
{
public:
    QAction *actionOpen;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QRadioButton *emfButton;
    QRadioButton *imageButton;
    QSpacerItem *horizontalSpacer_2;
    QSlider *horizontalSlider;
    CustomGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SampleGraphicsViewAppClass)
    {
        if (SampleGraphicsViewAppClass->objectName().isEmpty())
            SampleGraphicsViewAppClass->setObjectName(QString::fromUtf8("SampleGraphicsViewAppClass"));
        SampleGraphicsViewAppClass->resize(627, 400);
        actionOpen = new QAction(SampleGraphicsViewAppClass);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        centralWidget = new QWidget(SampleGraphicsViewAppClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer = new QSpacerItem(165, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        emfButton = new QRadioButton(centralWidget);
        emfButton->setObjectName(QString::fromUtf8("emfButton"));

        gridLayout->addWidget(emfButton, 0, 1, 1, 1);

        imageButton = new QRadioButton(centralWidget);
        imageButton->setObjectName(QString::fromUtf8("imageButton"));
        imageButton->setChecked(true);

        gridLayout->addWidget(imageButton, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(60, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 3, 1, 1);

        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setMinimum(200);
        horizontalSlider->setMaximum(1000);
        horizontalSlider->setSingleStep(10);
        horizontalSlider->setPageStep(50);
        horizontalSlider->setValue(200);
        horizontalSlider->setTracking(true);
        horizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider, 0, 4, 1, 1);

        graphicsView = new CustomGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        QBrush brush(QColor(108, 108, 108, 255));
        brush.setStyle(Qt::SolidPattern);
        graphicsView->setBackgroundBrush(brush);

        gridLayout->addWidget(graphicsView, 1, 0, 1, 5);

        SampleGraphicsViewAppClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SampleGraphicsViewAppClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 627, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        SampleGraphicsViewAppClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(SampleGraphicsViewAppClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        SampleGraphicsViewAppClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);

        retranslateUi(SampleGraphicsViewAppClass);

        QMetaObject::connectSlotsByName(SampleGraphicsViewAppClass);
    } // setupUi

    void retranslateUi(QMainWindow *SampleGraphicsViewAppClass)
    {
        SampleGraphicsViewAppClass->setWindowTitle(QApplication::translate("SampleGraphicsViewAppClass", "SampleGraphicsViewApp", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("SampleGraphicsViewAppClass", "Open", 0, QApplication::UnicodeUTF8));
        emfButton->setText(QApplication::translate("SampleGraphicsViewAppClass", "Emf", 0, QApplication::UnicodeUTF8));
        imageButton->setText(QApplication::translate("SampleGraphicsViewAppClass", "Image", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("SampleGraphicsViewAppClass", "File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SampleGraphicsViewAppClass: public Ui_SampleGraphicsViewAppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAMPLEGRAPHICSVIEWAPP_H
