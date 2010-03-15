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
* Created 08/03/2010
*/

#include "metadatadialog.h"
#include "ui_metadatadialog.h"

MetadataDialog::MetadataDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::MetadataDialog)
{
    ui->setupUi(this);

}

MetadataDialog::~MetadataDialog()
{
    delete ui;
}

void MetadataDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MetadataDialog::populate(GpxType *gpx)
{
    if (gpx == NULL)
        return;
    QHash<QString, QString> hash = gpx->getMetadata()->getMetadataList();
    int row = 0;
    //adding two more tags that we can found outside metadata...still interesting though
    if (!(gpx->getCreator().isNull()))
    {
        hash.insert("Creator",gpx->getCreator());
    }
    if (!(gpx->getVersion().isNull())) {
        hash.insert("Version",gpx->getVersion());
    }
    ui->tableWidget->setRowCount(hash.count());
    ui->tableWidget->setColumnCount(2);

    QHashIterator<QString, QString> i(hash);
    while (i.hasNext()) {
        i.next();
        //loads values from hash
        QTableWidgetItem* item1 = new QTableWidgetItem(i.key());
        QTableWidgetItem* item2 = new QTableWidgetItem(i.value());

        //set the values as read only
        item1->setFlags(Qt::ItemIsSelectable);
        item2->setFlags(Qt::ItemIsSelectable);

        //adds items to table widget
        ui->tableWidget->setItem(row,0,item1);
        ui->tableWidget->setItem(row,1,item2);
        row++;
    }

    QStringList labels;
    labels << tr("Property") << tr("Value");
    ui->tableWidget->setHorizontalHeaderLabels(labels);
    ui->tableWidget -> horizontalHeader() -> resizeSections(QHeaderView::ResizeToContents);
}
