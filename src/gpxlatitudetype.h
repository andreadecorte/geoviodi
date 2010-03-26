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
* Last edit %DATE%
*/
#ifndef GPXLATITUDETYPE_H
#include <QDebug>
#define GPXLATITUDETYPE_H

/**
The latitude of the point.  Decimal degrees, WGS84 datum.
          */
class GpxLatitudeType
{
public:
    GpxLatitudeType();
    GpxLatitudeType(QString lat);
    GpxLatitudeType(double lat);

    double const getLatitude();
    void setLatitude(double lat);
    void setLatitude(QString lat);

private:
    double _latitude;
};

#endif // GPXLATITUDETYPE_H
