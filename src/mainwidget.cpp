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

#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QShowEvent>

#if _MSC_VER >= 1600
    #pragma execution_character_set("utf-8")
#endif

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget),
    m_recognition(new FaceRecognition(this))
{
    ui->setupUi(this);
    this->initUI();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::initRecognition()
{
    if(!m_recognition->load())
    {
        QMessageBox::critical(this, tr("Error"), tr("Model loading failed."));
        this->close();              // it's working but program still RUN
        QApplication::quit();       // it's not working
    }
}

void MainWidget::initUI()
{
    this->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
}

void MainWidget::on_photoBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"选择图片",QDir::homePath(),
        "图片文件 (*.bmp *.jpg *jpeg *.gif *.png *.ico)");
    if(fileName.isEmpty())
        return;

    cv::Mat image = cv::imread(fileName.toLocal8Bit().toStdString());
    if(image.empty())
    {
        QMessageBox::critical(this, tr("Error"), tr("Can not open file."));
        return;
    }

    m_ImageRecognitionDialog = new ImageRecognitionDialog(image, this);
    m_ImageRecognitionDialog->setWindowTitle(fileName);
    m_ImageRecognitionDialog->setAttribute(Qt::WA_DeleteOnClose);
    m_ImageRecognitionDialog->setRecognition(m_recognition);
    m_ImageRecognitionDialog->recognitionImage();
    m_ImageRecognitionDialog->exec();
    m_ImageRecognitionDialog = nullptr;
}

void MainWidget::on_cameraBtn_clicked()
{
    m_VideoRecognitionDialog = new VideoRecognitionDialog(this);
    m_VideoRecognitionDialog->setAttribute(Qt::WA_DeleteOnClose);
    m_VideoRecognitionDialog->openVideo(cv::CAP_ANY, cv::CAP_DSHOW);
    m_VideoRecognitionDialog->setRecognition(m_recognition);
    m_VideoRecognitionDialog->exec();
    m_VideoRecognitionDialog = nullptr;
}

void MainWidget::on_videoBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"选择视频",QDir::homePath(),
        "视频文件 (*.mp4 *.avi *.gif *.mpg)");
    if(fileName.isEmpty())
        return;

    m_VideoRecognitionDialog = new VideoRecognitionDialog(this);
    m_VideoRecognitionDialog->setAttribute(Qt::WA_DeleteOnClose);
    m_VideoRecognitionDialog->openVideo(fileName);
    m_VideoRecognitionDialog->setRecognition(m_recognition);
    m_VideoRecognitionDialog->exec();
    m_VideoRecognitionDialog = nullptr;
}

void MainWidget::on_aboutBtn_clicked()
{
    m_AboutDialog = new AboutDialog(this);
    m_AboutDialog->setAttribute(Qt::WA_DeleteOnClose);
    m_AboutDialog->exec();
    m_AboutDialog = nullptr;
}
