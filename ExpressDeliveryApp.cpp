#include "ExpressDeliveryApp.h"

#include <QtGui/QLabel>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>
#include <QtGui/QMessageBox>
#include <QDebug>
#include <QVariant>
#include <QInputDialog>
#include <QDateTime>
#include <QtSql/qsqlrelationaldelegate.h>
#include <qwt/qwt.h>
#include <qwt/qwt_double_interval.h>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_grid.h>
#include <HistogramItem/HistogramItem.h>

#include "ui_main.h"
#include "md5/md5.h"
#include "DateDialog/DateDialog.h"
#define SUBMIT_TYPE QSqlTableModel::OnRowChange
#define TIME_FORMAT "yyyy-MM-dd hh:mm:ss"
#define MAX_COL 20

inline static QVariant getValue(const QSqlQuery& query,const QString& item)
{
    return query.value(query.record().indexOf(item));
}

QString encode(const QString& password)
{
    return QString::fromStdString(md5(md5(md5(password.toStdString()))));
}

void ExpressDeliveryApp::showAllColumn()
{
    for (int i=0; i<MAX_COL; i++)
        m_tableView->showColumn(i);
}

void ExpressDeliveryApp::loadPlaceInfo(const QString& path)
{
    if (!isAdmin){
        showMessage("You are not administrator , you cannot import place info!");
        return ;
    }
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        showMessage("Failed opening file");
        return ;
    }
    bool ok;
    QVariantMap info = parser.parse(&file,&ok).toMap();
    if (!ok) {
        showMessage("failed converting data!");
        return ;
    }
    QSqlQuery query(database);
    for (QVariantMap::iterator it=info.begin(); it!=info.end(); it++) {
        QString queryStr("INSERT INTO `%1`.`place_to_place` (`from_place`,`to_place`,`costing`,`price`) VALUES ('%2', '%3', %4, %5);");
        QVariantMap toPlaceMap = it.value().toMap();
        for (QVariantMap::iterator j=toPlaceMap.begin(); j!=toPlaceMap.end(); j++) {
            QVariantMap cur = j.value().toMap();
            bool ok = query.exec(queryStr.arg(schemeName)
                       .arg(it.key())
                       .arg(j.key())
                       .arg(cur["costing"].toDouble())
                       .arg(cur["price"].toDouble())
                      );
            if (!ok)
                showMessage("Import one item failed with error : " + query.lastError().text());
        }
    }
    showMessage("Import success!");
}

void ExpressDeliveryApp::exportPlaceInfo(const QString& path)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) {
        showMessage("Failed opening file");
        return ;
    }
    //PlaceInfoMap info;
    QVariantMap info;
    info.clear();
    QSqlQuery query(database);
    QString queryStr("SELECT * FROM `%1`.`place_to_place`");
    query.exec(queryStr.arg(schemeName));
    while (query.next()) {
        QString fromPlace = getValue(query,"from_place").toString();
        QString toPlace = getValue(query,"to_place").toString();
        double costing = getValue(query,"costing").toDouble();
        double price = getValue(query,"price").toDouble();
        QVariantMap toPlaceMap = info[fromPlace].toMap();
        QVariantMap cur;
        cur.clear();
        cur["costing"] = costing;
        cur["price"] = price;
        toPlaceMap[toPlace] = cur;
        info[fromPlace] = toPlaceMap;
    }
    //bool ok;
    //serializer.serialize(info,&file,&ok);
    QByteArray array = serializer.serialize(QVariant(info));
    file.write(array);
    file.close();
    //qDebug() << array;
    showMessage("Export success!");
}

void ExpressDeliveryApp::getStatistics(const QDate& date, double& got, double& spent)
{
    QString queryStr = "SELECT SUM(`order_list`.`costing`) AS tot_costing,SUM(`order_list`.`price`) AS tot_price \
    FROM `%1`.order_list \
    WHERE (`order_list`.`order_sent_time`>='%2') AND (`order_list`.`order_sent_time`<'%3')";
    QSqlQuery query(database);
    query.exec(queryStr.arg(schemeName)
               .arg(QDateTime(date,QTime(0,0)).toString(TIME_FORMAT))
               .arg(QDateTime(date.addDays(1),QTime(0,0)).toString(TIME_FORMAT)));
    query.next();
    got = getValue(query,"tot_price").toDouble();
    spent = getValue(query,"tot_costing").toDouble();
    //got = query.value(0).toDouble();
    //spent = query.value(1).toDouble();
}

