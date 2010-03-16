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

#ifndef GPXTRKSEGTYPE_H
#define GPXTRKSEGTYPE_H
#include <QList>
#include "gpxwpttype.h"

/**
  * A Track Segment holds a list of Track Points which are logically connected in order. To represent a single GPS track where GPS reception was lost, or the GPS receiver was turned off, start a new Track Segment for each continuous span of track data.
*/
class GpxTrksegType
{
public:
    GpxTrksegType();
    QList<GpxWptType*> getTrkpt();
    void setTrkpt (QList<GpxWptType*> trkpt);
    void addTrkpt (GpxWptType* trkpt);

private:
     QList<GpxWptType*> _trkpt;
     //GpxExtensionsType _extensions;

};

#endif // GPXTRKSEGTYPE_H
