QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../lib/thc.cpp \
    ../../src/Chessboard_handler.cpp \
    ../../src/DEC_module.cpp \
    ../../src/Database_parser.cpp \
    ../../src/Engine_handler.cpp \
    ../../src/Process_handler.cpp \
    analinfowindow.cpp \
    analysislogwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    new_anal_window.cpp

HEADERS += \
    ../../lib/thc.h \
    ../../src/Chessboard_handler.h \
    ../../src/DEC_module.h \
    ../../src/DataBase_parser.h \
    ../../src/Engine_handler.h \
    ../../src/Process_handler.h \
    analinfowindow.h \
    analysislogwindow.h \
    mainwindow.h \
    new_anal_window.h

FORMS += \
    analinfowindow.ui \
    analysislogwindow.ui \
    mainwindow.ui \
    new_anal_window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
