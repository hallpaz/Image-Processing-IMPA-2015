/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qt-opencv/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[20];
    char stringdata0[417];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 24), // "captureAndShowVideoFrame"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 28), // "on_actionLoadImage_triggered"
QT_MOC_LITERAL(4, 66, 28), // "on_actionSaveImage_triggered"
QT_MOC_LITERAL(5, 95, 24), // "on_actionReset_triggered"
QT_MOC_LITERAL(6, 120, 32), // "on_actionCameraCapture_triggered"
QT_MOC_LITERAL(7, 153, 30), // "on_actionCameraCapture_toggled"
QT_MOC_LITERAL(8, 184, 6), // "toggle"
QT_MOC_LITERAL(9, 191, 34), // "on_actionGradientMagnitude_to..."
QT_MOC_LITERAL(10, 226, 4), // "arg1"
QT_MOC_LITERAL(11, 231, 18), // "on_scale_0_toggled"
QT_MOC_LITERAL(12, 250, 7), // "checked"
QT_MOC_LITERAL(13, 258, 18), // "on_scale_1_toggled"
QT_MOC_LITERAL(14, 277, 18), // "on_scale_2_toggled"
QT_MOC_LITERAL(15, 296, 18), // "on_scale_3_toggled"
QT_MOC_LITERAL(16, 315, 24), // "on_actionPyramid_toggled"
QT_MOC_LITERAL(17, 340, 36), // "on_actionGradientOrientation_..."
QT_MOC_LITERAL(18, 377, 30), // "on_thresholdSlider_sliderMoved"
QT_MOC_LITERAL(19, 408, 8) // "position"

    },
    "MainWindow\0captureAndShowVideoFrame\0"
    "\0on_actionLoadImage_triggered\0"
    "on_actionSaveImage_triggered\0"
    "on_actionReset_triggered\0"
    "on_actionCameraCapture_triggered\0"
    "on_actionCameraCapture_toggled\0toggle\0"
    "on_actionGradientMagnitude_toggled\0"
    "arg1\0on_scale_0_toggled\0checked\0"
    "on_scale_1_toggled\0on_scale_2_toggled\0"
    "on_scale_3_toggled\0on_actionPyramid_toggled\0"
    "on_actionGradientOrientation_toggled\0"
    "on_thresholdSlider_sliderMoved\0position"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x09 /* Protected */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    1,   89,    2, 0x08 /* Private */,
       9,    1,   92,    2, 0x08 /* Private */,
      11,    1,   95,    2, 0x08 /* Private */,
      13,    1,   98,    2, 0x08 /* Private */,
      14,    1,  101,    2, 0x08 /* Private */,
      15,    1,  104,    2, 0x08 /* Private */,
      16,    1,  107,    2, 0x08 /* Private */,
      17,    1,  110,    2, 0x08 /* Private */,
      18,    1,  113,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Int,   19,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->captureAndShowVideoFrame(); break;
        case 1: _t->on_actionLoadImage_triggered(); break;
        case 2: _t->on_actionSaveImage_triggered(); break;
        case 3: _t->on_actionReset_triggered(); break;
        case 4: _t->on_actionCameraCapture_triggered(); break;
        case 5: _t->on_actionCameraCapture_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->on_actionGradientMagnitude_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_scale_0_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_scale_1_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_scale_2_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->on_scale_3_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->on_actionPyramid_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->on_actionGradientOrientation_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->on_thresholdSlider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
