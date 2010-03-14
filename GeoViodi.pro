# -------------------------------------------------
# Project created by QtCreator 2010-03-03T16:50:37
# -------------------------------------------------
QT += xml \
    network
TARGET = GeoViodi
TEMPLATE = app
SOURCES += src/main.cpp \
    src/mainwindow.cpp \
    src/gpxlatitudetype.cpp \
    src/gpxlongitudetype.cpp \
    src/gpxdegreestype.cpp \
    src/gpxwpttype.cpp \
    src/gpxtype.cpp \
    src/gpxlinktype.cpp \
    src/gpxtrksegtype.cpp \
    src/gpxtrktype.cpp \
    src/xmlloader.cpp \
    src/gpxmetadatatype.cpp \
    src/gpxboundstype.cpp \
    src/QMapControl/yahoomapadapter.cpp \
    src/QMapControl/wmsmapadapter.cpp \
    src/QMapControl/tilemapadapter.cpp \
    src/QMapControl/point.cpp \
    src/QMapControl/osmmapadapter.cpp \
    src/QMapControl/openaerialmapadapter.cpp \
    src/QMapControl/mapnetwork.cpp \
    src/QMapControl/maplayer.cpp \
    src/QMapControl/mapcontrol.cpp \
    src/QMapControl/mapadapter.cpp \
    src/QMapControl/linestring.cpp \
    src/QMapControl/layermanager.cpp \
    src/QMapControl/layer.cpp \
    src/QMapControl/imagepoint.cpp \
    src/QMapControl/imagemanager.cpp \
    src/QMapControl/gps_position.cpp \
    src/QMapControl/googlesatmapadapter.cpp \
    src/QMapControl/googlemapadapter.cpp \
    src/QMapControl/geometrylayer.cpp \
    src/QMapControl/geometry.cpp \
    src/QMapControl/fixedimageoverlay.cpp \
    src/QMapControl/emptymapadapter.cpp \
    src/QMapControl/curve.cpp \
    src/QMapControl/circlepoint.cpp \
    src/metadatadialog.cpp
HEADERS += src/mainwindow.h \
    src/gpxlatitudetype.h \
    src/gpxlongitudetype.h \
    src/gpxlongitudetype.h \
    src/gpxdegreestype.h \
    src/gpxwpttype.h \
    src/gpxtype.h \
    src/gpxlinktype.h \
    src/gpxtrksegtype.h \
    src/gpxtrktype.h \
    src/xmlloader.h \
    src/gpxmetadatatype.h \
    src/gpxboundstype.h \
    src/QMapControl/yahoomapadapter.h \
    src/QMapControl/wmsmapadapter.h \
    src/QMapControl/tilemapadapter.h \
    src/QMapControl/point.h \
    src/QMapControl/osmmapadapter.h \
    src/QMapControl/openaerialmapadapter.h \
    src/QMapControl/mapnetwork.h \
    src/QMapControl/maplayer.h \
    src/QMapControl/mapcontrol.h \
    src/QMapControl/mapadapter.h \
    src/QMapControl/linestring.h \
    src/QMapControl/layermanager.h \
    src/QMapControl/layer.h \
    src/QMapControl/imagepoint.h \
    src/QMapControl/imagemanager.h \
    src/QMapControl/gps_position.h \
    src/QMapControl/googlesatmapadapter.h \
    src/QMapControl/googlemapadapter.h \
    src/QMapControl/geometrylayer.h \
    src/QMapControl/geometry.h \
    src/QMapControl/fixedimageoverlay.h \
    src/QMapControl/emptymapadapter.h \
    src/QMapControl/curve.h \
    src/QMapControl/circlepoint.h \
    src/metadatadialog.h
FORMS += src/mainwindow.ui \
    src/metadatadialog.ui
OTHER_FILES += bregoli.gpx
