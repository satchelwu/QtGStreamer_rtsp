#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QGst/Element>
#include <QGst/Bin>
#include <QGst/Pad>
#include <QGst/Pipeline>
#include <gst/gst.h>
#include <QGst/Message>
#include <QGst/Caps>
#include <memory>
#include <QGst/Buffer>
#include <QMutex>
#include <QTime>
#include <QTimer>


namespace QGst {
namespace Quick {
    class VideoSurface;
}
}

class Camera : public QObject
{
    Q_OBJECT
public:
    explicit Camera(QObject *parent = nullptr);
    ~Camera();
    void SetRtspAddress(const QString& strRtspAddress);
    Q_INVOKABLE QGst::Quick::VideoSurface* VideoSurface();
    Q_INVOKABLE void Replay();
    Q_INVOKABLE void Reset();

private Q_SLOTS:
    bool OnRtspsrcSelectStream(int num, const QGst::CapsPtr& caps);
    void OnRtspsrcPadAdded(const QGst::PadPtr& pad);
    void onRtspsrcPadRemoved(const QGst::PadPtr& pad);
    void onQueueRunning();
    void onQueueUnderRun();
//    void OnRtspsrcPushBackChannelBuffer(int arg0, const QGst::BufferPtr& buffer);

    void OnDecodebinPadAdded(const QGst::PadPtr& pad);
    void OnDecodebinPadRemoved(const QGst::PadPtr& pad);
    void OnWatchSourceStatus();
    bool OnWatchSourceAsyncStateChange();
    void OnReconnect();
//public Q_SLOTS:
//    static void PadAdded(GstElement *element, GstPad*pad, gpointer data);

//    static gboolean SelectStreamCallBack(GstElement *rtspsrc, guint num, GstCaps *caps, gpointer user_data);
    void OnBusMessage(const QGst::MessagePtr& message);


private:
    static GstPadProbeReturn   QueueSinkPadProbeFunc(GstPad *pad, GstPadProbeInfo *info,
                                                 gpointer user_data);
    Q_INVOKABLE bool ResetSourceBin();
private:
    QGst::PipelinePtr m_pipeline;
    QGst::ElementPtr m_rtspsrc;
    QGst::ElementPtr m_rtphdepay;
    QGst::ElementPtr m_parse;
    QGst::ElementPtr m_decodebin;
    QGst::ElementPtr m_queue;
    QGst::ElementPtr m_videoconvert;
    QGst::ElementPtr m_qtquick2videosink;
    gulong m_queueSinkPadProbeId;
    QMutex m_mutex;
    QTime m_lastBufferTime;
    QTimer m_watchSourceStatusTimer;
    QTimer m_watchSourceAsyncStateChangetimer;
    QTimer m_resetTimer;
    QGst::Quick::VideoSurface* m_pVideoSurface{nullptr};
    QString m_lastRtspAddress;
    int m_nRtspReconnectInterval{5};
    bool m_bAsnycStateWatchRunning{false};
    bool m_bReconfiguring{false};
    QTime m_lastReconnectTime;

};

#endif // CAMERA_H
