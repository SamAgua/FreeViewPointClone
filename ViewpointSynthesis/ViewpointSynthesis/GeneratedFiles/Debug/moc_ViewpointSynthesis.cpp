/****************************************************************************
** Meta object code from reading C++ file 'ViewpointSynthesis.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ViewpointSynthesis.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ViewpointSynthesis.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ViewpointSynthesis_t {
    QByteArrayData data[14];
    char stringdata0[220];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ViewpointSynthesis_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ViewpointSynthesis_t qt_meta_stringdata_ViewpointSynthesis = {
    {
QT_MOC_LITERAL(0, 0, 18), // "ViewpointSynthesis"
QT_MOC_LITERAL(1, 19, 16), // "handleExitButton"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 16), // "handleCam1Button"
QT_MOC_LITERAL(4, 54, 16), // "handleCam2Button"
QT_MOC_LITERAL(5, 71, 16), // "handleCam3Button"
QT_MOC_LITERAL(6, 88, 16), // "handleCam4Button"
QT_MOC_LITERAL(7, 105, 16), // "handleCam5Button"
QT_MOC_LITERAL(8, 122, 16), // "handleCam6Button"
QT_MOC_LITERAL(9, 139, 18), // "handleStitchedView"
QT_MOC_LITERAL(10, 158, 17), // "handleStartStream"
QT_MOC_LITERAL(11, 176, 16), // "handleStopStream"
QT_MOC_LITERAL(12, 193, 12), // "handleZoomIn"
QT_MOC_LITERAL(13, 206, 13) // "handleZoomOut"

    },
    "ViewpointSynthesis\0handleExitButton\0"
    "\0handleCam1Button\0handleCam2Button\0"
    "handleCam3Button\0handleCam4Button\0"
    "handleCam5Button\0handleCam6Button\0"
    "handleStitchedView\0handleStartStream\0"
    "handleStopStream\0handleZoomIn\0"
    "handleZoomOut"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ViewpointSynthesis[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    0,   84,    2, 0x08 /* Private */,
      13,    0,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ViewpointSynthesis::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ViewpointSynthesis *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->handleExitButton(); break;
        case 1: _t->handleCam1Button(); break;
        case 2: _t->handleCam2Button(); break;
        case 3: _t->handleCam3Button(); break;
        case 4: _t->handleCam4Button(); break;
        case 5: _t->handleCam5Button(); break;
        case 6: _t->handleCam6Button(); break;
        case 7: _t->handleStitchedView(); break;
        case 8: _t->handleStartStream(); break;
        case 9: _t->handleStopStream(); break;
        case 10: _t->handleZoomIn(); break;
        case 11: _t->handleZoomOut(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject ViewpointSynthesis::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_ViewpointSynthesis.data,
    qt_meta_data_ViewpointSynthesis,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ViewpointSynthesis::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ViewpointSynthesis::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ViewpointSynthesis.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ViewpointSynthesis::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE