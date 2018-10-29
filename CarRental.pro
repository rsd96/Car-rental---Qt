#-------------------------------------------------
#
# Project created by QtCreator 2017-12-08T13:37:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = car-rental
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    driverdialog.cpp \
    driver.cpp \
    vehicle.cpp \
    vehicles.cpp \
    drivers.cpp \
    driverwindow.cpp \
    vehiclewindow.cpp \
    vehicledialog.cpp \
    assignmentwindow.cpp \
    assignment.cpp \
    assignmentdialog.cpp \
    assignable.cpp

HEADERS  += mainwindow.h \
    driverdialog.h \
    driver.h \
    vehicle.h \
    vehicles.h \
    drivers.h \
    driverwindow.h \
    vehiclewindow.h \
    vehicledialog.h \
    assignmentwindow.h \
    assignment.h \
    assignmentdialog.h \
    assignable.h

FORMS    += mainwindow.ui \
    driverdialog.ui \
    driverwindow.ui \
    vehiclewindow.ui \
    vehicledialog.ui \
    assignmentwindow.ui \
    assignmentdialog.ui

RESOURCES += \
    qdarkstyle/style.qrc \
    res.qrc