void ExpressDeliveryApp::showMessage(const QString& message)
{
    qDebug() << message;
    m_statusBar->showMessage(message);
}

QString ExpressDeliveryApp::setFilter(const QString& table,const QString& time)
{
    QString filter = "";
    if (m_idFilterCheckBox->checkState()) {
        filter += QString("(%1.id>=%2 AND %1.id<=%3)").arg(table).arg(filterFromId).arg(filterToId);
    }
    if (m_timeFilterCheckBox->checkState() && time!="") {
        if (filter!="")
            filter += " AND ";
        filter += QString("(%1.%2>='%3' AND %1.%2<='%4')")
                  .arg(table)
                  .arg(time)
                  .arg(filterFromTime.toString(TIME_FORMAT))
                  .arg(filterToTime.toString(TIME_FORMAT));
    }
    return filter;
}

void ExpressDeliveryApp::showUserInformation()
{
    tableModel->setTable("account");
    tableModel->setEditStrategy(SUBMIT_TYPE);
    if (setFilter()!="")
        tableModel->setFilter(setFilter("account"));
    tableModel->select();
    tableModel->setHeaderData(1,Qt::Horizontal, tr("Account Name"));
    tableModel->setHeaderData(2,Qt::Horizontal, tr("User Name"));
    tableModel->setHeaderData(3,Qt::Horizontal, tr("Address"));
    tableModel->setHeaderData(4,Qt::Horizontal, tr("is Admin"));
    tableModel->setHeaderData(5,Qt::Horizontal, tr("Password"));
    tableModel->setHeaderData(6,Qt::Horizontal, tr("Telephone"));

    m_tableView->setModel(tableModel);
    showAllColumn();
    //m_tableView->hideColumn(0);
    m_tableView->show();
    stat = UserInformationStat;
}

void ExpressDeliveryApp::showOrderInformation(bool onlyMe)
{
    if (!loggedIn) {
        showMessage("Please log in first!");
        return ;
    }
    tableModel->setTable("order_list");
    tableModel->setEditStrategy(SUBMIT_TYPE);
    tableModel->setRelation(4, QSqlRelation("order_category","id","order_category_name"));
    tableModel->setRelation(5, QSqlRelation("account","id","account_name"));
    //tableModel->setRelation(6, QSqlRelation("delivery","id","postman_telephone"));
    if (!isAdmin || onlyMe) {
        QString filter = "account_id='%1'";
        QString extFilter = setFilter("order_list","order_sent_time");
        if (extFilter!="")
            tableModel->setFilter(filter.arg(accountId) + " AND (" + extFilter + ")");
        else
            tableModel->setFilter(filter.arg(accountId));
    }
    else {
        if (setFilter("order_list","order_sent_time")!="")
            tableModel->setFilter(setFilter("order_list","order_sent_time"));
    }
    tableModel->select();
    qDebug() << tableModel->lastError();
    tableModel->setHeaderData(0,Qt::Horizontal, tr("ID"));
    tableModel->setHeaderData(1,Qt::Horizontal, tr("From Place"));
    tableModel->setHeaderData(2,Qt::Horizontal, tr("To Place"));
    tableModel->setHeaderData(3,Qt::Horizontal, tr("Sent Time"));
    tableModel->setHeaderData(4,Qt::Horizontal, tr("Category"));
    tableModel->setHeaderData(5,Qt::Horizontal, tr("Account"));
    tableModel->setHeaderData(6,Qt::Horizontal, tr("Costing"));
    tableModel->setHeaderData(7,Qt::Horizontal, tr("Price"));
    tableModel->setHeaderData(8,Qt::Horizontal, tr("Postman Name"));
    tableModel->setHeaderData(9,Qt::Horizontal, tr("Postman Phone"));
    tableModel->setHeaderData(10,Qt::Horizontal, tr("Delivery Start"));
    tableModel->setHeaderData(11,Qt::Horizontal, tr("Delivery Arrival"));

    m_tableView->setModel(tableModel);
    showAllColumn();
    if (!isAdmin)
        m_tableView->hideColumn(6);
    m_tableView->show();
    stat = OrderInformationStat;
}

