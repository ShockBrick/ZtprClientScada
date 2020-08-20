#include <QCoreApplication>

#include <QApplication>

#include <clientservice.h>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ClientService a;
    return app.exec();
}

