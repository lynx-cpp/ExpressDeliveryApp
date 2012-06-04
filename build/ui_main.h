/********************************************************************************
** Form generated from reading UI file 'main.ui'
**
** Created: Tue Jun 5 02:48:17 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_H
#define UI_MAIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
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
    QAction *actionOrder_Query;
    QAction *actionModify_Type;
    QAction *actionToday;
    QAction *actionOtherTime;
    QAction *actionLogout;
    QAction *actionList_Place_Info;
    QAction *actionNew_Place_Info;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QTableView *tableView;
    QVBoxLayout *verticalLayout_2;
    QPushButton *submitButton;
    QPushButton *discardButton;
    QPushButton *addButton;
    QPushButton *removeButton;
    QGroupBox *timeFilterGroupBox;
    QLabel *filterFromLabel;
    QDateTimeEdit *dateTimeEdit_from;
    QLabel *filterToLabel;
    QDateTimeEdit *dateTimeEdit_to;
    QCheckBox *timeFilterCheckBox;
    QGroupBox *idFilterGroupBox;
    QCheckBox *idFilterCheckBox;
    QLabel *fromIdLabel;
    QSpinBox *fromIdSpinBox;
    QLabel *label_2;
    QSpinBox *toIdSpinBox;
    QPushButton *refreshButton;
    QLabel *infoLabel;
    QLabel *label;
    QMenuBar *menubar;
    QMenu *menuUser;
    QMenu *menuOrder;
    QMenu *menuOrderType;
    QMenu *menuStatistics;
    QMenu *menuPlace_Info;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(624, 590);
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
        actionOrder_Query = new QAction(MainWindow);
        actionOrder_Query->setObjectName(QString::fromUtf8("actionOrder_Query"));
        actionModify_Type = new QAction(MainWindow);
        actionModify_Type->setObjectName(QString::fromUtf8("actionModify_Type"));
        actionToday = new QAction(MainWindow);
        actionToday->setObjectName(QString::fromUtf8("actionToday"));
        actionOtherTime = new QAction(MainWindow);
        actionOtherTime->setObjectName(QString::fromUtf8("actionOtherTime"));
        actionLogout = new QAction(MainWindow);
        actionLogout->setObjectName(QString::fromUtf8("actionLogout"));
        actionList_Place_Info = new QAction(MainWindow);
        actionList_Place_Info->setObjectName(QString::fromUtf8("actionList_Place_Info"));
        actionNew_Place_Info = new QAction(MainWindow);
        actionNew_Place_Info->setObjectName(QString::fromUtf8("actionNew_Place_Info"));
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
        submitButton = new QPushButton(centralwidget);
        submitButton->setObjectName(QString::fromUtf8("submitButton"));

        verticalLayout_2->addWidget(submitButton);

        discardButton = new QPushButton(centralwidget);
        discardButton->setObjectName(QString::fromUtf8("discardButton"));

        verticalLayout_2->addWidget(discardButton);

        addButton = new QPushButton(centralwidget);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        verticalLayout_2->addWidget(addButton);

        removeButton = new QPushButton(centralwidget);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));

        verticalLayout_2->addWidget(removeButton);

        timeFilterGroupBox = new QGroupBox(centralwidget);
        timeFilterGroupBox->setObjectName(QString::fromUtf8("timeFilterGroupBox"));
        timeFilterGroupBox->setMinimumSize(QSize(0, 150));
        filterFromLabel = new QLabel(timeFilterGroupBox);
        filterFromLabel->setObjectName(QString::fromUtf8("filterFromLabel"));
        filterFromLabel->setGeometry(QRect(10, 50, 200, 20));
        filterFromLabel->setMaximumSize(QSize(16777215, 20));
        dateTimeEdit_from = new QDateTimeEdit(timeFilterGroupBox);
        dateTimeEdit_from->setObjectName(QString::fromUtf8("dateTimeEdit_from"));
        dateTimeEdit_from->setGeometry(QRect(0, 70, 200, 23));
        filterToLabel = new QLabel(timeFilterGroupBox);
        filterToLabel->setObjectName(QString::fromUtf8("filterToLabel"));
        filterToLabel->setGeometry(QRect(10, 90, 200, 20));
        filterToLabel->setMaximumSize(QSize(16777215, 20));
        dateTimeEdit_to = new QDateTimeEdit(timeFilterGroupBox);
        dateTimeEdit_to->setObjectName(QString::fromUtf8("dateTimeEdit_to"));
        dateTimeEdit_to->setGeometry(QRect(0, 110, 200, 23));
        timeFilterCheckBox = new QCheckBox(timeFilterGroupBox);
        timeFilterCheckBox->setObjectName(QString::fromUtf8("timeFilterCheckBox"));
        timeFilterCheckBox->setGeometry(QRect(0, 30, 200, 21));

        verticalLayout_2->addWidget(timeFilterGroupBox);

        idFilterGroupBox = new QGroupBox(centralwidget);
        idFilterGroupBox->setObjectName(QString::fromUtf8("idFilterGroupBox"));
        idFilterGroupBox->setMinimumSize(QSize(0, 100));
        idFilterCheckBox = new QCheckBox(idFilterGroupBox);
        idFilterCheckBox->setObjectName(QString::fromUtf8("idFilterCheckBox"));
        idFilterCheckBox->setGeometry(QRect(0, 20, 201, 21));
        fromIdLabel = new QLabel(idFilterGroupBox);
        fromIdLabel->setObjectName(QString::fromUtf8("fromIdLabel"));
        fromIdLabel->setGeometry(QRect(20, 40, 61, 16));
        fromIdSpinBox = new QSpinBox(idFilterGroupBox);
        fromIdSpinBox->setObjectName(QString::fromUtf8("fromIdSpinBox"));
        fromIdSpinBox->setGeometry(QRect(20, 60, 53, 23));
        label_2 = new QLabel(idFilterGroupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(120, 40, 61, 16));
        toIdSpinBox = new QSpinBox(idFilterGroupBox);
        toIdSpinBox->setObjectName(QString::fromUtf8("toIdSpinBox"));
        toIdSpinBox->setGeometry(QRect(120, 60, 53, 23));

        verticalLayout_2->addWidget(idFilterGroupBox);

        refreshButton = new QPushButton(centralwidget);
        refreshButton->setObjectName(QString::fromUtf8("refreshButton"));

        verticalLayout_2->addWidget(refreshButton);

        infoLabel = new QLabel(centralwidget);
        infoLabel->setObjectName(QString::fromUtf8("infoLabel"));
        infoLabel->setMinimumSize(QSize(200, 0));

        verticalLayout_2->addWidget(infoLabel);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(200, 0));

        verticalLayout_2->addWidget(label);


        horizontalLayout->addLayout(verticalLayout_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 624, 21));
        menuUser = new QMenu(menubar);
        menuUser->setObjectName(QString::fromUtf8("menuUser"));
        menuOrder = new QMenu(menubar);
        menuOrder->setObjectName(QString::fromUtf8("menuOrder"));
        menuOrderType = new QMenu(menubar);
        menuOrderType->setObjectName(QString::fromUtf8("menuOrderType"));
        menuStatistics = new QMenu(menubar);
        menuStatistics->setObjectName(QString::fromUtf8("menuStatistics"));
        menuPlace_Info = new QMenu(menubar);
        menuPlace_Info->setObjectName(QString::fromUtf8("menuPlace_Info"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuUser->menuAction());
        menubar->addAction(menuOrder->menuAction());
        menubar->addAction(menuOrderType->menuAction());
        menubar->addAction(menuPlace_Info->menuAction());
        menubar->addAction(menuStatistics->menuAction());
        menuUser->addAction(actionLogin);
        menuUser->addAction(actionLogout);
        menuUser->addAction(actionRegister);
        menuUser->addSeparator();
        menuUser->addAction(actionInformation);
        menuOrder->addAction(actionOrder_from_Me);
        menuOrder->addAction(actionOrder);
        menuOrder->addSeparator();
        menuOrder->addAction(actionNew_Order);
        menuOrderType->addAction(actionOrder_Query);
        menuOrderType->addAction(actionModify_Type);
        menuStatistics->addAction(actionToday);
        menuStatistics->addAction(actionOtherTime);
        menuPlace_Info->addAction(actionList_Place_Info);
        menuPlace_Info->addAction(actionNew_Place_Info);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "ExpressDeliveryApp", 0, QApplication::UnicodeUTF8));
        actionLogin->setText(QApplication::translate("MainWindow", "Login", 0, QApplication::UnicodeUTF8));
        actionRegister->setText(QApplication::translate("MainWindow", "Register", 0, QApplication::UnicodeUTF8));
        actionInformation->setText(QApplication::translate("MainWindow", "Information", 0, QApplication::UnicodeUTF8));
        actionOrder_from_Me->setText(QApplication::translate("MainWindow", "Order from Me", 0, QApplication::UnicodeUTF8));
        actionOrder->setText(QApplication::translate("MainWindow", "Order from All", 0, QApplication::UnicodeUTF8));
        actionNew_Order->setText(QApplication::translate("MainWindow", "New Order", 0, QApplication::UnicodeUTF8));
        actionOrder_Query->setText(QApplication::translate("MainWindow", "Type Query", 0, QApplication::UnicodeUTF8));
        actionModify_Type->setText(QApplication::translate("MainWindow", "Add Type", 0, QApplication::UnicodeUTF8));
        actionToday->setText(QApplication::translate("MainWindow", "Today", 0, QApplication::UnicodeUTF8));
        actionOtherTime->setText(QApplication::translate("MainWindow", "Other Time", 0, QApplication::UnicodeUTF8));
        actionLogout->setText(QApplication::translate("MainWindow", "Logout", 0, QApplication::UnicodeUTF8));
        actionList_Place_Info->setText(QApplication::translate("MainWindow", "List Place Info", 0, QApplication::UnicodeUTF8));
        actionNew_Place_Info->setText(QApplication::translate("MainWindow", "New Place Info", 0, QApplication::UnicodeUTF8));
        submitButton->setText(QApplication::translate("MainWindow", "Submit", 0, QApplication::UnicodeUTF8));
        discardButton->setText(QApplication::translate("MainWindow", "Discard", 0, QApplication::UnicodeUTF8));
        addButton->setText(QApplication::translate("MainWindow", "Add", 0, QApplication::UnicodeUTF8));
        removeButton->setText(QApplication::translate("MainWindow", "Remove", 0, QApplication::UnicodeUTF8));
        timeFilterGroupBox->setTitle(QApplication::translate("MainWindow", "Time Filter", 0, QApplication::UnicodeUTF8));
        filterFromLabel->setText(QApplication::translate("MainWindow", "From Time :", 0, QApplication::UnicodeUTF8));
        filterToLabel->setText(QApplication::translate("MainWindow", "To Time :", 0, QApplication::UnicodeUTF8));
        timeFilterCheckBox->setText(QApplication::translate("MainWindow", "Enabled", 0, QApplication::UnicodeUTF8));
        idFilterGroupBox->setTitle(QApplication::translate("MainWindow", "ID Filter", 0, QApplication::UnicodeUTF8));
        idFilterCheckBox->setText(QApplication::translate("MainWindow", "Enabled", 0, QApplication::UnicodeUTF8));
        fromIdLabel->setText(QApplication::translate("MainWindow", "From ID :", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "To ID :", 0, QApplication::UnicodeUTF8));
        refreshButton->setText(QApplication::translate("MainWindow", "Refresh", 0, QApplication::UnicodeUTF8));
        infoLabel->setText(QString());
        label->setText(QString());
        menuUser->setTitle(QApplication::translate("MainWindow", "User", 0, QApplication::UnicodeUTF8));
        menuOrder->setTitle(QApplication::translate("MainWindow", "Order", 0, QApplication::UnicodeUTF8));
        menuOrderType->setTitle(QApplication::translate("MainWindow", "Order Type", 0, QApplication::UnicodeUTF8));
        menuStatistics->setTitle(QApplication::translate("MainWindow", "Statistics", 0, QApplication::UnicodeUTF8));
        menuPlace_Info->setTitle(QApplication::translate("MainWindow", "Place Info", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_H
