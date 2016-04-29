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
    actionOpen = new QAction("Open", this);
    connect(actionOpen, &QAction::triggered, this, &ElfScout::openFile);
    
    // File -> Reload
    actionReload = new QAction("Reload", this);
    connect(actionReload, &QAction::triggered, this, &ElfScout::reopenFile);

    // File -> Save
    actionSave = new QAction("Save", this);
    connect(actionSave, &QAction::triggered, this, &ElfScout::saveFile);

    // File -> Save and Reload
    actionSaveReload = new QAction("Save and Reload", this);
    connect(actionSaveReload, &QAction::triggered, this,
        &ElfScout::saveReloadFile);

    // File -> Exit
    actionExit = new QAction("Exit", this);
    connect(actionExit, &QAction::triggered, this, &ElfScout::close);

    // File
    menuFile = menuBar()->addMenu("File");
    menuFile->addAction(actionOpen);
    menuFile->addAction(actionReload);
    menuFile->addAction(actionSave);
    menuFile->addSeparator();
    menuFile->addAction(actionSaveReload);
    menuFile->addSeparator();
    menuFile->addAction(actionExit);
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

    // Add widget
    tabWidget = new QTabWidget();
    mainLayout->addWidget(tabWidget);

    // Alloc memoery for tabs
    tab1 = new ElfIdentification(this, &libElf);
    tab2 = new ElfHeader(&libElf);
    tab3 = new SectionHeaders(&libElf);
    tab4 = new ProgramHeaders(&libElf);
}

void ElfScout::showTabs()
{
    // Remove previously added tabs
    tabWidget->clear();

    // Load and display data if they are ok
    if (libElf.get_elf_identification()->is_ok()) {
        tab1->load();
        tabWidget->addTab(tab1, "ELF Identification");
    }

    // Load and display data if they are ok
    if (libElf.get_elf_header()->is_ok()) {
        tab2->load();
        tabWidget->addTab(tab2, "ELF Header");
    }

    // Load and display data if they are ok
    if (libElf.get_sections()->is_ok()) {
        tab3->load();
        tabWidget->addTab(tab3, "Section Headers");
    }

    // Load and display data if they are ok
    if (libElf.get_segments()->is_ok()) {
        tab4->load();
        tabWidget->addTab(tab4, "Program Headers");
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

