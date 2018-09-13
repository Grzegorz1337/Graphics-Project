/********************************************************************************
** Form generated from reading UI file 'mywindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYWINDOW_H
#define UI_MYWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyWindow
{
public:
    QWidget *centralWidget;
    QFrame *frame;
    QGroupBox *groupBox1;
    QPushButton *quit;
    QPushButton *reset;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MyWindow)
    {
        if (MyWindow->objectName().isEmpty())
            MyWindow->setObjectName(QStringLiteral("MyWindow"));
        MyWindow->resize(596, 565);
        centralWidget = new QWidget(MyWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(7, 70, 581, 427));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        groupBox1 = new QGroupBox(centralWidget);
        groupBox1->setObjectName(QStringLiteral("groupBox1"));
        groupBox1->setGeometry(QRect(10, -11, 301, 61));
        quit = new QPushButton(groupBox1);
        quit->setObjectName(QStringLiteral("quit"));
        quit->setGeometry(QRect(200, 20, 100, 40));
        QFont font;
        font.setFamily(QStringLiteral("Segoe UI Light"));
        font.setPointSize(13);
        quit->setFont(font);
        quit->setCursor(QCursor(Qt::CrossCursor));
        reset = new QPushButton(groupBox1);
        reset->setObjectName(QStringLiteral("reset"));
        reset->setGeometry(QRect(0, 20, 100, 40));
        reset->setFont(font);
        reset->setCursor(QCursor(Qt::CrossCursor));
        MyWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MyWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 596, 22));
        MyWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MyWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MyWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MyWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MyWindow->setStatusBar(statusBar);

        retranslateUi(MyWindow);

        QMetaObject::connectSlotsByName(MyWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MyWindow)
    {
        MyWindow->setWindowTitle(QApplication::translate("MyWindow", "Bry\305\202a 3D", nullptr));
        groupBox1->setTitle(QString());
        quit->setText(QApplication::translate("MyWindow", "Wyj\305\233cie", nullptr));
        reset->setText(QApplication::translate("MyWindow", "Mieszaj", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyWindow: public Ui_MyWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYWINDOW_H
