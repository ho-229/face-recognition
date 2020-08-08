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
#include "ui_camerarecognitiondialog.h"

#include <QDebug>
#include <QUrl>
#include <QDir>
#include <QTimer>
#include <QPainter>
#include <QCameraInfo>
#include <QMessageBox>
#include <QDesktopServices>

#if _MSC_VER >= 1600
    #pragma execution_character_set("utf-8")
#endif

VideoRecognitionDialog::VideoRecognitionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CameraRecognitionDialog),
    m_Timer(new QTimer(this)),
    m_FaceRecognition(new FaceRecognition(this))
{
    ui->setupUi(this);
    this->initUI();

    if(!m_FaceRecognition->load())
    {
        QMessageBox::critical(this,"错误","模型加载失败");
        this->close();
        return;
    }

    m_pen.setWidth(3);

    connect(m_Timer,&QTimer::timeout,this,&VideoRecognitionDialog::processFrame);
}

VideoRecognitionDialog::~VideoRecognitionDialog()
{        
    delete ui;
}

void VideoRecognitionDialog::openVideo(const cv::String &filename, int apiPreference)
{
    qDebug()<<filename.c_str();
    if(!m_videoCapture.open(filename ,apiPreference))
    {
        QMessageBox::critical(this,"错误","视频文件加载失败");
        this->close();
        return;
    }
    this->setWindowTitle(filename.c_str());
    m_Timer->start(100);
}

void VideoRecognitionDialog::openVideo(int index, int apiPreference)
{
    if(!m_videoCapture.open(index ,apiPreference))
    {
        QMessageBox::critical(this,"错误","摄像头加载失败");
        this->close();
        return;
    }
    this->setWindowTitle("摄像头 - " + QCameraInfo::defaultCamera().description());
    m_Timer->start(100);
}

void VideoRecognitionDialog::processFrame()
{
    m_videoCapture >> m_frame;             // 读取帧
    if(!m_frame.empty())
    {
        m_FaceRecognition->setImage(m_frame);
        m_FaceRecognition->start();         // 开始识别
        m_faces = m_FaceRecognition->faces();
        m_imageFrame = FaceRecognition::cvMatToImage(m_frame);

        QCoreApplication::processEvents();  // 防止GUI冻结

        if(!m_faces.empty())
        {
            /* 绘制矩形 */
            QPainter painter(&m_imageFrame);

            painter.setRenderHint(QPainter::Antialiasing);
            painter.setFont(QFont("Microsoft YaHei",18,QFont::Bold));

            std::size_t i = 1;
            for(cv::Rect &face : m_faces)
            {
                m_pen.setColor(Qt::red);
                painter.setPen(m_pen);
                painter.drawRect(face.x,face.y,face.width,face.height);

                m_pen.setColor(Qt::blue);
                painter.setPen(m_pen);
                painter.drawText(face.x,face.y-2,QString::number(i));

                ++i;
            }
            painter.end();
        }
        ui->infoLabel->setText(QString("已识别人脸：%1").arg(m_faces.size()));
        ui->frameLabel->setPixmap(QPixmap::fromImage(m_imageFrame));
    }
}

void VideoRecognitionDialog::initUI()
{
    this->setWindowFlag(Qt::WindowContextHelpButtonHint,false);
    this->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
}

void VideoRecognitionDialog::closeEvent(QCloseEvent *)
{
    m_Timer->stop();            // 停止QTimer
    m_videoCapture.release();   // 关闭摄像头
}

void VideoRecognitionDialog::on_saveToLocalBtn_clicked()
{
    if(!m_faces.empty())
    {
        QDir facesDir("./faces/camera/");
        if(!facesDir.exists())
            facesDir.mkpath("./");

        std::size_t i = 1;
        for(cv::Rect &face : m_faces)
        {
            /* 裁剪并保存 */
            if(!m_imageFrame.copy(face.x + 3,face.y + 3,face.width - 6,face.height - 6)
                    .save("./faces/camera/"+QString::number(i)+".jpg","JPG",100))
                QMessageBox::critical(this,"错误",QString::number(i)+".jpg 保存失败");
            ++i;
        }
        // 用资源管理器打开
        QDesktopServices::openUrl(QUrl("file:./faces/camera/", QUrl::TolerantMode));
    }
}
