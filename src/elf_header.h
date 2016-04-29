#pragma once

#include <QtWidgets>
#include "dialog.hpp"
#include "lib_elf.h"

class ElfHeader : public QTreeWidget
{
    public:
        ElfHeader(LibElf::LibElf *libElf);
        ~ElfHeader();

        void load();
        void reload();

    private:
        void setUp();
        void addItem(QString caption, QString data, bool check);
        void reloadItem(int row, QString data, bool check);

        void editType();
        void editMachine();
        void editVersion();
        void editEntry();
        void editPhOff();
        void editShOff();
        void editFlags();
        void editEhSize();
        void editPhEntSize();
        void editPhNum();
        void editShEntSize();
        void editShNum();
        void editShStrNdx();

        // Events
        void contextMenuEvent(QContextMenuEvent *event);

        // Slots
        void edit();

    private:
        enum Columns { COLUMN_1, COLUMN_2 };
        enum Items { TYPE, MACHINE, VERSION, ENTRY, PHOFF, SHOFF, FLAGS, EHSIZE,
            PHENTSIZE, PHNUM, SHENTSIZE, SHNUM, SHSTRNDX };
        const int COLUMN_SIZE = 2;
        const int COLUMN_WIDTH = 250;

        Dialog dialog;
        LibElf::LibElf *libElf;
};