void ExpressDeliveryApp::showOrderTypeInformation()
{
    tableModel->setTable("order_category");
    tableModel->setEditStrategy(SUBMIT_TYPE);
    tableModel->select();
    tableModel->setHeaderData(0,Qt::Horizontal, "ID");
    tableModel->setHeaderData(1,Qt::Horizontal, "Type Name");
    tableModel->setHeaderData(2,Qt::Horizontal, "Price");
    tableModel->setHeaderData(3,Qt::Horizontal, "Costing");
    m_tableView->setModel(tableModel);
    showAllColumn();
    if (!isAdmin) {
        qDebug() << "not admin , so hide costing";
        m_tableView->hideColumn(3);
    }
    m_tableView->show();
    stat = OrderTypeInformationStat;
}

void ExpressDeliveryApp::showPlaceInformation()
{
    tableModel->setTable("place_to_place");
    tableModel->setHeaderData(0,Qt::Horizontal,"From Place");
    tableModel->setHeaderData(1,Qt::Horizontal,"To Place");
    tableModel->setHeaderData(2,Qt::Horizontal,"Costing");
    tableModel->setHeaderData(3,Qt::Horizontal,"Price");
    tableModel->select();

    m_tableView->setModel(tableModel);
    showAllColumn();
    if (!isAdmin)
        m_tableView->hideColumn(2);
    m_tableView->show();
    stat = PlaceInfomationStat;
}

