#include "camera.h"
#include <QGst/ElementFactory>
#include <QGlib/Connect>
#include <QGst/Bus>
#include <gst/gst.h>
#include <QGst/Structure>
#include <QGst/Message>
#include "globaldefine.h"
#include <QGst/Quick/VideoSurface>


Camera::Camera(QObject *parent) : QObject(parent)
{

    //    m_pipeline = QGst::Pipeline::create();
    //    m_pipeline->setState(QGst::StatePlaying);
    m_watchStatusTimer.setInterval(20);
    m_watchStatusTimer.setSingleShot(false);
    m_pipeline = QGst::Pipeline::create();
    m_rtspsrc = QGst::ElementFactory::make(GStreamer::Plugin::rtspsrc);
    m_rtspsrc->setProperty(GStreamer::rtspsrc::LATENCY, 10);
    m_rtspsrc->setProperty(GStreamer::rtspsrc::DROP_ON_LATENCY, true);
    m_decodebin = QGst::ElementFactory::make(GStreamer::Plugin::decodebin);
    m_queue = QGst::ElementFactory::make(GStreamer::Plugin::queue);
#ifdef __aarch64__
    m_videoconvert = QGst::ElementFactory::make(GStreamer::Plugin::nvvideoconvert);
#else
    m_videoconvert = QGst::ElementFactory::make(GStreamer::Plugin::videoconvert);
#endif
    m_pVideoSurface = new QGst::Quick::VideoSurface(this);
    m_qtquick2videosink = m_pVideoSurface->videoSink();
    m_qtquick2videosink->setProperty(GStreamer::qtquick2videosink::SYNC, false);
    m_qtquick2videosink->setProperty(GStreamer::qtquick2videosink::ASYNC, false);
    m_qtquick2videosink->setProperty(GStreamer::qtquick2videosink::FORCE_ASPECT_RATIO, true);

    m_pipeline->add(m_rtspsrc, m_decodebin, m_queue, m_videoconvert, m_qtquick2videosink);
    bool b = QGst::Element::linkMany(m_queue, m_videoconvert, m_qtquick2videosink);
    if(!b)
    {
        qDebug() << "link failed";
    }

    QGst::PadPtr queueSinkPad = m_queue->getStaticPad(GStreamer::SINK);
        m_queueSinkPadProbeId = gst_pad_add_probe((GstPad*)queueSinkPad, GST_PAD_PROBE_TYPE_BUFFER, &Camera::QueueSinkPadProbeFunc, this, nullptr);

#if 1
    QGlib::connect(m_decodebin, "pad-added", this, &Camera::OnDecodebinPadAdded);
    QGlib::connect(m_decodebin, "pad-removed", this, &Camera::OnDecodebinPadRemoved);

    QGlib::connect(m_rtspsrc, "pad-added", this, &Camera::OnRtspsrcPadAdded);
    QGlib::connect(m_rtspsrc, "pad-removed", this, &Camera::onRtspsrcPadRemoved);
    QGlib::connect(m_rtspsrc, "select-stream", this, &Camera::OnRtspsrcSelectStream);
#endif
    QGst::BusPtr bus = m_pipeline->bus();
    bus->addSignalWatch();


    QGlib::connect(bus, "message", this, &Camera::OnBusMessage);
    m_pipeline->setState(QGst::StatePlaying);
    m_watchStatusTimer.start();

}

Camera::~Camera()
{
    m_watchStatusTimer.stop();
    QGst::PadPtr queueSinkPad = m_queue->getStaticPad(GStreamer::SINK);
    gst_pad_remove_probe((GstPad*)queueSinkPad, m_queueSinkPadProbeId);
    if(!m_pipeline.isNull())
    {
        m_pipeline->setState(QGst::StateNull);
    }
//    if(m_pVideoSurface)
//    {
//        delete m_pVideoSurface;
//        m_pVideoSurface = nullptr;
//    }
}

void Camera::SetRtspAddress(const QString& strRtspAddress)
{
    m_rtspsrc->setState(QGst::StateNull);
    m_rtspsrc->setProperty("location", strRtspAddress);

    m_rtspsrc->syncStateWithParent();
//    m_pipeline->setState(QGst::StatePlaying);
    //    m_rtspsrc->setState(QGst::StatePlaying);
}

QGst::Quick::VideoSurface* Camera::VideoSurface()
{
    return m_pVideoSurface;
}


