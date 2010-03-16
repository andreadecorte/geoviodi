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

#ifndef GPXMETADATATYPE_H
#define GPXMETADATATYPE_H
#include <QList>
#include <QDateTime>
#include "gpxlinktype.h"
#include "gpxboundstype.h"
#include "gpxpersontype.h"

/**
  * Information about the GPX file, author, and copyright restrictions goes in the metadata section.  Providing rich,
  * meaningful information about your GPX files allows others to search for and use your GPS data.
*/
class GpxMetadataType
{
public:
    GpxMetadataType();
    QString const getName();
    void setName (QString name);
    QString const getDesc();
    void setDesc (QString desc);
    GpxPersonType* const getAuthor();
    void setAuthor (GpxPersonType* author);
    QDateTime const getTime();
    void setTime (QDateTime time);
    void setTime (QString time);
    GpxBoundsType* const getBounds();
    void setBounds (GpxBoundsType* bounds);
    QString const getKeywords();
    void setKeywords (QString keywords);
    QHash<QString,QString> const getMetadataList();
    QList<GpxLinkType*> getLinks();
    void setLinks(QList<GpxLinkType*> links);


private:
    //The name of the GPX file.
    QString _name;
    //A description of the contents of the GPX file.
    QString _desc;
    //The person or organization who created the GPX file.
    GpxPersonType* _author;
    //Copyright and license information governing use of the file.
    //GpxCopyrightType* _copyright;
    //URLs associated with the location described in the file.
    QList<GpxLinkType*> _link;
    //The creation date of the file.
    QDateTime _time;
    //Keywords associated with the file.  Search engines or databases can use this information to classify the data.
    QString _keywords;
    //Minimum and maximum coordinates which describe the extent of the coordinates in the file.
    GpxBoundsType* _bounds;
    //You can add extend GPX by adding your own elements from another schema here.
    //GpxExtensionsType* _extensions;

};

#endif // GPXMETADATATYPE_H