ExpressDeliveryApp::ExpressDeliveryApp(QWidget* parent, Qt::WindowFlags flags):QMainWindow(parent,flags),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    m_actionLogin = m_ui->actionLogin;
    m_actionNew_Order = m_ui->actionNew_Order;
    m_actionOrder = m_ui->actionOrder;
    m_actionOrder_from_Me = m_ui->actionOrder_from_Me;
    m_actionRegister = m_ui->actionRegister;
    m_tableView = m_ui->tableView;
    m_infoLabel = m_ui->infoLabel;
    m_statusBar = m_ui->statusbar;
    m_actionInformation = m_ui->actionInformation;
    m_submitButton = m_ui->submitButton;
    m_discardButton = m_ui->discardButton;
    m_actionLogout = m_ui->actionLogout;
    m_addbutton = m_ui->addButton;
    m_removeButton = m_ui->removeButton;
    m_refreshButton = m_ui->refreshButton;
    m_actionOrderType = m_ui->actionOrder_Query;
    m_actionOrderTypeAdd = m_ui->actionModify_Type;
    m_timeFilterCheckBox = m_ui->timeFilterCheckBox;
    m_dateTimeEdit_from = m_ui->dateTimeEdit_from;
    m_dateTimeEdit_to = m_ui->dateTimeEdit_to;
    m_idFilterCheckBox = m_ui->idFilterCheckBox;
    m_fromIdSpinBox = m_ui->fromIdSpinBox;
    m_toIdSpinBox = m_ui->toIdSpinBox;
    m_actionToday = m_ui->actionToday;
    m_actionOtherTime = m_ui->actionOtherTime;
    m_actionList_Place_Info = m_ui->actionList_Place_Info;
    m_actionNew_Place_Info = m_ui->actionNew_Place_Info;
    m_actionExport = m_ui->actionExport;
    m_actionImport = m_ui->actionImport;

    connect(m_actionLogin,SIGNAL(triggered(bool)),this,SLOT(actionLoginTriggered()));
    connect(m_actionNew_Order,SIGNAL(triggered(bool)),this,SLOT(actionNewOrderTriggered()));
    connect(m_actionOrder,SIGNAL(triggered(bool)),this,SLOT(actionOrderTriggered()));
    connect(m_actionOrder_from_Me,SIGNAL(triggered(bool)),this,SLOT(actionOrder_From_MeTriggered()));
    connect(m_actionRegister,SIGNAL(triggered(bool)),this,SLOT(actionRegisterTriggered()));
    connect(m_actionInformation,SIGNAL(triggered(bool)),this,SLOT(actionInformationTriggered()));
    connect(m_actionLogout,SIGNAL(triggered(bool)),this, SLOT(actionLogoutTriggered()));
    connect(m_addbutton, SIGNAL(clicked(bool)),this, SLOT(addButtonClicked()));
    connect(m_removeButton, SIGNAL(clicked(bool)),this, SLOT(removeButtonClicked()));
    connect(m_refreshButton, SIGNAL(clicked(bool)),this, SLOT(refreshButtonClicked()));
    connect(m_actionOrderType, SIGNAL(triggered(bool)),this, SLOT(actionOrderTypeTriggered()));
    connect(m_actionOrderTypeAdd, SIGNAL(triggered(bool)),this, SLOT(actionOrderTypeAddTriggered()));
    connect(m_dateTimeEdit_from, SIGNAL(dateTimeChanged(QDateTime)),this, SLOT(fromTimeChanged()));
    connect(m_dateTimeEdit_to, SIGNAL(dateTimeChanged(QDateTime)),this, SLOT(toTimeChanged()));
    connect(m_fromIdSpinBox, SIGNAL(valueChanged(int)),this, SLOT(fromIdChanged()));
    connect(m_toIdSpinBox, SIGNAL(valueChanged(int)),this, SLOT(toIdChanged()));
    connect(m_idFilterCheckBox, SIGNAL(stateChanged(int)),this, SLOT(idCheckBoxStateChanged()));
    connect(m_timeFilterCheckBox, SIGNAL(stateChanged(int)),this, SLOT(timeCheckBoxStateChanged()));
    connect(m_actionToday, SIGNAL(triggered(bool)),this, SLOT(actionTodayTriggered()));
    connect(m_actionOtherTime, SIGNAL(triggered(bool)),this, SLOT(actionOtherTimeTriggered()));
    connect(m_actionList_Place_Info, SIGNAL(triggered(bool)),this, SLOT(actionList_Place_InfoTriggered()));
    connect(m_actionNew_Place_Info, SIGNAL(triggered(bool)),this, SLOT(actionNew_Place_InfoTriggered()));
    connect(m_actionExport, SIGNAL(triggered(bool)),this, SLOT(actionExportTriggered()));
    connect(m_actionImport, SIGNAL(triggered(bool)),this, SLOT(actionImportTriggered()));

    schemeName = "ExpressDelivery";
    driverName = "QMYSQL";
    hostName = "localhost";
    db_userName = "root";
    /*db_password = QInputDialog::getText(NULL,tr("Input Database Password"),
     *                           tr("Password"),
     *                           QLineEdit::Password);
     */
    db_password = "";
    database = QSqlDatabase::addDatabase(driverName);
    database.setConnectOptions();
    database.setDatabaseName(schemeName);
    database.setHostName(hostName);
    database.setUserName(db_userName);
    database.setPassword(db_password);

    address = accountName = userName = "";
    loggedIn = false;
    isAdmin = false;
    isAvailable = false;
    if (database.open()==true) {
        showMessage("Database opened successfully!");
        isAvailable = true;
    }
    else
        showMessage("Failed opening database");
    qDebug() << database.lastError();
    tableModel = new QSqlRelationalTableModel(this,database);
    tableModel->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    //m_tableView->setItemDelegate((new QSqlRelationalDelegate(m_tableView,this)));
    //showOrderInformation();
    connect(m_submitButton, SIGNAL(clicked(bool)),this, SLOT(submitButtonClicked()));
    connect(m_discardButton, SIGNAL(clicked(bool)),this, SLOT(discardButtonClicked()));
    //qDebug() << QString::fromStdString(md5("123"));
    qDebug() << encode("123");
    stat = NotSet;
}

ExpressDeliveryApp::~ExpressDeliveryApp()
{}

void ExpressDeliveryApp::actionLoginTriggered()
{
    if (!isAvailable) {
        showMessage("Database is not available,please check if MySQL works!");
        return ;
    }
    QString password;
    accountName = QInputDialog::getText(NULL,tr("username : "),
                                        tr("User Name"),
                                        QLineEdit::Normal
                                       );
    password = QInputDialog::getText(NULL,tr("Password : "),
                                     tr("Password"),
                                     QLineEdit::Password
                                    );
    QSqlQuery query(
        "select * from account where account_name='" + accountName + "' and password='" + encode(password)+ "'",
        database
    );
    if (!query.exec())
        showMessage("Error while trying to log in!");
    loggedIn = query.next();
    if (!loggedIn) {
        showMessage("Username or Password wrong!");
        return ;
    }
    showMessage("Successfully logged in !");
    qDebug() << "logged in";
    accountId = getValue(query,"id").toString();
    accountName = getValue(query,"account_name").toString();
    address = getValue(query,"address").toString();
    userName = getValue(query,"user_name").toString();
    isAdmin = getValue(query,"is_admin").toBool();
    telephone = getValue(query,"telephone").toString();
    qDebug() << accountName << " " << address << " "<< userName << " " << isAdmin;
    if (isAdmin) {
        QSqlQuery data(database);
        data.exec("select account_name,user_name,address,is_admin from account");
        showUserInformation();
    }
    else {
        m_tableView->setModel(NULL);
        showOrderInformation();
    }
}

