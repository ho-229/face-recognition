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

#include "imagerecognitiondialog.h"
#include "ui_imagerecognitiondialog.h"

#include <QUrl>
#include <QDir>
#include <QPainter>
#include <QMessageBox>
#include <QDesktopServices>

#if _MSC_VER >= 1600
    #pragma execution_character_set("utf-8")
#endif

ImageRecognitionDialog::ImageRecognitionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageRecognitionDialog),
    m_image(new QImage),
    m_showImage(new QImage),
    m_FaceRecognition(new FaceRecognition(this))
{
    ui->setupUi(this);
    this->initUI();
}

ImageRecognitionDialog::~ImageRecognitionDialog()
{
    delete ui;
}

void ImageRecognitionDialog::recognitionImage()
{
    m_FaceRecognition->setImage(*m_image);
    if(!m_FaceRecognition->load())
    {
        QMessageBox::critical(this,"错误","模型加载失败");
        return;
    }
    m_FaceRecognition->start();
    m_faces = m_FaceRecognition->faces();

    if(!m_faces.empty())
    {
        QPainter painter(m_showImage);

        QPen pen;
        pen.setWidth(3);

        painter.setRenderHint(QPainter::Antialiasing);
        painter.setFont(QFont("Microsoft YaHei",16,QFont::Bold));

        std::size_t i = 1;
        for(cv::Rect &face  : m_faces)
        {
            pen.setColor(Qt::red);
            painter.setPen(pen);
            painter.drawRect(face.x,face.y,face.width,face.height);

            pen.setColor(QColor(69,198,214));
            painter.setPen(pen);
            painter.drawText(face.x,face.y-2,QString::number(i));

            ++i;
        }
        painter.end();
    }

    if(m_showImage->size().width() > 1280)
        ui->imageLabel->setPixmap(QPixmap::fromImage(*m_showImage).scaledToWidth(1680));
    if(m_showImage->size().height() > 900)
        ui->imageLabel->setPixmap(QPixmap::fromImage(*m_showImage).scaledToHeight(900));
    else
        ui->imageLabel->setPixmap(QPixmap::fromImage(*m_showImage));

    ui->infoLabel->setText(QString("已识别人脸：%1").arg(m_faces.size()));
}

void ImageRecognitionDialog::initUI()
{
    this->setWindowFlag(Qt::WindowContextHelpButtonHint,false);
}

void ImageRecognitionDialog::on_saveToLocalBtn_clicked()
{
    if(!m_faces.empty())
    {
        QDir facesDir("./faces/photo/");
        if(!facesDir.exists())
            facesDir.mkpath("./");

        std::size_t i = 1;
        for(cv::Rect &face : m_faces)
        {
            if(!m_image->copy(face.x,face.y,face.width,face.height)
                    .save("./faces/photo/"+QString::number(i)+".jpg","JPG",100))
                QMessageBox::critical(this,"错误",QString::number(i)+".jpg 保存失败");
            ++i;
        }
        QDesktopServices::openUrl(QUrl("file:./faces/photo/", QUrl::TolerantMode));
    }
}
