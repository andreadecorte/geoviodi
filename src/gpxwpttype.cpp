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

#include "gpxwpttype.h"

GpxWptType::GpxWptType()
{
    _ele = -10000;
}

double const GpxWptType::getEle()
{
    return _ele;
}

void GpxWptType::setEle(double ele)
{
    if (ele < 0)
        qDebug() << "Elevation < 0";
    _ele = ele;
}

bool GpxWptType::setEle(QString ele)
{
    bool ok;
    double res;
    //Because we should interpret always the dot as decimal separator
    QLocale::setDefault(QLocale::C);
    res = ele.toDouble(&ok);
    if (res < 0)
        qDebug() << "Elevation < 0: " << ele;
    _ele = res;
    return ok;
}

QString const GpxWptType::getName()
{
    return _name;
}

void GpxWptType::setName(QString name)
{
    _name = name;
}

QString const GpxWptType::getCmt()
{
    return _cmt;
}

void GpxWptType::setCmt(QString cmt)
{
    _cmt = cmt;
}

QDateTime const GpxWptType::getTime()
{
    return _time;
}

void GpxWptType::setTime(QDateTime time)
{
    _time = time;
}

void GpxWptType::setTime(QString time)
{
    //check
    QDateTime dateTime = QDateTime::fromString(time, "yyyy-MM-ddThh:mm:ssZ");
    _time = dateTime;
}

GpxLatitudeType* const GpxWptType::getLat()
{
    return _lat;
}

void GpxWptType::setLat(GpxLatitudeType *lat)
{
    _lat = lat;
}

GpxLongitudeType* const GpxWptType::getLon()
{
    return _lon;
}

void GpxWptType::setLon(GpxLongitudeType *lon)
{
    _lon = lon;
}

/** @brief sets both latitude and longitude
  @param lat the latitude
  @param lon the longitude
  */
void GpxWptType::setLatLon(QString lat, QString lon)
{
    GpxLatitudeType* latitude = new GpxLatitudeType;
    latitude->setLatitude(lat);
    _lat = latitude;

    GpxLongitudeType* longitude = new GpxLongitudeType;
    longitude->setLongitude(lon);
    _lon = longitude;
}

QString const GpxWptType::getSym()
{
    return _sym;
}

void GpxWptType::setSym(QString sym)
{
    _sym = sym;
}

QString const GpxWptType::getDesc()
{
    return _desc;
}

void GpxWptType::setDesc(QString desc)
{
    _desc = desc;
}

QString const GpxWptType::getType()
{
    return _type;
}

void GpxWptType::setType(QString type)
{
    _type = type;
}

double const GpxWptType::getGeoidheight()
{
    return _geoidheight;
}

void GpxWptType::setGeoidheight(double height)
{
    _geoidheight = height;
}

bool GpxWptType::setGeoidheight(QString height)
{
    bool ok;
    double res;
    //Because we should interpret always the dot as decimal separator
    QLocale::setDefault(QLocale::C);
    res = height.toDouble(&ok);
    _geoidheight = res;
    return ok;
}

FixType GpxWptType::getFix()
{
    return _fix;
}

QString GpxWptType::getFixString()
{
    switch (_fix)
    {
    case NONE: return "None";
    case FIX2D: return "2D";
    case FIX3D: return "3D";
    case DGPS: return "DGPS";
    case PPS: return "PPS";
    default: return "None";
    }
}

void GpxWptType::setFix (QString fix)
{
    if (fix == "2d")
        _fix = FIX2D;
    if (fix == "3d")
        _fix = FIX3D;
    if (fix == "none")
        _fix = NONE;
    if (fix == "dgps")
        _fix = DGPS;
    if (fix == "pps")
        _fix = PPS;
}

double const GpxWptType::getHdop()
{
    return _hdop;
}

bool GpxWptType::setHdop (QString hdop)
{
    bool ok;
    double res;
    //Because we should interpret always the dot as decimal separator
    QLocale::setDefault(QLocale::C);
    res = hdop.toDouble(&ok);
    _hdop = res;
    return ok;
}

double const GpxWptType::getVdop()
{
    return _vdop;
}

bool GpxWptType::setVdop (QString vdop)
{
    bool ok;
    double res;
    //Because we should interpret always the dot as decimal separator
    QLocale::setDefault(QLocale::C);
    res = vdop.toDouble(&ok);
    _vdop = res;
    return ok;
}

double const GpxWptType::getPdop()
{
    return _pdop;
}

bool GpxWptType::setPdop (QString pdop)
{
    bool ok;
    double res;
    //Because we should interpret always the dot as decimal separator
    QLocale::setDefault(QLocale::C);
    res = pdop.toDouble(&ok);
    _pdop = res;
    return ok;
}

