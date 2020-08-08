#ifndef VIDEORECOGNITIONDIALOG_H
#define VIDEORECOGNITIONDIALOG_H

#include <QPen>
#include <QDialog>
#include <opencv2/opencv.hpp>

#include "facerecognition.h"

class QTimer;

namespace Ui {
class CameraRecognitionDialog;
}

class VideoRecognitionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VideoRecognitionDialog(QWidget *parent = nullptr);
    ~VideoRecognitionDialog() Q_DECL_OVERRIDE;

    void openVideo(const cv::String& filename, int apiPreference = cv::CAP_ANY);

    void openVideo(int index, int apiPreference = cv::CAP_ANY);

private slots:
    void processFrame();

    void on_saveToLocalBtn_clicked();

private:
    Ui::CameraRecognitionDialog *ui;

    inline void initUI();

    void closeEvent(QCloseEvent *) Q_DECL_OVERRIDE;

    QTimer *m_Timer = nullptr;
    FaceRecognition *m_FaceRecognition = nullptr;

    cv::VideoCapture m_videoCapture;
    cv::Mat m_frame;

    std::vector<cv::Rect> m_faces;

    QPen      m_pen;
    QImage    m_imageFrame;
};

#endif // VIDEORECOGNITIONDIALOG_H
