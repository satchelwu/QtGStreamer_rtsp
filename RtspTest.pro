QT += quick  widgets sql testlib
CONFIG += c++14
CONFIG += link_pkgconfig

#static{
    QTPLUGIN += qtvirtualkeyboardplugin
#}
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QGLIB_HAVE_CXX0X QGST_BIN_ADD_MAX_ARGS QT_DEPRECATED_WARNINGS QT_NO_KEYWORDS

DEFINES *= QT_USE_QSTRINGBUILDER

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Tell qmake to use pkg-config to find QtGStreamer.

# Now tell qmake to link to QtGStreamer and also use its include path and Cflags.
PKGCONFIG += Qt5GStreamerQuick-1.0 opencv4 #glib2.0

#DEFINES *= QT_USE_QSTRINGBUILDER
SOURCES += main.cpp \
    camera.cpp \
#    camerapool.cpp \
#    test.cpp \
#    deepstream_common.c \
#    MainBin.cpp \
#    pipeline.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
PKGCONFIG += Qt5GStreamer-1.0 Qt5GStreamerQuick-1.0 opencv4 #glib2.0

INCLUDEPATH += /opt/nvidia/deepstream/deepstream/sources/includes /usr/include/Qt5GStreamer

LIBS += -L/opt/nvidia/deepstream/deepstream/lib
LIBS += -lglib-2.0 -lgstbase-1.0
LIBS += -lgobject-2.0 -lgstreamer-1.0 -lgstrtspserver-1.0 -lgstrtp-1.0  -lgstrtsp-1.0\
        -lgstvideo-1.0 -lnvbufsurface -lnvds_meta -lnvbufsurftransform \
        -lnvdsgst_meta -lgstrtp-1.0 -lnvds_utils -lnvds_infer -lnvds_osd -lnvds_nvtxhelper -lnvdsgst_helper  \
        -lnvdsgst_smartrecord
        #-lnvdsgstinfer
LIBS += -lopencv_core

HEADERS += \
    camera.h \
#    camerapool.h \
#    test.h \
#    globaldefine.h \
#    deepstream_common.h \
#    MainBin.h \
#    pipeline.h
    globaldefine.h
