#pragma once
#include <memory>
#include <QOpenGLWidget>

class Scene;
class GLWidget : public QOpenGLWidget {
    Q_OBJECT
public:
    GLWidget(QWidget *parent);
public slots:
    void animate();
protected:
    void drawScene(QPainter* painter);
    void paintEvent(QPaintEvent *event) override;
private:
    const uint16_t WIDTH = 800;
    const uint16_t HEIGHT = 600;
    const uint16_t BOT_SIZE = 5;
    std::shared_ptr<Scene> m_scene;
};