void ExpressDeliveryApp::actionNewOrderTriggered()
{
    if (!loggedIn) {
        showMessage("Please log in first");
        emit actionLoginTriggered();
        return ;
    }
    bool ok;
    QSqlQuery query(database);
    QString queryStr,fromPlace,toPlace;
    int categoryID;
    double price,costing;
    do {
        fromPlace = QInputDialog::getText(this,"from place","where your order will start from?",QLineEdit::Normal,"",&ok);
        if (!ok)
            break;

        toPlace = QInputDialog::getText(this,"to place","where your order will arrive at?",QLineEdit::Normal,"",&ok);
        if (!ok)
            break;

        query.exec("select distinct order_category_name from order_category");
        QStringList items;
        items.clear();
        while (query.next()) {
            items << getValue(query,"order_category_name").toString();
        }
        QString category = QInputDialog::getItem(this,"category","what category will your order be?",items,0,false,&ok);
        if (!ok)
            break;
        queryStr = "select * from %1.order_category where order_category_name=\"%2\"";
        query.exec(queryStr.arg(schemeName).arg(category));
        query.next();
        categoryID = getValue(query,"id").toInt();
        price = getValue(query,"price").toDouble();
        costing = getValue(query,"costing").toDouble();
    } while (0);
    if (!ok) {
        showMessage("New Order Operation Canceled");
        return ;
    }
    queryStr = "SELECT * FROM `%1`.`place_to_place` WHERE from_place='%2' and to_place='%3'";
    query.exec(queryStr.arg(schemeName)
               .arg(fromPlace)
               .arg(toPlace)
              );
    if (!query.next()) {
        showMessage("route from " + fromPlace + " to " + toPlace + " is not supported");
        return ;
    }
    price += getValue(query,"price").toDouble();
    costing += getValue(query,"costing").toDouble();
    queryStr = "INSERT INTO `%1`.`order_list` (`from_place`, `to_place`, `order_sent_time`, `order_category_id`, `account_id`, `price`, `costing`) VALUES ('%2', '%3', '%4', %5, %6, %7, %8);";
    ok = query.exec(queryStr.arg(schemeName)
                    .arg(fromPlace)
                    .arg(toPlace)
                    .arg(QDateTime::currentDateTime().toString(TIME_FORMAT))
                    .arg(categoryID)
                    .arg(accountId)
                    .arg(price)
                    .arg(costing)
                   );
    if (!ok) {
        showMessage("Failed creating new order :" + query.lastError().text());
        return ;
    }
    else
        showMessage("Successfully created new order");
}

void ExpressDeliveryApp::actionOrder_From_MeTriggered()
{
    showOrderInformation(true);
}

void ExpressDeliveryApp::actionOrderTriggered()
{
    showOrderInformation();
}

void ExpressDeliveryApp::actionInformationTriggered()
{
    if (!loggedIn) {
        showMessage("Not logged in , no information to show");
        return ;
    }
    QString password = QInputDialog::getText(NULL,tr("Password : "),
                       tr("Password"),
                       QLineEdit::Password
                                            );
    QSqlQuery query(
        "select * from account where account_name='" + accountName + "' and password='" + encode(password)+ "'",
        database
    );
    if (!query.exec()) {
        showMessage("Error while trying authorize!");
        return ;
    }
    loggedIn = query.next();
    if (!loggedIn) {
        showMessage("Password wrong!");
        return ;
    }

    UserInfo* userInfo = new UserInfo(this);
    QEventLoop loop;
    connect(userInfo, SIGNAL(accepted()),&loop, SLOT(quit()));
    connect(userInfo, SIGNAL(rejected()),&loop, SLOT(quit()));
    userInfo->setAccountName(accountName);
    userInfo->setAddress(address);
    userInfo->setIsAdmin(isAdmin);
    userInfo->setTelephone(telephone);
    do {
        userInfo->show();
        loop.exec();
    } while (userInfo->result()==QDialog::Accepted && (!check(userInfo)));
    if (userInfo->result()==QDialog::Rejected) {
        showMessage("Operation canceled");
        return ;
    }
    QString queryStr("UPDATE `%1`.`account` SET `account_name`='%2', `user_name`='%3', `address`='%4', `is_admin`=%5, `telephone`='%6' WHERE `id`='%7';");
    bool result = query.exec(queryStr.arg(schemeName)
                             .arg(userInfo->accountName())
                             .arg(userInfo->userName())
                             .arg(userInfo->address())
                             .arg(userInfo->isAdmin())
                             .arg(userInfo->telephone())
                             .arg(accountId)
                            );
    if (!result) {
        int error = query.lastError().number();
        if (error==1062)
            showMessage("Account name exists!");
        else
            showMessage("Database Operation failed : "+query.lastError().text());
    }
    else {
        showMessage("Register Operation succeeded: ");
    }
    delete userInfo;
}

