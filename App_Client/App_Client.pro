TEMPLATE = app
TARGET = MI6.ChatClient
QT += core gui
QT += widgets network
QT += widgets
QT += xml
DEPENDPATH += .
INCLUDEPATH += .

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


#Input
SOURCES += \
    fenetreConnexion.cpp \
    main.cpp \
    clienttcp.cpp \
    xmldoc.cpp

HEADERS += \
    clienttcp.h \
    xmldoc.h \
    fenetreConnexion.h

FORMS += \
    clienttcp.ui \
    fenetreConnexion.ui

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release){
LIBS += -L$$PWD/../build/win/crypt/release/ -lMI6.Crypt -L$$PWD/../lib/win/mpir/release/ -lmpir
INCLUDEPATH += $$PWD/../lib/win/mpir/release
DEPENDPATH += $$PWD/../lib/win/mpir/release
dlls_to_move.path = "$$OUT_PWD/release"
dlls_to_move.files += "$$PWD/../build/win/crypt/release/mpir.dll" "$$PWD/../build/win/crypt/release/MI6.Crypt.dll"
INSTALLS += dlls_to_move
}
else:win32:CONFIG(debug, debug|release){
LIBS += -L$$PWD/../build/win/crypt/debug/ -lMI6.Crypt -L$$PWD/../lib/win/mpir/debug/ -lmpir
INCLUDEPATH += $$PWD/../lib/win/mpir/debug
DEPENDPATH += $$PWD/../lib/win/mpir/debug
dlls_to_move.path = "$$OUT_PWD/debug"
dlls_to_move.files += "$$PWD/../build/win/crypt/debug/mpir.dll" "$$PWD/../build/win/crypt/debug/MI6.Crypt.dll"
INSTALLS += dlls_to_move
}

unix:!macx:CONFIG(release, debug|release){
LIBS += -L$$PWD/../lib/unix/mpir/release/ -lmpir -L$$PWD/../build/unix/crypt/release/ -lMI6.Crypt
INCLUDEPATH += $$PWD/../lib/unix/mpir/release
DEPENDPATH += $$PWD/../lib/unix/mpir/release
}
else:unix:!macx:CONFIG(debug, debug|release){
LIBS += -L$$PWD/../lib/unix/mpir/debug/ -lmpir -L$$PWD/../build/unix/crypt/debug/ -lMI6.Crypt
INCLUDEPATH += $$PWD/../lib/unix/mpir/debug
DEPENDPATH += $$PWD/../lib/unix/mpir/debug
}

INCLUDEPATH += $$PWD/../Crypt
DEPENDPATH += $$PWD/../Crypt
