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
* Created 05/03/2010
*/

#include "gpxboundstype.h"

GpxBoundsType::GpxBoundsType()
{
}

/** @brief Constructor to create a BoundsType on the fly
  @param minlon
  */
GpxBoundsType::GpxBoundsType(double minlon, double maxlon, double minlat, double maxlat)
{
    _minlon = new GpxLongitudeType(minlon);
    _maxlon = new GpxLongitudeType(maxlon);
    _minlat = new GpxLatitudeType(minlat);
    _maxlat = new GpxLatitudeType(maxlat);
}

GpxLatitudeType* const GpxBoundsType::getMinlat()
{
    return _minlat;
}

GpxLatitudeType* const GpxBoundsType::getMaxlat()
{
    return _maxlat;
}

void GpxBoundsType::setMinlat(GpxLatitudeType* minlat)
{
    _minlat = minlat;
}

void GpxBoundsType::setMaxlat(GpxLatitudeType* maxlat)
{
    _maxlat = maxlat;
}

GpxLongitudeType* const GpxBoundsType::getMinlon()
{
    return _minlon;
}

GpxLongitudeType* const GpxBoundsType::getMaxlon()
{
    return _maxlon;
}

void GpxBoundsType::setMinlon(GpxLongitudeType* minlon)
{
    _minlon = minlon;
}

void GpxBoundsType::setMaxlon(GpxLongitudeType* maxlon)
{
    _maxlon = maxlon;
}