void ExpressDeliveryApp::actionRegisterTriggered()
{
    UserInfo* registerApp = new UserInfo(this);
    QEventLoop loop;
    connect(registerApp, SIGNAL(accepted()),&loop, SLOT(quit()));
    connect(registerApp, SIGNAL(rejected()),&loop, SLOT(quit()));
    do {
        registerApp->show();
        loop.exec();
    } while (registerApp->result()==QDialog::Accepted && (!check(registerApp)));
    if (registerApp->result()==QDialog::Rejected) {
        showMessage("Register operation canceled");
        return ;
    }
    QString queryStr("INSERT INTO `%1`.`account` (`account_name`, `user_name`, `address`, `is_admin`, `password`, `telephone`) VALUES ('%2', '%3', '%4', %5, '%6','%7');");
    QSqlQuery query(database);
    bool result = query.exec(
                      queryStr.arg(schemeName)
                      .arg(registerApp->accountName())
                      .arg(registerApp->userName())
                      .arg(registerApp->address())
                      .arg(registerApp->isAdmin())
                      .arg(encode(registerApp->password()))
                      .arg(registerApp->telephone())
                  );
    if (!result) {
        int error = query.lastError().number();
        if (error==1062)
            showMessage("Account name exists!");
        else
            showMessage("Database Operation failed : "+query.lastError().text());
    }
    else {
        showMessage("Register Operation succeeded: ");
    }
    delete registerApp;
}

bool ExpressDeliveryApp::check(const UserInfo* registerApp)
{
    QMessageBox msgBox;
    if (registerApp->accountName()=="") {
        msgBox.setText("account name cannot be NULL!");
        msgBox.exec();
        return false;
    }
    if (registerApp->address()=="") {
        msgBox.setText("address cannot be NULL!");
        msgBox.exec();
        return false;
    }
    if (registerApp->address()=="") {
        msgBox.setText("password cannot be NULL!");
        msgBox.exec();
        return false;
    }
    if (registerApp->isAdmin()==true && isAdmin==false) {
        msgBox.setText("You are not administrator so you cannot register administrator account!");
        msgBox.exec();
        return false;
    }
    if (registerApp->password()!=registerApp->verifiedPassword()) {
        msgBox.setText("Password mismatches repeated password!");
        msgBox.exec();
        return false;
    }
    return true;
}

void ExpressDeliveryApp::submitButtonClicked()
{
    if (tableModel->submitAll())
        showMessage("Submit suceess");
    else
        showMessage("Submit failure");
}

void ExpressDeliveryApp::discardButtonClicked()
{
    tableModel->revertAll();
}

void ExpressDeliveryApp::actionLogoutTriggered()
{
    loggedIn = false;
    isAdmin = false;
    stat = NotSet;
    tableModel->clear();
    showMessage("Logged out.");
}

void ExpressDeliveryApp::addButtonClicked()
{
    if (stat==UserInformationStat)
        emit actionRegisterTriggered();
    else if (stat==OrderInformationStat)
        emit actionNewOrderTriggered();
    else if (stat==PlaceInfomationStat)
        emit actionNew_Place_InfoTriggered();
}

void ExpressDeliveryApp::refreshButtonClicked()
{
    //qDebug() << stat;
    if (stat==UserInformationStat)
        showUserInformation();
    else if (stat==OrderInformationStat)
        showOrderInformation();
    else if (stat==PlaceInfomationStat)
        showPlaceInformation();
}

