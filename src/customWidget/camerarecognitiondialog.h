#ifndef CAMERARECOGNITIONDIALOG_H
#define CAMERARECOGNITIONDIALOG_H

#include <QPen>
#include <QDialog>
#include <opencv2/opencv.hpp>

#include "facerecognition.h"

class QTimer;

namespace Ui {
class CameraRecognitionDialog;
}

class CameraRecognitionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CameraRecognitionDialog(QWidget *parent = nullptr);
    ~CameraRecognitionDialog() Q_DECL_OVERRIDE;

private slots:
    void processFrame();

    void on_saveToLocalBtn_clicked();

private:
    Ui::CameraRecognitionDialog *ui;

    inline void initUI();

    void closeEvent(QCloseEvent *) Q_DECL_OVERRIDE;

    QTimer *m_Timer = nullptr;
    FaceRecognition *m_FaceRecognition = nullptr;

    cv::VideoCapture m_cameraCapture;
    cv::Mat m_frame;

    std::vector<cv::Rect> m_faces;

    QPen      m_pen;
    QImage    m_imageFrame;
};

#endif // CAMERARECOGNITIONDIALOG_H
