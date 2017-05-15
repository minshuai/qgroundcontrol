/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#include "AirMapManager.h"
#include "Vehicle.h"
#include "QmlObjectListModel.h"
#include "JsonHelper.h"

#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonArray>
#include <QNetworkProxy>

QGC_LOGGING_CATEGORY(AirMapManagerLog, "AirMapManagerLog")

AirMapManager::AirMapManager(QGCApplication* app, QGCToolbox* toolbox)
    : QGCTool(app, toolbox)
{

}

AirMapManager::~AirMapManager()
{

}

void AirMapManager::setROI(QGeoCoordinate& center, double radiusMeters)
{
    _roiCenter = center;
    _roiRadius = radiusMeters;

    // Build up the polygon for the query

    QJsonObject     polygonJson;

    polygonJson["type"] = "Polygon";

    QGeoCoordinate left =   center.atDistanceAndAzimuth(radiusMeters, -90);
    QGeoCoordinate right =  center.atDistanceAndAzimuth(radiusMeters, 90);
    QGeoCoordinate top =    center.atDistanceAndAzimuth(radiusMeters, 0);
    QGeoCoordinate bottom = center.atDistanceAndAzimuth(radiusMeters, 180);

    QGeoCoordinate topLeft(top.latitude(), left.longitude());
    QGeoCoordinate topRight(top.latitude(), right.longitude());
    QGeoCoordinate bottomLeft(bottom.latitude(), left.longitude());
    QGeoCoordinate bottomRight(bottom.latitude(), left.longitude());

    QJsonValue  vertex;
    QJsonArray  rgVertex;

    JsonHelper::saveGeoCoordinate(topLeft, false /* writeAltitude */, vertex);
    rgVertex.append(vertex);
    JsonHelper::saveGeoCoordinate(topRight, false /* writeAltitude */, vertex);
    rgVertex.append(vertex);
    JsonHelper::saveGeoCoordinate(bottomRight, false /* writeAltitude */, vertex);
    rgVertex.append(vertex);
    JsonHelper::saveGeoCoordinate(bottomLeft, false /* writeAltitude */, vertex);
    rgVertex.append(vertex);
    JsonHelper::saveGeoCoordinate(topLeft, false /* writeAltitude */, vertex);
    rgVertex.append(vertex);

    QJsonArray rgPolygon;
    rgPolygon.append(rgVertex);

    polygonJson["coordinates"] = rgPolygon;
    QJsonDocument polygonJsonDoc(polygonJson);

    // Build up the http query

    QUrlQuery airspaceQuery;

    airspaceQuery.addQueryItem(QStringLiteral("geometry"), QString::fromUtf8(polygonJsonDoc.toJson(QJsonDocument::Compact)));
    airspaceQuery.addQueryItem(QStringLiteral("types"), QStringLiteral("airport,controlled_airspace,tfr,wildfire"));
    airspaceQuery.addQueryItem(QStringLiteral("full"), QStringLiteral("true"));
    airspaceQuery.addQueryItem(QStringLiteral("geometry_format"), QStringLiteral("wkt"));

    QUrl airMapAirspaceUrl(QStringLiteral("https://api.airmap.com/airspace/v2/search"));
    airMapAirspaceUrl.setQuery(airspaceQuery);

    qDebug() << airMapAirspaceUrl;

    _get(airMapAirspaceUrl);
}

void AirMapManager::_get(QUrl url)
{
    QNetworkRequest request(url);

    qDebug() << url.toString(QUrl::FullyEncoded);
    request.setRawHeader("X-API-Key", "Key goes here");

    QNetworkProxy tProxy;
    tProxy.setType(QNetworkProxy::DefaultProxy);
    _networkManager.setProxy(tProxy);

    QNetworkReply* networkReply = _networkManager.get(request);
    if (!networkReply) {
        // FIXME
        qWarning() << "QNetworkAccessManager::get failed";
        return;
    }

    connect(networkReply, &QNetworkReply::finished,                                                                 this, &AirMapManager::_getFinished);
    connect(networkReply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &AirMapManager::_getError);
}

void AirMapManager::_getFinished(void)
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(QObject::sender());

    // When an error occurs we still end up here. So bail out in those cases.
    if (reply->error() != QNetworkReply::NoError) {
        return;
    }

    // Check for redirection
    QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (!redirectionTarget.isNull()) {
        QUrl redirectUrl = reply->url().resolved(redirectionTarget.toUrl());
        _get(redirectUrl);
        reply->deleteLater();
        return;
    }

    qDebug() << "_getFinished";
    qDebug() << QString::fromUtf8(reply->readAll());
}

void AirMapManager::_getError(QNetworkReply::NetworkError code)
{
    QString errorMsg;

    if (code == QNetworkReply::OperationCanceledError) {
        errorMsg = "Download cancelled";

    } else if (code == QNetworkReply::ContentNotFoundError) {
        errorMsg = "Error: File Not Found";

    } else {
        errorMsg = QString("Error during download. Error: %1").arg(code);
    }

    // FIXME
    qWarning() << errorMsg;
}

void AirMapManager::_addFakeData(void)
{
    _rgPolygon.clear();
    _rgCircle.clear();

    _rgCircle.append(_roiCenter);

    QList<QGeoCoordinate> polygon;
    polygon.append(_roiCenter.atDistanceAndAzimuth(200, 45));
    polygon.append(_roiCenter.atDistanceAndAzimuth(200, 135));
    polygon.append(_roiCenter.atDistanceAndAzimuth(200, 225));
    polygon.append(_roiCenter.atDistanceAndAzimuth(200, 315));
    _rgPolygon.append(polygon);

    emit polygonsChanged();
    emit circlesChanged();
}