void ExpressDeliveryApp::removeButtonClicked()
{
    if (stat==NotSet) {
        showMessage("Nothing to display , nothing to remove");
        return ;
    }
    int fromInt = QInputDialog::getInt(this,"From Row","From row :",0,0,tableModel->rowCount());
    int toInt = QInputDialog::getInt(this,"To Row","To row :",0,fromInt,tableModel->rowCount());
    tableModel->removeRows(fromInt - 1,toInt - fromInt + 1);
}

void ExpressDeliveryApp::actionOrderTypeAddTriggered()
{
    if (!isAdmin) {
        showMessage("You are not administrator , so you cannot add new order type!");
        return ;
    }
    bool ok;
    QString typeName;
    double price,costing;
    do {
        typeName = QInputDialog::getText(this,"Type Name","Input Type Name :",QLineEdit::Normal,"",&ok);
        if (!ok) break;
        price = QInputDialog::getDouble(this,"Price","Input Price :",-2147483648,2147483647,QLineEdit::Normal,2,&ok);
        if (!ok) break;
        costing = QInputDialog::getDouble(this,"Costing","Input Costing :",-2147483648,2147483647,QLineEdit::Normal,2,&ok);
        if (!ok) break;
    } while (0);
    if (!ok) {
        showMessage("New Order Type operation canceled.");
        return ;
    }
    QString queryStr = "INSERT INTO `%1`.`order_category` (`order_category_name`,`price`,`costing`) VALUES ('%2', %3, %4);";
    QSqlQuery query(database);
    ok = query.exec(queryStr.arg(schemeName)
                    .arg(typeName)
                    .arg(price)
                    .arg(costing)
                   );
    if (!ok)
        showMessage("Database error : " + query.lastError().text());
    else
        showMessage("Successfully added new type");
}

void ExpressDeliveryApp::actionOrderTypeTriggered()
{
    showOrderTypeInformation();
}

void ExpressDeliveryApp::fromIdChanged()
{
    filterFromId = m_fromIdSpinBox->value();
}

void ExpressDeliveryApp::fromTimeChanged()
{
    filterFromTime = m_dateTimeEdit_from->dateTime();
}

void ExpressDeliveryApp::idCheckBoxStateChanged()
{
    emit fromIdChanged();
    emit toIdChanged();
    emit refreshButtonClicked();
}

void ExpressDeliveryApp::timeCheckBoxStateChanged()
{
    emit fromTimeChanged();
    emit toTimeChanged();
    emit refreshButtonClicked();
}


void ExpressDeliveryApp::toIdChanged()
{
    filterToId = m_toIdSpinBox->value();
}


void ExpressDeliveryApp::toTimeChanged()
{
    filterToTime = m_dateTimeEdit_to->dateTime();
}

void ExpressDeliveryApp::actionTodayTriggered()
{
    if (!isAdmin) {
        showMessage("You are not administrator , so you cannot view statistics");
        return ;
    }
    double got,spent;
    getStatistics(QDate::currentDate(),got,spent);
    QMessageBox msgBox(this);
    QString text = "\
    Today Got     : %1      \n\
    Today Spent   : %2      \n\
    Today Profit  : %3      \n";
    msgBox.setText(text.arg(got).arg(spent).arg(got - spent));
    msgBox.setWindowTitle("Statistics");
    msgBox.setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    msgBox.exec();
    //qDebug() <<"!!!!" << text.arg(got).arg(spent);
}

