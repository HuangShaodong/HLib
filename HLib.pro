TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp \
    Object.cpp \
    Exception.cpp

HEADERS += \
    Object.h \
    Exception.h \
    Pointer.h \
    UniquePointer.h \
    SharedPointer.h
