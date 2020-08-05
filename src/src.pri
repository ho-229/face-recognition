INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += \
    $$PWD/main.cpp \
    $$PWD/mainwidget.cpp \

HEADERS += \
    $$PWD/mainwidget.h \

FORMS += \
    $$PWD/mainwidget.ui \


include($$PWD/customWidget/customWidget.pri)
include($$PWD/facerecognition/facerecognition.pri)
