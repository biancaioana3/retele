#include <QApplication>
#include "../common/functions.h"
#include "MainWindow.h"


int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    MainWindow * pMainWindow = new MainWindow;
    pMainWindow->resize(800, 600);
    pMainWindow->show();

    return QApplication::exec();
}
