#include "robotcontrol.h"

#include <QLabel>
#include <QMessageBox>

#include <iostream>

namespace HIC
{

RobotControl::RobotControl(QWidget *parent) : QWidget(parent), _glWidget(NULL)
{
    this->setLayout(new QVBoxLayout(this));
}

void RobotControl::setGLWidget(HIC::ApplicationGLWidget* glWidget)
{
    _glWidget = glWidget;

    PDC::Robot* robot = _glWidget->robot();

    for(int index=0; index < robot->LinkCount(); index++)
    {
        PDC::Link* link = robot->GetLink(index);
        HIC::JointControl* jointControl = new HIC::JointControl(this, link, _glWidget);
        this->layout()->addWidget(jointControl);
    }
}


} // namespace HIC
