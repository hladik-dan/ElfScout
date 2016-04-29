#pragma once

#include <typeinfo>
#include <QtWidgets>
#include "lib_data.h"

class Dialog : public QDialog
{
    public:
        Dialog()
        {
            this->setWindowTitle("Edit");
        }

        ~Dialog()
        {
        }

        template<typename T>
        T getItem(std::map<T, const char *> map, T value)
        {
            // Make sure dialog is empty
            this->clear();

            // Get items from std::map to QMap for better manipulation
            QMap<T, QString> *items = new QMap<T, QString>();
            for (auto it = map.begin(); it != map.end(); ++it)
                items->insert(it->first, it->second);

            // Set up combo box and pre-select value;
            QComboBox *comboBox = new QComboBox();
            comboBox->addItems(items->values());
            comboBox->setCurrentIndex(comboBox->findText(items->value(value)));

            // Set up dialog buttons
            QDialogButtonBox *dialogButtonBox =
                new QDialogButtonBox(
                    QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
            connect(dialogButtonBox, &QDialogButtonBox::accepted, this,
                &QDialog::accept);
            connect(dialogButtonBox, &QDialogButtonBox::rejected, this,
                &QDialog::reject);

            // Set up layout
            QVBoxLayout *mainLayout = new QVBoxLayout();
            mainLayout->addWidget(comboBox);
            mainLayout->addWidget(dialogButtonBox);

            // Set up dialog
            this->setLayout(mainLayout);

            // Run dialog and return default value if rejected
            if (!this->exec())
                return value;

            // Return selected value if accepted
            return items->key(comboBox->currentText());
        }

        template<typename T>
        T getValue(T value)
        {
            // Make sure dialog is empty
            this->clear();

            // Set up line edit
            QLineEdit *lineEdit = new QLineEdit();
            lineEdit->setAlignment(Qt::AlignCenter);
            lineEdit->setText(QString::number(value));
            lineEdit->selectAll();

            // Set up dialog buttons
            QDialogButtonBox *dialogButtonBox =
                new QDialogButtonBox(
                    QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
            connect(dialogButtonBox, &QDialogButtonBox::accepted, this,
                &QDialog::accept);
            connect(dialogButtonBox, &QDialogButtonBox::rejected, this,
                &QDialog::reject);

            // Set up layout
            QVBoxLayout *mainLayout = new QVBoxLayout();
            mainLayout->addWidget(lineEdit);
            mainLayout->addWidget(dialogButtonBox);

            // Set up dialog
            this->setLayout(mainLayout);

            // Run dialog and return default value if rejected
            if (!this->exec())
                return value;

            // Return entered value if accepted
            return static_cast<T>(lineEdit->text().toULongLong());
        }

        template<typename T>
        T getFlags(std::map<T, const char *> map, T value)
        {
            // Make sure dialog is empty
            this->clear();

            // Get items from std::map to QMap for better manipulation
            QMap<T, QString> *items = new QMap<T, QString>();
            for (auto it = map.begin(); it != map.end(); ++it)
                items->insert(it->first, it->second);

            // Prepare layout for checkboxes
            QVBoxLayout *vBoxLayout = new QVBoxLayout();

            // Add checkbox item for each value
            QMapIterator<T, QString> i(*items);
            while (i.hasNext()) {
                i.next();

                QCheckBox *checkBox = new QCheckBox(i.value(), this);

                // Pre-select value
                if ((value & i.key()) == i.key())
                    checkBox->setChecked(true);

                vBoxLayout->addWidget(checkBox);
            }

            // Set up dialog buttons
            QDialogButtonBox *dialogButtonBox =
                new QDialogButtonBox(
                    QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
            connect(dialogButtonBox, &QDialogButtonBox::accepted, this,
                &QDialog::accept);
            connect(dialogButtonBox, &QDialogButtonBox::rejected, this,
                &QDialog::reject);

            // Set up layout
            QVBoxLayout *mainLayout = new QVBoxLayout();
            mainLayout->addLayout(vBoxLayout);
            mainLayout->addWidget(dialogButtonBox);

            // Set up dialog
            this->setLayout(mainLayout);

            // Run dialog and return default value if rejected
            if (!this->exec())
                return value;

            // Get new value from checkboxes and return it
            T newValue = 0;
            while (QLayoutItem *item = vBoxLayout->takeAt(0)) {
                QCheckBox *checkBox =
                    reinterpret_cast<QCheckBox *>(item->widget());
                if (checkBox->isChecked())
                    newValue += items->key(checkBox->text());
            }

            return newValue;
        }

    private:
        void clear()
        {
            while (QWidget *widget =
                findChild<QWidget *>(QString(), Qt::FindDirectChildrenOnly)) {
                delete widget;
            }
            delete this->layout();
        }
};
