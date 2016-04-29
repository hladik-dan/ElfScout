#include "elf_header.h"

ElfHeader::ElfHeader(LibElf::LibElf *libElf)
{
    this->libElf = libElf;

    this->setUp();
}

ElfHeader::~ElfHeader()
{
}

void ElfHeader::setUp()
{
    this->setAlternatingRowColors(true);
    this->setColumnCount(COLUMN_SIZE);
    this->setColumnWidth(COLUMN_1, COLUMN_WIDTH);
    this->setHeaderHidden(true);
}

void ElfHeader::addItem(QString caption, QString data, bool check)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(this);
    item->setText(COLUMN_1, caption);
    item->setText(COLUMN_2, data);

    if (!check) {
        item->setBackgroundColor(COLUMN_1, "#B33A3A");
        item->setBackgroundColor(COLUMN_2, "#B33A3A");
    }
}

void ElfHeader::reloadItem(int row, QString data, bool check)
{
    QTreeWidgetItem *item = this->topLevelItem(row);
    item->setText(COLUMN_2, data);

    if (!check) {
        item->setBackgroundColor(COLUMN_1, "#B33A3A");
        item->setBackgroundColor(COLUMN_2, "#B33A3A");
    } else {
        item->setBackground(COLUMN_1, QBrush());
        item->setBackground(COLUMN_2, QBrush());
    }
}

void ElfHeader::load()
{
    this->clear();

    this->addItem("Type",
        libElf->get_elf_header()->get_type_string().c_str(),
        libElf->get_elf_header()->check_type());
    this->addItem("Machine",
        libElf->get_elf_header()->get_machine_string().c_str(),
        libElf->get_elf_header()->check_machine());
    this->addItem("Version",
        "0x" + QString::number(libElf->get_elf_header()->get_version(), 16),
        libElf->get_elf_header()->check_version());
    this->addItem("Entry point address",
        "0x" + QString::number(libElf->get_elf_header()->get_entry(), 16),
        libElf->get_elf_header()->check_entry());
    this->addItem("Start of program headers",
        libElf->get_elf_header()->get_phoff_string().c_str(),
        libElf->get_elf_header()->check_phoff());
    this->addItem("Start of section headers",
        libElf->get_elf_header()->get_shoff_string().c_str(),
        libElf->get_elf_header()->check_shoff());
    this->addItem("Flags",
        "0x" + QString::number(libElf->get_elf_header()->get_flags(), 16),
        libElf->get_elf_header()->check_flags());
    this->addItem("Size of this header",
        libElf->get_elf_header()->get_ehsize_string().c_str(),
        libElf->get_elf_header()->check_ehsize());
    this->addItem("Size of program headers",
        libElf->get_elf_header()->get_phentsize_string().c_str(),
        libElf->get_elf_header()->check_phentsize());
    this->addItem("Number of program headers",
        libElf->get_elf_header()->get_phnum_string().c_str(),
        libElf->get_elf_header()->check_phnum());
    this->addItem("Size of section headers",
        libElf->get_elf_header()->get_shentsize_string().c_str(),
        libElf->get_elf_header()->check_shentsize());
    this->addItem("Number of section headers",
        libElf->get_elf_header()->get_shnum_string().c_str(),
        libElf->get_elf_header()->check_shnum());
    this->addItem("Section header string table index",
        libElf->get_elf_header()->get_shstrndx_string().c_str(),
                  libElf->get_elf_header()->check_shstrndx());
}

void ElfHeader::reload()
{
    this->reloadItem(Items::TYPE,
        libElf->get_elf_header()->get_type_string().c_str(),
        libElf->get_elf_header()->check_type());
    this->reloadItem(Items::MACHINE,
        libElf->get_elf_header()->get_machine_string().c_str(),
        libElf->get_elf_header()->check_machine());
    this->reloadItem(Items::VERSION,
        "0x" + QString::number(libElf->get_elf_header()->get_version(), 16),
        libElf->get_elf_header()->check_version());
    this->reloadItem(Items::ENTRY,
        "0x" + QString::number(libElf->get_elf_header()->get_entry(), 16),
        libElf->get_elf_header()->check_entry());
    this->reloadItem(Items::PHOFF,
        libElf->get_elf_header()->get_phoff_string().c_str(),
        libElf->get_elf_header()->check_phoff());
    this->reloadItem(Items::SHOFF,
        libElf->get_elf_header()->get_shoff_string().c_str(),
        libElf->get_elf_header()->check_shoff());
    this->reloadItem(Items::FLAGS,
        "0x" + QString::number(libElf->get_elf_header()->get_flags(), 16),
        libElf->get_elf_header()->check_flags());
    this->reloadItem(Items::EHSIZE,
        libElf->get_elf_header()->get_ehsize_string().c_str(),
        libElf->get_elf_header()->check_ehsize());
    this->reloadItem(Items::PHENTSIZE,
        libElf->get_elf_header()->get_phentsize_string().c_str(),
        libElf->get_elf_header()->check_phentsize());
    this->reloadItem(Items::PHNUM,
        libElf->get_elf_header()->get_phnum_string().c_str(),
        libElf->get_elf_header()->check_phnum());
    this->reloadItem(Items::SHENTSIZE,
        libElf->get_elf_header()->get_shentsize_string().c_str(),
        libElf->get_elf_header()->check_shentsize());
    this->reloadItem(Items::SHNUM,
        libElf->get_elf_header()->get_shnum_string().c_str(),
        libElf->get_elf_header()->check_shnum());
    this->reloadItem(Items::SHSTRNDX,
        libElf->get_elf_header()->get_shstrndx_string().c_str(),
        libElf->get_elf_header()->check_shstrndx());
}

