#ifndef ANIMATONDIALOG_H
#define ANIMATONDIALOG_H

#include <QDialog>
#include <QList>
#include <QPainter>
#include <QPen>
#include <QPoint>
#include <QPointF>
#include<QPixmap>
#include <QTimer>
#include <QtMath>
namespace Ui {
class Dialog;
}
typedef struct _XY_Data
{
    qreal X_Pos;
    qreal Y_Pos;

} XY_DATA;
typedef struct _XY_Speed
{
    // 加工速度
    qreal X_ProcessSpeed;
    qreal Y_ProcessSpeed;
    // 加速度
    qreal X_Acceleration;
    qreal Y_Acceleration;
} XY_SPEED;
typedef enum _ProcessType
{
    ProcessPoint,
    ProcessJump, // 转跳
    ProcessLine  // 直线
}PROCESSTYPE;

typedef struct _LaserMarkData
{
    // 图元参数
    PROCESSTYPE mProcessType;
    XY_DATA mXY_Data;
    XY_SPEED mXY_Speed;

} LASER_MARK_DATA;

class animation : public QDialog {
public:
    animation(QDialog *parent = nullptr);
     ~animation();

protected:
    void paintEvent(QPaintEvent *event)  ;

public slots:
    //定时器响应函数进行界面更新
    void animate();
    //实现绘画
    void drawline(QPen pen,QPointF startpoint,QPointF endpoint,QPainter *painter, qreal progress,qreal speed);
    //获取链表数据
    void GetData(QList<LASER_MARK_DATA> MarkData_List);
    qreal calculateDistance(QPointF point1, QPointF point2);
    //设置参数
    void setplatformData(int W,int H,qreal Xpos,qreal Ypos);
    void setSpeedFactor(qreal factor);
    void setJumpSpeed(qreal jumpspeed);
    void setMarkSpeed(qreal markspeed);
private:
    Ui::Dialog *ui;
    //定时器
    QTimer *timer;
    //点
    QPointF m_startpoint;
    QPointF m_endpoint;
    //平台大小
    int m_platform_W;
    int m_platform_H;
    //创建画笔
    QPen Emp_pen;
    QPen Laser_pen;
    //序号
    int m_currentShapeIndex;
    qreal m_currentProgress;
    //速度参数
    qreal m_speed;
    qreal m_Jump_speed;
    qreal m_Mark_speed;
    qreal m_speedFactor;
    //创建绘图缓冲区
    QPixmap m_pixmap; // 绘图缓冲区
    QPainter m_painter; // 在缓冲区上绘图的 QPainter 对象
    //创建激光加工数据结构链表
    QList<LASER_MARK_DATA> m_MarkData_List;
    LASER_MARK_DATA laserData;
    LASER_MARK_DATA platformData;
};
#endif // ANIMATONDIALOG_H
