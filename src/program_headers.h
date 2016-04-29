#pragma once

#include <QtWidgets>
#include "dialog.hpp"
#include "lib_elf.h"

class ProgramHeaders : public QTreeWidget
{
    public:
        ProgramHeaders(LibElf::LibElf *libElf);
        ~ProgramHeaders();

        void load();
        void reload();

    private:
        void setUp();
        QTreeWidgetItem *addItem(QString caption, QString data);
        void addSubitem(QTreeWidgetItem *parent, QString caption, QString data,
            bool check);
        void reloadItem(int row, QString data);
        void reloadSubitem(QTreeWidgetItem *root, int row, QString data,
            bool check);

        void editType();
        void editOffset();
        void editVaddr();
        void editPaddr();
        void editFilesz();
        void editMemsz();
        void editFlags();
        void editAlign();

        void itemContextMenu(QContextMenuEvent *event);
        void subitemContextMenu(QContextMenuEvent *event);

        // Events
        void contextMenuEvent(QContextMenuEvent *event);

        // Slots
        void edit();

    private:
        enum Columns { COLUMN_1, COLUMN_2 };
        enum Subitems { TYPE, OFFSET, VADDR, PADDR, FILESZ, MEMSZ, FLAGS,
            ALIGN };
        const int COLUMN_SIZE = 2;
        const int COLUMN_WIDTH = 275;

        Dialog dialog;
        LibElf::LibElf *libElf;
};
