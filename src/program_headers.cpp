#include "program_headers.h"

ProgramHeaders::ProgramHeaders(LibElf::LibElf *libElf)
{
    this->libElf = libElf;

    this->setUp();
}

ProgramHeaders::~ProgramHeaders()
{
}

void ProgramHeaders::load()
{
    this->clear();

    for (Elf_Half i = 0; i < libElf->get_elf_header()->get_phnum(); ++i) {
        QTreeWidgetItem *item = this->addItem(
            libElf->get_segments()->get_header(i)->get_type_string().c_str(),
            QString());
        this->addSubitem(item, "Type",
            libElf->get_segments()->get_header(i)->get_type_string().c_str(),
            libElf->get_segments()->get_header(i)->check_type());
        this->addSubitem(item, "Offset",
            "0x" + QString::number(
                libElf->get_segments()->get_header(i)->get_offset(), 16),
            libElf->get_segments()->get_header(i)->check_offset());
        this->addSubitem(item, "Virtual address",
            "0x" + QString::number(
                libElf->get_segments()->get_header(i)->get_vaddr(), 16),
            libElf->get_segments()->get_header(i)->check_vaddr());
        this->addSubitem(item, "Physical address",
            "0x" + QString::number(
                libElf->get_segments()->get_header(i)->get_paddr(), 16),
            libElf->get_segments()->get_header(i)->check_paddr());
        this->addSubitem(item, "File size",
            "0x" + QString::number(
                libElf->get_segments()->get_header(i)->get_filesz(), 16),
            libElf->get_segments()->get_header(i)->check_filesz());
        this->addSubitem(item, "Memory size",
            "0x" + QString::number(
                libElf->get_segments()->get_header(i)->get_memsz(), 16),
            libElf->get_segments()->get_header(i)->check_memsz());
        this->addSubitem(item, "Flags",
            libElf->get_segments()->get_header(i)->get_flags_string().c_str(),
            libElf->get_segments()->get_header(i)->check_flags());
        this->addSubitem(item, "Alignment",
            libElf->get_segments()->get_header(i)->get_align_string().c_str(),
            libElf->get_segments()->get_header(i)->check_align());
    }
}

void ProgramHeaders::reload()
{
    for (Elf_Half i = 0; i < libElf->get_elf_header()->get_phnum(); ++i) {
        QTreeWidgetItem *item = this->topLevelItem(i);

        this->reloadItem(i,
            libElf->get_segments()->get_header(i)->get_type_string().c_str());
        this->reloadSubitem(item, Subitems::TYPE,
            libElf->get_segments()->get_header(i)->get_type_string().c_str(),
            libElf->get_segments()->get_header(i)->check_type());
        this->reloadSubitem(item, Subitems::OFFSET,
            "0x" + QString::number(
                libElf->get_segments()->get_header(i)->get_offset(), 16),
            libElf->get_segments()->get_header(i)->check_offset());
        this->reloadSubitem(item, Subitems::VADDR,
            "0x" + QString::number(
                libElf->get_segments()->get_header(i)->get_vaddr(), 16),
            libElf->get_segments()->get_header(i)->check_vaddr());
        this->reloadSubitem(item, Subitems::PADDR,
            "0x" + QString::number(
                libElf->get_segments()->get_header(i)->get_paddr(), 16),
            libElf->get_segments()->get_header(i)->check_paddr());
        this->reloadSubitem(item, Subitems::FILESZ,
            "0x" + QString::number(
                libElf->get_segments()->get_header(i)->get_filesz(), 16),
            libElf->get_segments()->get_header(i)->check_filesz());
        this->reloadSubitem(item, Subitems::MEMSZ,
            "0x" + QString::number(
                libElf->get_segments()->get_header(i)->get_memsz(), 16),
            libElf->get_segments()->get_header(i)->check_memsz());
        this->reloadSubitem(item, Subitems::FLAGS,
            libElf->get_segments()->get_header(i)->get_flags_string().c_str(),
            libElf->get_segments()->get_header(i)->check_flags());
        this->reloadSubitem(item, Subitems::ALIGN,
            libElf->get_segments()->get_header(i)->get_align_string().c_str(),
            libElf->get_segments()->get_header(i)->check_align());
    }
}

void ProgramHeaders::setUp()
{
    this->setAlternatingRowColors(true);
    this->setColumnCount(COLUMN_SIZE);
    this->setColumnWidth(COLUMN_1, COLUMN_WIDTH);
    this->setHeaderHidden(true);
}

QTreeWidgetItem *ProgramHeaders::addItem(QString caption, QString data)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(this);
    item->setText(COLUMN_1, caption);
    item->setText(COLUMN_2, data);

    return item;
}

void ProgramHeaders::addSubitem(QTreeWidgetItem *parent, QString caption,
    QString data, bool check)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(parent);
    item->setText(COLUMN_1, caption);
    item->setText(COLUMN_2, data);

    if (!check) {
        item->setBackgroundColor(COLUMN_1, "#B33A3A");
        item->setBackgroundColor(COLUMN_2, "#B33A3A");

        item->parent()->setBackgroundColor(COLUMN_1, "#B33A3A");
        item->parent()->setBackgroundColor(COLUMN_2, "#B33A3A");
    }
}

