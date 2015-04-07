/*************************************************************************
    CSC418/2504, Winter 20l5
    Assignment 1

    Instructions:
        See main.cpp for more instructions.

        This file contains the OpenGL portion of the main window.
**************************************************************************/

#ifndef __GLWidget_h__
#define __GLWidget_h__

#include "include_gl.h"
#include "GLState.h"
#include "GLShape.h"
#include <QtOpenGL/QtOpenGL>

// Before transformed, this class displays a unit square 
//centered closer to the one of the edges.
class UnitSquare : public GLShape
{
public:
    using GLShape::initialize;

    void initialize(int shader_input_location)
    {
	// Use two triangles to create the square.
        GLfloat square_vertices[][2] =
        {
            { -0.5, -0.5 },  // Triangle 1
            {  0.5, -0.5 },
            {  0.5,  0.5 },
            { -0.5, -0.5 },  // Triangle 2
            {  0.5,  0.5 },
            { -0.5,  0.5 },
        };
		
		
        initialize(
	    shader_input_location,
            reinterpret_cast<const GLfloat *>(square_vertices),
            /*num_vertices=*/6,
	    GL_TRIANGLES); // Each group of three coordinates is a triangle
    
    }
};



// Before transformed, this class displays a unit circle centered at the
// origin.
class UnitCircle : public GLShape
{
public:
    using GLShape::initialize;

    void initialize(int shader_input_location, int num_circle_segments)
    {
        // We will draw a circle as a triangle fan.  We are careful to send
	// the second coordinate twice to properly close the circle.
        //        3     2     1
        //         +----+----+
        //        / \   |   /
        //       /   \  |  /
        //      /     \ | /
        //     /       \|/
        //   4+---------+ 0
        //        ...
        std::vector<GLfloat> circle_vertices;
        circle_vertices.push_back(0.0);
        circle_vertices.push_back(0.0);
        for (int i=0; i<=num_circle_segments; ++i)
        {
            double angle = (2 * M_PI * i) / num_circle_segments;
            circle_vertices.push_back(cos(angle));
            circle_vertices.push_back(sin(angle));
        }

        initialize(
	    shader_input_location,
            &circle_vertices[0],
            num_circle_segments + 1,
	    GL_TRIANGLE_FAN);
    }
};


//============================ADDED============================
//Shapes for the body elements
//tetragon used for the arm
class Tetragon : public GLShape
{
public:
    using GLShape::initialize;

    void initialize(int shader_input_location)
    {
	// Use two triangles to create the square.
        GLfloat square_vertices[][2] =
        {
            { -0.3, -0.5 },  // Triangle 1
            {  0.3, -0.5 },
            {  0.5,  0.5 },
            { -0.3, -0.5 },  // Triangle 2
            {  0.5,  0.5 },
            { -0.5,  0.5 },  
        };
		
		
        initialize(
	    shader_input_location,
            reinterpret_cast<const GLfloat *>(square_vertices),
            /*num_vertices=*/6,
	    GL_TRIANGLES); // Each group of three coordinates is a triangle
    
    }
};


// pentagon used for the head
class Pentagon : public GLShape
{
public:
    using GLShape::initialize;

    void initialize(int shader_input_location)
    {
	// Use three triangles to create the polygon.
        GLfloat pentagon_vertices[][2] =
        {
            { -1.0, -1.0 },  // Triangle 1
            {  1.0, -1.0 },
            {  0.8,  0.0 },
            { -1.0, -1.0 },  // Triangle 2
            { -0.5,  0.3 },
            {  0.8,  0.0 },
            { -1.0, -1.0 },  // Triangle 3
            { -0.5,  0.3 },
            { -0.8,  0.0 },
        };

        initialize(
	    shader_input_location,
            reinterpret_cast<const GLfloat *>(pentagon_vertices),
            /*num_vertices=*/9,
	    GL_TRIANGLES); // Each group of three coordinates is a triangle
    }
};


// hexagon used for the body
class Hexagon : public GLShape
{
public:
    using GLShape::initialize;

