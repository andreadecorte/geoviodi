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

#ifndef GPXTYPE_H
#define GPXTYPE_H
#include "gpxwpttype.h"
#include "gpxtrktype.h"
#include "gpxmetadatatype.h"
#include "gpxrtetype.h"

class GpxType
{
public:
    GpxType();
    GpxWptType* getFirstWpt();
    void addWpt (GpxWptType* wpt);
    QList<GpxWptType*> const getWptList();
    void addTrk (GpxTrkType* trk);
    QList<GpxTrkType*> const getTrkList();
    QString const getVersion();
    void setVersion (QString version);
    QString const getCreator();
    void setCreator (QString creator);
    GpxMetadataType* const getMetadata();
    void setMetadata(GpxMetadataType* metadata);
    QList<GpxRteType*> getRteList();
    void addRte (GpxRteType* rte);

private:
    GpxMetadataType* _metadata;
    QList<GpxWptType*> _wptList;
    QList<GpxRteType*> _rteList;
    QList<GpxTrkType*> _trkList;
    QString _version;
    QString _creator;
};

#endif // GPXTYPE_H
