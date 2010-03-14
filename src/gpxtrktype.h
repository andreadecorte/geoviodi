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

#ifndef GPXTRKTYPE_H
#define GPXTRKTYPE_H
#include "gpxlinktype.h"
#include "gpxtrksegtype.h"
#include <QString>

/**
  * trk represents a track - an ordered list of points describing a path.
*/
class GpxTrkType
{
public:
    GpxTrkType();
    QString const getName();
    void setName (QString name);
    uint const getNumber();
    void setNumber (uint num);
    QList<GpxTrksegType*> const getTrksegType();
    void addTrksegType(GpxTrksegType* seg);
    void setTrksegType(QList<GpxTrksegType*> trksegs);

private:
    /* GPS name of track.*/
    QString _name;
    /* GPS comment for track. */
    QString _cmt;
    /* User description of track. */
    QString _desc;
    /* Source of data. Included to give user some idea of reliability and accuracy of data. */
    QString _src;
    /* Links to external information about track. */
    GpxLinkType* _link;
    /* GPS track number. */
    uint _number;
    /* Type (classification) of track. */
    QString _type;
    //GpxExtensionsType _extensions;
    /* A Track Segment holds a list of Track Points which are logically connected in order. To represent a single GPS track where GPS reception was lost, or the GPS receiver was turned off, start a new Track Segment for each continuous span of track data. */
    QList<GpxTrksegType*> _trkseg;

};

#endif // GPXTRKTYPE_H
