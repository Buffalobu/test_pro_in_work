#include "sparamwidget.h"
#include "ui_sparamwidget.h"
#include <QPainter>

sParamWidget::sParamWidget(QWidget* srcWidget, QWidget *desWidget, QWidget *parent, int id, bool isCopyed) :
    srcWidget(srcWidget),desWidget(desWidget), QWidget(parent), id(id), isCopyed(isCopyed),
    ui(new Ui::sParamWidget)
{
    ui->setupUi(this);
    this->resize(QSize(80, 60));
    this->setAttribute(Qt::WA_TransparentForMouseEvents, isCopyed);
    this->move(this->srcWidget->pos().x() + this->rect().width() * id + 10*(id +1), this->srcWidget->pos().y() + 10);
    mMoving = false;
    alreadyMoved = false;
    count++;
    infLabel = new QLabel(this);
    infLabel->move(10, 10);
    infLabel->setText(QString::number(id + 1));
}

int sParamWidget::count = 0;
int sParamWidget::count_in_des = 0;

sParamWidget::~sParamWidget()
{
    delete ui;
}

void sParamWidget::mousePressEvent(QMouseEvent *event)
{
    mMoving = true;
    //鼠标相对于窗口的位置=鼠标相对于整个屏幕的位置-窗口相对于整个屏幕的位置
    mMovePosition = event->globalPos() - this->pos();
    return QWidget::mousePressEvent(event);
}

void sParamWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(!desWidget || alreadyMoved){
        this->setCursor(QCursor(Qt::ArrowCursor));
        return;
    }
    //鼠标移动到控件上指针变成手形
    if(this->rect().contains(event->pos()))
        this->setCursor(QCursor(Qt::OpenHandCursor));
    else
        this->setCursor(QCursor(Qt::ArrowCursor));

    if(mMoving && (event->buttons() &&Qt::LeftButton)
            && (event->globalPos() - mMovePosition).manhattanLength() > QApplication::startDragDistance()
            && desWidget->rect().contains(QPoint(this->rect().x(), this->rect().y())))
    {
        this->move(event->globalPos() - mMovePosition);
        mMovePosition = event->globalPos() - this->pos();
    }
    return QWidget::mouseMoveEvent(event);
}

void sParamWidget:: mouseReleaseEvent(QMouseEvent *event)
{
    mMoving = false;
    if(desWidget->rect().contains(QPoint(this->rect().x(), this->rect().y()))
            && !alreadyMoved)
    {
        this->move(desWidget->pos().x() + this->rect().width() * count_in_des + 10*(count_in_des +1), desWidget->pos().y() + 10);
        count_in_des++;
        alreadyMoved = true;
        emit cntChanged();
    }
    return QWidget::mouseReleaseEvent(event);
}

/**
 * @brief 绘制控件边框
 * @param event
 */
void sParamWidget::paintEvent(QPaintEvent *event)
{
    QPainter* painter = new QPainter;
    painter->begin(this);
    painter->setPen(QPen(Qt::blue, 2, Qt::SolidLine));
    painter->drawRect(QRect(this->rect().x(), this->rect().y(), this->rect().width(), this->rect().height()));
    painter->end();
}
