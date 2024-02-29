#include "animationsetwidget.h"
#include "ui_widget.h"


AnimationSetWidget::AnimationSetWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setData(ProcessJump,150,150);
    setData(ProcessLine,200,300);
    int numPoints = 50;  // 将圆分成20份
    // Center of the circle
    qreal centerX = 250;
    qreal centerY = 250;
    // Radius of the circle
    qreal radius = 50;
    for (int i = 0; i <=numPoints; ++i) {
        qreal angle = M_PI + 2 * M_PI * (i /(qreal)numPoints);
        if (i == 0) {
            setData(ProcessJump,centerX + radius * cos(angle),centerY + radius * sin(angle));
            } else {
            setData(ProcessLine,centerX + radius * cos(angle),centerY + radius * sin(angle));
            }
    }

}

AnimationSetWidget::~AnimationSetWidget()
{
    delete ui;
}

void AnimationSetWidget::on_pushButton_clicked()
{
    animation animation;
    //动画类获取链表信息
    animation.GetData(MarkData_List);
    //获取倍速
    animation.setSpeedFactor(ui->lineEdit_Factor->text().toDouble());
    //设置加工速度
    animation.setJumpSpeed(ui->lineEdit_Jump->text().toDouble());
    animation.setMarkSpeed(ui->lineEdit_Mark->text().toDouble());
    //获取平面参数
    animation.setplatformData(ui->lineEdit_platform_W->text().toInt(), ui->lineEdit_platform_H->text().toInt(),
                              ui->lineEdit_platform_X->text().toDouble(),ui->lineEdit_platform_Y->text().toDouble());
   //弹出动画
   animation.resize(500, 500);
   animation.exec();
}

//输入链表数据
void AnimationSetWidget::setData(PROCESSTYPE processtype, qreal xPos, qreal yPos)
{
    LASER_MARK_DATA m;
    m.mProcessType=processtype;
    m.mXY_Data.X_Pos=xPos;
    m.mXY_Data.Y_Pos=yPos;
    MarkData_List.append(m);
}

//对输入进行限制
void AnimationSetWidget::isWithinLimits(QLineEdit* lineEdit, double max, double min)
{
    double input =lineEdit->text().toDouble();
        if (input < min || input > max) {
            QMessageBox::warning(this, "Warning", "Please enter a number between "
                                 +QString::number(min,'f',2)+" and "+QString::number(max,'f',2));
            lineEdit->clear(); // 清空文本框内容
        }
}

void AnimationSetWidget::isWithinLimits(QLineEdit *lineEdit, int max, int min)
{
    int input =lineEdit->text().toInt();
     if (input < min || input > max) {
         QMessageBox::warning(this, "Warning", "Please enter a number between "
                              +QString::number(min)+" and "+QString::number(max));
         lineEdit->clear(); // 清空文本框内容
     }
}
void AnimationSetWidget::on_lineEdit_Factor_editingFinished()
{
    double max=10.00;
    double min=0.00;
    isWithinLimits(ui->lineEdit_Factor,max,min);
}

void AnimationSetWidget::on_lineEdit_Jump_editingFinished()
{
        isWithinLimits(ui->lineEdit_Jump,200.00,0.00);
}

void AnimationSetWidget::on_lineEdit_Mark_editingFinished()
{
    isWithinLimits(ui->lineEdit_Mark,100.00,0.00);
}

void AnimationSetWidget::on_lineEdit_platform_X_editingFinished()
{
    isWithinLimits(ui->lineEdit_platform_X,500.00,0.00);
}

void AnimationSetWidget::on_lineEdit_platform_Y_editingFinished()
{
    isWithinLimits(ui->lineEdit_platform_Y,500.00,0.00);
}

void AnimationSetWidget::on_lineEdit_platform_W_editingFinished()
{

    isWithinLimits(ui->lineEdit_platform_W,500,0);
}

void AnimationSetWidget::on_lineEdit_platform_H_editingFinished()
{
    isWithinLimits(ui->lineEdit_platform_H,500,0);
}
