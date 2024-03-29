######################################################################
# Automatically generated by qmake (3.1) Tue May 2 21:45:21 2023
######################################################################

TEMPLATE = app
TARGET = project1
INCLUDEPATH += .

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += mainwindow.h \
           page_class/gamepage.h \
           page_class/menupage.h \
           util/gameobject.h \
           util/util.h \
           page_class/gameclass/bullet.h \
           page_class/gameclass/doodle.h \
           page_class/gameclass/item.h \
           page_class/gameclass/monster.h \
           page_class/gameclass/platform.h
SOURCES += main.cpp \
           mainwindow.cpp \
           page_class/gamepage.cpp \
           page_class/menupage.cpp \
           util/util.cpp \
           page_class/gameclass/bullet.cpp \
           page_class/gameclass/doodle.cpp \
           page_class/gameclass/item.cpp \
           page_class/gameclass/monster.cpp \
           page_class/gameclass/platform.cpp
