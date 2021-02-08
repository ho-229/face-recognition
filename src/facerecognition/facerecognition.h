#ifndef FACERECOGNITION_H
#define FACERECOGNITION_H

#include "videocapture.h"

#include <vector>
#include <opencv2/opencv.hpp>

class FaceRecognition : public QObject
{
    Q_OBJECT

public:
    explicit FaceRecognition(QObject *parent = nullptr);
    ~FaceRecognition() ;

    bool load() const;

    const std::vector<cv::Rect>& faces(){ return m_faces; }

    cv::Mat& frame(){ return m_frame; }

    void setVideoCapture(VideoCapture *capture)
    {
        if(capture == nullptr)
            return;

        m_capture = capture;
    }

    void recognition(const cv::Mat& frame)
    {
        m_frame = frame;
        this->recognition();
    }

    void recognition();

private:
    VideoCapture *m_capture = nullptr;
    cv::CascadeClassifier *m_cascada = nullptr;

    cv::Mat m_frame;
    std::vector<cv::Rect> m_faces;
};

#endif // FACERECOGNITION_H
