QT       += core gui
QT       += sql
QT += core gui widgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ArpTable.cpp \
    ArpTableWorker.cpp \
    Port.cpp \
    PortWorker.cpp \
    RouteTable.cpp \
    RouteTableWorker.cpp \
    Router.cpp \
    RouterWorker.cpp \
    arptablewindow.cpp \
    main.cpp \
    mainwindow.cpp \
    registerdevicewindow.cpp \
    routingtablewindow.cpp

HEADERS += \
    ArpTable.h \
    ArpTableEntry.h \
    ArpTableWorker.h \
    Port.h \
    PortWorker.h \
    RouteTable.h \
    RouteTableEntry.h \
    RouteTableWorker.h \
    Router.h \
    RouterWorker.h \
    Traffic.h \
    arptablewindow.h \
    mainwindow.h \
    registerdevicewindow.h \
    routingtablewindow.h

FORMS += \
    arptablewindow.ui \
    mainwindow.ui \
    registerdevicewindow.ui \
    routingtablewindow.ui

# Net-SNMP 헤더 경로
INCLUDEPATH += /usr/include/net-snmp

# Net-SNMP 라이브러리 링크
LIBS += -lnetsnmp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
