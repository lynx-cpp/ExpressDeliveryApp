#include <QtGui/QApplication>
#include "ExpressDeviveryApp.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    ExpressDeviveryApp foo;
    foo.show();
    return app.exec();
}
