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

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionAbout_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    gpxFile = NULL;

    // create MapControl
    mc = new MapControl(QSize(400,300));

    // create MapAdapter to get maps from
    mapadapter = new OSMMapAdapter();

    // create a map layer with the mapadapter
    l = new MapLayer("Map layer", mapadapter);

    // add Layer to the MapControl
    mc->addLayer(l);

    geom = new GeometryLayer("Geometry layer", mapadapter);

    ui->verticalLayout->insertWidget(0, mc, 2);

    //zoom on starting coordinates
    goToInitialCoordinates();

    //show the map scale
    mc->showScale(true);
    addZoomButtons();

    //create menus to choose the map provider
    QActionGroup* mapproviderGroup = new QActionGroup(this);
    osmAction = new QAction(tr("OpenStreetMap"), mapproviderGroup);
    yahooActionMap = new QAction(tr("Yahoo: Map"), mapproviderGroup);
    yahooActionSatellite = new QAction(tr("Yahoo: Satellite"), mapproviderGroup);
    googleActionMap = new QAction(tr("Google: Map"), mapproviderGroup);
    osmAction->setCheckable(true);
    yahooActionMap->setCheckable(true);
    yahooActionSatellite->setCheckable(true);
    //not working at the moment
    googleActionMap->setCheckable(true);
    googleActionMap->setEnabled(false);
    osmAction->setChecked(true);
    connect(mapproviderGroup, SIGNAL(triggered(QAction*)),this, SLOT(mapproviderSelected(QAction*)));

    ui->menu_View->addAction(osmAction);
    ui->menu_View->addAction(yahooActionMap);
    ui->menu_View->addAction(yahooActionSatellite);
    ui->menu_View->addAction(googleActionMap);

    //hides the dock that shows waypoint's properties
    ui->wptDockWidget->hide();

    //disables menu
    ui->action_Info->setEnabled(false);
    ui->action_Close->setEnabled(false);

}

