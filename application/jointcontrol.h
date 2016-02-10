#ifndef HIC_JOINTCONTROL_H
#define HIC_JOINTCONTROL_H

#include <QWidget>

#include <QDoubleSpinBox>
#include <QPushButton>

#include "Link.h"
#include "applicationglwidget.h"

namespace HIC {

class JointControl : public QWidget
{
    Q_OBJECT

public:
    explicit JointControl(QWidget *parent, PDC::Link *link, HIC::ApplicationGLWidget* glWidget);

protected:
    PDC::Link* _link;
    QPushButton* _leftButton;
    QDoubleSpinBox* _spinBox;
    QPushButton* _rightButton;
    HIC::ApplicationGLWidget* _glWidget;

protected slots:
    void leftButtonClick();
    void rightButtonClick();
    void jointValueChanged(double value);

};

} // namespace HIC

#endif // HIC_JOINTCONTROL_H
