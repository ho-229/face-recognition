#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

#include "aboutdialog.h"
#include "imagerecognitiondialog.h"
#include "videorecognitiondialog.h"

#include "facerecognition.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget() Q_DECL_OVERRIDE;

    void initRecognition();

private slots:
    void on_aboutBtn_clicked();

    void on_cameraBtn_clicked();

    void on_photoBtn_clicked();

    void on_videoBtn_clicked();

private:
    Ui::MainWidget *ui;

    inline void initUI();

    FaceRecognition *m_recognition = nullptr;

    AboutDialog  *m_AboutDialog  = nullptr;
    ImageRecognitionDialog *m_ImageRecognitionDialog = nullptr;
    VideoRecognitionDialog *m_VideoRecognitionDialog = nullptr;
};

#endif // MAINWIDGET_H
