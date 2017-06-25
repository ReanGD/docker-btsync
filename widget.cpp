#include "widget.h"
#include "helper.h"

#include <QPaintEvent>
#include <QPainter>
#include <QTimer>

Widget::Widget(Helper *helper, QWidget *parent)
    : QWidget(parent)
    , helper(helper)
{
    setFixedSize(800, 600);
}

void Widget::animate()
{
    update();
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    helper->paint(&painter, event->rect());
    painter.end();
}
