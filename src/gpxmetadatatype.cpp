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
* Created 05/03/2010
*/

#include "gpxmetadatatype.h"

GpxMetadataType::GpxMetadataType()
{
    _bounds = NULL;
}

QString const GpxMetadataType::getName()
{
    return _name;
}

void GpxMetadataType::setName(QString name)
{
    _name = name;
}

QString const GpxMetadataType::getDesc()
{
    return _desc;
}

void GpxMetadataType::setDesc(QString desc)
{
    _desc = desc;
}

QString const GpxMetadataType::getAuthor()
{
    return _author;
}

void GpxMetadataType::setAuthor(QString author)
{
    _author = author;
}

QDateTime const GpxMetadataType::getTime()
{
    return _time;
}

void GpxMetadataType::setTime(QDateTime time)
{
    _time = time;
}

void GpxMetadataType::setTime(QString time)
{
    //check
    QDateTime dateTime = QDateTime::fromString(time,
                                               "yyyy-MM-ddThh:mm:ssZ");
    _time = dateTime;
}

GpxBoundsType* const GpxMetadataType::getBounds()
{
    return _bounds;
}

void GpxMetadataType::setBounds(GpxBoundsType *bounds)
{
    _bounds = bounds;
}

QString const GpxMetadataType::getKeywords()
{
    return _keywords;
}

void GpxMetadataType::setKeywords(QString keywords)
{
    _keywords = keywords;
}

QHash<QString,QString> const GpxMetadataType::getMetadataList()
{
    QHash<QString,QString> dict;
    if (!_name.isEmpty())
        dict.insert("Name", _name);
    if (!_desc.isEmpty())
        dict.insert("Description", _desc);
    if (!_author.isEmpty())
        dict.insert("Author", _author);
    if (!_time.isNull())
        dict.insert("Date", _time.toString());
    if (!_keywords.isNull())
        dict.insert("Keywords", _keywords);
    if (_bounds != NULL)
    {
        dict.insert("Bounds min lat", QString::number(_bounds->getMinlat()->getLatitude()));
        //qDebug() << getBounds()->getMinlat()->getLatitude();
        dict.insert("Bounds max lat", QString::number(_bounds->getMaxlat()->getLatitude()));
        dict.insert("Bounds min lon", QString::number(_bounds->getMinlon()->getLongitude()));
        dict.insert("Bounds max lon", QString::number(_bounds->getMaxlon()->getLongitude()));
    }
    if (!_link.isEmpty())
    {
        QListIterator<GpxLinkType*> k(_link);
        while (k.hasNext()) {
            GpxLinkType* current = k.next();
            QString key = QString().append(current->getText()).append(" (").append(current->getUrl()->toString()).append(" )");
            dict.insert("Link", key);
        }
    }
    return dict;
}

QList<GpxLinkType*> GpxMetadataType::getLinks()
{
    return _link;
}

void GpxMetadataType::setLinks(QList<GpxLinkType*> links)
{
    _link = links;
}
