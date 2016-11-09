#-------------------------------------------------
#
# Project created by QtCreator 2016-09-09T19:33:52
#
#-------------------------------------------------

QT       += core gui\
            xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = proto2doc
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    includes/xmlRelevant.cpp \
    local_xml_content.cpp \
    xml_dialog.cpp \
    mydebug.cpp \
    document_writer.cpp \
    entry.cpp \
    select_dialog.cpp \
    document_reader.cpp

HEADERS  += mainwindow.h \
    includes/xmlRelevant.h \
    local_xml_content.h \
    xml_dialog.h \
    entry.h \
    mydebug.h \
    document_writer.h \
    select_dialog.h \
    document_reader.h

FORMS    += mainwindow.ui \
    select_dialog.ui
