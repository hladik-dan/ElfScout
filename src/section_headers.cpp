#include "section_headers.h"

SectionHeaders::SectionHeaders(LibElf::LibElf *libElf)
{
    this->libElf = libElf;

    this->setUp();
}

SectionHeaders::~SectionHeaders()
{
}

void SectionHeaders::load()
{
    this->clear();

    for (Elf_Half i = 0; i < libElf->get_elf_header()->get_shnum(); ++i) {
        QTreeWidgetItem *item = this->addItem(
            libElf->get_sections()->get_header(i)->get_name_string().c_str(),
            QString());
        this->addSubitem(item, "Name",
            QString::number(libElf->get_sections()->get_header(i)->get_name()),
            libElf->get_sections()->get_header(i)->check_name());
        this->addSubitem(item, "Type",
            libElf->get_sections()->get_header(i)->get_type_string().c_str(),
            libElf->get_sections()->get_header(i)->check_type());
        this->addSubitem(item, "Address",
            "0x" + QString::number(
                libElf->get_sections()->get_header(i)->get_addr(), 16),
            libElf->get_sections()->get_header(i)->check_addr());
        this->addSubitem(item, "Offset",
            "0x" + QString::number(
                libElf->get_sections()->get_header(i)->get_offset(), 16),
            libElf->get_sections()->get_header(i)->check_offset());
        this->addSubitem(item, "Size",
            "0x" + QString::number(
                libElf->get_sections()->get_header(i)->get_size(), 16),
                libElf->get_sections()->get_header(i)->check_size());
        this->addSubitem(item, "Entry size",
            "0x" + QString::number(
                libElf->get_sections()->get_header(i)->get_entsize(), 16),
                libElf->get_sections()->get_header(i)->check_entsize());
        this->addSubitem(item, "Flags",
            libElf->get_sections()->get_header(i)->get_flags_string().c_str(),
            libElf->get_sections()->get_header(i)->check_flags());
        this->addSubitem(item, "Link",
            libElf->get_sections()->get_header(i)->get_link_string().c_str(),
            libElf->get_sections()->get_header(i)->check_link());
        this->addSubitem(item, "Info",
            libElf->get_sections()->get_header(i)->get_info_string().c_str(),
            libElf->get_sections()->get_header(i)->check_info());
        this->addSubitem(item, "Alignment",
            libElf->get_sections()->get_header(i)->get_addralign_string()
                .c_str(),
            libElf->get_sections()->get_header(i)->check_addralign());
    }
}

void SectionHeaders::reload()
{
    for (Elf_Half i = 0; i < libElf->get_elf_header()->get_shnum(); ++i) {
        QTreeWidgetItem *item = this->topLevelItem(i);

        this->reloadItem(i,
            libElf->get_sections()->get_header(i)->get_name_string().c_str());
        this->reloadSubitem(item, Subitems::NAME,
            QString::number(libElf->get_sections()->get_header(i)->get_name()),
            libElf->get_sections()->get_header(i)->check_name());
        this->reloadSubitem(item, Subitems::TYPE,
            libElf->get_sections()->get_header(i)->get_type_string().c_str(),
            libElf->get_sections()->get_header(i)->check_type());
        this->reloadSubitem(item, Subitems::ADDR,
            "0x" + QString::number(
                libElf->get_sections()->get_header(i)->get_addr(), 16),
            libElf->get_sections()->get_header(i)->check_addr());
        this->reloadSubitem(item, Subitems::OFFSET,
            "0x" + QString::number(
                libElf->get_sections()->get_header(i)->get_offset(), 16),
            libElf->get_sections()->get_header(i)->check_offset());
        this->reloadSubitem(item, Subitems::SIZE,
            "0x" + QString::number(
                libElf->get_sections()->get_header(i)->get_size(), 16),
            libElf->get_sections()->get_header(i)->check_size());
        this->reloadSubitem(item, Subitems::ENTSIZE,
            "0x" + QString::number(
                libElf->get_sections()->get_header(i)->get_entsize(), 16),
                libElf->get_sections()->get_header(i)->check_entsize());
        this->reloadSubitem(item, Subitems::FLAGS,
            libElf->get_sections()->get_header(i)->get_flags_string().c_str(),
            libElf->get_sections()->get_header(i)->check_flags());
        this->reloadSubitem(item, Subitems::LINK,
            libElf->get_sections()->get_header(i)->get_link_string().c_str(),
            libElf->get_sections()->get_header(i)->check_link());
        this->reloadSubitem(item, Subitems::INFO,
            libElf->get_sections()->get_header(i)->get_info_string().c_str(),
            libElf->get_sections()->get_header(i)->check_info());
        this->reloadSubitem(item, Subitems::ADDRALIGN,
            libElf->get_sections()->get_header(i)->get_addralign_string()
                .c_str(),
            libElf->get_sections()->get_header(i)->check_addralign());
    }
}

void SectionHeaders::setUp()
{
    this->setAlternatingRowColors(true);
    this->setColumnCount(COLUMN_SIZE);
    this->setColumnWidth(COLUMN_1, COLUMN_WIDTH);
    this->setHeaderHidden(true);
}

