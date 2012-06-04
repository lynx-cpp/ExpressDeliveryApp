#include <QtGui/QApplication>
#include "ExpressDeliveryApp.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    ExpressDeliveryApp foo;
    foo.show();
    return app.exec();
}
