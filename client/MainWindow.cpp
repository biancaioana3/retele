#include <QVBoxLayout>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
#include "MainWindow.h"
#include "LoginWidget.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent){
    connectServer();

    resize(800, 600);

    mainLayout = new QVBoxLayout();
    mainLayout->setAlignment(Qt::AlignCenter);

    setLayout(mainLayout);

    loginWidget = new LoginWidget(this );

    mainLayout->addWidget(loginWidget);


    connect(this->loginWidget, & LoginWidget::connected, [this] {
        this->mainLayout->removeWidget(loginWidget);
        this->treeWidget = new TreeWidget(this);
        this->mainLayout->addWidget(treeWidget);
    });

}

MainWindow::~MainWindow() {
    loginWidget = nullptr;

}

void MainWindow::connectServer() {
    s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server;
    server.sin_port = htons(63500);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;

    if(-1 == ::connect(s, (struct sockaddr *) &server, sizeof(server))){
        std::cout << "[ERROR] Connection error";
    }
}

