CONFIG -= qt

TEMPLATE = lib
DEFINES += CRYPT_LIBRARY
TARGET = MI6.Crypt

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cesar.cpp \
    engine.cpp \
    global.cpp \
    key.cpp \
    math.cpp \
    random.cpp \
    rsa.cpp \
    std.cpp

HEADERS += \
    crypt/cesar.h \
    crypt/engine.h \
    crypt/global.h \
    crypt/key.h \
    crypt/math.h \
    crypt/random.h \
    crypt/rsa.h \
    crypt/std.h

# Default rules for deployment.
#unix {
#    target.path = /usr/lib
#}
#!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release){
LIBS += -L$$PWD/../lib/win/mpir/release/ -lmpir
INCLUDEPATH += "$$PWD/../lib/win/mpir/release"
DEPENDPATH += "$$PWD/../lib/win/mpir/release"
dlls_to_move.path = "$$OUT_PWD/release"
dlls_to_move.files += "$$PWD/../lib/win/mpir/release/mpir.dll"
INSTALLS += dlls_to_move
}
else:win32:CONFIG(debug, debug|release){
LIBS += -L$$PWD/../lib/win/mpir/debug/ -lmpir
INCLUDEPATH += "$$PWD/../lib/win/mpir/debug"
DEPENDPATH += "$$PWD/../lib/win/mpir/debug"
dlls_to_move.path = "$$OUT_PWD/debug"
dlls_to_move.files += "$$PWD/../lib/win/mpir/debug/mpir.dll"
INSTALLS += dlls_to_move
}

unix:!macx:CONFIG(release, debug|release){
LIBS += -L$$PWD/../lib/unix/mpir/release/ -lmpir
INCLUDEPATH += $$PWD/../lib/unix/mpir/release
DEPENDPATH += $$PWD/../lib/unix/mpir/release
}
else:unix:!macx:CONFIG(debug, debug|release){
LIBS += -L$$PWD/../lib/unix/mpir/debug/ -lmpir
INCLUDEPATH += $$PWD/../lib/unix/mpir/debug
DEPENDPATH += $$PWD/../lib/unix/mpir/debug
}