bool Camera::OnRtspsrcSelectStream(int num, const QGst::CapsPtr &caps)
{
    if(caps.isNull())
    {
        return false;
    }
    qDebug() << caps->toString();
    if(caps->size())
    {
        QGst::StructurePtr s = caps->internalStructure(0);
        if(s->hasField("media") && s->hasField("encoding-name"))
        {
            QString strMediaType = s->value("media").toString();
            QString strEncodingName = s->value("encoding-name").toString();
            qDebug() << "media type: " << strMediaType;

            if(strMediaType == "video")
            {
                if(!m_rtphdepay.isNull())
                {
                    m_pipeline->remove(m_rtphdepay);
                    m_rtphdepay.clear();
                }
                if(!m_parse.isNull())
                {
                    m_pipeline->remove(m_parse);
                    m_parse.clear();
                }

                if(strEncodingName == "H264")
                {
                    m_rtphdepay = QGst::ElementFactory::make(GStreamer::Plugin::rtph264depay);
                    m_parse = QGst::ElementFactory::make(GStreamer::Plugin::h264parse);
                    m_pipeline->add(m_rtphdepay);
                    m_pipeline->add(m_parse);
                    bool bLinked =  QGst::Element::linkMany(m_rtphdepay, m_parse, m_decodebin);
                    if(!bLinked)
                    {
                        qDebug() << "rtphdepay link parse: " << bLinked;
                        return false;
                    }
//                    QGst::PadPtr parseSrcPad = m_parse->getStaticPad(GStreamer::SRC);
//                    QGst::PadPtr decodebinSinPad = m_decodebin->getStaticPad(GStreamer::SINK);
//                    QGst::PadLinkReturn padLinkResult = parseSrcPad->link(decodebinSinPad);
//                    if(padLinkResult != QGst::PadLinkOk)
//                    {
//                        qDebug() << "depay src pad link decodebin sink pad failed";
//                        return false;
//                    }
                    bool b = m_rtphdepay->syncStateWithParent();
                    if(!b)
                    {
                        qDebug() << "rtph depay sync failed";
                        return false;
                    }
                    b = m_parse->syncStateWithParent();
                    if(!b)
                    {
                        qDebug() << "parse sync failed";
                        return false;
                    }
                    return true;

                }
                else if(strEncodingName == "H265"){
                    m_rtphdepay = QGst::ElementFactory::make(GStreamer::Plugin::rtph265depay);
                    m_parse = QGst::ElementFactory::make(GStreamer::Plugin::h265parse);
                    m_pipeline->add(m_rtphdepay);
                    m_pipeline->add(m_parse);
//                    bool bLinked =  m_rtphdepay->link(m_parse);
                    bool bLinked =  QGst::Element::linkMany(m_rtphdepay, m_parse, m_decodebin);

                    if(!bLinked)
                    {
                        qDebug() << "rtphdepay link parse: " << bLinked;
                        return false;
                    }
//                    QGst::PadPtr parseSrcPad = m_parse->getStaticPad(GStreamer::SRC);
//                    QGst::PadPtr decodebinSinPad = m_decodebin->getStaticPad(GStreamer::SINK);
//                    QGst::PadLinkReturn padLinkResult = parseSrcPad->link(decodebinSinPad);
//                    if(padLinkResult != QGst::PadLinkOk)
//                    {
//                        qDebug() << "depay src pad link decodebin sink pad failed";
//                        return false;
//                    }
                    m_rtphdepay->syncStateWithParent();
                    m_parse->syncStateWithParent();
                    return true;
                }
                else{
                    qDebug() << "not supported encoding name " << strEncodingName;
                    return false;
                }

            }

        }
    }
    return false;
}

void Camera::OnRtspsrcPadAdded(const QGst::PadPtr& pad)
{
    if(pad.isNull())
    {
        return;
    }
    QGst::CapsPtr caps =  pad->currentCaps();
    QString strCaps = caps->toString();
    if(strCaps.contains("x-rtp"))
    {
        QGst::PadPtr  rtphdepaySinkPad = m_rtphdepay->getStaticPad(GStreamer::SINK);
        QGst::PadLinkReturn padLinkResult = pad->link(rtphdepaySinkPad);
        if(padLinkResult != QGst::PadLinkOk)
        {
            qDebug() << "rtspsrc pad link rtphdepay sink pad failed";
            return;
        }

    }



    //    qDebug() << "rtspsrc pad added: " << s->toString();

}

