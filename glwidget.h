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
    std::shared_ptr<Scene> m_scene;
};
