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
#include "gpxlatitudetype.h"

GpxLatitudeType::GpxLatitudeType()
{
    setLatitude(0);
}

GpxLatitudeType::GpxLatitudeType(QString lat)
{
    setLatitude(lat);
}

GpxLatitudeType::GpxLatitudeType(double lat)
{
    setLatitude(lat);
}

double const GpxLatitudeType::getLatitude()
{
    return _latitude;
}

void GpxLatitudeType::setLatitude(double lat)
{
    if (lat>90.0 || lat < -90.0)
        qDebug() << "Wrong latitude range" << lat;
    _latitude = lat;
}

bool GpxLatitudeType::setLatitude(QString lat)
{
    bool ok;
    double res;
    //Because we should interpret always the dot as decimal separator
    QLocale::setDefault(QLocale::C);
    res = lat.toDouble(&ok);
    _latitude = res;
    return ok;
}
