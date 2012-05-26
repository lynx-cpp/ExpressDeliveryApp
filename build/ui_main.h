/********************************************************************************
** Form generated from reading UI file 'main.ui'
**
** Created: Wed May 23 18:58:17 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_H
#define UI_MAIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLogin;
    QAction *actionRegister;
    QAction *actionInformation;
    QAction *actionOrder_from_Me;
    QAction *actionOrder;
    QAction *actionNew_Order;
    QAction *actionNew_Order_from_Home;
    QAction *actionOrder_Query;
    QAction *actionModify_Type;
    QAction *actionToday;
    QAction *actionOther_Time;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QTableView *tableView;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *infoLabel;
    QMenuBar *menubar;
    QMenu *menuUser;
    QMenu *menuOrder;
    QMenu *menuOrderType;
    QMenu *menuStatistics;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(734, 431);
        actionLogin = new QAction(MainWindow);
        actionLogin->setObjectName(QString::fromUtf8("actionLogin"));
        actionRegister = new QAction(MainWindow);
        actionRegister->setObjectName(QString::fromUtf8("actionRegister"));
        actionInformation = new QAction(MainWindow);
        actionInformation->setObjectName(QString::fromUtf8("actionInformation"));
        actionOrder_from_Me = new QAction(MainWindow);
        actionOrder_from_Me->setObjectName(QString::fromUtf8("actionOrder_from_Me"));
        actionOrder = new QAction(MainWindow);
        actionOrder->setObjectName(QString::fromUtf8("actionOrder"));
        actionNew_Order = new QAction(MainWindow);
        actionNew_Order->setObjectName(QString::fromUtf8("actionNew_Order"));
        actionNew_Order_from_Home = new QAction(MainWindow);
        actionNew_Order_from_Home->setObjectName(QString::fromUtf8("actionNew_Order_from_Home"));
        actionOrder_Query = new QAction(MainWindow);
        actionOrder_Query->setObjectName(QString::fromUtf8("actionOrder_Query"));
        actionModify_Type = new QAction(MainWindow);
        actionModify_Type->setObjectName(QString::fromUtf8("actionModify_Type"));
        actionToday = new QAction(MainWindow);
        actionToday->setObjectName(QString::fromUtf8("actionToday"));
        actionOther_Time = new QAction(MainWindow);
        actionOther_Time->setObjectName(QString::fromUtf8("actionOther_Time"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tableView = new QTableView(centralwidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        horizontalLayout->addWidget(tableView);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_2->setContentsMargins(0, -1, -1, -1);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(200, 0));

        verticalLayout_2->addWidget(label);

        infoLabel = new QLabel(centralwidget);
        infoLabel->setObjectName(QString::fromUtf8("infoLabel"));
        infoLabel->setMinimumSize(QSize(200, 0));

        verticalLayout_2->addWidget(infoLabel);


        horizontalLayout->addLayout(verticalLayout_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 734, 21));
        menuUser = new QMenu(menubar);
        menuUser->setObjectName(QString::fromUtf8("menuUser"));
        menuOrder = new QMenu(menubar);
        menuOrder->setObjectName(QString::fromUtf8("menuOrder"));
        menuOrderType = new QMenu(menubar);
        menuOrderType->setObjectName(QString::fromUtf8("menuOrderType"));
        menuStatistics = new QMenu(menubar);
        menuStatistics->setObjectName(QString::fromUtf8("menuStatistics"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuUser->menuAction());
        menubar->addAction(menuOrder->menuAction());
        menubar->addAction(menuOrderType->menuAction());
        menubar->addAction(menuStatistics->menuAction());
        menuUser->addAction(actionLogin);
        menuUser->addAction(actionRegister);
        menuUser->addSeparator();
        menuUser->addAction(actionInformation);
        menuOrder->addAction(actionOrder_from_Me);
        menuOrder->addAction(actionOrder);
        menuOrder->addSeparator();
        menuOrder->addAction(actionNew_Order);
        menuOrder->addAction(actionNew_Order_from_Home);
        menuOrderType->addAction(actionOrder_Query);
        menuOrderType->addAction(actionModify_Type);
        menuStatistics->addAction(actionToday);
        menuStatistics->addAction(actionOther_Time);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionLogin->setText(QApplication::translate("MainWindow", "Login", 0, QApplication::UnicodeUTF8));
        actionRegister->setText(QApplication::translate("MainWindow", "Register", 0, QApplication::UnicodeUTF8));
        actionInformation->setText(QApplication::translate("MainWindow", "Information", 0, QApplication::UnicodeUTF8));
        actionOrder_from_Me->setText(QApplication::translate("MainWindow", "Order from Me", 0, QApplication::UnicodeUTF8));
        actionOrder->setText(QApplication::translate("MainWindow", "Order from Other User", 0, QApplication::UnicodeUTF8));
        actionNew_Order->setText(QApplication::translate("MainWindow", "New Order", 0, QApplication::UnicodeUTF8));
        actionNew_Order_from_Home->setText(QApplication::translate("MainWindow", "New Order from Home", 0, QApplication::UnicodeUTF8));
        actionOrder_Query->setText(QApplication::translate("MainWindow", "Type Query", 0, QApplication::UnicodeUTF8));
        actionModify_Type->setText(QApplication::translate("MainWindow", "Modify Type", 0, QApplication::UnicodeUTF8));
        actionToday->setText(QApplication::translate("MainWindow", "Today", 0, QApplication::UnicodeUTF8));
        actionOther_Time->setText(QApplication::translate("MainWindow", "Other Time", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        infoLabel->setText(QString());
        menuUser->setTitle(QApplication::translate("MainWindow", "User", 0, QApplication::UnicodeUTF8));
        menuOrder->setTitle(QApplication::translate("MainWindow", "Order", 0, QApplication::UnicodeUTF8));
        menuOrderType->setTitle(QApplication::translate("MainWindow", "Order Type", 0, QApplication::UnicodeUTF8));
        menuStatistics->setTitle(QApplication::translate("MainWindow", "Statistics", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_H
