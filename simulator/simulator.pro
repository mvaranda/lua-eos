QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += LUA_EMBEDDED

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../lua/src/lapi.c \
    ../lua/src/lauxlib.c \
    ../lua/src/lbaselib.c \
    ../lua/src/lcode.c \
    ../lua/src/lcorolib.c \
    ../lua/src/lctype.c \
    ../lua/src/ldblib.c \
    ../lua/src/ldebug.c \
    ../lua/src/ldo.c \
    ../lua/src/ldump.c \
    ../lua/src/lfunc.c \
    ../lua/src/lgc.c \
    ../lua/src/linit.c \
    ../lua/src/liolib.c \
    ../lua/src/llex.c \
    ../lua/src/lmathlib.c \
    ../lua/src/lmem.c \
    ../lua/src/loadlib.c \
    ../lua/src/lobject.c \
    ../lua/src/lopcodes.c \
    ../lua/src/loslib.c \
    ../lua/src/lparser.c \
    ../lua/src/lstate.c \
    ../lua/src/lstring.c \
    ../lua/src/lstrlib.c \
    ../lua/src/ltable.c \
    ../lua/src/ltablib.c \
    ../lua/src/ltm.c \
    ../lua/src/lua.c \
    ../lua/src/lundump.c \
    ../lua/src/lutf8lib.c \
    ../lua/src/lvm.c \
    ../lua/src/lzio.c \
    ../utils/malloc.c \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../lua/src/lapi.h \
    ../lua/src/lauxlib.h \
    ../lua/src/lcode.h \
    ../lua/src/lctype.h \
    ../lua/src/ldebug.h \
    ../lua/src/ldo.h \
    ../lua/src/lfunc.h \
    ../lua/src/lgc.h \
    ../lua/src/ljumptab.h \
    ../lua/src/llex.h \
    ../lua/src/llimits.h \
    ../lua/src/lmem.h \
    ../lua/src/lobject.h \
    ../lua/src/lopcodes.h \
    ../lua/src/lopnames.h \
    ../lua/src/lparser.h \
    ../lua/src/lprefix.h \
    ../lua/src/lstate.h \
    ../lua/src/lstring.h \
    ../lua/src/ltable.h \
    ../lua/src/ltm.h \
    ../lua/src/lua.h \
    ../lua/src/lua.hpp \
    ../lua/src/luaconf.h \
    ../lua/src/lualib.h \
    ../lua/src/lundump.h \
    ../lua/src/lvm.h \
    ../lua/src/lzio.h \
    ../utils/malloc.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
