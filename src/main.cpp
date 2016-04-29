#include <QApplication>
#include "elf_scout.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    ElfScout elfScout;
    elfScout.show();

    return app.exec();
}
