#pragma once

#include <QtWidgets>
#include "lib_elf.h"

class StringTables : public QWidget
{
    public:
        StringTables(LibElf::LibElf *libElf);
        ~StringTables();

    private:
        void setUI();
        void addTab(Elf_Half shndx);

    private:
        // Constants
        const QString TITLE = "String Tables";
        const int WIDTH = 550;
        const int HEIGHT = 400;

        // Libraries
        LibElf::LibElf *libElf;

        // Widgets
        QTabWidget *tabWidget;
        QVBoxLayout *mainLayout;
};
