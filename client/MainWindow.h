#ifndef MYFTP_BI_MAINWINDOW_H
#define MYFTP_BI_MAINWINDOW_H


#include <QWidget>
#include "LoginWidget.h"
#include "TreeWidget.h"

class MainWindow : public QWidget{

    Q_OBJECT

public:
    int s;
    std::string username;

    MainWindow(QWidget * parent = nullptr);
    ~MainWindow() override;

    void connectServer();

private:

    QLayout * mainLayout;
    LoginWidget * loginWidget;
    TreeWidget * treeWidget;

};


#endif //MYFTP_BI_MAINWINDOW_H
