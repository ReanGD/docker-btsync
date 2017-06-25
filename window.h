#pragma once

#include <QWidget>
#include "helper.h"


class Window : public QWidget
{
    Q_OBJECT
public:
    Window();
private:
    Helper helper;
};
