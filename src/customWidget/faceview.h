#ifndef FACEVIEW_H
#define FACEVIEW_H

#include <QPen>
#include <vector>
#include <QWidget>

#include <opencv2/opencv.hpp>

#include "videocapture.h"
#include "facerecognition.h"

class FaceView : public QWidget
{
    Q_OBJECT
public:
    explicit FaceView(QWidget *parent = nullptr);
    ~FaceView() Q_DECL_OVERRIDE;

    void setFrame(QImage& frame)
    {
        m_frame = frame;
        m_faces = m_recognition->faces();

        if(!(m_frame.isNull() && m_faces.empty()))
        {
            this->paintFacesRect();
            this->repaint();
        }
    }

    void setVideoCapture(VideoCapture *capture)
    {
        m_capture = capture;
        QObject::connect(m_capture, &VideoCapture::processFrame, this,
                         &FaceView::updateFrame);
    }

    void setRecognition(FaceRecognition *recongititon)
    { m_recognition = recongititon; }

    const QImage& frame(){ return m_frame; }

signals:
    void findFaces(size_t num);

public slots:
    void updateFrame();

private:
    QPen m_pen;
    QImage m_frame;

    VideoCapture *m_capture = nullptr;
    FaceRecognition *m_recognition = nullptr;

    std::vector<cv::Rect> m_faces;

    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    void paintFacesRect();
};

#endif // FACEVIEW_H
