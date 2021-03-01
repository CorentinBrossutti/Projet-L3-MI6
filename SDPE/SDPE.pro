TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    SDPE.cpp



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

INCLUDEPATH += $$PWD/../Crypt
DEPENDPATH += $$PWD/../Crypt
