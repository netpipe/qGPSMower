#include "leftwidget.h"
#include <QPainter>
#include <QPainterPath>
#include <QtMath>
LeftWidget::LeftWidget(QWidget *parent) : QWidget(parent)
{
   m_finish = false;
   ball_radius = 20;
   ball_stroke = 1;
   cur_speed = 8;
   m_animating = false;
}

float calcDist(QPoint a, QPoint b)
{
    return qSqrt( (a.x() - b.x()) * (a.x() - b.x()) + (a.y() - b.y()) * (a.y() - b.y()));
}
void LeftWidget::paintEvent(QPaintEvent *event)
{
    QPainter pa(this);

    int i;
    for(i = 0; i<m_points.size(); i++)
    {
        QPoint p = m_points[i];
        pa.fillRect(QRect(p.x()-5,p.y()-5,10,10), Qt::red);
    }

    if(m_finish)
    {
        QPolygon po(m_points);
        pa.drawPolygon(po);
    }

    if(m_animating)
    {
        //start , end point
        int ps = m_points.size();
        QPoint a = m_points[ (cur_line ) % ps];
        QPoint b = m_points[ (cur_line + 1 ) % ps];
        cur_length = calcDist(a, b);

        float rate = cur_off / cur_length;
        int x = (b.x() - a.x()) * rate + a.x();
        int y = (b.y() - a.y()) * rate + a.y();

        pa.setBrush(Qt::blue);
        pa.setPen( QPen(Qt::black, ball_stroke));
        pa.drawEllipse( x - ball_radius/2, y - ball_radius/2, ball_radius, ball_radius);
    }
}
void LeftWidget::startAnimation()
{
    if(m_points.size() < 3) return;
    cur_length = calcDist(m_points[0], m_points[1]);
    cur_off = 0.0;
    cur_line = 0;
    m_animating = true;

    update();

    timer.start(100);
    connect(&timer, SIGNAL(timeout()), this, SLOT(onTimer()) );

}
void LeftWidget::onTimer()
{
    cur_off += cur_speed;

    if(cur_off >= cur_length)
    {
        cur_line ++ ;
        cur_off = 0;

        int ps = m_points.size();
        QPoint a = m_points[ (cur_line ) % ps];
        QPoint b = m_points[ (cur_line + 1 ) % ps];

        cur_length = calcDist( a, b);

    }
    update();
}
void LeftWidget::mousePressEvent(QMouseEvent *e)
{
    if(m_animating) return;
    m_points.append(e->pos());
    update();
}
