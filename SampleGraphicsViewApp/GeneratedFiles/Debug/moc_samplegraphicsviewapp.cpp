/****************************************************************************
** Meta object code from reading C++ file 'samplegraphicsviewapp.h'
**
** Created: Tue Feb 28 13:11:33 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../samplegraphicsviewapp.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'samplegraphicsviewapp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SampleGraphicsViewApp[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x0a,
      55,   39,   22,   22, 0x0a,
      65,   22,   22,   22, 0x0a,
      83,   22,   22,   22, 0x0a,
     102,   22,   22,   22, 0x0a,
     127,   22,   22,   22, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SampleGraphicsViewApp[] = {
    "SampleGraphicsViewApp\0\0openDirectory()\0"
    "scalePercentage\0zoom(int)\0onSliderPressed()\0"
    "onSliderReleased()\0setImageFileFilter(bool)\0"
    "setEmfFileFilter(bool)\0"
};

const QMetaObject SampleGraphicsViewApp::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_SampleGraphicsViewApp,
      qt_meta_data_SampleGraphicsViewApp, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SampleGraphicsViewApp::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SampleGraphicsViewApp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SampleGraphicsViewApp::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SampleGraphicsViewApp))
        return static_cast<void*>(const_cast< SampleGraphicsViewApp*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int SampleGraphicsViewApp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: openDirectory(); break;
        case 1: zoom((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: onSliderPressed(); break;
        case 3: onSliderReleased(); break;
        case 4: setImageFileFilter((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: setEmfFileFilter((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
