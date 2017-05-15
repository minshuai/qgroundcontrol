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

#include <QGeoCoordinate>
#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkReply>

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

    const QList<QList<QGeoCoordinate>>& rgPolygon(void) const { return _rgPolygon; }
    const QList<QGeoCoordinate>&        rgCircle(void) const { return _rgCircle; }
        
signals:
    void polygonsChanged(void);
    void circlesChanged(void);

private slots:
    void _getFinished(void);
    void _getError(QNetworkReply::NetworkError code);

private:
    void _get(QUrl url);
    void _addFakeData(void);

    QGeoCoordinate                  _roiCenter;
    double                          _roiRadius;
    QList<QList<QGeoCoordinate>>    _rgPolygon;
    QList<QGeoCoordinate>           _rgCircle;
    QNetworkAccessManager           _networkManager;
};

#endif
