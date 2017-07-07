#include "window.h"
#include <QTimer>
#include <QLabel>
#include <QGridLayout>
#include "glwidget.h"
#include "settings.h"
#include "scene.h"


Window::Window()
  : m_world(std::make_shared<World>())
  , m_glWidget(new GLWidget(this, m_world))
  , m_topInfo(new QLabel(this))
  , m_bottomInfo(new QLabel(this)) {

  setWindowTitle(tr("Evolution"));

  m_topInfo->setAlignment(Qt::AlignBottom | Qt::AlignLeft);

  QGridLayout *layout = new QGridLayout;
  layout->addWidget(m_topInfo, 0, 0);
  layout->addWidget(m_glWidget, 1, 0);
  layout->addWidget(m_bottomInfo, 2, 0);
  setLayout(layout);

  m_start = std::chrono::steady_clock::now();
  QTimer::singleShot(0, this, &Window::step);
}

void Window::step() {
  const uint32_t updatePerStep = 200;
  const uint32_t drawPerStep = 5;

  if (m_step % updatePerStep == 0) {
    auto now = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_start).count();
    float sps = (updatePerStep * 1000.0f / static_cast<float>(ms));
    float ups = (updatePerStep * 1000.0f / (drawPerStep * static_cast<float>(ms)));
    float fps = m_glWidget->getFps();
    m_start = now;
    m_topInfo->setText("Step: " + QString::number(m_step) + " (" +
                       QString::number(sps, 'f', 2) + " step/sec, " +
                       QString::number(ups, 'f', 2) + " update/sec, " +
                       QString::number(fps, 'f', 2) + " frame/sec)");
  }

  m_world->step();

  if (m_step % drawPerStep == 0) {
    m_glWidget->update();
  }
  m_step++;
  QTimer::singleShot(5, this, &Window::step);
}