MainWindow::~MainWindow()
{
    delete ui;
    //delete geom;
    delete mapadapter;
    delete mc;
    delete gpxFile;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_action_Open_triggered()
{
    if (gpxFile != NULL)
        on_action_Close_triggered();
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open GPX file"), "", tr("Gpx files (*.gpx)"));
    if (fileName.isEmpty())
        return;
    gpxFile = XmlLoader::loadFromGpx(fileName);
    ui->statusBar->showMessage(fileName + " " + tr("loaded"));

    geom->clearGeometries();

    QList<QList<Point*> > tracks = prepareTrkLine();

    QListIterator<QList<Point*> > i(tracks);
    while (i.hasNext())
    {
        // A QPen also can use transparency
        QPen* linepen = new QPen(QColor((rand()%255), 60, 60, 100)); //randomize red value
        linepen->setWidth(7);
        LineString* line = new LineString(i.next(), "", linepen);
        // Add the LineString to the layer
        geom->addGeometry(line);
    }

    connect(geom, SIGNAL(geometryClicked(Geometry*,QPoint)),this,SLOT(pointClicked(Geometry*,QPoint)));

    QListIterator<GpxWptType*> l(gpxFile->getList());
    while (l.hasNext())
    {
        GpxWptType* current = l.next();
        QString wptCurrentName = "";
        if (!current->getName().isEmpty())
        {
            wptCurrentName = current->getName();
        }
        else
        {
            wptCurrentName.append("No name");
        }
        wptCurrentName.append("???");
        if (!current->getTime().isNull())
            wptCurrentName.append(current->getTime().toString());
        else
        {
            wptCurrentName.append("No");
        }
        wptCurrentName.append("???");
        if (current->getEle() != -10000)
            wptCurrentName.append(QString::number(current->getEle()));
        else
        {
            wptCurrentName.append("No");
        }
        wptCurrentName.append("???");
        if (!current->getDesc().isEmpty())
            wptCurrentName.append(current->getDesc());
        else
        {
            wptCurrentName.append("No");
        }
        wptCurrentName.append("???");
        if (!current->getType().isEmpty())
            wptCurrentName.append(current->getType());
        else
        {
            wptCurrentName.append("No");
        }

        geom->addGeometry(new CirclePoint(current->getLon()->getLongitude(), current->getLat()->getLatitude(), wptCurrentName, Point::Middle));
    }

    mc->addLayer(geom);

    //let's enable the menus
    ui->action_Info->setEnabled(true);
    ui->action_Close->setEnabled(true);

    QList<QPointF> view;
    if (gpxFile->getMetadata()->getBounds() != NULL)
    {
        //without this, the zoom won't be the right one
        mc->setZoom(0);

        view.append(QPointF(gpxFile->getMetadata()->getBounds()->getMinlon()->getLongitude(), gpxFile->getMetadata()->getBounds()->getMinlat()->getLatitude()));
        view.append(QPointF(gpxFile->getMetadata()->getBounds()->getMaxlon()->getLongitude(), gpxFile->getMetadata()->getBounds()->getMaxlat()->getLatitude()));
        mc->setViewAndZoomIn(view);
    }
    else
    {
        //this shouldn't happen, but just in case...
        goToInitialCoordinates();
    }
}

void MainWindow::on_action_Exit_triggered()
{    
    /*QLocale c(QLocale::C);
    QLocale::setDefault(QLocale::Irish);

    qDebug() << c.toDouble(("44.48934600"));
    qDebug() << QString::number(44.48934600,'g',8);*/
    QCoreApplication::exit(0);
}

/** @brief Adds zoom buttons to the main window
  */
void MainWindow::addZoomButtons()
{
    // create buttons as controls for zoom
    QPushButton* zoomin = new QPushButton("+");
    QPushButton* zoomout = new QPushButton("-");
    zoomin->setMaximumWidth(50);
    zoomout->setMaximumWidth(50);

    connect(zoomin, SIGNAL(clicked(bool)),
            mc, SLOT(zoomIn()));
    connect(zoomout, SIGNAL(clicked(bool)),
            mc, SLOT(zoomOut()));

    // add zoom buttons to the layout of the MapControl
    QVBoxLayout* innerlayout = new QVBoxLayout;
    innerlayout->addWidget(zoomin);
    innerlayout->addWidget(zoomout);
    mc->setLayout(innerlayout);
}

/** @brief Reimplements wheel event so we can use mouse wheel to zoom in/out
  */
void MainWindow::wheelEvent(QWheelEvent *event)
{
    //int numDegrees = event->delta() / 8;
    //int numTicks = numDegrees / 15;

    if (event->orientation() == Qt::Horizontal)
    {
        event->ignore();
    } else
    {
        if (event->delta() > 0)
            mc->zoomIn();
        else
        {
            mc->zoomOut();
        }
    }
}

void MainWindow::resizeEvent ( QResizeEvent * event )
{
    mc->resize(event->size());
}

void MainWindow::on_action_Info_triggered()
{
    MetadataDialog* metadataDiag = new MetadataDialog();
    metadataDiag->setWindowTitle(tr("File information"));
    metadataDiag->populate(gpxFile);
    metadataDiag->show();
}

void MainWindow::on_action_Close_triggered()
{
    if (gpxFile == NULL)
        return;
    delete gpxFile;
    geom->clearGeometries();
    ui->statusBar->clearMessage();
    ui->action_Close->setEnabled(false);
    ui->action_Info->setEnabled(false);
    gpxFile = NULL;
    goToInitialCoordinates();
    return;
}

void MainWindow::goToInitialCoordinates()
{
    mc->setZoom(0);
    QList<QPointF> view;
    //we have to put 2 different points
    view.append(QPointF(11.309925, 44.495541));
    view.append(QPointF(11.509925, 44.495541));
    mc->setViewAndZoomIn(view);
    //repaint otherwise the map won't be updated
    mc->repaint();
}


void MainWindow::mapproviderSelected(QAction* action)
{
    if (action == osmAction)
    {
        int zoom = mapadapter->adaptedZoom();
        mc->setZoom(0);

        mapadapter = new OSMMapAdapter();
        l->setMapAdapter(mapadapter);
        geom->setMapAdapter(mapadapter);

        mc->updateRequestNew();
        mc->setZoom(zoom);

    } else if (action == yahooActionMap)
    {
        int zoom = mapadapter->adaptedZoom();
        mc->setZoom(0);

        mapadapter = new YahooMapAdapter();
        l->setMapAdapter(mapadapter);
        geom->setMapAdapter(mapadapter);

        mc->updateRequestNew();
        mc->setZoom(zoom);

    } else if (action == yahooActionSatellite)
    {
        int zoom = mapadapter->adaptedZoom();
        QPointF a = mc->currentCoordinate();
        mc->setZoom(0);

        mapadapter = new YahooMapAdapter("us.maps3.yimg.com", "/aerial.maps.yimg.com/png?v=1.7&t=a&s=256&x=%2&y=%3&z=%1");
        l->setMapAdapter(mapadapter);
        geom->setMapAdapter(mapadapter);

        mc->updateRequestNew();
        mc->setZoom(zoom);

    } else if (action == googleActionMap)
    {
        int zoom = mapadapter->adaptedZoom();
        mc->setZoom(0);
        mapadapter = new GoogleSatMapAdapter();
        l->setMapAdapter(mapadapter);
        geom->setMapAdapter(mapadapter);
        mc->updateRequestNew();
        mc->setZoom(zoom);
    }
}

void MainWindow::pointClicked(Geometry *geometry,QPoint)
{
    if (ui->wptDockWidget->isHidden())
        ui->wptDockWidget->show();
    //qDebug() << "parent: " << geometry->parentGeometry();
    //qDebug() << "Element clicked: " << geometry->name();
    QList< Point  * > list = geometry->points();
    QListIterator<Point*> i(list);
    while (i.hasNext())
    {
        Point* current = i.next();

        //populate info dock
        QStringList list = current->name().split("???");
        ui->lbl_Name->setText(list.at(0));
        ui->lbl_Type->setText(geometry->GeometryType);
        ui->lbl_X->setText(QString::number(current->longitude()));
        ui->lbl_Y->setText(QString::number(current->latitude()));
        ui->lbl_Time->setText(list.at(1));
        ui->lbl_Ele->setText(list.at(2));
        ui->lbl_Desc->setText(list.at(3));
        ui->lbl_Type->setText(list.at(4));
    }
}

QList<QList<Point*> > MainWindow::prepareTrkLine()
{
    //we need a nested list since we could have more tracks in a single gpx file
    QList<QList<Point*> > tracks;

    int trkCounter = 0;

    //needs this to calculate the bounds
    double minLat = -180.0;
    double maxLat = 180.0;
    double minLon = -180.0;
    double maxLon = 180.0;
    bool boundsCalc = false;
    if (gpxFile->getMetadata()->getBounds() == NULL)
        boundsCalc = true;

    GpxWptType* previousWpt = NULL;
    double length = 0;

    QListIterator<GpxTrkType*> i(gpxFile->getTrkList());
    while (i.hasNext())
    {
        trkCounter++;
        QList<Point*> points;
        QListIterator<GpxTrksegType*> j((i.next())->getTrksegType());
        while (j.hasNext())
        {
            QListIterator<GpxWptType*> k((j.next())->getTrkpt());
            GpxWptType* currentWpt;
            while (k.hasNext()) {
                //qDebug() << counter++;
                currentWpt = k.next();
                if (boundsCalc)
                {
                    if (currentWpt->getLon()->getLongitude() > minLon)
                        minLon = currentWpt->getLon()->getLongitude();
                    if (currentWpt->getLon()->getLongitude() < maxLon)
                        maxLon = currentWpt->getLon()->getLongitude();
                    if (currentWpt->getLat()->getLatitude() > minLat)
                        minLat = currentWpt->getLat()->getLatitude();
                    if (currentWpt->getLat()->getLatitude() < maxLat)
                        maxLat = currentWpt->getLat()->getLatitude();
                }

                //if (tempWpt == NULL || tempWpt->getLon() == NULL)
                //    break;
                if (previousWpt != NULL)
                {
                    length += calculateLength(previousWpt, currentWpt);
                }
                QString wptName = "";
                if (!currentWpt->getName().isNull())
                {
                    wptName = currentWpt->getName();
                }
                points.append(new Point(currentWpt->getLon()->getLongitude(), currentWpt->getLat()->getLatitude(), wptName, Point::BottomLeft));
                previousWpt = currentWpt;
            }
        }
        tracks.append(points);
    }

    qDebug() << "lunghezza percorso " << length;
    qDebug() << "numero tracce " << trkCounter;
    if (boundsCalc)
    {
        gpxFile->getMetadata()->setBounds(new GpxBoundsType(minLon, maxLon, minLat, maxLat));
    }

    return tracks;
}

/** @brief Computes the arc, in radian, between two WGS-84 positions.
*
* The result is equal to <code>Distance(from,to)/EARTH_RADIUS_IN_METERS</code>
*    <code>= 2*asin(sqrt(h(d/EARTH_RADIUS_IN_METERS )))</code>
*
* where:<ul>
*    <li>d is the distance in meters between 'from' and 'to' positions.</li>
*    <li>h is the haversine function: <code>h(x)=sin²(x/2)</code></li>
* </ul>
*
* The haversine formula gives:
*    <code>h(d/R) = h(from.lat-to.lat)+h(from.lon-to.lon)+cos(from.lat)*cos(to.lat)</code>
*
* @sa http://en.wikipedia.org/wiki/Law_of_haversines
*/

double MainWindow::calculateLength(GpxWptType* from, GpxWptType* to)
{
    /// @brief The usual PI/180 constant
    static const double DEG_TO_RAD = 0.017453292519943295769236907684886;
    /// @brief Earth's quatratic mean radius for WGS-84
    static const double EARTH_RADIUS_IN_METERS = 6372797.560856;

    double latitudeArc  = (from->getLat()->getLatitude() - to->getLat()->getLatitude()) * DEG_TO_RAD;
    double longitudeArc = (from->getLon()->getLongitude() - to->getLon()->getLongitude()) * DEG_TO_RAD;
    double latitudeH = sin(latitudeArc * 0.5);
    latitudeH *= latitudeH;
    double lontitudeH = sin(longitudeArc * 0.5);
    lontitudeH *= lontitudeH;
    double tmp = cos(from->getLat()->getLatitude()*DEG_TO_RAD) * cos(to->getLat()->getLatitude()*DEG_TO_RAD);
    return (EARTH_RADIUS_IN_METERS * 2.0 * asin(sqrt(latitudeH + tmp*lontitudeH)));
}


void MainWindow::on_action_About_triggered()
{
    QMessageBox::about(this, tr("About GeoViodi"), tr("<b>GeoViodi</b> © 2010 Andrea \"Klenje\" Decorte<br />Version 0.01<br /><br /><a href=\"http://code.google.com/p/geoviodi\">Home page</a><br /><br />Thanks to <i>ildiavolo</i> for testing and ideas."));
}
