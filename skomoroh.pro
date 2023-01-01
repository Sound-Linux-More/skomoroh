# -------------------------------------------------
# Project created by QtCreator 2010-06-15T19:22:58
# -------------------------------------------------


TARGET = skomoroh
TEMPLATE = app
VERSION = 1.0
DEFINES += APP_VERSION="$$VERSION"
INCLUDEPATH += src

greaterThan(QT_MAJOR_VERSION, 4)
{
    QT += widgets
}

SOURCES += \
    src/menestrel.cpp \
    src/config.cpp \
    src/znaktemp.cpp \
    src/markf.cpp \
    src/openf.cpp \
    src/savelex.cpp \
    src/main.cpp
HEADERS += \
    src/menestrel.h \
    src/config.h \
    src/znaktemp.h \
    src/markf.h \
    src/openf.h \
    src/savelex.h
FORMS += \
    src/menestrel.ui \
    src/config.ui \
    src/znaktemp.ui \
    src/markf.ui \
    src/openf.ui \
    src/savelex.ui

# OTHER_FILES +=

RESOURCES += \
    skomoroh.qrc

# DESTDIR = build/target/
OBJECTS_DIR = build/obj/
UI_DIR  = build/ui/
MOC_DIR = build/moc/
RCC_DIR = build/rcc/
# LIBS += -L/usr/lib -lFestival -lestools -leststring -lestbase -lncurses

unix {
    PREFIX = /usr
    BINDIR = $$PREFIX/bin
    target.path = $$BINDIR
    INSTALLS += target
}

win32 {
    PREFIX = /Skomoroh
    INSTALLS += target
}

OTHER_FILES += \
    testtemp.txt
