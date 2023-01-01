#include <QApplication>
#include "menestrel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Menestrel w;
    w.show();
    return a.exec();
}
