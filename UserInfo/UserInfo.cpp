#include "UserInfo.h"
#include <QVBoxLayout>

UserInfo::UserInfo(QWidget* parent, Qt::WindowFlags f): QDialog(parent, f)
{
    setLayout(new QVBoxLayout);
    
    m_accountNameLabel = new QLabel("account name : ",this);
    m_accountNameInput = new QLineEdit(this);
    
    m_passwordLabel = new QLabel("password : ",this);
    m_passwordInput = new QLineEdit(this);
    m_passwordInput->setEchoMode(QLineEdit::Password);
    
    m_verifiedPasswordLabel = new QLabel("repeat password : ",this);
    m_verifiedPasswordInput = new QLineEdit(this);
    m_verifiedPasswordInput->setEchoMode(QLineEdit::Password);
    
    m_isAdminCheckBox = new QCheckBox("Admin account?",this);
    
    m_userNameLabel = new QLabel("your name : ",this);
    m_userNameInput = new QLineEdit(this);
    
    m_addressLabel = new QLabel("address : ",this);
    m_addressInput = new QLineEdit(this);
    
    m_telephoneLabel = new QLabel("telephone : ",this);
    m_telephoneInput = new QLineEdit(this);
    
    m_buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal,
        this
    );
    connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(m_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    
    layout()->addWidget(m_accountNameLabel);
    layout()->addWidget(m_accountNameInput);
    layout()->addWidget(m_passwordLabel);
    layout()->addWidget(m_passwordInput);
    layout()->addWidget(m_verifiedPasswordLabel);
    layout()->addWidget(m_verifiedPasswordInput);
    layout()->addWidget(m_isAdminCheckBox);
    layout()->addWidget(m_userNameLabel);
    layout()->addWidget(m_userNameInput);
    layout()->addWidget(m_addressLabel);
    layout()->addWidget(m_addressInput);
    layout()->addWidget(m_telephoneLabel);
    layout()->addWidget(m_telephoneInput);
    layout()->addWidget(m_buttonBox);
    
}

void UserInfo::accept()
{
    m_accountName = m_accountNameInput->text();
    m_password = m_passwordInput->text();
    m_verifiedPassword = m_verifiedPasswordInput->text();
    m_address = m_addressInput->text();
    m_telephone = m_telephoneInput->text();
    m_userName = m_userNameInput->text();
    m_isAdmin = m_isAdminCheckBox->isChecked();
    QDialog::accept();
}

QString UserInfo::accountName() const
{
    return m_accountName;
}

QString UserInfo::address() const
{
    return m_address;
}

QString UserInfo::password() const
{
    return m_password;
}

QString UserInfo::telephone() const
{
    return m_telephone;
}

QString UserInfo::userName() const
{
    return m_userName;
}

QString UserInfo::verifiedPassword() const
{
    return m_verifiedPassword;
}

bool UserInfo::isAdmin() const
{
    return m_isAdmin;
}

void UserInfo::setAccountName(const QString& value)
{
    m_accountName = value;
    m_accountNameInput->setText(value);
}

void UserInfo::setAddress(const QString& value)
{
    m_address = value;
    m_addressInput->setText(value);
}

void UserInfo::setIsAdmin(bool value)
{
    m_isAdmin = value;
    if (value)
        m_isAdminCheckBox->setCheckState(Qt::Checked);
    else
        m_isAdminCheckBox->setCheckState(Qt::Unchecked);
}

void UserInfo::setTelephone(const QString& value)
{
    m_telephone = value;
    m_telephoneInput->setText(value);
}

void UserInfo::setUserName(const QString& value)
{
    m_userName = value;
    m_userNameInput->setText(value);
}

UserInfo::~UserInfo()
{
    
}
