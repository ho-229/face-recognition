/* ======================================================================
 * This file is part of the Face-recognition
 * Copyright (C) 2020 Ho 229
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 *
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ======================================================================== */

#include "videorecognitiondialog.h"
#include "ui_videorecognitiondialog.h"

#include <QDebug>
#include <QUrl>
#include <QDir>
#include <QCameraInfo>
#include <QMessageBox>
#include <QDesktopServices>

#if _MSC_VER >= 1600
    #pragma execution_character_set("utf-8")
#endif

VideoRecognitionDialog::VideoRecognitionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CameraRecognitionDialog),
    m_capture(new VideoCapture(this))
{
    ui->setupUi(this);
    this->initUI();

    ui->faceView->setVideoCapture(m_capture);

    QObject::connect(ui->faceView, &FaceView::findFaces,
                     [this](size_t num){
        ui->infoLabel->setText(tr("faces: ").append(QString::number(num)));
    });
}

VideoRecognitionDialog::~VideoRecognitionDialog()
{        
    delete ui;
}

void VideoRecognitionDialog::openVideo(const QString &filename, int apiPreference)
{
    if(!m_capture->start(filename, apiPreference))
    {
        QMessageBox::critical(this, "错误", "视频文件加载失败");
        this->close();
        return;
    }
    this->setWindowTitle(filename);
}

void VideoRecognitionDialog::openVideo(int index, int apiPreference)
{
    if(!m_capture->start(index ,apiPreference))
    {
        QMessageBox::critical(this,"错误","摄像头加载失败");
        this->close();
        return;
    }
    this->setWindowTitle("摄像头 - " + QCameraInfo::defaultCamera().description());
}

void VideoRecognitionDialog::setRecognition(FaceRecognition *recongititon)
{
    m_FaceRecognition = recongititon;
    ui->faceView->setRecognition(m_FaceRecognition);
}

void VideoRecognitionDialog::initUI()
{
    this->setWindowFlag(Qt::WindowContextHelpButtonHint,false);
}

void VideoRecognitionDialog::closeEvent(QCloseEvent *)
{
    m_capture->stop();
}

void VideoRecognitionDialog::on_saveToLocalBtn_clicked()
{
    m_faces = m_FaceRecognition->faces();
    if(!m_faces.empty())
    {
        QDir facesDir("./faces/camera/");
        if(!facesDir.exists())
            facesDir.mkpath("./");

        std::size_t i = 1;
        for(cv::Rect &face : m_faces)
        {
            /* 裁剪并保存 */
            if(!ui->faceView->frame().copy(face.x + 3, face.y + 3, face.width - 6, face.height - 6)
                    .save("./faces/camera/" + QString::number(i) +  ".jpg", "JPG", 100))
                QMessageBox::critical(this,"错误",QString::number(i) + ".jpg 保存失败");
            ++i;
        }
        // 用资源管理器打开
        QDesktopServices::openUrl(QUrl("file:./faces/camera/", QUrl::TolerantMode));
    }
}
