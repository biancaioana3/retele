#include <QHBoxLayout>
#include <QMessageBox>
#include "LoginWidget.h"
#include "MainWindow.h"

LoginWidget::LoginWidget(QWidget *parent) : QWidget(parent) {

    mainLayout = new QVBoxLayout();
    mainLayout->setAlignment(Qt::AlignCenter);

    setLayout(mainLayout);

    createCredentialsGroup();
    alignCredentialsGroup();
    customizeCredentialsGroup();

    buttongroup();
}

LoginWidget::~LoginWidget() {
    labelLayout->removeWidget(passwordInput);
    labelLayout->removeWidget(usernameInput);

    lineEditLayout->removeWidget(passwordInput);
    lineEditLayout->removeWidget(usernameInput);

    credentialsLayout->removeItem(labelLayout);
    credentialsLayout->removeItem(lineEditLayout);

    buttonLayout->removeWidget(createAccountButton);
    buttonLayout->removeWidget(loginButton);

    mainLayout->removeItem(buttonLayout);
    mainLayout->removeItem(credentialsLayout);

    delete usernameLabel;
    delete passwordLabel;
    delete usernameInput;
    delete passwordInput;
    delete loginButton;
    delete createAccountButton;
    delete labelLayout;
    delete buttonLayout;
    delete lineEditLayout;
    delete credentialsLayout;
    delete mainLayout;

}

void LoginWidget::createCredentialsGroup() {
    credentialsLayout = new QHBoxLayout();
    labelLayout = new QVBoxLayout();
    lineEditLayout = new QVBoxLayout();

    usernameLabel = new QLabel(this);
    passwordLabel = new QLabel(this);
    usernameInput = new QLineEdit(this);
    passwordInput = new QLineEdit(this);

    mainLayout->addItem(credentialsLayout);
}

void LoginWidget::alignCredentialsGroup() {
    credentialsLayout->addItem(labelLayout);
    credentialsLayout->addItem(lineEditLayout);

    labelLayout->addWidget(usernameLabel);
    labelLayout->addWidget(passwordLabel);

    lineEditLayout->addWidget(usernameInput);
    lineEditLayout->addWidget(passwordInput);
}

void LoginWidget::customizeCredentialsGroup() {
    usernameLabel->setText("Username");
    passwordLabel->setText("Password");
    usernameInput->setPlaceholderText("Username");
    passwordInput->setPlaceholderText("Password");
    passwordInput->setEchoMode(QLineEdit::Password);
}

void LoginWidget::buttongroup() {
    buttonLayout = new QHBoxLayout();

    loginButton = new QPushButton(this);
    createAccountButton = new QPushButton(this);

    loginButton->setText("Login");
    createAccountButton->setText("Create Account");

    buttonLayout->addWidget(loginButton);
    buttonLayout->addWidget(createAccountButton);

    mainLayout->addItem(buttonLayout);

    connect(loginButton, SIGNAL(clicked()), this, SLOT(login()));
    connect(createAccountButton, SIGNAL(clicked()), this, SLOT(createAccount()));

}

#include "../common/functions.h"
#include <QCryptographicHash>


void LoginWidget::createAccount() {
    auto parent = dynamic_cast<MainWindow *>(this->parent());

    if(usernameInput->text().isEmpty() || passwordInput->text().isEmpty()){
        return;
    }

    QCryptographicHash hasher(QCryptographicHash::Sha256);
    hasher.addData(passwordInput->text().toStdString());
    auto hashedPwd = QString(hasher.result().toHex()).toStdString();

    write_message(parent->s, "REQ_CREATE");
    write_message(parent->s, usernameInput->text().toStdString());
    write_message(parent->s, hashedPwd);

    string server_response;
    read_message(parent->s, server_response);

    if(server_response != "RESP_201"){
        QMessageBox::warning(this, "Create account Status", "Create account failed");
        return;
    }

    parent->username = usernameInput->text().toStdString();
    emit this->connected();

}

void LoginWidget::login() {
    auto parent = dynamic_cast<MainWindow *>(this->parent());

    if(usernameInput->text().isEmpty() || passwordInput->text().isEmpty()){
        return;
    }

    QCryptographicHash hasher(QCryptographicHash::Sha256);
    hasher.addData(passwordInput->text().toStdString());
    auto hashedPwd = QString(hasher.result().toHex()).toStdString();


    write_message(parent->s, "REQ_LOGIN");
    write_message(parent->s, usernameInput->text().toStdString());
    write_message(parent->s, hashedPwd);

    string server_response;
    read_message(parent->s, server_response);

    if(server_response != "RESP_200"){
        QMessageBox::warning(this, "Login Status", "Login failed");
        return;
    }

    parent->username = usernameInput->text().toStdString();
    emit this->connected();

}
