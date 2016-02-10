#ifndef APPLICATIONGLWIDGET_H
#define APPLICATIONGLWIDGET_H

#include <QGLWidget>
#include <QGenericMatrix>
#include <GL/gl.h>

#include "Robot.h"

namespace HIC
{
    class ApplicationGLWidget : public QGLWidget
    {
        Q_OBJECT

    public:
        explicit ApplicationGLWidget(QWidget *parent = 0);
        ~ApplicationGLWidget();
        void setRobot(PDC::Robot* robot);
        PDC::Robot* robot();

        void rotateX(double angle);
        void rotateY(double angle);
        void rotateZ(double angle);

        void translateX(double value);
        void translateY(double value);
        void translateZ(double value);

    protected:
        void initializeGL();
        void paintGL();
        void resizeGL(int width, int height);

        void renderRobot();
        GLdouble* convertMatrixToGLFormat(double (*matrix)[4][4]);

        QGenericMatrix<4,4,double> _pose;
        int _glutArgc;
        char* _glutArgv;
        PDC::Robot* _robot;
        GLdouble* _glMatrix;
        double _angleX, _angleY, _angleZ;
        double _posX, _posY, _posZ;
    };
}

#endif // APPLICATIONGLWIDGET_H
