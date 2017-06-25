#include "glwidget.h"
#include "helper.h"

#include <QPaintEvent>
#include <QPainter>
#include <QTimer>

GLWidget::GLWidget(Helper *helper, QWidget *parent)
    : QOpenGLWidget(parent)
    , helper(helper)
{
    setFixedSize(800, 600);
    setAutoFillBackground(false);
}

void GLWidget::animate()
{
    update();
}

void GLWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    helper->paint(&painter, event->rect());
    painter.end();
}
