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

#include "gpxlongitudetype.h"

GpxLongitudeType::GpxLongitudeType()
{
    setLongitude(0);
}

GpxLongitudeType::GpxLongitudeType(QString lon)
{
    setLongitude(lon);
}

GpxLongitudeType::GpxLongitudeType(double lon)
{
    setLongitude(lon);
}

double const GpxLongitudeType::getLongitude()
{
    return _longitude;
}

void GpxLongitudeType::setLongitude(double lon)
{
    if (lon>180.0 || lon < -180.0)
        qDebug() << "Wrong longitude range" << lon;
    _longitude = lon;
}

bool GpxLongitudeType::setLongitude(QString lon)
{
    bool ok;
    double res;
    //Because we should interpret always the dot as decimal separator
    QLocale::setDefault(QLocale::C);
    res = lon.toDouble(&ok);
    _longitude = res;
    return ok;
}
