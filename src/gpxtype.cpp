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

#include "gpxtype.h"

GpxType::GpxType()
{

}

GpxWptType* GpxType::getFirstWpt()
{
    return _wptList.first();
}

void GpxType::addWpt(GpxWptType *wpt)
{
    _wptList.append(wpt);
}

QList<GpxWptType*> const GpxType::getWptList()
{
    return _wptList;
}

void GpxType::addTrk (GpxTrkTypeExtended* trk)
{
    _trkList.append(trk);
}

QList<GpxTrkTypeExtended*> GpxType::getTrkList()
{
    return _trkList;
}

QString const GpxType::getVersion()
{
    return _version;
}

void GpxType::setVersion (QString version)
{
    _version = version;
}

QString const GpxType::getCreator()
{
    return _creator;
}

void GpxType::setCreator (QString creator)
{
    _creator = creator;
}

GpxMetadataType* const GpxType::getMetadata()
{
    return _metadata;
}

void GpxType::setMetadata(GpxMetadataType* metadata)
{
    _metadata = metadata;
}

QList<GpxRteType*> GpxType::getRteList()
{
    return _rteList;
}

void GpxType::addRte (GpxRteType* rte)
{
    _rteList.append(rte);
}
