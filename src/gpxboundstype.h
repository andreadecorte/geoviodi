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
* Created 05/03/2010
*/

#ifndef GPXBOUNDSTYPE_H
#define GPXBOUNDSTYPE_H
#include "gpxlongitudetype.h"
#include "gpxlatitudetype.h"

/**
 * Two lat/lon pairs defining the extent of an element.
*/
class GpxBoundsType
{
public:
    GpxBoundsType();
    GpxBoundsType(double minlon, double maxlon, double minlat, double maxlat);
    GpxLatitudeType* const getMinlat();
    GpxLatitudeType* const getMaxlat();
    void setMinlat(GpxLatitudeType* minlat);
    void setMaxlat(GpxLatitudeType* maxlat);
    GpxLongitudeType* const getMinlon();
    GpxLongitudeType* const getMaxlon();
    void setMinlon(GpxLongitudeType* minlon);
    void setMaxlon(GpxLongitudeType* maxlon);

private:
    GpxLatitudeType* _minlat;
    GpxLatitudeType* _maxlat;
    GpxLongitudeType* _minlon;
    GpxLongitudeType* _maxlon;
};

#endif // GPXBOUNDSTYPE_H
