#include "glwidget.h"
#include "window.h"

#include <QGridLayout>
#include <QTimer>

Window::Window() {
  setWindowTitle(tr("Evolution"));
  GLWidget *openGL = new GLWidget(this);
  QGridLayout *layout = new QGridLayout;
  layout->addWidget(openGL, 0, 1);
  setLayout(layout);

  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, openGL, &GLWidget::animate);
  timer->start(50);
}