void ElfHeader::editType()
{
    Elf_Half value =
        dialog.getItem(e_type, libElf->get_elf_header()->get_type());
    libElf->get_elf_header()->set_type(value);
}

void ElfHeader::editMachine()
{
    Elf_Half value =
        dialog.getItem(e_machine, libElf->get_elf_header()->get_machine());
    libElf->get_elf_header()->set_machine(value);
}

void ElfHeader::editVersion()
{
    Elf_Word value = dialog.getValue(libElf->get_elf_header()->get_version());
    libElf->get_elf_header()->set_version(value);
}

void ElfHeader::editEntry()
{
    Elf_Addr value = dialog.getValue(libElf->get_elf_header()->get_entry());
    libElf->get_elf_header()->set_entry(value);
}

void ElfHeader::editPhOff()
{
    Elf_Off value = dialog.getValue(libElf->get_elf_header()->get_phoff());
    libElf->get_elf_header()->set_phoff(value);
}

void ElfHeader::editShOff()
{
    Elf_Off value = dialog.getValue(libElf->get_elf_header()->get_shoff());
    libElf->get_elf_header()->set_shoff(value);
}

void ElfHeader::editFlags()
{
    Elf_Word value = dialog.getValue(libElf->get_elf_header()->get_flags());
    libElf->get_elf_header()->set_flags(value);
}

void ElfHeader::editEhSize()
{
    Elf_Half value = dialog.getValue(libElf->get_elf_header()->get_ehsize());
    libElf->get_elf_header()->set_ehsize(value);
}

void ElfHeader::editPhEntSize()
{
    Elf_Half value = dialog.getValue(libElf->get_elf_header()->get_phentsize());
    libElf->get_elf_header()->set_phentsize(value);
}

void ElfHeader::editPhNum()
{
    Elf_Half value = dialog.getValue(libElf->get_elf_header()->get_phnum());
    libElf->get_elf_header()->set_phnum(value);
}

void ElfHeader::editShEntSize()
{
    Elf_Half value = dialog.getValue(libElf->get_elf_header()->get_shentsize());
    libElf->get_elf_header()->set_shentsize(value);
}

void ElfHeader::editShNum()
{
    Elf_Half value = dialog.getValue(libElf->get_elf_header()->get_shnum());
    libElf->get_elf_header()->set_shnum(value);
}

void ElfHeader::editShStrNdx()
{
    Elf_Half value = dialog.getValue(libElf->get_elf_header()->get_shstrndx());
    libElf->get_elf_header()->set_shstrndx(value);
}

void ElfHeader::contextMenuEvent(QContextMenuEvent *event)
{
    // ContextMenu -> Edit
    QAction actionEdit("Edit", this);
    connect(&actionEdit, &QAction::triggered, this, &ElfHeader::edit);

    // ContextMenu
    QMenu contextMenu(this);
    contextMenu.addAction(&actionEdit);

    contextMenu.exec(mapToGlobal(event->pos()));
}

void ElfHeader::edit()
{
    switch (this->currentIndex().row()) {
        case Items::TYPE:
            editType();
            break;
        case Items::MACHINE:
            editMachine();
            break;
        case Items::VERSION:
            editVersion();
            break;
        case Items::ENTRY:
            editEntry();
            break;
        case Items::PHOFF:
            editPhOff();
            break;
        case Items::SHOFF:
            editShOff();
            break;
        case Items::FLAGS:
            editFlags();
            break;
        case Items::EHSIZE:
            editEhSize();
            break;
        case Items::PHENTSIZE:
            editPhEntSize();
            break;
        case Items::PHNUM:
            editPhNum();
            break;
        case Items::SHENTSIZE:
            editShEntSize();
            break;
        case Items::SHNUM:
            editShNum();
            break;
        case Items::SHSTRNDX:
            editShStrNdx();
            break;
        default:
            break;
    }

    this->reload();
}
