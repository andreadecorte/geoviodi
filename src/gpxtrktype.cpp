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
* Created 03/03/2010
*/

#include "gpxtrktype.h"

GpxTrkType::GpxTrkType()
{
}

QString const GpxTrkType::getName()
{
    return _name;
}

void GpxTrkType::setName (QString name)
{
    _name = name;
}

uint const GpxTrkType::getNumber()
{
    return _number;
}

void GpxTrkType::setNumber (uint num)
{
    _number = num;
}

QList<GpxTrksegType*> const GpxTrkType::getTrksegType()
{
    return _trkseg;
}

void GpxTrkType::setTrksegType(QList<GpxTrksegType*> segs)
{
    _trkseg = segs;
}

void GpxTrkType::addTrksegType(GpxTrksegType* seg)
{
    _trkseg.append(seg);
}
