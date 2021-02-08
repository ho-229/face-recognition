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

void FaceRecognition::recognition()
{
    cvtColor(m_frame, m_frame, cv::COLOR_BGR2GRAY);       // 转换成灰度图
    m_cascada->detectMultiScale(m_frame, m_faces, 1.1, 5, cv::CASCADE_DO_ROUGH_SEARCH,
                                cv::Size(10, 10), cv::Size(1000, 1000));
}
