#include "elf_identification.h"
#include "elf_scout.h"

ElfIdentification::ElfIdentification(ElfScout *elfScout, LibElf::LibElf *libElf)
{
    this->elfScout = elfScout;
    this->libElf = libElf;

    this->setUp();
}

ElfIdentification::~ElfIdentification()
{
}

void ElfIdentification::load()
{
    this->clear();

    this->addItem("Magic number 0",
        QString::number(libElf->get_elf_identification()->get_mag_0(), 16),
        libElf->get_elf_identification()->check_mag_0());
    this->addItem("Magic number 1",
        libElf->get_elf_identification()->get_mag_1_string().c_str(),
        libElf->get_elf_identification()->check_mag_1());
    this->addItem("Magic number 2",
        libElf->get_elf_identification()->get_mag_2_string().c_str(),
        libElf->get_elf_identification()->check_mag_2());
    this->addItem("Magic number 3",
        libElf->get_elf_identification()->get_mag_3_string().c_str(),
        libElf->get_elf_identification()->check_mag_3());
    this->addItem("Class",
        libElf->get_elf_identification()->get_class_string().c_str(),
        libElf->get_elf_identification()->check_class());
    this->addItem("Data",
        libElf->get_elf_identification()->get_data_string().c_str(),
        libElf->get_elf_identification()->check_data());
    this->addItem("ELF Version",
        libElf->get_elf_identification()->get_version_string().c_str(),
        libElf->get_elf_identification()->check_version());
    this->addItem("OS/ABI",
        libElf->get_elf_identification()->get_osabi_string().c_str(),
        libElf->get_elf_identification()->check_osabi());
    this->addItem("ABI Version",
        libElf->get_elf_identification()->get_abiversion_string().c_str(),
        libElf->get_elf_identification()->check_abiversion());
}

void ElfIdentification::setUp()
{
    this->setAlternatingRowColors(true);
    this->setColumnCount(COLUMN_SIZE);
    this->setColumnWidth(COLUMN_1, COLUMN_WIDTH);
    this->setHeaderHidden(true);
}

void ElfIdentification::addItem(QString caption, QString data, bool check)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(this);
    item->setText(COLUMN_1, caption);
    item->setText(COLUMN_2, data);

    if (!check) {
        item->setBackgroundColor(COLUMN_1, "#B33A3A");
        item->setBackgroundColor(COLUMN_2, "#B33A3A");
    }
}

void ElfIdentification::editMag0()
{
    unsigned char value =
        dialog.getValue(libElf->get_elf_identification()->get_mag_0());
    libElf->get_elf_identification()->set_mag_0(value);
}

void ElfIdentification::editMag1()
{
    unsigned char value =
        dialog.getValue(libElf->get_elf_identification()->get_mag_1());
    libElf->get_elf_identification()->set_mag_1(value);
}

void ElfIdentification::editMag2()
{
    unsigned char value =
        dialog.getValue(libElf->get_elf_identification()->get_mag_2());
    libElf->get_elf_identification()->set_mag_2(value);
}

void ElfIdentification::editMag3()
{
    unsigned char value =
        dialog.getValue(libElf->get_elf_identification()->get_mag_3());
    libElf->get_elf_identification()->set_mag_3(value);
}

void ElfIdentification::editClass()
{
    unsigned char value =
        dialog.getItem(ei_class, libElf->get_elf_identification()->get_class());
    libElf->get_elf_identification()->set_class(value);
}

void ElfIdentification::editData()
{
    unsigned char value =
        dialog.getItem(ei_data, libElf->get_elf_identification()->get_data());
    libElf->get_elf_identification()->set_data(value);
}

void ElfIdentification::editElfVersion()
{
    unsigned char value =
        dialog.getItem(ei_version,
            libElf->get_elf_identification()->get_version());
    libElf->get_elf_identification()->set_version(value);
}

void ElfIdentification::editOsAbi()
{
    unsigned char value =
        dialog.getItem(ei_osabi, libElf->get_elf_identification()->get_osabi());
    libElf->get_elf_identification()->set_osabi(value);
}

void ElfIdentification::editAbiVersion()
{
    unsigned char value =
        dialog.getValue(libElf->get_elf_identification()->get_abiversion());
    libElf->get_elf_identification()->set_abiversion(value);
}

void ElfIdentification::contextMenuEvent(QContextMenuEvent *event)
{
    // ContextMenu -> Edit
    QAction actionEdit("Edit", this);
    connect(&actionEdit, &QAction::triggered, this, &ElfIdentification::edit);

    // ContextMenu
    QMenu contextMenu(this);
    contextMenu.addAction(&actionEdit);

    contextMenu.exec(mapToGlobal(event->pos()));
}

void ElfIdentification::edit()
{
    switch (this->currentIndex().row()) {
        case Items::MAG0:
            editMag0();
            break;
        case Items::MAG1:
            editMag1();
            break;
        case Items::MAG2:
            editMag2();
            break;
        case Items::MAG3:
            editMag3();
            break;
        case Items::CLASS:
            editClass();
            break;
        case Items::DATA:
            editData();
            break;
        case Items::VERSION:
            editElfVersion();
            break;
        case Items::OSABI:
            editOsAbi();
            break;
        case Items::ABIVERSION:
            editAbiVersion();
            break;
        default:
            break;
    }

    // Try to save data after edit
    if (!libElf->save_elf_identification())
        qDebug() << "Library could not save file correctly";

    // Reload file and view
    elfScout->reopenFile();
}
