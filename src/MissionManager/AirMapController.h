/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#ifndef AirMapController_H
#define AirMapController_H

#include "AirMapManager.h"
#include "QGCMapPolygon.h"
#include "QGCLoggingCategory.h"

Q_DECLARE_LOGGING_CATEGORY(AirMapControllerLog)

class AirMapManager;

class AirMapController : public QObject
{
    Q_OBJECT
    
public:
    AirMapController(QObject* parent = NULL);
    ~AirMapController();

    Q_PROPERTY(QmlObjectListModel*  polygons    READ polygons   CONSTANT)
    Q_PROPERTY(QmlObjectListModel*  circles     READ circles    CONSTANT)

    Q_INVOKABLE void setROI(QGeoCoordinate center, double radius) { _manager->setROI(center, radius); }

<<<<<<< HEAD
    QmlObjectListModel* polygons(void) { return _manager->polygonRestrictions(); }
    QmlObjectListModel* circles(void) { return _manager->circularRestrictions(); }
=======
    QmlObjectListModel* polygons(void) { return &_polygonList; }
    QmlObjectListModel* circles(void) { return &_circleList; }
>>>>>>> origin/AirMap

signals:
    void polygonChanged(void);
    void circlesChanged(void);

private slots:
    void _managerPolygonsChanged(void);
    void _managerCirclesChanged(void);

private:
    AirMapManager*      _manager;
    QmlObjectListModel  _polygonList;
    QmlObjectListModel  _circleList;
};

#endif
