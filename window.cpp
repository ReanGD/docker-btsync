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
  , m_bottomInfo(new QLabel(this))
  , m_worldStep(0)
  , m_thread([this](){ worldStart(); }) {

  setWindowTitle(tr("Evolution"));

  m_topInfo->setAlignment(Qt::AlignBottom | Qt::AlignLeft);

  QGridLayout *layout = new QGridLayout;
  layout->addWidget(m_topInfo, 0, 0);
  layout->addWidget(m_glWidget, 1, 0);
  layout->addWidget(m_bottomInfo, 2, 0);
  setLayout(layout);

  m_start = std::chrono::steady_clock::now();
  QTimer::singleShot(10, this, &Window::step);
}

void Window::step() {
  if (m_step % 60 == 0) {
    auto now = std::chrono::steady_clock::now();
    auto dtSec = static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(now - m_start).count()) / 1000.0f;
    m_start = now;

    uint32_t nowWorldStep = m_worldStep;
    float sps = (nowWorldStep - m_startWorldStep) / dtSec;
    m_startWorldStep = nowWorldStep;

    QString generation = QString::number(m_world->getGeneration());
    QString life = QString::number(m_world->getGenerationStepLife());

    m_topInfo->setText("Step: " + QString::number(nowWorldStep / 1000) + "x10^3 (" + QString::number(sps, 'f', 2) + " step/sec)\n" +
                       "Fps: " + QString::number(m_glWidget->getFps(), 'f', 2) + "\n"
                       "Generation: " + generation + " (life: " + life + " step)");
  }

  m_step++;
  m_glWidget->update();
  QTimer::singleShot(40, this, &Window::step);
}

void Window::worldStart() {
  while (true) {
    m_world->step();
    m_worldStep++;
  }
}
