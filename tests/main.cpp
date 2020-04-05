#include <QApplication>
#include "qmaindialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainDialog mainWindow;
    mainWindow.show();

    return a.exec();
}
