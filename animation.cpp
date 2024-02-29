#include"animation.h"
#include "ui_animation.h"
animation::animation(QDialog *parent): QDialog(parent)
  , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    //初始化进度参数
    m_currentProgress = 0.0;
    m_currentShapeIndex=0;
    //初始化起点
    m_startpoint=QPointF(250.0,250.0);
    //总定时器
    timer=new QTimer(this);
    m_speedFactor = 1.0; // 动画速度比例因子，默认为1.0
    connect(timer, &QTimer::timeout, this, &animation::animate);
    timer->start(10);// 设置定时器间隔为10毫秒
    //初始化画家窗口
    m_pixmap = QPixmap(500,500); // 初始化绘图缓冲区为窗口大小
    m_pixmap.fill(Qt::white); // 用白色填充缓冲区
    m_painter.begin(&m_pixmap); // 在缓冲区上开始绘图
    m_painter.setRenderHint(QPainter::Antialiasing);//抗锯齿
}
//重写画家事件完成
void animation::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    //设置画家画笔
    QPainter painter(this);
    Emp_pen.setWidth(3);
    Emp_pen.setColor(Qt::green);
    Emp_pen.setStyle(Qt::DashLine);
    Laser_pen.setWidth(3);
    Laser_pen.setColor(Qt::red);
    //设置缓冲区
    painter.drawPixmap(0, 0, m_pixmap); // 将绘图缓冲区的内容绘制到窗口上
    painter.setRenderHint(QPainter::Antialiasing);//抗锯齿
    // 绘制平台
    painter.drawRect(static_cast<int>(platformData.mXY_Data.X_Pos),
                     static_cast<int>(platformData.mXY_Data.Y_Pos), m_platform_W,m_platform_H);
    // 绘制原点
    painter.setBrush(Qt::red);
    painter.drawEllipse(m_pixmap.width()/2, m_pixmap.height()/2, 5, 5);
    int i=m_currentShapeIndex;
    //从链表取出图形进行绘制
     if(i<m_MarkData_List.size())
     {
        //设置终点
        m_endpoint.rx()=m_MarkData_List.at(i).mXY_Data.X_Pos;
        m_endpoint.ry()=m_MarkData_List.at(i).mXY_Data.Y_Pos;
        //判断加工类型
        if(m_MarkData_List.at(i).mProcessType==ProcessJump){
           drawline(Emp_pen,m_startpoint,m_endpoint,&m_painter,m_currentProgress,m_Jump_speed);
          }
        else if(m_MarkData_List.at(i).mProcessType==ProcessLine) {
           drawline(Laser_pen,m_startpoint,m_endpoint,&m_painter,m_currentProgress,m_Mark_speed);
            }
     }
     //回零
     if (i == m_MarkData_List.size()){
        m_endpoint =QPointF(250,250);
       drawline(Emp_pen,m_startpoint,m_endpoint,&m_painter,m_currentProgress,m_Jump_speed);
     }
}
//对动画进度进行更新
void animation::animate()
{
    qreal step = 0.01; // 定义每次更新的步长
    qreal distance;
    //调整速度
    distance = calculateDistance(m_startpoint, m_endpoint); // 计算起点到终点的距离
    qreal speed = m_speed * m_speedFactor/distance; // 根据距离调整速度
    //速度太大会断点
    m_currentProgress += step*speed ; // 根据速度调整进度
    if (m_currentProgress>=1.0) { // 如果当前进度达到或超过1.0
       m_currentProgress = 0.0; // 重置当前进度为0
       m_currentShapeIndex++; // 切换到下一个图形
       //重设置起点
       m_startpoint=m_endpoint;
     if (m_currentShapeIndex>m_MarkData_List.size()) { // 如果已经到达图形列表的末尾
         timer->stop();
        }
    }
    update();
}
//画图方法
void animation::drawline(QPen pen,QPointF startpoint, QPointF endpoint, QPainter *painter, qreal progress, qreal speed)
{
    m_speed=speed;
    qreal endX = startpoint.rx()
            + (endpoint.rx() - startpoint.rx()) *progress;
    qreal endY = startpoint.ry()
            + (endpoint.ry() - startpoint.ry())*progress;
    painter->setPen(pen);
    painter->drawLine(startpoint, QPointF(endX, endY));

    update();
}
//从animationsetwidget获取链表
void animation::GetData(QList<LASER_MARK_DATA> MarkData_List)
{
    m_MarkData_List=MarkData_List;
}

qreal animation::calculateDistance(QPointF point1, QPointF point2)
{
        qreal dx = point2.rx() - point1.rx();
        qreal dy = point2.ry() - point1.ry();
        return qSqrt(dx * dx + dy * dy); // 计算两点之间的距离
}

void animation::setplatformData(int W,int H,qreal Xpos,qreal Ypos)
{
    m_platform_W=W;
    m_platform_H=H;
    platformData.mXY_Data.X_Pos=Xpos;
    platformData.mXY_Data.Y_Pos=Ypos;

}
void animation::setSpeedFactor(qreal factor)
{
    m_speedFactor = factor; // 设置动画速度比例因子
}

void animation::setJumpSpeed(qreal jumpspeed)
{
    m_Jump_speed=jumpspeed;
}

void animation::setMarkSpeed(qreal markspeed)
{
    m_Mark_speed=markspeed;
}
animation::~animation()
{
    delete ui;
}
