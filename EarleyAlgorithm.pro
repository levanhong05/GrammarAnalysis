#-------------------------------------------------
#
# Project created by QtCreator 2017-05-12T19:16:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

unix:TARGET = ../bin/EarleyAlgorithm
win32:TARGET = ../dist/bin/EarleyAlgorithm
TEMPLATE = app

SOURCES +=  main.cpp\
            mainwindow.cpp \
            grammarrule.cpp \
            earleyalgorithm.cpp \
            stack.cpp \
            dictionary.cpp \
            table.cpp

HEADERS  += mainwindow.h \
            grammarrule.h \
            earleyalgorithm.h \
            stack.h \
            dictionary.h \
            table.h

FORMS    += mainwindow.ui

win32:RC_FILE = EarleyAlgorithm.rc

win32 {
    SOURCEPATH = $$PWD/data
    DESTPATH = $$OUT_PWD/dist/bin
    copydata.commands = "$(COPY_DIR) $$replace(SOURCEPATH,/,\\) $$replace(DESTPATH,/,\\)"
}

unix {
    copydata.commands = "$(COPY_DIR) $$PWD/data $$OUT_PWD/../bin/"
}

first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)

QMAKE_EXTRA_TARGETS += first copydata

RESOURCES += \
    earley_res.qrc
