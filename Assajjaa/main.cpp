#include "Ui/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setOrganizationName("AAK");
    a.setOrganizationDomain("https://github.com/kariminf");
    a.setApplicationName("Assajjaa");

    a.setQuitOnLastWindowClosed( false );

    MainWindow w;
    w.show();

    return a.exec();
}
