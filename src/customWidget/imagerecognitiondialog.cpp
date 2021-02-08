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

ImageRecognitionDialog::ImageRecognitionDialog(cv::Mat& image, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageRecognitionDialog),
    m_image(image)
{
    ui->setupUi(this);
    this->initUI();
}

ImageRecognitionDialog::~ImageRecognitionDialog()
{
    delete ui;
}

void ImageRecognitionDialog::setRecognition(FaceRecognition *recongititon)
{
    m_FaceRecognition = recongititon;
    ui->faceView->setRecognition(m_FaceRecognition);
}

void ImageRecognitionDialog::recognitionImage()
{
    m_FaceRecognition->recognition(m_image);
    VideoCapture::cvMatToImage(m_image, m_frame);

    ui->faceView->setFrame(m_frame);
    ui->infoLabel->setText(tr("faces: %1").arg(m_FaceRecognition->faces().size()));
}

void ImageRecognitionDialog::initUI()
{
    this->setWindowFlag(Qt::WindowContextHelpButtonHint, false);
}

void ImageRecognitionDialog::on_saveToLocalBtn_clicked()
{
    m_faces = m_FaceRecognition->faces();
    if(!m_faces.empty())
    {
        QDir facesDir("./faces/photo/");
        if(!facesDir.exists())
            facesDir.mkpath("./");

        std::size_t i = 1;
        for(cv::Rect &face : m_faces)
        {
            if(!m_frame.copy(face.x, face.y, face.width, face.height)
                    .save("./faces/photo/" + QString::number(i) + ".jpg","JPG",100))
                QMessageBox::critical(this, "错误", QString::number(i) + ".jpg 保存失败");
            ++i;
        }
        QDesktopServices::openUrl(QUrl("file:./faces/photo/", QUrl::TolerantMode));
    }
}