void ProgramHeaders::reloadItem(int row, QString data)
{
    QTreeWidgetItem *item = this->topLevelItem(row);
    item->setText(COLUMN_1, data);

    item->setBackground(COLUMN_1, QBrush());
    item->setBackground(COLUMN_2, QBrush());
}

void ProgramHeaders::reloadSubitem(QTreeWidgetItem *root, int row, QString data,
    bool check)
{
    QTreeWidgetItem *item = root->child(row);
    item->setText(COLUMN_2, data);

    if (!check) {
        item->setBackgroundColor(COLUMN_1, "#B33A3A");
        item->setBackgroundColor(COLUMN_2, "#B33A3A");

        item->parent()->setBackgroundColor(COLUMN_1, "#B33A3A");
        item->parent()->setBackgroundColor(COLUMN_2, "#B33A3A");
    } else {
        item->setBackground(COLUMN_1, QBrush());
        item->setBackground(COLUMN_2, QBrush());
    }
}

void ProgramHeaders::editType()
{
    Elf_Half shndx = this->currentIndex().parent().row();
    Elf_Word value = dialog.getItem(p_type,
        libElf->get_segments()->get_header(shndx)->get_type());
    libElf->get_segments()->get_header(shndx)->set_type(value);
}

void ProgramHeaders::editOffset()
{
    Elf_Half shndx = this->currentIndex().parent().row();
    Elf_Off value = dialog.getValue(
        libElf->get_segments()->get_header(shndx)->get_offset());
    libElf->get_segments()->get_header(shndx)->set_offset(value);
}

void ProgramHeaders::editVaddr()
{
    Elf_Half shndx = this->currentIndex().parent().row();
    Elf_Addr value = dialog.getValue(
        libElf->get_segments()->get_header(shndx)->get_vaddr());
    libElf->get_segments()->get_header(shndx)->set_vaddr(value);
}

void ProgramHeaders::editPaddr()
{
    Elf_Half shndx = this->currentIndex().parent().row();
    Elf_Addr value = dialog.getValue(
        libElf->get_segments()->get_header(shndx)->get_paddr());
    libElf->get_segments()->get_header(shndx)->set_paddr(value);
}

void ProgramHeaders::editFilesz()
{
    Elf_Half shndx = this->currentIndex().parent().row();
    Elf_Xword value = dialog.getValue(
        libElf->get_segments()->get_header(shndx)->get_filesz());
    libElf->get_segments()->get_header(shndx)->set_filesz(value);
}

void ProgramHeaders::editMemsz()
{
    Elf_Half shndx = this->currentIndex().parent().row();
    Elf_Xword value = dialog.getValue(
        libElf->get_segments()->get_header(shndx)->get_memsz());
    libElf->get_segments()->get_header(shndx)->set_memsz(value);
}

void ProgramHeaders::editFlags()
{
    Elf_Half shndx = this->currentIndex().parent().row();
    Elf_Word value = dialog.getFlags(p_flags,
        libElf->get_segments()->get_header(shndx)->get_flags());
    libElf->get_segments()->get_header(shndx)->set_flags(value);
}

void ProgramHeaders::editAlign()
{
    Elf_Half shndx = this->currentIndex().parent().row();
    Elf_Xword value = dialog.getValue(
        libElf->get_segments()->get_header(shndx)->get_align());
    libElf->get_segments()->get_header(shndx)->set_align(value);
}

void ProgramHeaders::itemContextMenu(QContextMenuEvent *event)
{
    // ContextMenu
    QMenu contextMenu(this);

    contextMenu.exec(mapToGlobal(event->pos()));
}

void ProgramHeaders::subitemContextMenu(QContextMenuEvent *event)
{
    // ContextMenu -> Edit
    QAction actionEdit("Edit", this);
    connect(&actionEdit, &QAction::triggered, this, &ProgramHeaders::edit);

    // ContextMenu
    QMenu contextMenu(this);
    contextMenu.addAction(&actionEdit);

    contextMenu.exec(mapToGlobal(event->pos()));
}

void ProgramHeaders::contextMenuEvent(QContextMenuEvent *event)
{
    if (!this->topLevelItemCount())
        return;

    if(!this->currentItem()->parent())
        itemContextMenu(event);
    else
        subitemContextMenu(event);
}

void ProgramHeaders::edit()
{
    switch (this->currentIndex().row()) {
        case Subitems::TYPE:
            editType();
            break;
        case Subitems::OFFSET:
            editOffset();
            break;
        case Subitems::VADDR:
            editVaddr();
            break;
        case Subitems::PADDR:
            editPaddr();
            break;
        case Subitems::FILESZ:
            editFilesz();
            break;
        case Subitems::MEMSZ:
            editMemsz();
            break;
        case Subitems::FLAGS:
            editFlags();
            break;
        case Subitems::ALIGN:
            editAlign();
            break;
        default:
            break;
    }

    this->reload();
}
