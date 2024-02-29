#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<animation.h>
#include <cmath>
#include <QIntValidator>
#include <QMessageBox>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE
#include<QLineEdit>
class AnimationSetWidget : public QWidget
{
    Q_OBJECT

public:
    AnimationSetWidget(QWidget *parent = nullptr);
    ~AnimationSetWidget();
    //输入链表数据
    void setData(PROCESSTYPE processtype,qreal xPos,qreal yPos);

private slots:
    void on_pushButton_clicked();
    void isWithinLimits(QLineEdit* lineEdit,double max,double min);
    void isWithinLimits(QLineEdit* lineEdit,int max,int min);
    void on_lineEdit_Factor_editingFinished();

    void on_lineEdit_Jump_editingFinished();

    void on_lineEdit_Mark_editingFinished();

    void on_lineEdit_platform_X_editingFinished();

    void on_lineEdit_platform_Y_editingFinished();

    void on_lineEdit_platform_W_editingFinished();

    void on_lineEdit_platform_H_editingFinished();

private:
    Ui::Widget *ui;
    QList<LASER_MARK_DATA> MarkData_List;
};

#endif // WIDGET_H
