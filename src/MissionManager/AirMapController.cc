/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#include "AirMapController.h"
#include "AirMapManager.h"
#include "QGCApplication.h"
#include "QGCQGeoCoordinate.h"

QGC_LOGGING_CATEGORY(AirMapControllerLog, "AirMapControllerLog")

AirMapController::AirMapController(QObject* parent)
    : QObject(parent)
    , _manager(qgcApp()->toolbox()->airMapManager())
{
    connect(_manager, &AirMapManager::polygonsChanged,  this, &AirMapController::_managerPolygonsChanged);
    connect(_manager, &AirMapManager::circlesChanged,   this, &AirMapController::_managerCirclesChanged);

    _managerPolygonsChanged();
    _managerCirclesChanged();
}

AirMapController::~AirMapController()
{

}

void AirMapController::_managerPolygonsChanged(void)
{
<<<<<<< HEAD
#if 0
=======
>>>>>>> origin/AirMap
    _polygonList.clearAndDeleteContents();

    const QList<QList<QGeoCoordinate>>& rgPolygons = _manager->rgPolygon();

    for (int i=0; i<rgPolygons.count(); i++) {
        const QList<QGeoCoordinate>& polygon = rgPolygons[i];
        QGCMapPolygon* mapPolygon = new QGCMapPolygon(this, this);

        for (int j=0; j<polygon.count(); j++) {
            mapPolygon->appendVertex(polygon[j]);
        }

        _polygonList.append(mapPolygon);
    }
<<<<<<< HEAD
#endif
=======
>>>>>>> origin/AirMap
}


void AirMapController::_managerCirclesChanged(void)
{
<<<<<<< HEAD
#if 0
=======
>>>>>>> origin/AirMap
    _circleList.clearAndDeleteContents();

    const QList<QGeoCoordinate>& rgCircles = _manager->rgCircle();

    for (int i=0; i<rgCircles.count(); i++) {
        const QGeoCoordinate& center = rgCircles[i];

        _circleList.append(new QGCQGeoCoordinate(center, this));
    }
<<<<<<< HEAD
#endif
=======
>>>>>>> origin/AirMap
}
