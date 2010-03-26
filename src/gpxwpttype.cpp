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

/**
  * @brief overloaded method to parse a string
  */
void GpxWptType::setEle(QString ele)
{
    bool ok;
    //Because we should interpret always the dot as decimal separator
    QLocale c(QLocale::C);
    double res = c.toDouble(ele, &ok);
    if (ok)
    {
        if (res < 0)
            qDebug() << "Elevation < 0: " << ele;
        _ele = res;
    }
    else
    {
        qDebug() << "Conversion error" + ele;
    }
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

/**
  * @brief overloaded method to parse a string
  */
void GpxWptType::setGeoidheight(QString height)
{
    bool ok;
    //Because we should interpret always the dot as decimal separator
    QLocale c(QLocale::C);
    double res = c.toDouble(height, &ok);
    if (ok)
        _geoidheight = res;
    else
        qDebug() << "Conversion error" + height;
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

/**
  * @brief overloaded method to parse a string
  */
void GpxWptType::setHdop (QString hdop)
{
    bool ok;
    //Because we should interpret always the dot as decimal separator
    QLocale c(QLocale::C);
    double res = c.toDouble(hdop, &ok);
    if (ok)
        _hdop = res;
    else
        qDebug() << "Conversion error" + hdop;
}

double const GpxWptType::getVdop()
{
    return _vdop;
}

/**
  * @brief overloaded method to parse a string
  */
void GpxWptType::setVdop (QString vdop)
{
    bool ok;
    //Because we should interpret always the dot as decimal separator
    QLocale c(QLocale::C);
    double res = c.toDouble(vdop, &ok);
    if (ok)
        _vdop = res;
    else
        qDebug() << "Conversion error" + vdop;
}

double const GpxWptType::getPdop()
{
    return _pdop;
}

/**
  * @brief overloaded method to parse a string
  */
void GpxWptType::setPdop (QString pdop)
{
    bool ok;
    //Because we should interpret always the dot as decimal separator
    QLocale c(QLocale::C);
    double res = c.toDouble(pdop, &ok);
    if (ok)
        _pdop = res;
    else
        qDebug() << "Conversion error" + pdop;
}

double const GpxWptType::getAgeOfGpsData()
{
    return _ageofdgpsdata;
}

/**
  * @brief overloaded method to parse a string
  */
void GpxWptType::setAgeOfGpsData (QString age)
{
    bool ok;
    //Because we should interpret always the dot as decimal separator
    QLocale c(QLocale::C);
    double res = c.toDouble(age, &ok);
    if (ok)
        _ageofdgpsdata = res;
    else
        qDebug() << "Conversion error" + age;
}

uint const GpxWptType::getSat()
{
    return _sat;
}

/**
  * @brief overloaded method to parse a string
  */
void GpxWptType::setSat (QString sat)
{
    bool ok;
    //Because we should interpret always the dot as decimal separator
    QLocale c(QLocale::C);
    double res = c.toUInt(sat, &ok);
    if (ok)
        _sat = res;
    else
        qDebug() << "Conversion error" + sat;
}

uint const GpxWptType::getDgpsid()
{
    return _dgpsid;
}

//it should be a type on its own, but it's just a int limited from 0 to 1023
void GpxWptType::setDgpsid(QString id)
{
    bool ok;
    //Because we should interpret always the dot as decimal separator
    QLocale c(QLocale::C);
    double res = c.toUInt(id, &ok);
    if (ok)
    {
        if (res > 1023)
            qDebug() << "Invalid differential GPS station" << id;
        _dgpsid = res;
    }
    else
    {
        qDebug() << "Conversion error" + id;
    }
}
