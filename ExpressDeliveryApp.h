#ifndef ExpressDeliveryApp_H
#define ExpressDeliveryApp_H

#include <QtGui/QMainWindow>
#include <QtSql>
#include "ui_main.h"
#include "UserInfo/UserInfo.h"

class ExpressDeliveryApp : public QMainWindow
{
Q_OBJECT
public:
    enum AppStat{
        NotSet
       ,UserInformationStat
       ,OrderInformationStat
       ,OrderTypeInformationStat
       ,PlaceInfomationStat
    };
    explicit ExpressDeliveryApp(QWidget* parent = 0, Qt::WindowFlags flags = 0);
    virtual ~ExpressDeliveryApp();
private slots:
    void actionLoginTriggered();
    void actionOrder_From_MeTriggered();
    void actionOrderTriggered();
    void actionNewOrderTriggered();
    void actionInformationTriggered();
    void actionRegisterTriggered();
    void actionLogoutTriggered();
    void actionOrderTypeTriggered();
    void actionOrderTypeAddTriggered();
    void actionTodayTriggered();
    void actionOtherTimeTriggered();
    void actionList_Place_InfoTriggered();
    void actionNew_Place_InfoTriggered();
    void submitButtonClicked();
    void discardButtonClicked();
    void addButtonClicked();
    void removeButtonClicked();
    void refreshButtonClicked();
    void fromTimeChanged();
    void toTimeChanged();
    void fromIdChanged();
    void toIdChanged();
    void idCheckBoxStateChanged();
    void timeCheckBoxStateChanged();
private:
    bool check(const UserInfo*);
    void showMessage(const QString& message);
    void showUserInformation();
    void showOrderInformation(bool onlyMe=false);
    void showOrderTypeInformation();
    void showPlaceInformation();
    void getStatistics(const QDate& date,double& got,double& spent);
    void showAllColumn();
    QString setFilter(const QString& table = "order_list",const QString& time = "");
    
    //user information
    AppStat stat;
    bool loggedIn,isAdmin;
    bool isAvailable;
    QString accountId,accountName,userName,address;
    QString telephone;
    
    //filter information
    QDateTime filterFromTime,filterToTime;
    int filterFromId,filterToId;
    
    //other information
    QSqlDatabase database;
    QString schemeName,driverName,hostName,db_userName,db_password;
    Ui::MainWindow* m_ui;
    QAction* m_actionLogin;
    QAction* m_actionOrder_from_Me;
    QAction* m_actionOrder;
    QAction* m_actionNew_Order;
    QAction* m_actionRegister;
    QAction* m_actionInformation;
    QAction* m_typeQuery;
    QAction* m_actionLogout;
    QAction* m_actionOrderType;
    QAction* m_actionOrderTypeAdd;
    QAction* m_actionToday;
    QAction* m_actionOtherTime;
    QAction* m_actionList_Place_Info;
    QAction* m_actionNew_Place_Info;
    QPushButton* m_submitButton;
    QPushButton* m_discardButton;
    QPushButton* m_addbutton;
    QPushButton* m_removeButton;
    QPushButton* m_refreshButton;
    QCheckBox* m_timeFilterCheckBox;
    QCheckBox* m_idFilterCheckBox;
    QDateTimeEdit* m_dateTimeEdit_from;
    QDateTimeEdit* m_dateTimeEdit_to;
    QSpinBox* m_fromIdSpinBox;
    QSpinBox* m_toIdSpinBox;
    QLabel* m_infoLabel;
    QStatusBar* m_statusBar;
    QTableView* m_tableView;
    QSqlRelationalTableModel* tableModel;
};

#endif // ExpressDeliveryApp_H
