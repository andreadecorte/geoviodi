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
* Created 04/03/2010
*/

#include "xmlloader.h"

void XmlLoader::run()
{
    emit progress(0);

    GpxType* gpx = new GpxType;
    GpxTrksegType* trkseg;
    GpxTrkTypeExtended* trk;
    QFile file(_fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Error: Cannot read file " << qPrintable(_fileName)
                << ": " << qPrintable(file.errorString());
        return;
    }
    reader.setDevice(&file);

    GpxMetadataType* metadata = new GpxMetadataType;
    QList<GpxLinkType*> links;
    GpxPersonType* author = new GpxPersonType;

    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.tokenType() == QXmlStreamReader::StartDocument)
            ;
        else if (reader.tokenType() == QXmlStreamReader::StartElement)
        {
            //main gpx tag
            if (reader.name() == "gpx")
            {
                gpx->setCreator(reader.attributes().value("creator").toString());
                //this is particularly interesting
                gpx->setVersion(reader.attributes().value("version").toString());
            }
            //let's read metadata and related stuff
            if (gpx->getVersion() == "1.1")
            {
                //only gpx version 1.1 has metadata tag
                if (reader.name() == "metadata")
                {
                    while (!(reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "metadata"))
                    {
                        if (reader.name() == "name") {
                            metadata->setName(reader.readElementText());
                        }
                        if (reader.name() == "desc")
                        {
                            metadata->setDesc(reader.readElementText());
                        }
                        if (reader.name() == "time")
                            metadata->setTime(reader.readElementText());
                        if (reader.name() == "author")
                        {
                            while (!(reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "author"))
                            {
                                if (reader.name() == "name")
                                    author->setName(reader.readElementText());
                                if (reader.name() == "email")
                                {
                                    QString id, domain;
                                    while (!(reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "email"))
                                    {
                                        if (reader.name() == "id")
                                            id = reader.readElementText();
                                        if (reader.name() == "domain")
                                            domain = reader.readElementText();
                                        reader.readNext();
                                    }
                                    author->setEmail(id, domain);
                                }
                                if (reader.name() == "link")
                                {
                                    GpxLinkType* link = new GpxLinkType;
                                    while (!(reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "link"))
                                    {
                                        if (!reader.attributes().value("href").toString().isEmpty())
                                            link->setUrl(new QUrl(reader.attributes().value("href").toString()));
                                        if (reader.name() == "text") {
                                            link->setText(reader.readElementText());
                                        }
                                        if (reader.name() == "type") {
                                            link->setType(reader.readElementText());
                                        }
                                        reader.readNext();
                                    }
                                    author->setLink(link);
                                }
                                reader.readNext();
                            }
                            metadata->setAuthor(author);
                        }
                        if (reader.name() == "time")
                            metadata->setTime(reader.readElementText());
                        if (reader.name() == "bounds")
                        {
                            if (!reader.attributes().value("maxlat").toString().isEmpty())
                            {
                                GpxBoundsType* bounds = new GpxBoundsType;
                                bounds->setMaxlat(new GpxLatitudeType(reader.attributes().value("maxlat").toString()));
                                bounds->setMinlat(new GpxLatitudeType(reader.attributes().value("minlat").toString()));
                                bounds->setMaxlon(new GpxLongitudeType(reader.attributes().value("maxlon").toString()));
                                bounds->setMinlon(new GpxLongitudeType(reader.attributes().value("minlon").toString()));
                                metadata->setBounds(bounds);
                            }
                        }
                        if (reader.name() == "link")
                        {
                            GpxLinkType* link = new GpxLinkType;
                            while (!(reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "link"))
                            {
                                if (!reader.attributes().value("href").toString().isEmpty())
                                    link->setUrl(new QUrl(reader.attributes().value("href").toString()));
                                if (reader.name() == "text") {
                                    link->setText(reader.readElementText());
                                }
                                if (reader.name() == "type") {
                                    link->setType(reader.readElementText());
                                }
                                reader.readNext();
                            }
                            links.append(link);
                        }
                        if (reader.name() == "keywords")
                        {
                            metadata->setKeywords(reader.readElementText());
                        }

                        reader.readNext();
                    }
                }
            }
            if (gpx->getVersion() == "1.0")
            {
                GpxPersonType* author = new GpxPersonType;
                QUrl* url;
                QString urlname, email;
                //gpx version 1.0 has top level tags for metadata info
                //we store them in gpxmetadatatype class anyway
                if (reader.name() == "name")
                    metadata->setName(reader.readElementText());
                if (reader.name() == "desc")
                    metadata->setDesc(reader.readElementText());
                if (reader.name() == "time")
                    metadata->setTime(reader.readElementText());
                if (reader.name() == "author")
                    author->setName(reader.readElementText());
                if (reader.name() == "email")
                    email = reader.readElementText();
                if (reader.name() == "bounds")
                {
                    if (!reader.attributes().value("maxlat").toString().isEmpty())
                    {
                        GpxBoundsType* bounds = new GpxBoundsType;
                        bounds->setMaxlat(new GpxLatitudeType(reader.attributes().value("maxlat").toString()));
                        bounds->setMinlat(new GpxLatitudeType(reader.attributes().value("minlat").toString()));
                        bounds->setMaxlon(new GpxLongitudeType(reader.attributes().value("maxlon").toString()));
                        bounds->setMinlon(new GpxLongitudeType(reader.attributes().value("minlon").toString()));
                        metadata->setBounds(bounds);
                    }
                }
                if (reader.name() == "keywords")
                    metadata->setKeywords(reader.readElementText());
                if (reader.name() == "url")
                {
                    url = new QUrl(reader.readElementText());
                }
                if (reader.name() == "urlname")
                {
                    urlname = reader.readElementText();
                }
                //TODO find a better way to use url and urlname
                links.append(new GpxLinkType(urlname, url));

                //if email is not empty, add it to the author class
                if (!email.isEmpty())
                    author->setEmail(email);

                //then if the author is not empty, we add it to metadata
                if (!author->getName().isEmpty())
                    metadata->setAuthor(author);
            }

            //let's read a waypoint
            if (reader.name() == "wpt")
            {
                GpxWptType* wpt = new GpxWptType;
                wpt->setLatLon(reader.attributes().value("lat").toString(), reader.attributes().value("lon").toString());
                while (!(reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "wpt"))
                {
                    readWpt(wpt);
                    reader.readNext();
                }
                gpx->addWpt(wpt);
                qDebug() << "Aggiunto punto" << wpt->getName();
            }
            //let's read a track
            if (reader.name() == "trk")
            {
                trk = new GpxTrkTypeExtended;
                reader.readNext();
                while (!(reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "trk"))
                {
                    if (reader.name() == "name") {
                        trk->setName(reader.readElementText());
                    }
                    if (reader.name() == "number")
                        trk->setNumber(reader.readElementText().toUInt());
                    if (reader.name() == "trkseg")
                    {
                        trkseg = new GpxTrksegType;
                        GpxWptType* trkpt;
                        while (!(reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "trkseg"))
                        {
                            if (reader.name() == "trkpt")
                            {
                                //inizialitize trkpt otherwise we'll get always the same value
                                trkpt = new GpxWptType;
                                trkpt->setLatLon(reader.attributes().value("lat").toString(), reader.attributes().value("lon").toString());
                                //reader.readNext();
                                while (!(reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "trkpt"))
                                {
                                    readWpt(trkpt);
                                    reader.readNext();
                                }
                                trkseg->addTrkpt(trkpt);
                            }
                            reader.readNext();
                        }
                        trk->addTrksegType(trkseg);
                    }
                    reader.readNext();
                }
                gpx->addTrk(trk);
            }

            //let's read a route
            if (reader.name() == "rte")
            {
                GpxRteType* rte = new GpxRteType;
                reader.readNext();
                while (!(reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "rte"))
                {
                    if (reader.name() == "name")
                        rte->setName(reader.readElementText());
                    if (reader.name() == "cmt")
                        rte->setCmt(reader.readElementText());
                    if (reader.name() == "desc")
                        rte->setDesc(reader.readElementText());
                    if (reader.name() == "src")
                        rte->setSrc(reader.readElementText());
                    if (reader.name() == "type")
                        rte->setType(reader.readElementText());
                    if (reader.name() == "link")
                    {
                        GpxLinkType* link = new GpxLinkType;
                        while (!(reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "link"))
                        {
                            if (!reader.attributes().value("href").toString().isEmpty())
                                link->setUrl(new QUrl(reader.attributes().value("href").toString()));
                            if (reader.name() == "text") {
                                link->setText(reader.readElementText());
                            }
                            if (reader.name() == "type") {
                                link->setType(reader.readElementText());
                            }
                            reader.readNext();
                        }
                        rte->getLinks().append(link);
                    }
                    if (reader.name() == "number")
                        rte->setNumber(reader.readElementText());
                    if (reader.name() == "rtept")
                    {
                        //inizialitize rtept otherwise we'll get always the same value
                        GpxWptType* rtept = new GpxWptType;
                        rtept->setLatLon(reader.attributes().value("lat").toString(), reader.attributes().value("lon").toString());
                        while (!(reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "rtept"))
                        {
                            readWpt(rtept);
                            reader.readNext();
                        }
                        rte->addRtept(rtept);
                    }
                    reader.readNext();
                }
                gpx->addRte(rte);
                qDebug() << rte->getName() << rte->getRtept().length();
            }
        }

        //if we read another kind of node, do nothing
        else {
            //qDebug() << reader.name();
        }
    }
    emit progress(50);
    metadata->setLinks(links);
    gpx->setMetadata(metadata);
    file.close();
    qDebug() << "File closed";
    //nooooon eliminare!
    //delete trk;
    //delete trkseg;
    //delete metadata;

    _gpxFile = gpx;
    return;
}

