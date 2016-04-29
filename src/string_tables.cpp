#include "string_tables.h"

StringTables::StringTables(LibElf::LibElf *libElf)
{
    this->libElf = libElf;

    this->setUI();
}

StringTables::~StringTables()
{
}

void StringTables::setUI()
{
    // Set up window
    this->resize(WIDTH, HEIGHT);
    this->setWindowTitle(TITLE);

    // Set main layout
    mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);

    // Add tab widget
    tabWidget = new QTabWidget();
    mainLayout->addWidget(tabWidget);

    // Find string tables and add them as tabs
    for (Elf_Half i = 0; i < libElf->get_elf_header()->get_shnum(); ++i) {
        // Get section header's type
        Elf_Word type = libElf->get_sections()->get_header(i)->get_type();

        // If section is not string table then skip it
        if (type != SHT_STRTAB)
            continue;

        // Set up tab and add it to tab widget
        this->addTab(i);
    }
}

void StringTables::addTab(Elf_Half shndx)
{
    // Set up tab
    QTreeWidget *tab = new QTreeWidget();
    tab->setHeaderHidden(true);

    LibElf::SectionHeader *sectionHeader =
        libElf->get_sections()->get_header(shndx);
    LibElf::Section *section = libElf->get_sections()->get_section(shndx);

    for (Elf_Xword i = 0; i < sectionHeader->get_size(); ++i) {
        // Get text from section's data
        QString text = section->get_pointer(i);

        // Add item and set text
        QTreeWidgetItem *item = new QTreeWidgetItem(tab);
        item->setText(0, text);

        // Move index by length of text
        i += text.length();
    }

    // Add tab
    tabWidget->addTab(tab, sectionHeader->get_name_string().c_str());
}
