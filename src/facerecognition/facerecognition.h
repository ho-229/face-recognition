#ifndef FACERECOGNITION_H
#define FACERECOGNITION_H

#include <QObject>
#include <QImage>
#include <vector>
#include <opencv2/opencv.hpp>

class FaceRecognition : public QObject
{
    Q_OBJECT
public:
    explicit FaceRecognition(QObject *parent = nullptr);
    ~FaceRecognition() {  }

    void setImage(const cv::Mat &image) { m_image = image; }
    void setImage(const QImage  &image) { m_image = ImageTocvMat(image); }

    bool load();
    void start();

    std::vector<cv::Rect> faces() const { return m_faces; }

    static QImage cvMatToImage(cv::Mat& mat);
    static cv::Mat ImageTocvMat(const QImage &image);

signals:
    void recognitionFinished(std::vector<cv::Rect> );

private:
    cv::Mat m_image;
    cv::CascadeClassifier *m_cascada = nullptr;

    std::vector<cv::Rect> m_faces;
};

#endif // FACERECOGNITION_H
