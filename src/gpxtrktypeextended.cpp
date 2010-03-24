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

#include "gpxtrktypeextended.h"

GpxTrkTypeExtended::GpxTrkTypeExtended()
{
}

double const GpxTrkTypeExtended::getLength()
{
    return _length;
}

void GpxTrkTypeExtended::setLength(double length)
{
    _length = length;
}

QColor const GpxTrkTypeExtended::getColor()
{
    return _color;
}

void GpxTrkTypeExtended::setColor(QColor color)
{
    _color = color;
}

void GpxTrkTypeExtended::setColor(int index)
{
    switch (index){
    case 0:
        _color = Qt::cyan;
        break;
    case 1:
        _color = Qt::red;
        break;
    case 2:
        _color = Qt::green;
        break;
    case 3:
        _color = Qt::blue;
        break;
    case 4:
        _color = Qt::yellow;
        break;
    case 5:
        _color = Qt::magenta;
        break;
    case 6:
        _color = Qt::darkGray;
        break;
    case 7:
        _color = Qt::darkGreen;
        break;
    case 8:
        _color = Qt::darkRed;
        break;
    case 9:
        _color = Qt::darkMagenta;
        break;
    case 10:
        _color = Qt::darkYellow;
        break;
    case 11:
        _color = Qt::darkBlue;
        break;
    default:
        //if there are more than 12 tracks, they will just be black
        _color = Qt::black;
    }
}

QVector<double> GpxTrkTypeExtended::getX()
{
    return _x;
}

void GpxTrkTypeExtended::setX(QVector<double> x)
{
    _x = x;
}

QVector<double> GpxTrkTypeExtended::getY()
{
    return _y;
}

void GpxTrkTypeExtended::setY(QVector<double> y)
{
    _y = y;
}
