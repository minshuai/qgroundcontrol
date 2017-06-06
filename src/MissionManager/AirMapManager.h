/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#ifndef AirMapManager_H
#define AirMapManager_H

#include "QGCToolbox.h"
#include "QGCLoggingCategory.h"
<<<<<<< HEAD
#include "QmlObjectListModel.h"
=======
>>>>>>> origin/AirMap

#include <QGeoCoordinate>
#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkReply>
<<<<<<< HEAD
#include <QTimer>
=======
>>>>>>> origin/AirMap

Q_DECLARE_LOGGING_CATEGORY(AirMapManagerLog)

/// AirMap server communication support.
class AirMapManager : public QGCTool
{
    Q_OBJECT
    
public:
    AirMapManager(QGCApplication* app, QGCToolbox* toolbox);
    ~AirMapManager();

    /// Set the ROI for airspace information
    ///     @param center Center coordinate for ROI
    ///     @param radiusMeters Radius in meters around center which is of interest
    void setROI(QGeoCoordinate& center, double radiusMeters);

<<<<<<< HEAD
    QmlObjectListModel* polygonRestrictions(void) { return &_polygonList; }
    QmlObjectListModel* circularRestrictions(void) { return &_circleList; }
=======
    const QList<QList<QGeoCoordinate>>& rgPolygon(void) const { return _rgPolygon; }
    const QList<QGeoCoordinate>&        rgCircle(void) const { return _rgCircle; }
>>>>>>> origin/AirMap
        
signals:
    void polygonsChanged(void);
    void circlesChanged(void);

private slots:
    void _getFinished(void);
    void _getError(QNetworkReply::NetworkError code);
<<<<<<< HEAD
    void _updateToROI(void);

private:
    void _get(QUrl url);
    void _parseAirspaceJson(const QJsonDocument& airspaceDoc);

    QGeoCoordinate          _roiCenter;
    double                  _roiRadius;
    QNetworkAccessManager   _networkManager;
    QTimer                  _updateTimer;
    QmlObjectListModel      _polygonList;
    QmlObjectListModel      _circleList;
};

class AirspaceRestriction : public QObject
{
    Q_OBJECT

public:
    AirspaceRestriction(QObject* parent = NULL);
};

class PolygonAirspaceRestriction : public AirspaceRestriction
{
    Q_OBJECT

public:
    PolygonAirspaceRestriction(const QVariantList& polygon, QObject* parent = NULL);

    Q_PROPERTY(QVariantList polygon MEMBER _polygon CONSTANT)

private:
    QVariantList    _polygon;
};

class CircularAirspaceRestriction : public AirspaceRestriction
{
    Q_OBJECT

public:
    CircularAirspaceRestriction(const QGeoCoordinate& center, double radius, QObject* parent = NULL);

    Q_PROPERTY(QGeoCoordinate   center MEMBER _center CONSTANT)
    Q_PROPERTY(double           radius MEMBER _radius CONSTANT)

private:
    QGeoCoordinate  _center;
    double          _radius;
=======

private:
    void _get(QUrl url);
    void _addFakeData(void);

    QGeoCoordinate                  _roiCenter;
    double                          _roiRadius;
    QList<QList<QGeoCoordinate>>    _rgPolygon;
    QList<QGeoCoordinate>           _rgCircle;
    QNetworkAccessManager           _networkManager;
>>>>>>> origin/AirMap
};

#endif
