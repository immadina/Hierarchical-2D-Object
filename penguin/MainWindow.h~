/*************************************************************************
    CSC418/2504, Winter 20l5
    Assignment 1
  
  
    Instructions:
        See main.cpp for more instructions.

        This file contains the class for the main window of the program.
**************************************************************************/

#ifndef __MainWindow_h__
#define __MainWindow_h__

#include <QtGui/QtGui>
#include "GLWidget.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow()
    {
        // Create a GLWidget to hold the OpenGL viewport.
        m_gl_widget = new GLWidget();

        // Create a checkbox to turn animation on and off, and make it
        // call GLWidget::onPressAnimate when checked.
        m_animate_checkbox = new QCheckBox("Animate", this);
        connect(
            m_animate_checkbox, SIGNAL(stateChanged(int)),
            m_gl_widget, SLOT(onPressAnimate(int)));

        // Create a button to quit the program.
        m_quit_button = new QPushButton("Quit", this);
        connect(
            m_quit_button, SIGNAL(clicked(bool)),
            this, SLOT(onPressQuit(bool)));

        m_main_layout = new QVBoxLayout();
        m_main_layout->addWidget(m_gl_widget);

        // Create a slider to control the joint angle, and make it call
        // GLWidget::setJointAngle when the slider value changes.
        m_slider = create_joint_angle_slider(
	    "Joint", GLWidget::JOINT_MIN, GLWidget::JOINT_MAX);
        connect(
            m_slider, SIGNAL(valueChanged(int)),
            m_gl_widget, SLOT(setJointAngle(int)));

        //////////////////////////////////////////////////////
        // TODO: Add additional joint sliders here
        //////////////////////////////////////////////////////

        
        //============================ADDED============================
        m_slider_beak = create_joint_angle_slider(
	    "Beak", GLWidget::BEAK_MIN, GLWidget::BEAK_MAX);
        connect(
            m_slider_beak, SIGNAL(valueChanged(int)),
            m_gl_widget, SLOT(setBeakMove(int)));
        
        m_slider_neck = create_joint_angle_slider(
	    "Head", GLWidget::NECK_MIN, GLWidget::NECK_MAX);
        connect(
            m_slider_neck, SIGNAL(valueChanged(int)),
            m_gl_widget, SLOT(setHeadAngle(int)));
            
        m_slider_leg = create_joint_angle_slider(
	    "Leg joint", GLWidget::LEG_MIN, GLWidget::LEG_MAX);
        connect(
            m_slider_leg, SIGNAL(valueChanged(int)),
            m_gl_widget, SLOT(setLegAngle(int)));
        
        m_slider_foot = create_joint_angle_slider(
	    "Foot joint", GLWidget::FOOT_MIN, GLWidget::FOOT_MAX);
        connect(
            m_slider_foot, SIGNAL(valueChanged(int)),
            m_gl_widget, SLOT(setFootAngle(int)));
      
        m_slider_x = create_joint_angle_slider(
	    "Move left and right", GLWidget::X_MIN, GLWidget::X_MAX);
        connect(
            m_slider_x, SIGNAL(valueChanged(int)),
            m_gl_widget, SLOT(setXMove(int)));
        
        m_slider_y = create_joint_angle_slider(
	    "Move up and down", GLWidget::Y_MIN, GLWidget::Y_MAX);
        connect(
            m_slider_y, SIGNAL(valueChanged(int)),
            m_gl_widget, SLOT(setYMove(int)));
        //============================ADDED============================
        
        
        m_main_layout->addWidget(m_animate_checkbox);
        m_main_layout->addWidget(m_quit_button);
        setLayout(m_main_layout);

        m_slider->setValue(0);
        m_slider_neck->setValue(0);
        m_slider_leg->setValue(0);
        m_slider_foot->setValue(0);
        m_slider_beak->setValue(0);
        m_slider_x->setValue(0);
        m_slider_y->setValue(0);
        setWindowTitle("CSC418/2504 Assignment 1");
    }

public slots:
    void onPressQuit(bool)
    {
        exit(0);
    }

private:
    QSlider *create_joint_angle_slider(
	const char *label, int min_angle, int max_angle)
    {
        QSlider *slider = new QSlider(Qt::Horizontal, this);
        slider->setRange(min_angle, max_angle);
        slider->setSingleStep(1);
        slider->setPageStep(5);
        slider->setTickInterval(5);
        slider->setTickPosition(QSlider::TicksBelow);

	QBoxLayout *layout = new QHBoxLayout();
	layout->addWidget(new QLabel(label));
	layout->addWidget(slider);
	m_main_layout->addLayout(layout);

        return slider;
    }

    GLWidget *m_gl_widget;
    QCheckBox *m_animate_checkbox;
    QPushButton *m_quit_button;
    QSlider *m_slider;
    QSlider *m_slider_neck;
    QSlider *m_slider_leg;
    QSlider *m_slider_foot;
    QSlider *m_slider_beak;
    QSlider *m_slider_x;
    QSlider *m_slider_y;
    QVBoxLayout *m_main_layout;
};

#endif
