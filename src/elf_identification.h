#pragma once

#include <QtWidgets>
#include "dialog.hpp"
#include "lib_elf.h"

class ElfScout;

class ElfIdentification : public QTreeWidget
{
    public:
        ElfIdentification(ElfScout *elfScout, LibElf::LibElf *libElf);
        ~ElfIdentification();

        void load();

    private:
        void setUp();
        void addItem(QString caption, QString data, bool check);

        void editMag0();
        void editMag1();
        void editMag2();
        void editMag3();
        void editClass();
        void editData();
        void editElfVersion();
        void editOsAbi();
        void editAbiVersion();

        // Events
        void contextMenuEvent(QContextMenuEvent *event);

        // Slots
        void edit();

    private:
        enum Columns { COLUMN_1, COLUMN_2 };
        enum Items { MAG0, MAG1, MAG2, MAG3, CLASS, DATA, VERSION, OSABI,
            ABIVERSION };
        const int COLUMN_SIZE = 2;
        const int COLUMN_WIDTH = 250;

        Dialog dialog;
        ElfScout *elfScout;
        LibElf::LibElf *libElf;
};
