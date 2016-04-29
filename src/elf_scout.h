#pragma once

#include <QtWidgets>
#include "elf_identification.h"
#include "elf_header.h"
#include "section_headers.h"
#include "program_headers.h"
#include "string_tables.h"
#include "lib_elf.h"

class ElfScout : public QMainWindow
{
    friend class ElfIdentification;

    public:
        ElfScout();
        ~ElfScout();

    private:
        void setMenu();
        void setUi();
        void showTabs();

        // Slots
        void openFile();
        void reopenFile();
        void saveFile();
        void saveReloadFile();
        void showStringTableWindow();

    private:
        // Constants
        const QString TITLE = "ELF Scout";
        const int WIDTH = 550;
        const int HEIGHT = 400;

        // Libraries
        LibElf::LibElf libElf;

        // Tabs
        ElfIdentification *tab1;
        ElfHeader *tab2;
        SectionHeaders *tab3;
        ProgramHeaders *tab4;

        // Sections
        StringTables *string_tables;

        // Widgets
        QAction *actionOpen;
        QAction *actionReload;
        QAction *actionSave;
        QAction *actionSaveReload;
        QAction *actionExit;
        QAction *actionStringTable;
        QGridLayout *mainLayout;
        QMenu *menuFile;
        QMenu *menuShow;
        QTabWidget *tabWidget;
        QWidget *centralWidget;
};
