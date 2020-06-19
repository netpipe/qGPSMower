#ifndef LEFTWIDGET_H
#define LEFTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPaintEvent>
#include <QList>
#include <QTimer>
#include <QGraphicsItem>
class LeftWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LeftWidget(QWidget *parent = nullptr);
public:

    void paintEvent(QPaintEvent *event);
public:
    QVector<QPoint> m_points;
    bool m_finish;
    bool m_animating;
    //for animation
    int cur_line;
    float cur_length; //length of current line
    float cur_off; //currrent offset
    float cur_speed;
    int ball_stroke;
    int ball_radius;
    QTimer timer;
public:
    void mousePressEvent(QMouseEvent *e);
    void startAnimation();
public slots:
    void onTimer();
signals:

};

#endif // LEFTWIDGET_H
