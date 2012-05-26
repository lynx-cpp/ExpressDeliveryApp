#include "ExpressDeviveryApp.h"

#include <QtGui/QLabel>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>
#include <QDebug>
#include <QInputDialog>

#include "ui_main.h"
#include "RegisterApp/RegisterApp.h"

ExpressDeviveryApp::ExpressDeviveryApp(QWidget* parent, Qt::WindowFlags flags):QMainWindow(parent,flags),
m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    
    m_actionLogin = m_ui->actionLogin;
    m_actionNew_Order = m_ui->actionNew_Order;
    m_actionNew_Order_from_Home = m_ui->actionNew_Order_from_Home;
    m_actionOrder = m_ui->actionOrder;
    m_actionOrder_from_Me = m_ui->actionOrder_from_Me;
    m_actionRegister = m_ui->actionRegister;
    m_tableView = m_ui->tableView;
    m_infoLabel = m_ui->infoLabel;
    m_statusBar = m_ui->statusbar;
    
    connect(m_actionLogin,SIGNAL(triggered(bool)),this,SLOT(actionLoginTriggered()));
    connect(m_actionNew_Order,SIGNAL(triggered(bool)),this,SLOT(actionNewOrderTriggered()));
    connect(m_actionNew_Order_from_Home,SIGNAL(triggered(bool)),this,SLOT(actionNew_Order_from_HomeTriggered()));
    connect(m_actionOrder,SIGNAL(triggered(bool)),this,SLOT(actionOrderTriggered()));
    connect(m_actionOrder_from_Me,SIGNAL(triggered(bool)),this,SLOT(actionOrder_From_MeTriggered()));
    connect(m_actionRegister,SIGNAL(triggered(bool)),this,SLOT(actionRegisterTriggered()));
    
    schemeName = "mydb";
    driverName = "QMYSQL";
    hostName = "localhost";
    db_userName = "root";
    /*db_password = QInputDialog::getText(NULL,tr("Input Database Password"),
                               tr("Password"),
                               QLineEdit::Password);
                               */
    db_password = "";
    database = QSqlDatabase::addDatabase(driverName);
    database.setConnectOptions();
    database.setDatabaseName(schemeName);
    database.setHostName(hostName);
    database.setUserName(db_userName);
    database.setPassword(db_password);
    
    userName = "";
    password = "";
    loggedIn = false;
    if (database.open()==true)
        m_statusBar->showMessage("Database opened successfully!");
    else
        m_statusBar->showMessage("Failed opening database");
    qDebug() << database.lastError();
}

ExpressDeviveryApp::~ExpressDeviveryApp()
{}

void ExpressDeviveryApp::actionLoginTriggered()
{
    userName = QInputDialog::getText(NULL,tr("username : "),
                                     tr("User Name"),
                                     QLineEdit::Normal
    );
    password = QInputDialog::getText(NULL,tr("Password : "),
                                     tr("Password"),
                                     QLineEdit::Password
    );
    QSqlQuery query(
        "select account_name,password from account where account_name='" + userName + "' and password='" + password + "'",
        database
    );
    if (!query.exec()){
        m_statusBar->showMessage("Error while trying to log in!");
        qDebug() << "Error while trying to log in!";
    }
    loggedIn = query.next();
    if (loggedIn){
        m_statusBar->showMessage("Successfully logged in !");
        qDebug() << "logged in";
    }
    else{
        m_statusBar->showMessage("Username or Password wrong!");
        qDebug() << "Username or Password wrong!";
    }
}

void ExpressDeviveryApp::actionNew_Order_from_HomeTriggered()
{
    
}

void ExpressDeviveryApp::actionNewOrderTriggered()
{
    
}

void ExpressDeviveryApp::actionOrder_From_MeTriggered()
{
    
}

void ExpressDeviveryApp::actionOrderTriggered()
{
    
}

void ExpressDeviveryApp::actionRegisterTriggered()
{
    
}


#include "ExpressDeviveryApp.moc"
