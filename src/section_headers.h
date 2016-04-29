#pragma once

#include <QtWidgets>
#include "dialog.hpp"
#include "lib_elf.h"

class SectionHeaders : public QTreeWidget
{
    public:
        SectionHeaders(LibElf::LibElf *libElf);
        ~SectionHeaders();

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

        void editName();
        void editType();
        void editAddr();
        void editOffset();
        void editSize();
        void editEntsize();
        void editFlags();
        void editLink();
        void editInfo();
        void editAddralign();

        void itemContextMenu(QContextMenuEvent *event);
        void subitemContextMenu(QContextMenuEvent *event);

        // Events
        void contextMenuEvent(QContextMenuEvent *event);

        // Slots
        void edit();

    private:
        enum Columns { COLUMN_1, COLUMN_2 };
        enum Subitems { NAME, TYPE, ADDR, OFFSET, SIZE, ENTSIZE, FLAGS, LINK,
            INFO, ADDRALIGN };
        const int COLUMN_SIZE = 2;
        const int COLUMN_WIDTH = 275;

        Dialog dialog;
        LibElf::LibElf *libElf;
};
