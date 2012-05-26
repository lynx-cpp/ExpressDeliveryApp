#ifndef ExpressDeviveryApp_H
#define ExpressDeviveryApp_H

#include <QtGui/QMainWindow>
#include <QtSql>
#include "ui_main.h"

class ExpressDeviveryApp : public QMainWindow
{
Q_OBJECT
public:
    explicit ExpressDeviveryApp(QWidget* parent = 0, Qt::WindowFlags flags = 0);
    virtual ~ExpressDeviveryApp();
private slots:
    void actionLoginTriggered();
    void actionOrder_From_MeTriggered();
    void actionOrderTriggered();
    void actionNew_Order_from_HomeTriggered();
    void actionNewOrderTriggered();
    void actionRegisterTriggered();
private:
    bool loggedIn;
    QSqlDatabase database;
    QString schemeName,driverName,hostName,db_userName,db_password;
    QString userName,password;
    Ui::MainWindow* m_ui;
    QAction* m_actionLogin;
    QAction* m_actionOrder_from_Me;
    QAction* m_actionOrder;
    QAction* m_actionNew_Order_from_Home;
    QAction* m_actionNew_Order;
    QAction* m_actionRegister;
    QLabel* m_infoLabel;
    QStatusBar* m_statusBar;
    QTableView* m_tableView;
};

#endif // ExpressDeviveryApp_H
