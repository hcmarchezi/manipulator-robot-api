#include "jointcontrol.h"

#include <QHBoxLayout>


namespace HIC {

JointControl::JointControl(QWidget *parent, PDC::Link* link, ApplicationGLWidget *glWidget): QWidget(parent), _glWidget(glWidget)
{
    _link = link;
    //Q_ASSERT(link != NULL);

    QHBoxLayout* itemLayout = new QHBoxLayout(this);

    _leftButton = new QPushButton(tr("<<"), this);

    _spinBox = new QDoubleSpinBox(this);
    _spinBox->setMaximum(2.0);
    _spinBox->setMinimum(-2.0);
    _spinBox->setDecimals(3);
    _spinBox->setMinimumSize(50,30);

    _rightButton = new QPushButton(tr(">>"), this);

    itemLayout->addWidget(_leftButton);
    itemLayout->addWidget(_spinBox);
    itemLayout->addSpacing(20);
    itemLayout->addWidget(_rightButton);

    this->setLayout(itemLayout);

    QObject::connect(_leftButton,SIGNAL(clicked()),this,SLOT(leftButtonClick()));
    QObject::connect(_spinBox, SIGNAL(valueChanged(double)), this, SLOT(jointValueChanged(double)));
    QObject::connect(_rightButton,SIGNAL(clicked()),this,SLOT(rightButtonClick()));

}

void JointControl::leftButtonClick()
{
    _spinBox->setValue(_spinBox->value() - 0.1);
}

void JointControl::rightButtonClick()
{
    _spinBox->setValue(_spinBox->value() + 0.1);
}

void JointControl::jointValueChanged(double value)
{
    if (_link != NULL)
    {
        _link->SetJointMove(value);
        _glWidget->updateGL();
    }
}

} // namespace HIC
