#ifndef REGISTER_APP_H
#define REGISTER_APP_H
#include <QtGui>
#include <QObject>

class RegisterApp : public QDialog
{
    Q_OBJECT
public:
    RegisterApp();
    virtual ~RegisterApp();
    QString accountName();
    QString userName();
    QString telephone();
    QString address();
    QString password();
    QString verifiedPassword();
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
    QDialogButtonBox* m_buttonBox;
private:
    QString m_accountName,m_userName,m_telephone,m_address,m_password,m_verifiedPassword;
};

#endif