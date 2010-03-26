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
* Created 17/03/2010
*/

#ifndef GPXRTETYPE_H
#define GPXRTETYPE_H
#include "gpxwpttype.h"
#include "gpxlinktype.h"

/**
  * @brief rte represents route - an ordered list of waypoints representing a series of turn points leading to a destination.
  */
class GpxRteType
{
public:
    GpxRteType();
    QString const getName();
    void setName(QString name);
    QString const getCmt();
    void setCmt(QString cmt);
    QString const getDesc();
    void setDesc(QString desc);
    QString const getSrc();
    void setSrc(QString src);
    QList<GpxLinkType*> getLinks();
    void setLinks(QList<GpxLinkType*> links);
    uint const getNumber();
    void setNumber(uint number);
    void setNumber(QString number);
    QString const getType();
    void setType(QString type);
    QList<GpxWptType*> getRtept();
    void setRtept(QList<GpxWptType*> points);
    void addRtept(GpxWptType* pt);

private:
    //GPS name of route.
    QString _name;
    //GPS comment for route.
    QString _cmt;
    //Text description of route for user.  Not sent to GPS.
    QString _desc;
    //Source of data. Included to give user some idea of reliability and accuracy of data.
    QString _src;
    //Links to external information about the route.
    QList<GpxLinkType*> _link;
    //GPS route number.
    uint _number;
    //Type (classification) of route.
    QString _type;
    //    GpxExtensionsType _extensions;
    //A list of route points.
    QList<GpxWptType*> _rtept;
};

#endif // GPXRTETYPE_H
