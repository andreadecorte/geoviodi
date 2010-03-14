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
* Created 04/03/2010
*/

#include "xmlloader.h"

namespace XmlLoader
{
    GpxType* loadFromGpx(QString fileName)
    {
        /*
>From your separate thread, post an even to a listening object or emit a signal
>that contains the progress information. The main thread will receive that
>signal or event and will then update the progress bar.
>
>Since QProgressBar::setValue is a slot, you can connect your signal directly
>to it. Make sure the signal delivery is happening via a queued connection
>(the default settings for QObject::connect() will do that).
>
*/
        GpxType* gpx = new GpxType;
        GpxTrksegType* trkseg;
        GpxTrkType* trk;
        QXmlStreamReader reader;
        QFile file(fileName);
        if (!file.open(QFile::ReadOnly | QFile::Text)) {
            qDebug() << "Error: Cannot read file " << qPrintable(fileName)
                    << ": " << qPrintable(file.errorString());
            return false;
        }
        reader.setDevice(&file);

        GpxMetadataType* metadata = new GpxMetadataType;
        QList<GpxLinkType*> links;

        while (!reader.atEnd()) {
            reader.readNext();
            if (reader.tokenType() == QXmlStreamReader::StartDocument)
                qDebug() << reader.documentVersion();
            else if (reader.tokenType() == QXmlStreamReader::StartElement)
            {
                //let's read metadata and related stuff
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
                                    metadata->setAuthor(reader.readElementText());
                                reader.readNext();
                            }
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
                                qDebug() << "test bound" << metadata->getBounds()->getMinlat()->getLatitude();
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
                if (reader.name() == "name")
                    metadata->setName(reader.readElementText());
                if (reader.name() == "desc")
                    metadata->setDesc(reader.readElementText());
                if (reader.name() == "gpx")
                {
                    gpx->setCreator(reader.attributes().value("creator").toString());
                    gpx->setVersion(reader.attributes().value("version").toString());
                }
                //let's read a waypoint
                if (reader.name() == "wpt")
                {
                    GpxWptType* wpt = new GpxWptType;
                    wpt->setLatLon(reader.attributes().value("lat").toString(), reader.attributes().value("lon").toString());
                    while (!(reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "wpt"))
                    {
                        if (reader.name() == "name")
                        {
                            wpt->setName(reader.readElementText());
                        }
                        if (reader.name() == "cmt")
                        {
                            wpt->setCmt(reader.readElementText());
                        }
                        if (reader.name() == "sym")
                            wpt->setSym(reader.readElementText());
                        if (reader.name() == "time")
                        {
                            wpt->setTime(reader.readElementText());
                        }
                        reader.readNext();
                    }
                    gpx->addWpt(wpt);
                    qDebug() << "Aggiunto punto";
                }
                //let's read a track
                if (reader.name() == "trk")
                {
                    trk = new GpxTrkType;
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
                                        if (reader.name() == "ele") {
                                            trkpt->setEle(reader.readElementText());
                                        }
                                        //reader.readNext();
                                        if (reader.name() == "time")
                                            trkpt->setTime(reader.readElementText());
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
                    //not implemented yet
                }
            }

            //if we read another kind of node, do nothing
            else {
                //qDebug() << reader.name();
            }
        }

        metadata->setLinks(links);
        gpx->setMetadata(metadata);
        file.close();
        qDebug() << "File closed";
        //nooooon eliminare!
        //delete trk;
        //delete trkseg;
        //delete metadata;
        return gpx;
    }
};