//includes code for reading a waypoint, since it's used more times
void XmlLoader::readWpt(GpxWptType* wpt)
{
    if (reader.name() == "name")
        wpt->setName(reader.readElementText());
    if (reader.name() == "cmt")
        wpt->setCmt(reader.readElementText());
    if (reader.name() == "sym")
        wpt->setSym(reader.readElementText());
    if (reader.name() == "time")
        wpt->setTime(reader.readElementText());
    if (reader.name() == "ele")
        wpt->setEle(reader.readElementText());
    if (reader.name() == "desc")
        wpt->setDesc(reader.readElementText());
    if (reader.name() == "type")
        wpt->setType(reader.readElementText());
    if (reader.name() == "fix")
        wpt->setFix(reader.readElementText());
    if (reader.name() == "geoidheight")
        wpt->setGeoidheight(reader.readElementText());
    if (reader.name() == "hdop")
        wpt->setHdop(reader.readElementText());
    if (reader.name() == "vdop")
        wpt->setVdop(reader.readElementText());
    if (reader.name() == "pdop")
        wpt->setPdop(reader.readElementText());
    if (reader.name() == "sat")
        wpt->setSat(reader.readElementText());
    if (reader.name() == "ageofdgpsdata")
        wpt->setAgeOfGpsData(reader.readElementText());
}

void XmlLoader::setFileName(QString fileName)
{
    _fileName = fileName;
}

GpxType* XmlLoader::getGpx()
{
    return _gpxFile;
}

QString XmlLoader::getFileName()
{
    return _fileName;
}
