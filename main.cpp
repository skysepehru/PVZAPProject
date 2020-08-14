#include <QApplication>
#include "view.h"
#include <ctime>
#include <cstdlib>

int main(int argc,char *argv[])
{
    QApplication a(argc,argv);
    srand(time(0));
    View *myView = new View();
    myView->show();
    return a.exec();
}

