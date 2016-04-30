#include "elf_scout.h"

ElfScout::ElfScout()
{
    this->setMenu();
    this->setUi();
}

ElfScout::~ElfScout()
{
}

void ElfScout::setMenu()
{
    // File -> Open
    QAction *actionOpen = new QAction("Open", this);
    connect(actionOpen, &QAction::triggered, this, &ElfScout::openFile);
    
    // File -> Reload
    QAction *actionReload = new QAction("Reload", this);
    connect(actionReload, &QAction::triggered, this, &ElfScout::reopenFile);

    // File -> Save
    QAction *actionSave = new QAction("Save", this);
    connect(actionSave, &QAction::triggered, this, &ElfScout::saveFile);

    // File -> Save and Reload
    QAction *actionSaveReload = new QAction("Save and Reload", this);
    connect(actionSaveReload, &QAction::triggered, this,
        &ElfScout::saveReloadFile);

    // File -> Exit
    QAction *actionExit = new QAction("Exit", this);
    connect(actionExit, &QAction::triggered, this, &ElfScout::close);

    // File
    QMenu *menuFile = menuBar()->addMenu("File");
    menuFile->addAction(actionOpen);
    menuFile->addAction(actionReload);
    menuFile->addAction(actionSave);
    menuFile->addSeparator();
    menuFile->addAction(actionSaveReload);
    menuFile->addSeparator();
    menuFile->addAction(actionExit);


    // Show -> String Tables
    QAction *actionStringTable = new QAction("String Tables", this);
    connect(actionStringTable, &QAction::triggered, this,
        &ElfScout::showStringTableWindow);

    // Show
    QMenu *menuShow = menuBar()->addMenu("Show");
    menuShow->addAction(actionStringTable);
}

void ElfScout::setUi()
{
    // Set up window
    this->resize(WIDTH, HEIGHT);
    this->setWindowTitle(TITLE);

    // Set central widget
    centralWidget = new QWidget();
    this->setCentralWidget(centralWidget);

    // Set main layout
    mainLayout = new QGridLayout();
    centralWidget->setLayout(mainLayout);

    // Add tab widget
    tabWidget = new QTabWidget();
    mainLayout->addWidget(tabWidget);

    // Alloc memoery for tabs
    tabElfIdentification = new ElfIdentification(this, &libElf);
    tabElfHeader = new ElfHeader(&libElf);
    tabSectionHeaders = new SectionHeaders(&libElf);
    tabProgramHeaders = new ProgramHeaders(&libElf);
}

void ElfScout::showTabs()
{
    // Remove previously added tabs
    tabWidget->clear();

    // Load and display data if they are ok
    if (libElf.get_elf_identification()->is_ok()) {
        tabElfIdentification->load();
        tabWidget->addTab(tabElfIdentification, "ELF Identification");
    }

    // Load and display data if they are ok
    if (libElf.get_elf_header()->is_ok()) {
        tabElfHeader->load();
        tabWidget->addTab(tabElfHeader, "ELF Header");
    }

    // Load and display data if they are ok
    if (libElf.get_sections()->is_ok()) {
        tabSectionHeaders->load();
        tabWidget->addTab(tabSectionHeaders, "Section Headers");
    }

    // Load and display data if they are ok
    if (libElf.get_segments()->is_ok()) {
        tabProgramHeaders->load();
        tabWidget->addTab(tabProgramHeaders, "Program Headers");
    }
}

void ElfScout::openFile()
{
    // Open dialog for user to open file
    QString filename = QFileDialog::getOpenFileName(this);

    // Check if any file has been opened
    if (filename.isNull()) {
        qDebug() << "No file has been opened";
        return;
    }

    // Try to load data from file
    if (!libElf.load(filename.toStdString()))
        qDebug() << "Library could not load file correctly";

    // Display data
    this->showTabs();
}

void ElfScout::reopenFile()
{
    // Try to reload data from file
    if (!libElf.reload())
        qDebug() << "Library could not load file correctly";

    // Display data
    this->showTabs();
}

void ElfScout::saveFile()
{
    // Try to save data
    if (!libElf.save())
        qDebug() << "Library could not save file correctly";
}

void ElfScout::saveReloadFile()
{
    this->saveFile();
    this->reopenFile();
}

void ElfScout::showStringTableWindow()
{
    string_tables = new StringTables(&libElf);
    string_tables->show();
}

