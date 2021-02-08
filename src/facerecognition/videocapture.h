#ifndef VIDEOCAPTURE_H
#define VIDEOCAPTURE_H

#include <QImage>
#include <QObject>
#include <opencv2/opencv.hpp>

class VideoCapture : public QObject
{
    Q_OBJECT

public:
    explicit VideoCapture(QObject *parent = nullptr);
    ~VideoCapture() Q_DECL_OVERRIDE;

    bool start(const QString& fileName, int apiPreference = cv::CAP_ANY, int timeout = 75);
    bool start(int index, int apiPreference = cv::CAP_DSHOW, int timeout = 75);

    void stop();

    void getFrame(cv::Mat& frame){ frame = m_frame; }
    void getFrame(QImage& frame){ VideoCapture::cvMatToImage(m_frame, frame); }

    static void cvMatToImage(const cv::Mat& mat, QImage& image);

signals:
    void processFrame();

private:
    cv::VideoCapture m_capture;

    int m_timerId = 0;
    cv::Mat m_frame;
    QImage m_imageFrame;

    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;
};

#endif // VIDEOCAPTURE_H
