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
* Created 17/03/2010
*/

#include "gpxrtetype.h"

GpxRteType::GpxRteType()
{
}

QString const GpxRteType::getName()
{
    return _name;
}

void GpxRteType::setName(QString name)
{
    _name = name;
}

QString const GpxRteType::getCmt()
{
    return _cmt;
}

void GpxRteType::setCmt(QString cmt)
{
    _cmt = cmt;
}

QString const GpxRteType::getDesc()
{
    return _desc;
}

void GpxRteType::setDesc(QString desc)
{
    _desc = desc;
}

QString const GpxRteType::getSrc()
{
    return _src;
}

void GpxRteType::setSrc(QString src)
{
    _src = src;
}

QList<GpxLinkType*> GpxRteType::getLinks()
{
    return _link;
}

void GpxRteType::setLinks(QList<GpxLinkType*> links)
{
    _link = links;
}

uint const GpxRteType::getNumber()
{
    return _number;
}

void GpxRteType::setNumber(uint number)
{
    _number = number;
}

/**
  * @brief overloaded method to parse a string
  */
void GpxRteType::setNumber(QString number)
{
    bool ok;
    //Because we should interpret always the dot as decimal separator
    QLocale c(QLocale::C);
    double res = c.toDouble(number, &ok);
    if (ok)
        _number = res;
    else
        qDebug() << "Conversion error" + number;
}

QString const GpxRteType::getType()
{
    return _type;
}

void GpxRteType::setType(QString type)
{
    _type = type;
}

QList<GpxWptType*> GpxRteType::getRtept()
{
    return _rtept;
}

void GpxRteType::setRtept(QList<GpxWptType*> points)
{
    _rtept = points;
}

void GpxRteType::addRtept(GpxWptType* pt)
{
    _rtept.append(pt);
}

