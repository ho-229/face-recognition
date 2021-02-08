#-------------------------------------------------
#
# Project created by QtCreator 2020-05-03T09:08:51
#
#-------------------------------------------------

# ======================================================================
# This file is part of the Face-recognition
# Copyright (C) 2020 Ho 229
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
#
# (at your option) any later version.
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; If not, see <http://www.gnu.org/licenses/>.
# ========================================================================

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = face-recognition
TEMPLATE = app

include($$_PRO_FILE_PWD_/src/src.pri)

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
   res.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/opencv/build/x64/vc14/lib/ -lopencv_world420
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/opencv/build/x64/vc14/lib/ -lopencv_world420d

INCLUDEPATH += $$PWD/opencv/build/include
DEPENDPATH += $$PWD/opencv/build/include
