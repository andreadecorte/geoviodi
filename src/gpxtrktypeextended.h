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
* Created 21/03/2010
*/

#ifndef GPXTRKTYPEEXTENDED_H
#define GPXTRKTYPEEXTENDED_H
#include "gpxtrktype.h"

#include <QColor>

/**
  * @brief Extends GpxTrkType adding some useful fields
  */
class GpxTrkTypeExtended : public GpxTrkType
{
public:
    GpxTrkTypeExtended();
    double const getLength();
    void setLength(double length);
    QColor const getColor();
    void setColor (QColor color);
    void setColor (int index);
    QVector<double> getX();
    void setX(QVector<double> x);
    QVector<double> getY();
    void setY(QVector<double> y);
private:
    //track length
    double _length;
    //color assigned to the track
    QColor _color;
    //x coordinates for incline graph (distance from start)
    QVector<double> _x;
    //y coordinates for incline graph (elevation)
    QVector<double> _y;
};

#endif // GPXTRKTYPEEXTENDED_H