QTreeWidgetItem *SectionHeaders::addItem(QString caption, QString data)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(this);
    item->setText(COLUMN_1, caption);
    item->setText(COLUMN_2, data);

    return item;
}

void SectionHeaders::addSubitem(QTreeWidgetItem *parent, QString caption,
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

void SectionHeaders::reloadItem(int row, QString data)
{
    QTreeWidgetItem *item = this->topLevelItem(row);
    item->setText(COLUMN_1, data);

    item->setBackground(COLUMN_1, QBrush());
    item->setBackground(COLUMN_2, QBrush());
}

void SectionHeaders::reloadSubitem(QTreeWidgetItem *root, int row, QString data,
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

void SectionHeaders::editName()
{
    Elf_Half shndx = this->currentIndex().parent().row();
    Elf_Word value =
        dialog.getValue(libElf->get_sections()->get_header(shndx)->get_name());
    libElf->get_sections()->get_header(shndx)->set_name(value);
}

void SectionHeaders::editType()
{
    Elf_Half shndx = this->currentIndex().parent().row();
    Elf_Word value = dialog.getItem(sh_type,
        libElf->get_sections()->get_header(shndx)->get_type());
    libElf->get_sections()->get_header(shndx)->set_type(value);
}

void SectionHeaders::editAddr()
{
    Elf_Half shndx = this->currentIndex().parent().row();
    Elf_Addr value = dialog.getValue(
        libElf->get_sections()->get_header(shndx)->get_addr());
    libElf->get_sections()->get_header(shndx)->set_addr(value);
}

void SectionHeaders::editOffset()
{
    Elf_Half shndx = this->currentIndex().parent().row();
    Elf_Off value = dialog.getValue(
        libElf->get_sections()->get_header(shndx)->get_offset());
    libElf->get_sections()->get_header(shndx)->set_offset(value);
}

void SectionHeaders::editSize()
{
    Elf_Half shndx = this->currentIndex().parent().row();
    Elf_Xword value = dialog.getValue(
        libElf->get_sections()->get_header(shndx)->get_size());
    libElf->get_sections()->get_header(shndx)->set_size(value);
}

void SectionHeaders::editEntsize()
{
    Elf_Half shndx = this->currentIndex().parent().row();
    Elf_Xword value = dialog.getValue(
        libElf->get_sections()->get_header(shndx)->get_entsize());
    libElf->get_sections()->get_header(shndx)->set_entsize(value);
}

void SectionHeaders::editFlags()
{
    Elf_Half shndx = this->currentIndex().parent().row();
    Elf_Xword value = dialog.getFlags(sh_flags,
        libElf->get_sections()->get_header(shndx)->get_flags());
    libElf->get_sections()->get_header(shndx)->set_flags(value);
}

void SectionHeaders::editLink()
{
    Elf_Half shndx = this->currentIndex().parent().row();
    Elf_Word value = dialog.getValue(
        libElf->get_sections()->get_header(shndx)->get_link());
    libElf->get_sections()->get_header(shndx)->set_link(value);
}

void SectionHeaders::editInfo()
{
    Elf_Half shndx = this->currentIndex().parent().row();
    Elf_Word value = dialog.getValue(
        libElf->get_sections()->get_header(shndx)->get_info());
    libElf->get_sections()->get_header(shndx)->set_info(value);
}

void SectionHeaders::editAddralign()
{
    Elf_Half shndx = this->currentIndex().parent().row();
    Elf_Xword value = dialog.getValue(
        libElf->get_sections()->get_header(shndx)->get_addralign());
    libElf->get_sections()->get_header(shndx)->set_addralign(value);
}

void SectionHeaders::itemContextMenu(QContextMenuEvent *event)
{
    // ContextMenu
    QMenu contextMenu(this);

    contextMenu.exec(mapToGlobal(event->pos()));
}

void SectionHeaders::subitemContextMenu(QContextMenuEvent *event)
{
    // ContextMenu -> Edit
    QAction actionEdit("Edit", this);
    connect(&actionEdit, &QAction::triggered, this, &SectionHeaders::edit);

    // ContextMenu
    QMenu contextMenu(this);
    contextMenu.addAction(&actionEdit);

    contextMenu.exec(mapToGlobal(event->pos()));
}

void SectionHeaders::contextMenuEvent(QContextMenuEvent *event)
{
    if (!this->topLevelItemCount())
        return;

    if(!this->currentItem()->parent())
        itemContextMenu(event);
    else
        subitemContextMenu(event);
}

void SectionHeaders::edit()
{
    switch (this->currentIndex().row()) {
        case Subitems::NAME:
            editName();
            break;
        case Subitems::TYPE:
            editType();
            break;
        case Subitems::ADDR:
            editAddr();
            break;
        case Subitems::OFFSET:
            editOffset();
            break;
        case Subitems::SIZE:
            editSize();
            break;
        case Subitems::ENTSIZE:
            editEntsize();
            break;
        case Subitems::FLAGS:
            editFlags();
            break;
        case Subitems::LINK:
            editLink();
            break;
        case Subitems::INFO:
            editInfo();
            break;
        case Subitems::ADDRALIGN:
            editAddralign();
            break;
        default:
            break;
    }

    this->reload();
}
