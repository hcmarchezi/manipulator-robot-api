#ifndef HIC_ROBOTCONTROL_H
#define HIC_ROBOTCONTROL_H

#include <QWidget>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include "jointcontrol.h"
#include "applicationglwidget.h"

namespace HIC
{
    class RobotControl : public QWidget
    {
        Q_OBJECT

    public:
        explicit RobotControl(QWidget *parent = 0);
        void setGLWidget(HIC::ApplicationGLWidget* glWidget);

    protected:
        HIC::ApplicationGLWidget* _glWidget;
    };

} // namespace HIC

#endif // HIC_ROBOTCONTROL_H
