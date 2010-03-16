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

#ifndef XMLLOADER_H
#define XMLLOADER_H
#include "gpxtype.h"
#include "gpxwpttype.h"
#include "gpxtrktype.h"
#include "gpxtrksegtype.h"
#include <QString>
#include <QXmlStreamReader>
#include <QFile>
#include <QThread>

class XmlLoader : public QThread
{
    Q_OBJECT

public:
    void run();
    void setFileName (QString fileName);
    QString getFileName ();
    GpxType* getGpx();

private:
    QString _fileName;
    GpxType* _gpxFile;

signals:
    void progress ( int value );
};

#endif // XMLLOADER_H
