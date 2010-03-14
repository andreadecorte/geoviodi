/*
* Copyright 2010 Andrea Decorte <adecorte@gmail.com>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
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
#include <QDateTime>
#include "gpxdegreestype.h"
#include "gpxlatitudetype.h"
#include "gpxlongitudetype.h"
#include "gpxlinktype.h"
#define GPXWPTTYPE_H

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

private:
    double _ele;
    QDateTime _time;
    GpxDegreesType *_magvar;
    double _geoidheight;
    QString _name;
    /* GPS waypoint comment. Sent to GPS as comment. */
    QString _cmt;
    QString _desc;
    QString _src;
    GpxLinkType _link;
    //Text of GPS symbol name. For interchange with other programs, use the exact spelling of the symbol as displayed on the GPS.  If the GPS abbreviates words, spell them out.
    QString _sym;
    QString _type;
    //GpxFixType _fix;
    uint _sat;
    double _hdop;
    double _vdop;
    double _pdop;
//    GpxDgpsStationType _dgpsid;
//    GpxExtensionsType _extensions;
    GpxLatitudeType *_lat;
    GpxLongitudeType *_lon;

};

#endif // GPXWPTTYPE_H
