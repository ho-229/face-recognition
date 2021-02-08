#include "videocapture.h"

#include <QDebug>
#include <QTimerEvent>

VideoCapture::VideoCapture(QObject *parent) : QObject(parent)
{

}

VideoCapture::~VideoCapture()
{
    if(m_capture.isOpened())
        this->stop();
}

bool VideoCapture::start(const QString &fileName, int apiPreference, int timeout)
{
    if(m_capture.isOpened() || !m_capture.open(fileName.toLocal8Bit().toStdString(), apiPreference))
        return false;

    m_timerId = this->startTimer(timeout);
    return true;
}

bool VideoCapture::start(int index, int apiPreference, int timeout)
{
    if(m_capture.isOpened() || !m_capture.open(index, apiPreference))
        return false;

    m_timerId = this->startTimer(timeout);
    return true;
}

void VideoCapture::stop()
{
    if(!m_capture.isOpened())
        return;

    m_capture.release();
    this->killTimer(m_timerId);
}

void VideoCapture::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == m_timerId)
    {
        m_capture >> m_frame;
        emit processFrame();
    }
    else
        return QObject::timerEvent(event);
}

void VideoCapture::cvMatToImage(const cv::Mat& mat, QImage &image)
{
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if(mat.type() == CV_8UC1)
    {
        image = QImage(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);

        for(int i = 0; i < 256; i++)
            image.setColor(i, qRgb(i, i, i));

        // Copy input Mat
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, static_cast<const size_t>(mat.cols));
            pSrc += mat.step;
        }
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if(mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar *pSrc = mat.data;
        // Create QImage with same dimensions as input Mat
        image = QImage(pSrc, mat.cols, mat.rows, static_cast<const int>(mat.step),
                       QImage::Format_RGB888).rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
        // Copy input Mat
        const uchar *pSrc = mat.data;
        // Create QImage with same dimensions as input Mat
        image = QImage(pSrc, mat.cols, mat.rows, static_cast<const int>(mat.step), QImage::Format_ARGB32);
    }
    else
        image = QImage();
}
