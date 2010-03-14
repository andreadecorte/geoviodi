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

#include "gpxlinktype.h"

GpxLinkType::GpxLinkType()
{
}

QString const GpxLinkType::getText()
{
    return _text;
}

void GpxLinkType::setText(QString text)
{
    _text = text;
}

QString const GpxLinkType::getType()
{
    return _type;
}

void GpxLinkType::setType(QString type)
{
    _type = type;
}

QUrl* const GpxLinkType::getUrl()
{
    return _href;
}

void GpxLinkType::setUrl(QUrl* url)
{
    _href = url;
}
