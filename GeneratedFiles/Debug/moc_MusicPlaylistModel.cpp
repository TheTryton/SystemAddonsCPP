/****************************************************************************
** Meta object code from reading C++ file 'MusicPlaylistModel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MusicPlaylistModel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MusicPlaylistModel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MusicPlaylistModel_t {
    QByteArrayData data[36];
    char stringdata0[429];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MusicPlaylistModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MusicPlaylistModel_t qt_meta_stringdata_MusicPlaylistModel = {
    {
QT_MOC_LITERAL(0, 0, 18), // "MusicPlaylistModel"
QT_MOC_LITERAL(1, 19, 19), // "currentIndexChanged"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 8), // "position"
QT_MOC_LITERAL(4, 49, 23), // "currentMusicNameChanged"
QT_MOC_LITERAL(5, 73, 9), // "musicName"
QT_MOC_LITERAL(6, 83, 19), // "currentMusicChanged"
QT_MOC_LITERAL(7, 103, 18), // "const FMOD::Sound*"
QT_MOC_LITERAL(8, 122, 5), // "music"
QT_MOC_LITERAL(9, 128, 31), // "currentMusicTimePositionChanged"
QT_MOC_LITERAL(10, 160, 17), // "failedToLoadMusic"
QT_MOC_LITERAL(11, 178, 3), // "row"
QT_MOC_LITERAL(12, 182, 12), // "mutedChanged"
QT_MOC_LITERAL(13, 195, 5), // "muted"
QT_MOC_LITERAL(14, 201, 13), // "volumeChanged"
QT_MOC_LITERAL(15, 215, 6), // "volume"
QT_MOC_LITERAL(16, 222, 12), // "stateChanged"
QT_MOC_LITERAL(17, 235, 10), // "MusicState"
QT_MOC_LITERAL(18, 246, 5), // "state"
QT_MOC_LITERAL(19, 252, 15), // "durationChanged"
QT_MOC_LITERAL(20, 268, 8), // "duration"
QT_MOC_LITERAL(21, 277, 10), // "musicAdded"
QT_MOC_LITERAL(22, 288, 12), // "musicRemoved"
QT_MOC_LITERAL(23, 301, 16), // "musicDataChanged"
QT_MOC_LITERAL(24, 318, 5), // "pause"
QT_MOC_LITERAL(25, 324, 4), // "play"
QT_MOC_LITERAL(26, 329, 5), // "index"
QT_MOC_LITERAL(27, 335, 8), // "setMuted"
QT_MOC_LITERAL(28, 344, 27), // "setCurrentMusicTimePosition"
QT_MOC_LITERAL(29, 372, 9), // "setVolume"
QT_MOC_LITERAL(30, 382, 4), // "stop"
QT_MOC_LITERAL(31, 387, 4), // "next"
QT_MOC_LITERAL(32, 392, 8), // "previous"
QT_MOC_LITERAL(33, 401, 15), // "setCurrentIndex"
QT_MOC_LITERAL(34, 417, 3), // "pos"
QT_MOC_LITERAL(35, 421, 7) // "shuffle"

    },
    "MusicPlaylistModel\0currentIndexChanged\0"
    "\0position\0currentMusicNameChanged\0"
    "musicName\0currentMusicChanged\0"
    "const FMOD::Sound*\0music\0"
    "currentMusicTimePositionChanged\0"
    "failedToLoadMusic\0row\0mutedChanged\0"
    "muted\0volumeChanged\0volume\0stateChanged\0"
    "MusicState\0state\0durationChanged\0"
    "duration\0musicAdded\0musicRemoved\0"
    "musicDataChanged\0pause\0play\0index\0"
    "setMuted\0setCurrentMusicTimePosition\0"
    "setVolume\0stop\0next\0previous\0"
    "setCurrentIndex\0pos\0shuffle"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MusicPlaylistModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  134,    2, 0x06 /* Public */,
       4,    1,  137,    2, 0x06 /* Public */,
       6,    1,  140,    2, 0x06 /* Public */,
       9,    1,  143,    2, 0x06 /* Public */,
      10,    1,  146,    2, 0x06 /* Public */,
      12,    1,  149,    2, 0x06 /* Public */,
      14,    1,  152,    2, 0x06 /* Public */,
      16,    1,  155,    2, 0x06 /* Public */,
      19,    1,  158,    2, 0x06 /* Public */,
      21,    1,  161,    2, 0x06 /* Public */,
      22,    1,  164,    2, 0x06 /* Public */,
      23,    0,  167,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      24,    1,  168,    2, 0x0a /* Public */,
      25,    0,  171,    2, 0x0a /* Public */,
      25,    1,  172,    2, 0x0a /* Public */,
      25,    1,  175,    2, 0x0a /* Public */,
      27,    1,  178,    2, 0x0a /* Public */,
      28,    1,  181,    2, 0x0a /* Public */,
      29,    1,  184,    2, 0x0a /* Public */,
      30,    0,  187,    2, 0x0a /* Public */,
      31,    0,  188,    2, 0x0a /* Public */,
      32,    0,  189,    2, 0x0a /* Public */,
      33,    1,  190,    2, 0x0a /* Public */,
      35,    0,  193,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, QMetaType::UInt,   20,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,   24,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   26,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::Float,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   34,
    QMetaType::Void,

       0        // eod
};

void MusicPlaylistModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MusicPlaylistModel *_t = static_cast<MusicPlaylistModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->currentMusicNameChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->currentMusicChanged((*reinterpret_cast< const FMOD::Sound*(*)>(_a[1]))); break;
        case 3: _t->currentMusicTimePositionChanged((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 4: _t->failedToLoadMusic((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->mutedChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->volumeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->stateChanged((*reinterpret_cast< MusicState(*)>(_a[1]))); break;
        case 8: _t->durationChanged((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 9: _t->musicAdded((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->musicRemoved((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->musicDataChanged(); break;
        case 12: _t->pause((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->play(); break;
        case 14: _t->play((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->play((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 16: _t->setMuted((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: _t->setCurrentMusicTimePosition((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 18: _t->setVolume((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 19: _t->stop(); break;
        case 20: _t->next(); break;
        case 21: _t->previous(); break;
        case 22: _t->setCurrentIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->shuffle(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MusicPlaylistModel::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicPlaylistModel::currentIndexChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MusicPlaylistModel::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicPlaylistModel::currentMusicNameChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MusicPlaylistModel::*_t)(const FMOD::Sound * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicPlaylistModel::currentMusicChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MusicPlaylistModel::*_t)(uint );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicPlaylistModel::currentMusicTimePositionChanged)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (MusicPlaylistModel::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicPlaylistModel::failedToLoadMusic)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (MusicPlaylistModel::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicPlaylistModel::mutedChanged)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (MusicPlaylistModel::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicPlaylistModel::volumeChanged)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (MusicPlaylistModel::*_t)(MusicState );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicPlaylistModel::stateChanged)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (MusicPlaylistModel::*_t)(uint );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicPlaylistModel::durationChanged)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (MusicPlaylistModel::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicPlaylistModel::musicAdded)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (MusicPlaylistModel::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicPlaylistModel::musicRemoved)) {
                *result = 10;
                return;
            }
        }
        {
            typedef void (MusicPlaylistModel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicPlaylistModel::musicDataChanged)) {
                *result = 11;
                return;
            }
        }
    }
}

const QMetaObject MusicPlaylistModel::staticMetaObject = {
    { &QAbstractItemModel::staticMetaObject, qt_meta_stringdata_MusicPlaylistModel.data,
      qt_meta_data_MusicPlaylistModel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MusicPlaylistModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MusicPlaylistModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MusicPlaylistModel.stringdata0))
        return static_cast<void*>(const_cast< MusicPlaylistModel*>(this));
    return QAbstractItemModel::qt_metacast(_clname);
}

int MusicPlaylistModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractItemModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 24)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 24;
    }
    return _id;
}

// SIGNAL 0
void MusicPlaylistModel::currentIndexChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MusicPlaylistModel::currentMusicNameChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MusicPlaylistModel::currentMusicChanged(const FMOD::Sound * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MusicPlaylistModel::currentMusicTimePositionChanged(uint _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MusicPlaylistModel::failedToLoadMusic(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MusicPlaylistModel::mutedChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MusicPlaylistModel::volumeChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void MusicPlaylistModel::stateChanged(MusicState _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void MusicPlaylistModel::durationChanged(uint _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void MusicPlaylistModel::musicAdded(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void MusicPlaylistModel::musicRemoved(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void MusicPlaylistModel::musicDataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
