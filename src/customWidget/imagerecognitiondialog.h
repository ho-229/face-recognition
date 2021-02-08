#ifndef IMAGERECOGNITIONDIALOG_H
#define IMAGERECOGNITIONDIALOG_H

#include <QDialog>
#include <opencv2/opencv.hpp>

#include "facerecognition.h"

class QGraphicsScene;

namespace Ui {
class ImageRecognitionDialog;
}

class ImageRecognitionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImageRecognitionDialog(cv::Mat& image, QWidget *parent = nullptr);
    ~ImageRecognitionDialog();

    void setRecognition(FaceRecognition *recongititon);

    void recognitionImage();

private slots:
    void on_saveToLocalBtn_clicked();

private:
    Ui::ImageRecognitionDialog *ui;

    cv::Mat& m_image;
    QImage m_frame;

    FaceRecognition *m_FaceRecognition = nullptr;

    std::vector<cv::Rect> m_faces;

    inline void initUI();
};

#endif // IMAGERECOGNITIONDIALOG_H
