TEMPLATE = app
TARGET = ELF_Scout
QT += core widgets
QMAKE_CXXFLAGS += -std=c++11
INCLUDEPATH += ../LibElf/src

Debug:DESTDIR = bin/debug
Debug:OBJECTS_DIR = bin/debug/.obj
Debug:CONFIG += debug
Debug:LIBS += -L"../LibElf/bin/debug" -lLibElf

Release:DESTDIR = bin/release
Release:OBJECTS_DIR = bin/release/.obj
Release:CONFIG += release
Release:LIBS += -L"../LibElf/bin/release" -lLibElf

HEADERS += \
    src/dialog.hpp \
    src/elf_header.h \
    src/elf_identification.h \
    src/elf_scout.h \
    src/program_headers.h \
    src/section_headers.h

SOURCES += \
    src/elf_header.cpp \
    src/elf_identification.cpp \
    src/elf_scout.cpp \
    src/main.cpp \
    src/program_headers.cpp \
    src/section_headers.cpp
