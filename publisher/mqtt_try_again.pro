QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    callbacks.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    callbacks.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/'../../../../Program Files/Mosquitto/devel/' -lmosquitto
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/'../../../../Program Files/Mosquitto/devel/' -lmosquittod
else:unix: LIBS += -L$$PWD/'../../../../Program Files/Mosquitto/devel/' -lmosquitto

INCLUDEPATH += $$PWD/'../../../../Program Files/Mosquitto/devel'
DEPENDPATH += $$PWD/'../../../../Program Files/Mosquitto/devel'

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/'../../../../Program Files/Mosquitto/devel/' -lmosquittopp
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/'../../../../Program Files/Mosquitto/devel/' -lmosquittoppd
else:unix: LIBS += -L$$PWD/'../../../../Program Files/Mosquitto/devel/' -lmosquittopp

INCLUDEPATH += $$PWD/'../../../../Program Files/Mosquitto/devel'
DEPENDPATH += $$PWD/'../../../../Program Files/Mosquitto/devel'

unix|win32: LIBS += -L$$PWD/'../../../../Program Files/Mosquitto/devel/' -lmosquitto

INCLUDEPATH += $$PWD/'../../../../Program Files/Mosquitto/devel'
DEPENDPATH += $$PWD/'../../../../Program Files/Mosquitto/devel'
LIBS += "-LC:\Program Files\Mosquitto" \
        -lmosquitto \
        -llibcrypto-1_1-x64 \
        -llibssl-1_1-x64 \
        -lmosquittopp
