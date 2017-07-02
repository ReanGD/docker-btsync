#pragma once

#include <chrono>
#include <memory>
#include <QOpenGLWidget>

class World;
class GLWidget : public QOpenGLWidget {
    Q_OBJECT
public:
    GLWidget(QWidget *parent, std::shared_ptr<World> world);

    float getFps() const { return m_fps; }
protected:
    void drawScene(QPainter* painter);
    void paintEvent(QPaintEvent *event) override;
private:
    std::shared_ptr<World> m_world;
    uint32_t m_step = 0;
    float m_fps = 0.0f;
    std::chrono::steady_clock::time_point m_start;
};
