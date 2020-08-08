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

#include "facerecognition.h"

#include <opencv2/imgproc/types_c.h>

FaceRecognition::FaceRecognition(QObject *parent) :
    QObject(parent),
    m_cascada(new cv::CascadeClassifier)
{

}

FaceRecognition::~FaceRecognition()
{
    delete m_cascada;
}

bool FaceRecognition::load() const
{
    /* 加载模型 */
    return m_cascada->load("./haarcascade_frontalface_alt.xml");
}

void FaceRecognition::start()
{
    cvtColor(m_image,m_grayImage, cv::COLOR_BGR2GRAY); // 转换成灰度图
    m_cascada->detectMultiScale(m_grayImage, m_faces, 1.1, 5, cv::CASCADE_DO_ROUGH_SEARCH,
                             cv::Size(10, 10), cv::Size(1000, 1000));
}

QImage FaceRecognition::cvMatToImage(const cv::Mat& mat)
{
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if(mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, static_cast<const size_t>(mat.cols));
            pSrc += mat.step;
        }
        return image;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if(mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar *pSrc = mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, static_cast<const int>(mat.step), QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
        // Copy input Mat
        const uchar *pSrc = mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, static_cast<const int>(mat.step), QImage::Format_ARGB32);
        return image.copy();
    }
    else
        return QImage();
}

cv::Mat FaceRecognition::ImageTocvMat(const QImage &image)
{
    cv::Mat mat;
    switch(image.format())
    {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), static_cast<size_t>(image.bytesPerLine()));
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), static_cast<size_t>(image.bytesPerLine()));
        cv::cvtColor(mat, mat, CV_BGR2RGB);
        break;
    case QImage::Format_Indexed8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), static_cast<size_t>(image.bytesPerLine()));
        break;
    }
    return mat;
}
