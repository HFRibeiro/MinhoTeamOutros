//TO Windows
/*#include "glwidget.h"
#include "GL/glut.h"
#include <GL/gl.h>			// Header File For The OpenGL32 Library
#include <GL/glu.h>			// Header File For The GLu32 Library

#include "model.h"
GLuint MyDisplayList; // added by @jeffprod_com (twitter)

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    active = false;
    yaw = 0;
    pitch = 0;
    roll = 0;
    yawOffset = 0;
    pitchOffset = 0;
    rollOffset = 0;
    connect(&timer,SIGNAL(timeout()),this,SLOT(updateGL()));
    timer.start(16);
    zNear = 0.01;
    zFar = 99.99;
    AngleP = 80;
}

void GLWidget::initializeGL()
{
        glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
        glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);				// white Background
        glClearDepth(1.0f);									// Depth Buffer Setup
        glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
        glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

        // added by @jeffprod_com (twitter)
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);

        MyDisplayList=glGenLists(1);
        glNewList(MyDisplayList,GL_COMPILE);
        glEnable(GL_TEXTURE_2D);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        Model *model = new Model();
        model->drawModel();
        //DrawModel();
        //glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        //glDisable(GL_TEXTURE_2D);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHTING);
        glEnable(GL_COLOR_MATERIAL);

        glEndList();
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer

        glLoadIdentity();									// Reset The View
        glTranslatef(0.0f,0.0f,-5.0f);

        glRotatef(-pitch +pitchOffset+40, 1, 0, 0);
        glRotatef(-yaw +yawOffset, 0, 1, 0); //+90 -> Para ficar de frente
        glRotatef(-roll +rollOffset, 0, 0, 1);

        //glBindTexture(GL_TEXTURE_2D, texture[0]);

        glColor3f(1,0,0); //Model Color
        glCallList(MyDisplayList);  // added by @jeffprod_com (twitter)

}

void GLWidget::resizeGL(int w, int h)
{
    With = w;
    Heig = h;
    glViewport(0,0,w,h);                                // Reset The Current Viewport
    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
    glLoadIdentity();									// Reset The Projection Matrix
    gluPerspective(AngleP,(float)With/Heig,zNear,zFar); // Calculate The Aspect Ratio Of The Window
    glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
    glLoadIdentity();
}

void GLWidget::setYPR(float Y, float P, float R)
{
    active = true;
    yaw = Y;
    pitch = P;
    roll = R;
}

void GLWidget::setY(float Y)
{
    active = true;
    yaw = Y;
}

void GLWidget::setYPROffset(float Y, float P, float R)
{
    yawOffset = Y;
    pitchOffset = P;
    rollOffset = R;
}
void GLWidget::wheelEvent(QWheelEvent *event)
{
    int numDegrees = event->delta() / 8;
    int numSteps = numDegrees / 15;

    AngleP = AngleP-numSteps*1;
    glViewport(0, 0, (GLint)With, (GLint)Heig);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(AngleP,(float)With/Heig,zNear,zFar);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5,0,0,0,0,1,0);

    glRotatef(-pitch +pitchOffset+40, 1, 0, 0);
    glRotatef(-yaw +yawOffset, 0, 1, 0); //+90 -> Para ficar de frente
    glRotatef(-roll +rollOffset, 0, 0, 1);

    event->accept();
}*/

//TO UBUNTU
#include "glwidget.h"
#include "GL/glut.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    active = false;
    yaw = 0;
    pitch = 0;
    roll = 0;
    yawOffset = 0;
    pitchOffset = 0;
    rollOffset = 0;
    connect(&timer,SIGNAL(timeout()),this,SLOT(updateGL()));
    timer.start(16);
    zNear = 0.01;
    zFar = 99.99;
    AngleP = 70;
}

void GLWidget::initializeGL()
{
    glClearColor(0.2,0.2,0.2,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(active)
    {
        glViewport(0, 0, (GLint)With, (GLint)Heig);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(AngleP,(float)With/Heig,zNear,zFar);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0,0,5,0,0,0,0,1,0);


        glRotatef(-pitch +pitchOffset, 1, 0, 0);
        glRotatef(-yaw+90 +yawOffset, 0, 1, 0); //+90 -> Para ficar de frente
        glRotatef(-roll +rollOffset, 0, 0, 1);
        active = false;
    }

    glColor3f(1,1,1);

    glutSolidTeapot(0.5);

}

void GLWidget::resizeGL(int w, int h)
{
    With = w;
    Heig = h;
    glViewport(0, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(AngleP,(float)With/Heig,zNear,zFar);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5,0,0,0,0,1,0);
    glRotatef(-pitch +pitchOffset, 1, 0, 0);
    glRotatef(-yaw+90 +yawOffset, 0, 1, 0); //+90 -> Para ficar de frente
    glRotatef(-roll +rollOffset, 0, 0, 1);
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    int numDegrees = event->delta() / 8;
    int numSteps = numDegrees / 15;

    AngleP = AngleP-numSteps*1;
    glViewport(0, 0, (GLint)With, (GLint)Heig);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(AngleP,(float)With/Heig,zNear,zFar);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5,0,0,0,0,1,0);

    glRotatef(-pitch +pitchOffset, 1, 0, 0);
    glRotatef(-yaw+90 +yawOffset, 0, 1, 0); //+90 -> Para ficar de frente
    glRotatef(-roll +rollOffset, 0, 0, 1);

    event->accept();
}

void GLWidget::setYPR(float Y, float P, float R)
{
    active = true;
    yaw = Y;
    pitch = P;
    roll = R;
}

void GLWidget::setY(float Y)
{
    active = true;
    yaw = Y;
}

void GLWidget::setYPROffset(float Y, float P, float R)
{
    yawOffset = Y;
    pitchOffset = P;
    rollOffset = R;
}



