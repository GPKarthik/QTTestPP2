/****************************************************************************
** Meta object code from reading C++ file 'customgraphicsview.h'
**
** Created: Tue Feb 28 12:56:49 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../customgraphicsview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'customgraphicsview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CustomGraphicsView[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,
      48,   33,   19,   19, 0x0a,
      76,   19,   19,   19, 0x2a,
     110,  100,   19,   19, 0x0a,
     127,   19,   19,   19, 0x0a,
     148,   19,   19,   19, 0x0a,
     167,   19,   19,   19, 0x0a,
     186,  180,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CustomGraphicsView[] = {
    "CustomGraphicsView\0\0updateView()\0"
    "bSliderPressed\0setTransformationMode(bool)\0"
    "setTransformationMode()\0nItemSize\0"
    "setItemSize(int)\0onSliderPressed(int)\0"
    "onSliderReleased()\0updateItem()\0index\0"
    "updateItemImage(int)\0"
};

const QMetaObject CustomGraphicsView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_CustomGraphicsView,
      qt_meta_data_CustomGraphicsView, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CustomGraphicsView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CustomGraphicsView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CustomGraphicsView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CustomGraphicsView))
        return static_cast<void*>(const_cast< CustomGraphicsView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int CustomGraphicsView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateView(); break;
        case 1: setTransformationMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: setTransformationMode(); break;
        case 3: setItemSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: onSliderPressed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: onSliderReleased(); break;
        case 6: updateItem(); break;
        case 7: updateItemImage((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
