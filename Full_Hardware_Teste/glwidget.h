#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include <QWheelEvent>


class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w,int h);
    void setYPR(float Y,float P,float R);
    void setY(float Y);
    void setYPROffset(float Y,float P,float R);


    float zNear,zFar,AngleP;


private:
    QTimer timer;
    bool active;
    float yaw,pitch,roll;
    float yawOffset,pitchOffset,rollOffset;
    int With,Heig;

    void wheelEvent(QWheelEvent* event);

};

#endif // GLWIDGET_H
