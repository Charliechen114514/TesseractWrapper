CONFIG -= qt

TEMPLATE = lib
DEFINES += TESSEREACTWRAPPER_LIBRARY

# DEFINES += DEBUG_LIB

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    tesseractwrappercbridging.cpp \
    tesseractwrapperimpl.cpp \
    tessereactwrapper.cpp

HEADERS += \
    TessereactWrapper_global.h \
    tesseractwrapperimpl.h \
    tessereactwrapper.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

# Mingw Build
#win32:CONFIG(release, debug|release): LIBS += $$PWD/mingw/lib/*.dll -L$$PWD/mingw/lib -ltesseract54 -lws2_32
#else:win32:CONFIG(debug, debug|release): LIBS += $$PWD/mingw/lib/*.dll -L$$PWD/mingw/lib -ltesseract54 -lws2_32
#else:unix: LIBS += -L$$PWD/mingw/lib/ -ltesseract54
#INCLUDEPATH += $$PWD/include/
#DEPENDPATH += $$PWD/include/

## MSVC
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/msvc/lib/ -ltesseract54 -lleptonica-1.84.1
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/msvc/lib/ -ltesseract54d -lleptonica-1.84.1d
else:unix: LIBS += -L$$PWD/msvc/lib/ -ltesseract54 -lleptonica-1.84.1
INCLUDEPATH += $$PWD/msvc/include
DEPENDPATH += $$PWD/msvc/include
