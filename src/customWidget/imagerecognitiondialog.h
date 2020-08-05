#ifndef IMAGERECOGNITIONDIALOG_H
#define IMAGERECOGNITIONDIALOG_H

#include <QDialog>

#include "facerecognition.h"

class QGraphicsScene;

namespace Ui {
class ImageRecognitionDialog;
}

class ImageRecognitionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImageRecognitionDialog(QWidget *parent = nullptr);
    ~ImageRecognitionDialog();

    void setImage(QImage &image)
    {
        *m_image     = image;
        *m_showImage = image;
    }

    void recognitionImage();

private slots:
    void on_saveToLocalBtn_clicked();

private:
    Ui::ImageRecognitionDialog *ui;

    QImage *m_image     = nullptr;
    QImage *m_showImage = nullptr;

    FaceRecognition *m_FaceRecognition = nullptr;

    std::vector<cv::Rect> m_faces;

    inline void initUI();
};

#endif // IMAGERECOGNITIONDIALOG_H
