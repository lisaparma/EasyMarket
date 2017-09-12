QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProgettissimoP2
TEMPLATE = app

CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    MODEL/account.cpp \
    MODEL/admin.cpp \
    MODEL/articolo.cpp \
    MODEL/inventario.cpp \
    MODEL/listaaccount.cpp \
    MODEL/prodotto.cpp \
    MODEL/userbase.cpp \
    MODEL/userpremium.cpp \
    VIEW/adminview.cpp \
    VIEW/aggiungiart.cpp \
    VIEW/login.cpp \
    VIEW/signup.cpp \
    VIEW/userbaseview.cpp \
    VIEW/userpremiumview.cpp \
    main.cpp \
    MODEL/alimentare.cpp \
    MODEL/bevanda.cpp \
    MODEL/oggettistica.cpp

HEADERS  += \
    MODEL/account.h \
    MODEL/admin.h \
    MODEL/articolo.h \
    MODEL/inventario.h \
    MODEL/listaaccount.h \
    MODEL/prodotto.h \
    MODEL/userBase.h \
    MODEL/userPremium.h \
    VIEW/adminview.h \
    VIEW/aggiungiart.h \
    VIEW/login.h \
    VIEW/signup.h \
    VIEW/userbaseview.h \
    VIEW/userpremiumview.h \
    MODEL/alimentare.h \
    MODEL/bevanda.h \
    MODEL/oggettistica.h

FORMS    += \
    VIEW/UI/adminview.ui \
    VIEW/UI/aggiungiart.ui \
    VIEW/UI/login.ui \
    VIEW/UI/signup.ui \
    VIEW/UI/userbaseview.ui \
    VIEW/UI/userpremiumview.ui

RESOURCES += \
    VIEW/image.qrc



