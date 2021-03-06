#ifndef REGISTER_APP_H
#define REGISTER_APP_H
#include <QtGui>
#include <QObject>

class UserInfo : public QDialog
{
    Q_OBJECT
public:
    explicit UserInfo(QWidget* parent = 0, Qt::WindowFlags f = 0);
    virtual ~UserInfo();
    QString accountName() const;
    QString userName() const;
    QString telephone() const;
    QString address() const;
    QString password() const;
    QString verifiedPassword() const;
    bool isAdmin() const;
    void setAccountName(const QString& value);
    void setUserName(const QString& value);
    void setTelephone(const QString& value);
    void setAddress(const QString& value);
    void setIsAdmin(bool value);
protected slots:
    virtual void accept();
protected:
    QLabel* m_accountNameLabel;
    QLabel* m_userNameLabel;
    QLabel* m_telephoneLabel;
    QLabel* m_addressLabel;
    QLabel* m_passwordLabel;
    QLabel* m_verifiedPasswordLabel;
    QLineEdit* m_accountNameInput;
    QLineEdit* m_userNameInput;
    QLineEdit* m_telephoneInput;
    QLineEdit* m_addressInput;
    QLineEdit* m_passwordInput;
    QLineEdit* m_verifiedPasswordInput;
    QCheckBox* m_isAdminCheckBox;
    QDialogButtonBox* m_buttonBox;
private:
    QString m_accountName,m_userName,m_telephone,m_address,m_password,m_verifiedPassword;
    bool m_isAdmin;
};

#endif