#include "applicationglwidget.h"


#include <GL/glu.h>
#include <GL/glut.h>

HIC::ApplicationGLWidget::ApplicationGLWidget(QWidget *parent)
    : QGLWidget(parent), _pose(), _glutArgc(1), _glutArgv({}), _robot(NULL),
      _glMatrix(new GLdouble[16]), _angleX(0.0), _angleY(0.0), _angleZ(0.0),
      _posX(0.0), _posY(0.0), _posZ(0.0)
{
    _pose.setToIdentity();
}

HIC::ApplicationGLWidget::~ApplicationGLWidget()
{
    delete _glutArgv;
}

void HIC::ApplicationGLWidget::setRobot(PDC::Robot* robot)
{
    _robot = robot;
}

PDC::Robot* HIC::ApplicationGLWidget::robot()
{
    return _robot;
}

void HIC::ApplicationGLWidget::rotateX(double angle)
{
    _angleX = angle;
    updateGL();
}

void HIC::ApplicationGLWidget::rotateY(double angle)
{
    _angleY = angle;
    updateGL();
}

void HIC::ApplicationGLWidget::rotateZ(double angle)
{
    _angleZ = angle;
    updateGL();
}

void HIC::ApplicationGLWidget::translateX(double value)
{
    _posX = value * 10;
    updateGL();
}

void HIC::ApplicationGLWidget::translateY(double value)
{
    _posY = value * 10;
    updateGL();
}

void HIC::ApplicationGLWidget::translateZ(double value)
{
    _posZ = value * 10;
    updateGL();
}

void HIC::ApplicationGLWidget::initializeGL()
{
    GLfloat max = 2000.0f; /////////
    glEnable(GL_DEPTH_TEST);
    glOrtho(-max,max,-max,max,-max,max);
    glClearColor (0.0f,0.0f,0.0f,1.0f);
    glColor3f(1.0f,1.0f,1.0f);
    glutInit(&_glutArgc,&_glutArgv);
}

void HIC::ApplicationGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    glMultMatrixd(_pose.data());

    glTranslated(_posX, _posY, _posZ);

    glRotated(_angleX, 1.0, 0.0, 0.0);
    glRotated(_angleY, 0.0, 1.0, 0.0);
    glRotated(_angleZ, 0.0, 0.0, 1.0);

    glBegin(GL_LINES);
        glColor3f ( 1.0f, 0.0f, 0.0f);
        glVertex3f( 0.0f, 0.0f, 0.0f);
        glVertex3f(30.0f, 0.0f, 0.0f);
        glColor3f ( 0.0f, 1.0f, 0.0f);
        glVertex3f( 0.0f, 0.0f, 0.0f);
        glVertex3f( 0.0f,30.0f, 0.0f);
        glColor3f ( 0.0f, 0.0f, 1.0f);
        glVertex3f( 0.0f, 0.0f, 0.0f);
        glVertex3f( 0.0f, 0.0f,30.0f);
    glEnd();


    // Render robot if present
    if (_robot != NULL)
    {
        renderRobot();
    }
    // Render teapot so not to leave canvas empty
    else
    {
        glColor3f(1.0f,1.0f,1.0f);
        glutWireTeapot(50.0f);
    }

    glPopMatrix();
}

void HIC::ApplicationGLWidget::resizeGL(int width, int height)
{
    // Prevents division by zero
    if (height==0) height = 1;
    if (width==0) width = 1;

     // Keep aspect ratio
     if (width <= height)
      {
            glViewport (0,0, (GLint)width, (GLint)width );
      }
      else
      {
            glViewport (0,0, (GLint)height, (GLint)height );
      }
}

void HIC::ApplicationGLWidget::renderRobot()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glColor3f(1.0f,1.0f,1.0f);

    for (unsigned int linkIndex=0; linkIndex < _robot->LinkCount(); linkIndex++)
    {
        PDC::Link* link = _robot->GetLink(linkIndex);
        PDC::LinkType* linkType = link->GetLinkType();
        PDC::Geometry* geometry = linkType->GetGeometry();

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();

        double geometryPose[4][4];
        linkType->GetGeometryPose(&geometryPose);
        GLdouble* glGeometryMatrix = convertMatrixToGLFormat(&geometryPose);
        glMultMatrixd(glGeometryMatrix);

        glBegin(GL_LINES);
        for (unsigned long faceIndex=0; faceIndex < geometry->FacesCount(); faceIndex++)
        {
            PDC::Face face = geometry->GetFace(faceIndex);
            PDC::Point vertex1, vertex2, vertex3;
            long red, green, blue;
            face.GetParameters(vertex1, vertex2, vertex3, red, green , blue);
            glBegin(GL_LINE_LOOP);
                glVertex3f(vertex1.x,vertex1.y,vertex1.z);
                glVertex3f(vertex2.x,vertex2.y,vertex2.z);
                glVertex3f(vertex3.x,vertex3.y,vertex3.z);
            glEnd();
        }
        glEnd();

        glPopMatrix();

        double pose[4][4];
        linkType->CalculateFrame(link->GetJointMove(),&pose);
        GLdouble* glMatrix = convertMatrixToGLFormat(&pose);
        glMultMatrixd(glMatrix);
    }

    glPopMatrix();
}

GLdouble* HIC::ApplicationGLWidget::convertMatrixToGLFormat(double (*matrix)[4][4])
{
    _glMatrix[0]  = (*matrix)[0][0];
    _glMatrix[1]  = (*matrix)[1][0];
    _glMatrix[2]  = (*matrix)[2][0];
    _glMatrix[3]  = (*matrix)[3][0];

    _glMatrix[4]  = (*matrix)[0][1];
    _glMatrix[5]  = (*matrix)[1][1];
    _glMatrix[6]  = (*matrix)[2][1];
    _glMatrix[7]  = (*matrix)[3][1];

    _glMatrix[8]  = (*matrix)[0][2];
    _glMatrix[9]  = (*matrix)[1][2];
    _glMatrix[10] = (*matrix)[2][2];
    _glMatrix[11] = (*matrix)[3][2];

    _glMatrix[12] = (*matrix)[0][3];
    _glMatrix[13] = (*matrix)[1][3];
    _glMatrix[14] = (*matrix)[2][3];
    _glMatrix[15] = (*matrix)[3][3];

    return _glMatrix;
}

