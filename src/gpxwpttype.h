/*
* Copyright 2010 Andrea Decorte <adecorte@gmail.com>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor,
* Boston, MA 02110-1301 USA
*
* Created 03/03/2010
*/

#ifndef GPXWPTTYPE_H
#define GPXWPTTYPE_H
#include <QDateTime>
#include "gpxdegreestype.h"
#include "gpxlatitudetype.h"
#include "gpxlongitudetype.h"
#include "gpxlinktype.h"

/**
  * @brief Type of GPS fix.  none means GPS had no fix.  To signify the fix info is unknown, leave out fixType entirely. pps = military signal used
  */
typedef enum
{
    NONE,
    FIX2D, //can't put only 2d, compiler will complain
    FIX3D,
    DGPS,
    PPS
} FixType;

/**
  * @brief wpt represents a waypoint, point of interest, or named feature on a map.
  */
class GpxWptType
{
public:
    GpxWptType();
    double const getEle();
    void setEle(double ele);
    bool setEle(QString ele);
    QString const getName();
    void setName(QString name);
    QString const getCmt();
    void setCmt (QString cmt);
    QDateTime const getTime();
    void setTime(QDateTime time);
    void setTime(QString time);
    GpxLatitudeType* const getLat();
    void setLat (GpxLatitudeType* lat);
    GpxLongitudeType* const getLon();
    void setLon (GpxLongitudeType* lon);
    void setLatLon(QString lat, QString lon);
    QString const getSym();
    void setSym (QString sym);
    QString const getDesc();
    void setDesc (QString desc);
    QString const getType();
    void setType (QString type);
    double const getGeoidheight();
    void setGeoidheight(double height);
    bool setGeoidheight(QString height);
    FixType getFix();
    QString getFixString();
    void setFix (QString fix);
    double const getHdop();
    bool setHdop (QString hdop);
    double const getVdop();
    bool setVdop (QString vdop);
    double const getPdop();
    bool setPdop (QString pdop);

private:
    //Elevation (in meters) of the point.
    double _ele;
    //Creation/modification timestamp for element. Date and time in are in Univeral Coordinated Time (UTC), not local time! Conforms to ISO 8601 specification for date/time representation. Fractional seconds are allowed for millisecond timing in tracklogs.
    QDateTime _time;
    //Magnetic variation (in degrees) at the point
    GpxDegreesType *_magvar;
    //Height (in meters) of geoid (mean sea level) above WGS84 earth ellipsoid.  As defined in NMEA GGA message.
    double _geoidheight;
    //Description info
    //The GPS name of the waypoint. This field will be transferred to and from the GPS. GPX does not place restrictions on the length of this field or the characters contained in it. It is up to the receiving application to validate the field before sending it to the GPS.
    QString _name;
    //GPS waypoint comment. Sent to GPS as comment.
    QString _cmt;
    //A text description of the element. Holds additional information about the element intended for the user, not the GPS.
    QString _desc;
    //Source of data. Included to give user some idea of reliability and accuracy of data.  "Garmin eTrex", "USGS quad Boston North", e.g.
    QString _src;
    //Link to additional information about the waypoint.
    GpxLinkType _link;
    //Text of GPS symbol name. For interchange with other programs, use the exact spelling of the symbol as displayed on the GPS.  If the GPS abbreviates words, spell them out.
    QString _sym;
    //Type (classification) of the waypoint.
    QString _type;
    //Accuracy info
    //Type of GPX fix.
    FixType _fix;
    //Number of satellites used to calculate the GPX fix.
    uint _sat;
    //Horizontal dilution of precision.
    double _hdop;
    //Vertical dilution of precision.
    double _vdop;
    //Position dilution of precision.
    double _pdop;
    //Number of seconds since last DGPS update.
    double _ageofdgpsdata;
    //ID of DGPS station used in differential correction.
//    GpxDgpsStationType _dgpsid;
//    GpxExtensionsType _extensions;
    //The latitude of the point.  Decimal degrees, WGS84 datum.
    GpxLatitudeType *_lat;
    //The longitude of the point.  Decimal degrees, WGS84 datum.
    GpxLongitudeType *_lon;

};

#endif // GPXWPTTYPE_H
