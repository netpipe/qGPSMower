#include "leftwidget.h"
#include <QPainter>
#include <QPainterPath>
#include <QtMath>

LeftWidget::LeftWidget(QWidget *parent) : QWidget(parent)
{
   m_finish = false;
   m_radius = 3;
   m_stroke = 1;
   m_speed = 5;
   m_animating = false;
   m_ygap = 20;
   m_interval = 30;
}

float calcDist(QPointF a, QPointF b)
{
    return qSqrt( (a.x() - b.x()) * (a.x() - b.x()) + (a.y() - b.y()) * (a.y() - b.y()));
}

void LeftWidget::paintEvent(QPaintEvent *event)
{
    QPainter pa(this);

    int i;
    for(i = 0; i<m_points.size(); i++)
    {
        QPointF p = m_points[i];
        pa.fillRect(QRect(p.x()-5,p.y()-5,10,10), Qt::red);
    }

    if(m_finish)
    {
        QPolygonF po(m_points);
        pa.drawPolygon(po);
    }

    if(m_animating)
    {
        //track track
        int i;
        pa.setPen( QPen(Qt::red,1, Qt::DashLine));
        for(i = 0; i<m_track.size()-1; i++)
        {
            pa.drawLine( m_track[i].x(), m_track[i].y(),m_track[i+1].x(), m_track[i+1].y() );

        }
        pa.setPen( QPen(Qt::black, m_stroke));
        pa.setBrush( Qt::blue);
        pa.drawEllipse(m_cx - m_radius, m_cy - m_radius, m_radius*2, m_radius*2);
    }
}

//check if a line has a point in that y pos
bool LeftWidget::yposInLine(QPointF start, QPointF end, float y)
{
    if( ( (start.y() < y ) && (end.y() > y ) ) ||
            ( (start.y() > y ) && (end.y() < y ) ) )
    {
        return true;
    }
}

//calculate meet point: point vs line
float LeftWidget::yposMeetPoint(QPointF start, QPointF end, float y)
{
    float x = start.x() + (end.x() - start.x()) /(end.y() - start.y()) * (y - start.y());
    return x;
}

//calculate meet point: whole
float LeftWidget::yposMeetPoint(float y, int side)
{
    int i;
    int ps = m_points.size();

    float x;
    if(side == LEFT) x = 9999;
    else x = -9999;
    for(i = 0; i<ps; i++)
    {
        int j = (i+1) % ps;

        if(yposInLine(m_points[i], m_points[j], y))
        {
             float xx = yposMeetPoint(m_points[i], m_points[j], y);
             if(side==LEFT && xx < x )
                 x = xx;
             if(side==RIGHT && xx > x )
                 x = xx;
        }
    }
    return x;
}
void LeftWidget::startAnimation()
{
    if(m_points.size() < 3) return;
    m_track.clear();
    //calc top most, bottom most
    m_bottom = -1;
    int i;
    int top_index = 0;
    int ps = m_points.size();
    for(i = 0; i<ps; i++)
    {
        if(m_points[i].y() < m_points[top_index].y())
            top_index = i;
        if(m_points[i].y() > m_bottom)
            m_bottom = m_points[i].y();
    }

    //calc left one connected
    int left_index;
    int right_index;

    if( m_points[(top_index+1)%ps].x() > m_points[(top_index+ps - 1)%ps].x() )
    {
        left_index = (top_index+ps - 1)%ps;
        right_index = (top_index + 1)%ps;
    }
    else{
        right_index = (top_index+ps - 1)%ps;
        left_index = (top_index + 1)%ps;

    }



    float y = m_points[top_index].y() + m_ygap ;
    float x = yposMeetPoint(  m_points[top_index], m_points[left_index] ,y);

    m_track.append( QPointF(x,y));
    m_track.append( QPointF(x,y));

    m_cx = x;
    m_cy = y;



    x = yposMeetPoint(y, RIGHT);
    m_dest = QPointF(x, y);
    m_dir = HORZ;
    m_side = RIGHT;


    m_animating = true;


    update();

    timer.start(m_interval);
    connect(&timer, SIGNAL(timeout()), this, SLOT(onTimer()) );

}
void LeftWidget::onTimer()
{
    if(m_cy > m_bottom)
    {
        timer.stop();
    }
    //check if arrived
    float dist =calcDist(QPointF(m_cx, m_cy), m_dest);
    if( 0 < dist && dist  <= m_speed)
    {
        m_cx = m_dest.x();
        m_cy = m_dest.y();
    }
    else if(dist == 0)
    {
        m_dir = (int)m_dir * -1; //change direction
        m_track.append(QPointF(m_cx, m_cy));
        m_track.append(QPointF(m_cx, m_cy));
        if(m_dir == HORZ)
        {
            //calc dest
            m_side *= -1;
            float x = yposMeetPoint(m_cy, m_side);
            float x_next = yposMeetPoint(m_cy + m_ygap, m_side);

            if(m_side == LEFT && x < x_next && m_cy + m_ygap < m_bottom)
            {
                x = x_next;
            }
            if(m_side == RIGHT && x > x_next && m_cy + m_ygap < m_bottom)
            {
                x = x_next;
            }
            m_dest = QPointF(x, m_cy);

        }else{ //vertical
            if(m_cy + m_ygap > m_bottom) timer.stop();
            m_dest = QPointF(m_cx, m_cy + m_ygap);
        }
    }else{
        if(m_dir == HORZ)
        {
            m_cx += m_side * m_speed;

        }
        if(m_dir == VERT)
        {
            m_cy +=  m_speed;


        }
        m_track.pop_back();
        m_track.append(QPointF(m_cx, m_cy));
    }
    update();
}
void LeftWidget::mousePressEvent(QMouseEvent *e)
{
    if(m_animating) return;
    m_points.append(e->pos());
    update();
}
