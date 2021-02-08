#include "faceview.h"

#include <QPainter>

FaceView::FaceView(QWidget *parent) : QWidget(parent)
{
    m_pen.setWidth(3);
}

FaceView::~FaceView()
{

}

void FaceView::updateFrame()
{
    if(m_capture == nullptr || m_recognition == nullptr)
        return;

    m_capture->getFrame(m_frame);
    m_capture->getFrame(m_recognition->frame());

    if(m_frame.isNull())
        return;

    m_recognition->recognition();
    m_faces = m_recognition->faces();
    emit findFaces(m_faces.size());

    if(!m_faces.empty())
        this->paintFacesRect();

    this->repaint();
}

void FaceView::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);

    QImage frame;
    frame = m_frame.scaled(this->width(), this->height(),
                           Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Move to center
    QRect rect = frame.rect();
    rect.moveCenter(this->rect().center());

    painter.drawImage(rect, frame);
}

void FaceView::paintFacesRect()
{
    QPainter painter(&m_frame);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setFont(QFont("Microsoft YaHei", 16, QFont::Bold));

    std::size_t i = 1;
    for(cv::Rect &face  : m_faces)
    {
        m_pen.setColor(Qt::red);
        painter.setPen(m_pen);
        painter.drawRect(face.x,face.y,face.width,face.height);

        m_pen.setColor(QColor(69,198,214));
        painter.setPen(m_pen);
        painter.drawText(face.x,face.y-2,QString::number(i));

        ++i;
    }
}
