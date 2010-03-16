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

#ifndef GPXLINKTYPE_H
#define GPXLINKTYPE_H
#include <QString>
#include <QUrl>

/**
 * A link to an external resource (Web page, digital photo, video clip, etc) with additional information.
*/
class GpxLinkType
{
public:
    GpxLinkType();
    QString const getText();
    void setText (QString text);
    QString const getType();
    void setType (QString type);
    QUrl* const getUrl();
    void setUrl (QUrl* url);

private:
    //Text of hyperlink.
    QString _text;
    //Mime type of content (image/jpeg)
    QString _type;
    // URL of hyperlink.
    QUrl* _href;
};

#endif // GPXLINKTYPE_H
