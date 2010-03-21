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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QMapControl/mapcontrol.h"
#include "QMapControl/mapadapter.h"
#include "QMapControl/maplayer.h"
#include "QMapControl/osmmapadapter.h"
#include "QMapControl/yahoomapadapter.h"
#include "QMapControl/googlesatmapadapter.h"
#include "QMapControl/circlepoint.h"
#include "QMapControl/imagepoint.h"
#include "QMapControl/linestring.h"
#include "QMapControl/geometrylayer.h"

#include "metadatadialog.h"
#include "gpxlatitudetype.h"
#include "gpxwpttype.h"
#include "gpxtype.h"
#include "xmlloader.h"
#include "qwt_plot_curve.h"

#include <QMainWindow>
#include <QDateTime>
#include <QFileDialog>

using namespace qmapcontrol;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    double calculateLength(GpxWptType* from, GpxWptType* to);
    void goToInitialCoordinates();
    QList<QList<Point*> > prepareTrkLine();
    QList<QList<Point*> > prepareRteLine();

protected:
    void changeEvent(QEvent *e);
    void wheelEvent(QWheelEvent *event);
    void resizeEvent (QResizeEvent *event);

private:
    Ui::MainWindow *ui;
    MapControl* mc;
    MapAdapter* mapadapter;
    Layer* l;
    Layer* geom;
    GpxType* gpxFile;
    XmlLoader* xml;
    QProgressBar* loadingProgressBar;

    QAction* osmAction;
    QAction* yahooActionMap;
    QAction* yahooActionSatellite;
    QAction* yahooActionOverlay;
    QAction* googleActionMap;

    QwtPlotCurve *inclineCurve;

    void addZoomButtons();
    void clearWptInfo();

private slots:
    void on_inclineDock_dockLocationChanged(Qt::DockWidgetArea area);
    void on_action_About_triggered();
    void on_action_Close_triggered();
    void on_action_Info_triggered();
    void on_action_Exit_triggered();
    void on_action_Open_triggered();

public slots:
    void mapproviderSelected(QAction*);
    void pointClicked(Geometry  *geometry,QPoint);
    void drawMap();
};

#endif // MAINWINDOW_H
