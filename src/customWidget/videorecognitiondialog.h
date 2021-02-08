#ifndef VIDEORECOGNITIONDIALOG_H
#define VIDEORECOGNITIONDIALOG_H

#include <QPen>
#include <QDialog>
#include <opencv2/opencv.hpp>

#include "facerecognition.h"
#include "videocapture.h"

namespace Ui {
class CameraRecognitionDialog;
}

class VideoRecognitionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VideoRecognitionDialog(QWidget *parent = nullptr);
    ~VideoRecognitionDialog() Q_DECL_OVERRIDE;

    void openVideo(const QString& filename, int apiPreference = cv::CAP_ANY);
    void openVideo(int index, int apiPreference = cv::CAP_ANY);

    void setRecognition(FaceRecognition *recongititon);

private slots:
    void on_saveToLocalBtn_clicked();

private:
    Ui::CameraRecognitionDialog *ui;

    FaceRecognition *m_FaceRecognition = nullptr;
    VideoCapture *m_capture = nullptr;

    cv::Mat m_frame;

    std::vector<cv::Rect> m_faces;

    inline void initUI();
    void closeEvent(QCloseEvent *) Q_DECL_OVERRIDE;
};

#endif // VIDEORECOGNITIONDIALOG_H