void ExpressDeliveryApp::actionOtherTimeTriggered()
{
    if (!isAdmin) {
        showMessage("You are not administrator , so you cannot view statistics");
        return ;
    }
    DateDialog dateDialog(this);
    QEventLoop loop;
    connect(&dateDialog, SIGNAL(accepted()),&loop, SLOT(quit()));
    connect(&dateDialog, SIGNAL(rejected()),&loop, SLOT(quit()));
    QDate fromDate,toDate;
    do {
        dateDialog.setText("From Date : ");
        dateDialog.show();
        loop.exec();
        if (dateDialog.result()==QDialog::Rejected)
            break;
        fromDate = dateDialog.getDate();
        dateDialog.setText("To Date : ");
        dateDialog.show();
        loop.exec();
        if (dateDialog.result()==QDialog::Rejected)
            break;
        toDate = dateDialog.getDate();
    } while (false);
    if (dateDialog.result()==QDialog::Rejected) {
        showMessage("Statistics operation canceled");
        return ;
    }
    QwtPlot plot;
    plot.setTitle("Profit histogram of given date interval");

    QwtPlotGrid* grid = new QwtPlotGrid;
    grid->enableXMin(true);
    grid->enableYMin(true);
    grid->setMajPen(QPen(Qt::black,0,Qt::DotLine));
    grid->setMinPen(QPen(Qt::gray, 0,Qt::DotLine));
    grid->attach(&plot);

    int totDays = fromDate.daysTo(toDate) + 1;

    HistogramItem* histogram = new HistogramItem;
    int numValues = totDays;
    QwtArray<QwtDoubleInterval> intervals(numValues);
    QwtArray<double> values(numValues);
    double width = 1.0;

    double pos = 0.0;
    double tot_got,tot_spent;
    tot_got = tot_spent = 0;
    double max_val = -2147483647;
    for (int i=0; i<numValues; i++) {
        double got,spent;
        getStatistics(fromDate.addDays(i),got,spent);
        values[i] = got - spent;
        intervals[i] = QwtDoubleInterval(pos,pos + width);
        if (values[i]>max_val)
            max_val = values[i];
        tot_got += got;
        tot_spent += spent;
        qDebug () << got << " " << spent << " " << got - spent << " " << values[i];
        pos += width;
    }
    histogram->setData(QwtIntervalData(intervals,values));
    histogram->attach(&plot);

    qDebug() << max_val;
    plot.setAxisScale(QwtPlot::yLeft,0.0,max_val);
    plot.setAxisScale(QwtPlot::xBottom,0.0,pos + 3);
    plot.replot();
    plot.resize(600,400);
    plot.show();

    QMessageBox msgBox(this);
    QString text = "\
    Total Got     : %1      \n\
    Total Spent   : %2      \n\
    Total Profit  : %3      \n";
    msgBox.setText(text.arg(tot_got).arg(tot_spent).arg(tot_got - tot_spent));
    msgBox.setWindowTitle("Statistics");
    msgBox.setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    msgBox.exec();
}

void ExpressDeliveryApp::actionList_Place_InfoTriggered()
{
    showPlaceInformation();
}

void ExpressDeliveryApp::actionNew_Place_InfoTriggered()
{
    if (!isAdmin) {
        showMessage("You are not administrator , so you cannot add new place info!");
        return ;
    }
    QString fromPlace,toPlace;
    bool ok;
    double costing,price;
    do {
        fromPlace = QInputDialog::getText(this,"From Place","Please Input 'From Place' :",QLineEdit::Normal,"",&ok);
        if (!ok)
            break;
        toPlace = QInputDialog::getText(this,"To Place","Please Input 'To Place' :",QLineEdit::Normal,"",&ok);
        if (!ok)
            break;
        costing = QInputDialog::getDouble(this,"Costing","Please Input Costing :",0,-2147483647,2147483647,
                                          2,&ok);
        if (!ok)
            break;
        price = QInputDialog::getDouble(this,"Price","Please Input Price :",0,-2147483647,2147483647,
                                        2,&ok);
    } while (0);
    if (!ok) {
        showMessage("New Place operation canceled!");
        return ;
    }

    QSqlQuery query(database);
    QString queryStr("INSERT INTO `%1`.`place_to_place` (`from_place`, `to_place`, `costing`, `price`) VALUES ('%2', '%3', %4, %5)");
    ok = query.exec(queryStr.arg(schemeName)
                    .arg(fromPlace)
                    .arg(toPlace)
                    .arg(costing)
                    .arg(price)
                   );
    if (ok)
        showMessage("Successfully added place info!");
    else {
        showMessage("Failed adding place info!");
        qDebug() << query.lastError();
    }
    showPlaceInformation();
}

void ExpressDeliveryApp::actionExportTriggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Export File"
                       ,"~/tmp/"
                                                   );
    exportPlaceInfo(fileName);
}


void ExpressDeliveryApp::actionImportTriggered()
{
    //loadPlaceInfo("/home/lynx/tmp/1111");
    QString fileName = QFileDialog::getOpenFileName(this, "Export File"
                       ,"~/tmp/"
                                                   );
    loadPlaceInfo(fileName);
}

#include "ExpressDeliveryApp.moc"
