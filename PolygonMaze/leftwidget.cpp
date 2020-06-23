#include "leftwidget.h"
#include <QPainter>
#include <QPainterPath>
#include <QtMath>

LeftWidget::LeftWidget(QWidget *parent) : QWidget(parent)
{
   m_finish = false;
   m_radius = 10;
   m_stroke = 1;
   m_speed = 5;
   m_animating = false;
   m_ygap = 15;
   m_interval = 30;
}
float calcDist(QPointF a, QPointF b)
{
    return qSqrt( (a.x() - b.x()) * (a.x() - b.x()) + (a.y() - b.y()) * (a.y() - b.y()));
}
bool  LeftWidget::pointInLine(QPointF p, QPointF a, QPointF b)
{

    float len = calcDist(a, b);
    float slen = calcDist(p,a) + calcDist(p, b);

    if(qAbs(len-slen) < m_ygap * 0.01)
        return true;

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
        pa.setPen( QPen(Qt::red,1));
        for(i = 0; i<m_track.size()-1; i++)
        {
            pa.drawLine( m_track[i].x(), m_track[i].y(),m_track[i+1].x(), m_track[i+1].y() );

        }

//        for(i = 0; i<m_old_boundary.size()-1; i++)
//        {
//            pa.drawLine( m_old_boundary[i].x(), m_old_boundary[i].y(),m_old_boundary[i+1].x(), m_old_boundary[i+1].y() );

//        }


        pa.setPen( QPen(Qt::black, m_stroke));


        pa.drawEllipse(m_cx - m_radius, m_cy - m_radius, m_radius*2, m_radius*2);

        //test track calc track
//        int pc = m_curpoints.size();
//        for(i = 0; i< pc ; i++)
//        {
//            pa.fillRect( QRect(m_curpoints[i].x()-3, m_curpoints[i].y()-3,6,6), Qt::blue);

//        }

    }
}

void LeftWidget::calcPoints()
{
    m_old_boundary = m_boundary;
    int i;
    int pc= m_boundary.size();

    //clear curpoints
    m_curpoints.clear();

    //calc boundary points
    for(i = 0; i< pc ; i++)
    {
        QPointF np = m_boundary[(i+1)%pc];
        QPointF pp = m_boundary[(i+pc-1)%pc];
        ALine line2(m_boundary[i] , np);
        ALine off_line2 = line2.offset(m_ygap, RIGHT);

        ALine line1( pp, m_boundary[i]);
        ALine off_line1 = line1.offset(m_ygap, RIGHT);
        QPointF mp = off_line1.meetPoint(off_line2);

        m_curpoints.append(mp);

    }
    m_boundary = m_curpoints;
    //calc last point and append
    QPointF lp = m_boundary.last();
    QPointF fp = m_boundary.first();
    QPointF sp = m_boundary[1];
        //fist line in new boundary
    ALine fl(fp,sp);
    fl = fl.offset(m_ygap, RIGHT);
    ALine el(lp,fp);

    lp = fl.meetPoint(el);

    m_curpoints.append(lp);
    //renew first point
    m_curpoints[0]= QPointF(m_cx, m_cy);

}
void LeftWidget::startAnimation()
{
    if(m_points.size() < 3) return;
    m_track.clear();
    //calc first point
    QPointF lp = m_points.last();
    QPointF fp = m_points.first();
    QPointF sp = m_points[1];

    ALine fl(fp,sp);
    fl = fl.offset(m_ygap, RIGHT);
    ALine el(lp,fp);
    lp = fl.meetPoint(el);

    m_cx = lp.x();
    m_cy = lp.y();

    m_boundary = m_points;
    m_old_boundary = m_boundary;
    calcPoints();

    m_src = lp;
    m_dest = m_curpoints[1];
    m_offest = 0;
    m_curindex = 0;
    m_animating = true;
    m_track.append( m_src);
    m_track.append( m_src);
    update();

    timer.start(m_interval);
    connect(&timer, SIGNAL(timeout()), this, SLOT(onTimer()) );

}
void LeftWidget::onTimer()
{
    float len = calcDist(m_src, m_dest);


    if( 0< len - m_offest && len - m_offest< m_speed)
    {
        m_offest = len;
        m_cx = m_dest.x();
        m_cy = m_dest.y();
    }
    else if(m_offest == len)
    {
        m_curindex ++;
        m_track.append(m_dest);
        m_track.append(m_dest);
        //if last point
        if(m_curindex == m_curpoints.size() -1 )
        {
            calcPoints();
            m_curindex = 0;
            m_src = m_curpoints[0];
            m_dest = m_curpoints[1];
            m_offest = 0;
        } else{
            m_src = m_curpoints[m_curindex];
            m_dest = m_curpoints[m_curindex + 1];
            m_offest = 0;
        }


    }
    else{
        m_offest += m_speed;
        float x = ((len-m_offest) * m_src.x() + m_offest * m_dest.x())/len;
        float y = ((len-m_offest) * m_src.y() + m_offest * m_dest.y())/len;
        //check if end
        if(m_curindex != 0)
        {
            bool bEnd = false;
            int i;
            int mc = m_old_boundary.size();
            for(i = 0; i<mc; i++)
            {

                if(pointInLine(QPointF(x,y), m_old_boundary[i], m_old_boundary[(i+1)%mc] ))
                {
                    timer.stop();
                    bEnd = true;
                    return;
                }
            }

        }

        //end: check if end
        m_cx = x;
        m_cy = y;
        m_track.pop_back() ;
        m_track.push_back(QPointF(m_cx, m_cy));

    }

    update();
}
void LeftWidget::mousePressEvent(QMouseEvent *e)
{
    if(m_animating) return;
    m_points.append(e->pos());
    update();
}
