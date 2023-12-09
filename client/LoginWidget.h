#ifndef MYFTP_BI_LOGINWIDGET_H
#define MYFTP_BI_LOGINWIDGET_H


#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

class LoginWidget : public QWidget{

    Q_OBJECT

public:

    LoginWidget(QWidget * parent = nullptr);
    ~LoginWidget() override;

private:

    QLabel * usernameLabel, *passwordLabel;

    QLayout * lineEditLayout;
    QLayout * credentialsLayout;

    QLineEdit * usernameInput,* passwordInput;

    QPushButton * loginButton, * createAccountButton;

    QLayout * mainLayout,*labelLayout,* buttonLayout;


    void createCredentialsGroup();
    void alignCredentialsGroup();
    void customizeCredentialsGroup();
    void buttongroup();

public slots:
    void login();
    void createAccount();

signals:
//    void closed();
    void connected();

};


#endif //MYFTP_BI_LOGINWIDGET_H
