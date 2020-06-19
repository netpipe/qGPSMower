#ifndef LEFTWIDGET_H
#define LEFTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPaintEvent>
#include <QList>
#include <QTimer>
#include <QGraphicsItem>
#define LEFT -1
#define RIGHT 1

#define HORZ -1
#define VERT 1

class LeftWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LeftWidget(QWidget *parent = nullptr);
public:

    void paintEvent(QPaintEvent *event);
public:
    QVector<QPointF> m_points;
    bool m_finish;
    bool m_animating;
    //for animation
    float m_cx, m_cy;
    //speed
    float m_speed;
    float m_sx;
    float m_sy;
    //destination
    QPointF m_dest;
    int m_dir; //moving direction: horz vs vertical
    int m_side; //left , right
    float m_bottom;

    //track
    QList<QPointF> m_track;
    //ball
    int m_interval;
    int m_stroke;
    int m_radius;
    int m_ygap;;
    QTimer timer;

    //line calc
    bool yposInLine(QPointF start, QPointF end, float y);
    float yposMeetPoint(float y, int dir);
    float yposMeetPoint(QPointF start, QPointF end, float y);
public:
    void mousePressEvent(QMouseEvent *e);
    void startAnimation();
public slots:
    void onTimer();
signals:

};

#endif // LEFTWIDGET_H
