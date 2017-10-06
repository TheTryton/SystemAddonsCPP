/****************************************************************************
** Meta object code from reading C++ file 'MusicPlayer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MusicPlayer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MusicPlayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MusicPlayer_t {
    QByteArrayData data[31];
    char stringdata0[324];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MusicPlayer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MusicPlayer_t qt_meta_stringdata_MusicPlayer = {
    {
QT_MOC_LITERAL(0, 0, 11), // "MusicPlayer"
QT_MOC_LITERAL(1, 12, 15), // "positionChanged"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 8), // "position"
QT_MOC_LITERAL(4, 38, 12), // "mutedChanged"
QT_MOC_LITERAL(5, 51, 5), // "muted"
QT_MOC_LITERAL(6, 57, 13), // "volumeChanged"
QT_MOC_LITERAL(7, 71, 6), // "volume"
QT_MOC_LITERAL(8, 78, 12), // "stateChanged"
QT_MOC_LITERAL(9, 91, 10), // "MusicState"
QT_MOC_LITERAL(10, 102, 5), // "state"
QT_MOC_LITERAL(11, 108, 15), // "durationChanged"
QT_MOC_LITERAL(12, 124, 8), // "duration"
QT_MOC_LITERAL(13, 133, 19), // "currentMusicChanged"
QT_MOC_LITERAL(14, 153, 12), // "currentMusic"
QT_MOC_LITERAL(15, 166, 5), // "index"
QT_MOC_LITERAL(16, 172, 13), // "loadingFailed"
QT_MOC_LITERAL(17, 186, 5), // "music"
QT_MOC_LITERAL(18, 192, 10), // "musicAdded"
QT_MOC_LITERAL(19, 203, 12), // "musicRemoved"
QT_MOC_LITERAL(20, 216, 6), // "hiding"
QT_MOC_LITERAL(21, 223, 7), // "showing"
QT_MOC_LITERAL(22, 231, 12), // "hidePlaylist"
QT_MOC_LITERAL(23, 244, 12), // "showPlaylist"
QT_MOC_LITERAL(24, 257, 5), // "pause"
QT_MOC_LITERAL(25, 263, 4), // "play"
QT_MOC_LITERAL(26, 268, 8), // "setMuted"
QT_MOC_LITERAL(27, 277, 11), // "setPosition"
QT_MOC_LITERAL(28, 289, 9), // "setVolume"
QT_MOC_LITERAL(29, 299, 4), // "stop"
QT_MOC_LITERAL(30, 304, 19) // "playlistShowPercent"

    },
    "MusicPlayer\0positionChanged\0\0position\0"
    "mutedChanged\0muted\0volumeChanged\0"
    "volume\0stateChanged\0MusicState\0state\0"
    "durationChanged\0duration\0currentMusicChanged\0"
    "currentMusic\0index\0loadingFailed\0music\0"
    "musicAdded\0musicRemoved\0hiding\0showing\0"
    "hidePlaylist\0showPlaylist\0pause\0play\0"
    "setMuted\0setPosition\0setVolume\0stop\0"
    "playlistShowPercent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MusicPlayer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       1,  174, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      14,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  124,    2, 0x06 /* Public */,
       4,    1,  127,    2, 0x06 /* Public */,
       6,    1,  130,    2, 0x06 /* Public */,
       8,    1,  133,    2, 0x06 /* Public */,
      11,    1,  136,    2, 0x06 /* Public */,
      13,    1,  139,    2, 0x06 /* Public */,
      13,    1,  142,    2, 0x06 /* Public */,
      16,    1,  145,    2, 0x06 /* Public */,
      18,    0,  148,    2, 0x06 /* Public */,
      19,    0,  149,    2, 0x06 /* Public */,
      20,    0,  150,    2, 0x06 /* Public */,
      21,    0,  151,    2, 0x06 /* Public */,
      22,    0,  152,    2, 0x06 /* Public */,
      23,    0,  153,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      24,    1,  154,    2, 0x0a /* Public */,
      25,    0,  157,    2, 0x0a /* Public */,
      25,    1,  158,    2, 0x0a /* Public */,
      25,    1,  161,    2, 0x0a /* Public */,
      26,    1,  164,    2, 0x0a /* Public */,
      27,    1,  167,    2, 0x0a /* Public */,
      28,    1,  170,    2, 0x0a /* Public */,
      29,    0,  173,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, QMetaType::UInt,   12,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,   24,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::Float,    7,
    QMetaType::Void,

 // properties: name, type, flags
      30, QMetaType::Float, 0x00095103,

       0        // eod
};

void MusicPlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MusicPlayer *_t = static_cast<MusicPlayer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->positionChanged((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 1: _t->mutedChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->volumeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->stateChanged((*reinterpret_cast< MusicState(*)>(_a[1]))); break;
        case 4: _t->durationChanged((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 5: _t->currentMusicChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->currentMusicChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->loadingFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->musicAdded(); break;
        case 9: _t->musicRemoved(); break;
        case 10: _t->hiding(); break;
        case 11: _t->showing(); break;
        case 12: _t->hidePlaylist(); break;
        case 13: _t->showPlaylist(); break;
        case 14: _t->pause((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->play(); break;
        case 16: _t->play((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->play((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 18: _t->setMuted((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 19: _t->setPosition((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 20: _t->setVolume((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 21: _t->stop(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MusicPlayer::*_t)(uint );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicPlayer::positionChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MusicPlayer::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicPlayer::mutedChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MusicPlayer::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicPlayer::volumeChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MusicPlayer::*_t)(MusicState );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicPlayer::stateChanged)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (MusicPlayer::*_t)(uint );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicPlayer::durationChanged)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (MusicPlayer::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicPlayer::currentMusicChanged)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (MusicPlayer::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicPlayer::currentMusicChanged)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (MusicPlayer::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicPlayer::loadingFailed)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (MusicPlayer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicPlayer::musicAdded)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (MusicPlayer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicPlayer::musicRemoved)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (MusicPlayer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicPlayer::hiding)) {
                *result = 10;
                return;
            }
        }
        {
            typedef void (MusicPlayer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicPlayer::showing)) {
                *result = 11;
                return;
            }
        }
        {
            typedef void (MusicPlayer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicPlayer::hidePlaylist)) {
                *result = 12;
                return;
            }
        }
        {
            typedef void (MusicPlayer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicPlayer::showPlaylist)) {
                *result = 13;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        MusicPlayer *_t = static_cast<MusicPlayer *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->playlistShowPercent(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        MusicPlayer *_t = static_cast<MusicPlayer *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPlaylistShowPercent(*reinterpret_cast< float*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject MusicPlayer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MusicPlayer.data,
      qt_meta_data_MusicPlayer,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MusicPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MusicPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MusicPlayer.stringdata0))
        return static_cast<void*>(const_cast< MusicPlayer*>(this));
    return QWidget::qt_metacast(_clname);
}

int MusicPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 22;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void MusicPlayer::positionChanged(uint _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MusicPlayer::mutedChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MusicPlayer::volumeChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MusicPlayer::stateChanged(MusicState _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MusicPlayer::durationChanged(uint _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MusicPlayer::currentMusicChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MusicPlayer::currentMusicChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void MusicPlayer::loadingFailed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void MusicPlayer::musicAdded()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void MusicPlayer::musicRemoved()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void MusicPlayer::hiding()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void MusicPlayer::showing()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void MusicPlayer::hidePlaylist()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}

// SIGNAL 13
void MusicPlayer::showPlaylist()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
