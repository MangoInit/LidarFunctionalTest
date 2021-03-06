#-------------------------------------------------
#
# Project created by QtCreator 2018-12-17T14:21:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LidarFunctionalTest
TEMPLATE = app

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


SOURCES += \
    src/controlform.cpp \
    src/dialoglidar.cpp \
    src/flashgo.cpp \
    src/flashgodriver.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/math_tools.cpp \
    src/uart.cpp \

FORMS += \
    ui/controlform.ui \
    ui/dialoglidar.ui \
    ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QT += serialport

LIBS += -lpthread

DEFINES +=BOOST_USE_LIB

LIBS += /home/mango/boost_1_69_0/stage/lib/libboost_thread.a

LIBS += /home/mango/boost_1_69_0/stage/lib/libboost_system.a

HEADERS += \
    include/controlform.h \
    include/dialoglidar.h \
    include/event.h \
    include/fastmath.h \
    include/flashgo.h \
    include/flashgodriver.h \
    include/locker.h \
    include/mainwindow.h \
    include/math_tools.h \
    include/uart.h





