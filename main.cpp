#include <QApplication>
#include "applicationView.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ApplicationView view;
    view.show();
    view.switchToWindowByName("lobby");

    return a.exec();
}
