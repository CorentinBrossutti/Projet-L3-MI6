/****************************************************************************
** Meta object code from reading C++ file 'fenetreConnexion.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../App_Client/fenetreConnexion.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fenetreConnexion.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_fenetreConnexion_t {
    QByteArrayData data[23];
    char stringdata0[302];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_fenetreConnexion_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_fenetreConnexion_t qt_meta_stringdata_fenetreConnexion = {
    {
QT_MOC_LITERAL(0, 0, 16), // "fenetreConnexion"
QT_MOC_LITERAL(1, 17, 8), // "connecte"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 12), // "erreurSocket"
QT_MOC_LITERAL(4, 40, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(5, 69, 6), // "erreur"
QT_MOC_LITERAL(6, 76, 25), // "afficherFenetrePrincipale"
QT_MOC_LITERAL(7, 102, 21), // "afficherMenuConnexion"
QT_MOC_LITERAL(8, 124, 10), // "deconnecte"
QT_MOC_LITERAL(9, 135, 15), // "afficherMessage"
QT_MOC_LITERAL(10, 151, 10), // "QTextEdit*"
QT_MOC_LITERAL(11, 162, 9), // "afficheur"
QT_MOC_LITERAL(12, 172, 7), // "message"
QT_MOC_LITERAL(13, 180, 18), // "tentativeConnexion"
QT_MOC_LITERAL(14, 199, 16), // "sauvegardeDonnee"
QT_MOC_LITERAL(15, 216, 3), // "nom"
QT_MOC_LITERAL(16, 220, 2), // "ip"
QT_MOC_LITERAL(17, 223, 4), // "port"
QT_MOC_LITERAL(18, 228, 12), // "chargePseudo"
QT_MOC_LITERAL(19, 241, 8), // "chargeIp"
QT_MOC_LITERAL(20, 250, 10), // "chargePort"
QT_MOC_LITERAL(21, 261, 13), // "afficherDonne"
QT_MOC_LITERAL(22, 275, 26) // "on_boutonConnexion_clicked"

    },
    "fenetreConnexion\0connecte\0\0erreurSocket\0"
    "QAbstractSocket::SocketError\0erreur\0"
    "afficherFenetrePrincipale\0"
    "afficherMenuConnexion\0deconnecte\0"
    "afficherMessage\0QTextEdit*\0afficheur\0"
    "message\0tentativeConnexion\0sauvegardeDonnee\0"
    "nom\0ip\0port\0chargePseudo\0chargeIp\0"
    "chargePort\0afficherDonne\0"
    "on_boutonConnexion_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_fenetreConnexion[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    1,   80,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x08 /* Private */,
       9,    2,   86,    2, 0x08 /* Private */,
      13,    0,   91,    2, 0x08 /* Private */,
      14,    3,   92,    2, 0x08 /* Private */,
      18,    0,   99,    2, 0x08 /* Private */,
      19,    0,  100,    2, 0x08 /* Private */,
      20,    0,  101,    2, 0x08 /* Private */,
      21,    0,  102,    2, 0x08 /* Private */,
      22,    0,  103,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10, QMetaType::QString,   11,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   15,   16,   17,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void fenetreConnexion::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<fenetreConnexion *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connecte(); break;
        case 1: _t->erreurSocket((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 2: _t->afficherFenetrePrincipale(); break;
        case 3: _t->afficherMenuConnexion(); break;
        case 4: _t->deconnecte(); break;
        case 5: _t->afficherMessage((*reinterpret_cast< QTextEdit*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->tentativeConnexion(); break;
        case 7: _t->sauvegardeDonnee((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 8: { QString _r = _t->chargePseudo();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 9: { QString _r = _t->chargeIp();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 10: { QString _r = _t->chargePort();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 11: _t->afficherDonne(); break;
        case 12: _t->on_boutonConnexion_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTextEdit* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject fenetreConnexion::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_fenetreConnexion.data,
    qt_meta_data_fenetreConnexion,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *fenetreConnexion::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *fenetreConnexion::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_fenetreConnexion.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int fenetreConnexion::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
