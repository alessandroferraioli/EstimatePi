#include "estimatepi.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EstimatePi w(200);
    w.Estimate(5000);
    w.show();

    return a.exec();
}
