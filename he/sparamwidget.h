#ifndef SPARAMWIDGET_H
#define SPARAMWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QLabel>

namespace Ui {
class sParamWidget;
}

class sParamWidget : public QWidget
{
    Q_OBJECT

public:
    explicit sParamWidget(QWidget* srcWidget, QWidget* desWidget, QWidget *parent, int id, bool isCopyed);
    ~sParamWidget();

    int paramWidgetCount(){
        return count;
    }

protected:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void paintEvent(QPaintEvent *event);

private:
    Ui::sParamWidget *ui;
    QPoint mMovePosition;
    bool mMoving;
    bool alreadyMoved;      //移动之后，不再响应鼠标事件
    static int count;       //记录本控件个数
    static int count_in_des;//拖到目标控件的控件个数，用于计算拖动之后在目标控件中的位置
    QWidget* srcWidget;     //来源控件，本控件初始位置
    QWidget* desWidget;     //目标控件，本控件目标位置
    int id;                 //用于确定初始位置及显示在控件上的内容
    bool isCopyed;          //是否是复制的，若是，则关闭鼠标事件响应
    QLabel* infLabel;       //用于显示在控件右上角

signals:
    void cntChanged();      //拖走了复制一个
};

#endif // SPARAMWIDGET_H