void Camera::onRtspsrcPadRemoved(const QGst::PadPtr &pad)
{
    qDebug() << "linked: " <<  pad->isLinked();
    if(pad.isNull())
    {
        return;
    }
    qDebug() << pad->name() <<  "pad removed";
}

//void Camera::OnRtspsrcPushBackChannelBuffer(int arg0, const QGst::BufferPtr &buffer)
//{
//    bool b = true;
//}

void Camera::OnDecodebinPadAdded(const QGst::PadPtr &pad)
{
    if(pad.isNull())
    {
        return;
    }
    QGst::CapsPtr caps = pad->currentCaps();
    if(caps->size())
    {
        QGst::StructurePtr structure = caps->internalStructure(0);
        QString strS = structure->toString();
        qDebug() << "decodebin pad added: " << strS;
        QString strName = structure->name();
        if(structure->name() == "video/x-raw")
        {
            QGst::PadPtr queueSinkPad = m_queue->getStaticPad(GStreamer::SINK);
            QGst::PadLinkReturn padLinkResult = pad->link(queueSinkPad);
            if(QGst::PadLinkOk != padLinkResult)
            {
                qDebug() << "decode bin pad link queue sink pad failed";
            }
//            GST_DEBUG_BIN_TO_DOT_FILE_WITH_TS(GST_BIN((GstPipeline*)m_pipeline), GST_DEBUG_GRAPH_SHOW_ALL, "pipeline");
//            m_decodebin->syncStateWithParent();
        }
        //        if(strS.contains())

    }
}

void Camera::OnDecodebinPadRemoved(const QGst::PadPtr &pad)
{
    if(pad.isNull())
    {
        return;
    }
    qDebug() << pad->name() << "pad removed";

}

void Camera::OnWatchStatus()
{
    QTime currentTime = QTime::currentTime();
    int nTimespan = -1;
    {
        QMutexLocker locker(&m_mutexBuffer);
        nTimespan = m_lastBufferTime.msecsTo(currentTime);
    }
    if(nTimespan > 0)
    {
        qDebug() << "time spane: " <<  nTimespan;
    }
}



//void Camera::PadAdded(GstElement *element, GstPad *pad, gpointer data)
//{
//    bool b = true;
//}

//gboolean Camera::SelectStreamCallBack(GstElement *rtspsrc, guint num, GstCaps *caps, gpointer user_data)
//{


//    bool b = true;
//    return true;
//}

void Camera::OnBusMessage(const QGst::MessagePtr &message)
{
    //    QList<params propertyList = message->source()->listProperties();
    //    qDebug() << propertyList;
    switch (message->type()) {
    case QGst::MessageEos: //End of stream. We reached the end of the file.
        //        stop();
        if(message->source() == m_rtspsrc)
        {
            bool b = true;
        }
        break;
    case QGst::MessageError: //Some error occurred.
    {

        qCritical() << message.staticCast<QGst::ErrorMessage>()->error();

    }
        break;
    case QGst::MessageStateChanged:
    {
        QGst::ObjectPtr objectPtr = message->source();

        qDebug() << objectPtr->name();
        //        if(objectPtr == m_rtspsrc)
        //        {
        //            qDebug() << m_rtspsrc->name();
        //        }
        //        else if(objectPtr == m_decodebin)
        //        {
        //            qDebug() << m_decodebin->name();
        //        }
        //        else if(objectPtr == m_rtphdepay)
        //        {
        //            qDebug() << m_rtphdepay->name();
        //        }
        //        else if(objectPtr == m_parse)
        //        {
        //            qDebug() << m_parse->name();
        //        }
        QGst::StateChangedMessagePtr messagePtr = message.staticCast<QGst::StateChangedMessage>();
        qDebug() << messagePtr->oldState() << " -> " << messagePtr->newState() << "  pend to " << messagePtr->pendingState();


    }
        break;
    default:
        break;
    }
}

GstPadProbeReturn Camera::QueueSinkPadProbeFunc(GstPad *pad, GstPadProbeInfo *info, gpointer user_data)
{
    qDebug() << "probe func";
    Camera* camera = (Camera*)user_data;
    if(camera)
    {
        {
            QMutexLocker locker(&camera->m_mutexBuffer);
            camera->m_lastBufferTime = QTime::currentTime();
        }
    }
    return GST_PAD_PROBE_OK;
}