    void initialize(int shader_input_location)
    {
	// Use four triangles to create the hexagon.
        GLfloat hexagon_vertices[][2] =
        {
            { -0.6, -0.5 },  // Triangle 1
            {  0.6, -0.5 },
            {  1.0,  0.0 },
            {  0.3,  1.0 },  // Triangle 2
            { -0.3,  1.0 },
            { -1.0,  0.0 },
            { -0.6, -0.5 },  // Triangle 3
            {  1.0,  0.0 },
            { -1.0,  0.0 },
            { -1.0,  0.0 },  // Triangle 4
            {  0.3,  1.0 },
            {  1.0,  0.0 },
        };

        initialize(
	    shader_input_location,
            reinterpret_cast<const GLfloat *>(hexagon_vertices),
            /*num_vertices=*/12,
	    GL_TRIANGLES); // Each group of three coordinates is a triangle
    }
};


//============================ADDED============================



class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    // These values control the bounds to display on the joint angle sliders.
    //////////////////////////////////////////////////////////////////////////
    // TODO:
    //   Add different ranges for the different joints.  Use these ranges
    //   when constructing sliders and when animating joints.
    //////////////////////////////////////////////////////////////////////////
    static const int JOINT_MIN = -45;
    static const int JOINT_MAX = 45;
    
    //============================ADDED============================
    static const int NECK_MIN = -10;
    static const int NECK_MAX = 10;
    static const int LEG_MIN = -40;
    static const int LEG_MAX = 40;
    static const int FOOT_MIN = -30;
    static const int FOOT_MAX = 30;
    static const int BEAK_MIN = -4.0f;
    static const int BEAK_MAX = 4.0f;
    static const int X_MIN = -60.0f;
    static const int X_MAX = 60.0f;
    static const int Y_MIN = -30.0f;
    static const int Y_MAX = 30.0f;
    //============================ADDED============================
    
    GLWidget(QWidget *parent=NULL);

public slots:
    // This method is called when the user changes the joint angle slider.
    //////////////////////////////////////////////////////////////////////////
    // TODO:
    //   There is currently only one joint, but you need to add more.
    //////////////////////////////////////////////////////////////////////////
    void setJointAngle(int angle)
    {
        // This method is called when the user changes the slider value.
        m_joint_angle = angle;
	
        // Call update() to trigger a redraw.
        update();
    }

    //============================ADDED============================
    void setLegAngle(int angle)
    {
        // This method is called when the user changes the slider value.
        m_leg_angle = angle;
	
        // Call update() to trigger a redraw.
        update();
    }
    
    void setHeadAngle(int angle)
    {
        // This method is called when the user changes the slider value.
        m_head_angle = angle;
	
        // Call update() to trigger a redraw.
        update();
    }
    
    void setFootAngle(int angle)
    {
        // This method is called when the user changes the slider value.
        m_foot_angle = angle;
	
        // Call update() to trigger a redraw.
        update();
    }
    
    void setBeakMove(int range)
    {
        // This method is called when the user changes the slider value.
        m_beak = range;
     
        // Call update() to trigger a redraw.
        update();
    }
    
    void setXMove(int range)
    {
        // This method is called when the user changes the slider value.
        m_x_move = range;
        
        // Call update() to trigger a redraw.
        update();
    }
    
    void setYMove(int range)
    {
        // This method is called when the user changes the slider value.
        m_y_move = range;
        
        // Call update() to trigger a redraw.
        update();
    }
    
  
    //============================ADDED============================
    
    
    void onPressAnimate(int is_animating)
    {
        // This method is called when the user changes the animation checkbox.
        m_is_animating = (bool)is_animating;
        m_animation_frame = 0;
        update();
    }

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void timerEvent(QTimerEvent *event);

private:
    GLTransformStack &transformStack()
    { return m_gl_state.transformStack(); }

private:
    GLState m_gl_state;
    bool m_is_animating;
    int m_animation_frame;
    UnitSquare m_unit_square;
    UnitCircle m_unit_circle;
    
    double m_joint_angle;
    //============================ADDED============================
    Hexagon m_hexagon;
    Pentagon m_pentagon;
    Tetragon m_tetragon;
    //////////////////////////////////////////////////////////////////////////
    // TODO: Add additional joint parameters.
    //////////////////////////////////////////////////////////////////////////
    
    double m_head_angle;
    double m_leg_angle;
    double m_foot_angle;
    double m_beak;
    double m_x_move;
    double m_y_move;
    
    //============================ADDED============================
};

#endif
