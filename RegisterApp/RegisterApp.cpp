#include "RegisterApp.h"
#include <QVBoxLayout>

RegisterApp::RegisterApp()
{
    setLayout(new QVBoxLayout);
    
    m_accountNameLabel = new QLabel("account name : ",this);
    m_accountNameInput = new QLineEdit(this);
    
    m_userNameLabel = new QLabel("your name : ",this);
    m_userNameInput = new QLineEdit(this);
    
    m_addressLabel = new QLabel("address : ",this);
    m_addressInput = new QLineEdit(this);
    
    m_telephoneLabel = new QLabel("telephone : ",this);
    m_telephoneInput = new QLineEdit(this);
    
    m_passwordLabel = new QLabel("password : ",this);
    m_passwordInput = new QLineEdit(this);
    
    m_verifiedPasswordLabel = new QLabel("repeat password : ",this);
    m_verifiedPasswordInput = new QLineEdit(this);
    
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
    layout()->addWidget(m_userNameLabel);
    layout()->addWidget(m_userNameInput);
    layout()->addWidget(m_addressLabel);
    layout()->addWidget(m_addressInput);
    layout()->addWidget(m_telephoneLabel);
    layout()->addWidget(m_telephoneInput);
    layout()->addWidget(m_verifiedPasswordLabel);
    layout()->addWidget(m_verifiedPasswordInput);
    layout()->addWidget(m_buttonBox);
    
}

void RegisterApp::accept()
{
    m_accountName = m_accountNameInput->text();
    m_password = m_passwordInput->text();
    m_verifiedPassword = m_verifiedPasswordInput->text();
    m_address = m_addressInput->text();
    m_telephone = m_telephoneInput->text();
    m_userName = m_userNameInput->text();
    QDialog::accept();
}

QString RegisterApp::accountName()
{
    return m_accountName;
}

QString RegisterApp::address()
{
    return m_address;
}

QString RegisterApp::password()
{
    return m_password;
}

QString RegisterApp::telephone()
{
    return m_telephone;
}

QString RegisterApp::userName()
{
    return m_userName;
}

QString RegisterApp::verifiedPassword()
{
    return m_verifiedPassword;
}

RegisterApp::~RegisterApp()
{
    
}
