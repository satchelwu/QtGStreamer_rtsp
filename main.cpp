#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "camera.h"
#include <QGst/Init>
#include <gst/gst.h>
#include <QQuickView>
#include <QGst/Quick/VideoSurface>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    g_setenv("GST_DEBUG_DUMP_DOT_DIR", "/home/satchel/pipelines", TRUE);

    QGst::init(&argc, &argv);
    qmlRegisterType<QGst::Quick::VideoSurface>();
    Camera* camera = new Camera(&app);


//    QQmlApplicationEngine engine;
    QQuickView view;
    view.rootContext()->setContextProperty("id_camera", camera);
    view.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    camera->SetRtspAddress("rtsp://localhost:8554/ds-test");

//    if (engine.rootObjects().isEmpty())
//        return -1;
    view.resize(640, 480);
    view.show();
    return app.exec();
}

#if 0
static void on_pad_added (GstElement *element, GstPad *pad, gpointer data)
{
    GstPad *sinkpad;
    GstElement *decoder = (GstElement *) data;
    /* We can now link this pad with the rtsp-decoder sink pad */
    g_print ("Dynamic pad created, linking source/demuxer\n");
    sinkpad = gst_element_get_static_pad (decoder, "sink");
    gst_pad_link (pad, sinkpad);
    gst_object_unref (sinkpad);
}

static void cb_new_rtspsrc_pad(GstElement *element, GstPad*pad, gpointer data)
{
    gchar *name;
    GstCaps * p_caps;
    gchar * description;
    GstElement *p_rtph264depay;

     name = gst_pad_get_name(pad);
    g_print("A new pad %s was created\n", name);

    // here, you would setup a new pad link for the newly created pad
    // sooo, now find that rtph264depay is needed and link them?
     p_caps = gst_pad_get_pad_template_caps (pad);

     description = gst_caps_to_string(p_caps);
    printf("%s\n", p_caps, ", ", description,"\n");
    g_free(description);

     p_rtph264depay = GST_ELEMENT(data);

    // try to link the pads then ...
    if (!gst_element_link_pads(element, name, p_rtph264depay, "sink"))
    {
        printf("Failed to link elements 3\n");
    }

    g_free(name);
}


int main(int argc, char *argv[])
{
    /* Initialize GStreamer */
    gst_init(NULL, NULL);

    /* Build Pipeline */
    auto pipeline = gst_pipeline_new("CSDN");

    auto source    = gst_element_factory_make ( "rtspsrc", "source");
    g_object_set (G_OBJECT (source), "latency", 2000, NULL);
    auto rtppay    = gst_element_factory_make ( "rtph264depay", "depayl");
    auto parse     = gst_element_factory_make ( "h264parse",    "parse");
    auto decodebin = gst_element_factory_make ( "openh264dec",  "decode");
    auto sink      = gst_element_factory_make ( "xvimagesink", "sink");

    g_object_set (G_OBJECT (sink), "sync", FALSE, NULL);

    //create_uri(url,url_size, ip_address, port);
    g_object_set(GST_OBJECT(source), "location", "rtsp://localhost:8554/ds-test", NULL);
    //"rtsp://<ip>:554/live/ch00_0"

    //无必要
    auto filter1    = gst_element_factory_make("capsfilter", "filter");
    auto filtercaps = gst_caps_from_string("application/x-rtp");
    g_object_set (G_OBJECT (filter1), "caps", filtercaps, NULL);
    gst_caps_unref(filtercaps);

    gst_bin_add_many (GST_BIN (pipeline), source, rtppay, NULL);
    // listen for newly created pads
    g_signal_connect(source, "pad-added", G_CALLBACK(cb_new_rtspsrc_pad), rtppay);
    gst_bin_add_many (GST_BIN (pipeline), parse,NULL);
    if (!gst_element_link(rtppay, parse))
    {
        printf("\nNOPE\n");
    }

    gst_bin_add_many (GST_BIN (pipeline), decodebin, sink, NULL);

    if (!gst_element_link_many(parse, decodebin, sink, NULL))
    {
        printf("\nFailed to link parse to sink");
    }

    //不是必须
    //g_signal_connect(rtppay, "pad-added", G_CALLBACK(on_pad_added), parse);

    gst_element_set_state (pipeline, GST_STATE_PLAYING);

//    GstBus* bus = gst_element_get_bus(pipeline);
//    GstMessage* msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE, (GstMessageType)(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));
//    if (msg != NULL)
//    {
//        gst_message_unref(msg);
//    }
//    gst_object_unref (bus);

    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);


}

#endif
