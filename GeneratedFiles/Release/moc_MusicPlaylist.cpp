/****************************************************************************
** Meta object code from reading C++ file 'MusicPlaylist.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MusicPlaylist.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MusicPlaylist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MusicPlaylist_t {
    QByteArrayData data[15];
    char stringdata0[175];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MusicPlaylist_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MusicPlaylist_t qt_meta_stringdata_MusicPlaylist = {
    {
QT_MOC_LITERAL(0, 0, 13), // "MusicPlaylist"
QT_MOC_LITERAL(1, 14, 19), // "currentIndexChanged"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 8), // "position"
QT_MOC_LITERAL(4, 44, 23), // "currentMusicNameChanged"
QT_MOC_LITERAL(5, 68, 9), // "musicName"
QT_MOC_LITERAL(6, 78, 19), // "currentMusicChanged"
QT_MOC_LITERAL(7, 98, 12), // "FMOD::Sound*"
QT_MOC_LITERAL(8, 111, 5), // "music"
QT_MOC_LITERAL(9, 117, 15), // "playlistChanged"
QT_MOC_LITERAL(10, 133, 4), // "next"
QT_MOC_LITERAL(11, 138, 8), // "previous"
QT_MOC_LITERAL(12, 147, 15), // "setCurrentIndex"
QT_MOC_LITERAL(13, 163, 3), // "pos"
QT_MOC_LITERAL(14, 167, 7) // "shuffle"

    },
    "MusicPlaylist\0currentIndexChanged\0\0"
    "position\0currentMusicNameChanged\0"
    "musicName\0currentMusicChanged\0"
    "FMOD::Sound*\0music\0playlistChanged\0"
    "next\0previous\0setCurrentIndex\0pos\0"
    "shuffle"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MusicPlaylist[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    1,   57,    2, 0x06 /* Public */,
       6,    1,   60,    2, 0x06 /* Public */,
       9,    0,   63,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   64,    2, 0x0a /* Public */,
      11,    0,   65,    2, 0x0a /* Public */,
      12,    1,   66,    2, 0x0a /* Public */,
      14,    0,   69,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,

       0        // eod
};

void MusicPlaylist::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MusicPlaylist *_t = static_cast<MusicPlaylist *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->currentMusicNameChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->currentMusicChanged((*reinterpret_cast< FMOD::Sound*(*)>(_a[1]))); break;
        case 3: _t->playlistChanged(); break;
        case 4: _t->next(); break;
        case 5: _t->previous(); break;
        case 6: _t->setCurrentIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->shuffle(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MusicPlaylist::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicPlaylist::currentIndexChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MusicPlaylist::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicPlaylist::currentMusicNameChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MusicPlaylist::*_t)(FMOD::Sound * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicPlaylist::currentMusicChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MusicPlaylist::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicPlaylist::playlistChanged)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject MusicPlaylist::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MusicPlaylist.data,
      qt_meta_data_MusicPlaylist,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MusicPlaylist::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MusicPlaylist::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MusicPlaylist.stringdata0))
        return static_cast<void*>(const_cast< MusicPlaylist*>(this));
    return QObject::qt_metacast(_clname);
}

int MusicPlaylist::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void MusicPlaylist::currentIndexChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MusicPlaylist::currentMusicNameChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MusicPlaylist::currentMusicChanged(FMOD::Sound * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MusicPlaylist::playlistChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
