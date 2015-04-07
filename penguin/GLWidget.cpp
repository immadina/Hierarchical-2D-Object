/*************************************************************************
    CSC418/2504, Winter 20l5
    Assignment 1

    Instructions:
        See main.cpp for more instructions.

        This file contains the class OpenGL portion of the main window.
**************************************************************************/

#include "GLWidget.h"
#include <iostream>

static QGLFormat createQGLFormat()
{
    // Return a QGLFormat object that tells Qt information about what
    // OpenGL context we would like.
    QGLFormat format(QGL::SampleBuffers);
    if (supportsNewOpenGL())
    {
	// Choose a version of OpenGL that supports vertex array objects and
	// tell it that we do not want support for deprecated functions.
        format.setVersion(3, 3);
        format.setProfile(QGLFormat::CoreProfile);
    }
    return format;
}

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(createQGLFormat(), parent)
    , m_is_animating(false)
    , m_animation_frame(0)
    , m_joint_angle(0)
    , m_head_angle(0)
    , m_leg_angle(0)
    , m_foot_angle(0)
{
    // Start a timer that will call the timerEvent method every 50ms.
    startTimer(/*milliseconds=*/50);
}

void GLWidget::initializeGL()
{
    m_gl_state.initializeGL();

    // To aid with troubleshooting, print out which version of OpenGL we've
    // told the driver to use.
    std::cout << "Using OpenGL: " << glGetString(GL_VERSION) << std::endl;

    // Copy the data for the shapes we'll draw into the video card's memory.
    m_unit_square.initialize(m_gl_state.VERTEX_POSITION_SHADER_LOCATION);
    m_unit_circle.initialize(
	m_gl_state.VERTEX_POSITION_SHADER_LOCATION,
	/*num_circle_segments=*/100);
	
	
	//============================ADDED============================
	m_hexagon.initialize(m_gl_state.VERTEX_POSITION_SHADER_LOCATION);
	m_pentagon.initialize(m_gl_state.VERTEX_POSITION_SHADER_LOCATION);
	m_tetragon.initialize(m_gl_state.VERTEX_POSITION_SHADER_LOCATION);
	//============================ADDED============================
	

    // Tell OpenGL what color to fill the background to when clearing.
    glClearColor(/*red=*/0.7f, /*green=*/0.7f, /*blue=*/0.9f, /*alpha=*/1.0f);

}

void GLWidget::resizeGL(int width, int height)
{
    // Respond to the window being resized by updating the viewport and
    // projection matrices.

    checkForGLErrors();

    // Setup projection matrix for new window
    m_gl_state.setOrthographicProjectionFromWidthAndHeight(width, height);

    // Update OpenGL viewport and internal variables
    glViewport(0, 0, width, height);
    checkForGLErrors();
}

void GLWidget::timerEvent(QTimerEvent *)
{
    // Respond to a timer going off telling us to update the animation.
    if (!m_is_animating)
        return;

    // increment the frame number.
    m_animation_frame++;

    // Update joint angles.
    const double joint_rot_speed = 0.1;
    double joint_rot_t =
        (sin(m_animation_frame * joint_rot_speed) + 1.0) / 2.0;
    m_joint_angle = joint_rot_t * JOINT_MIN + (1 - joint_rot_t) * JOINT_MAX;

    //////////////////////////////////////////////////////////////////////////
    // TODO:
    //   Modify this function to animate the character's joints
    //   Note: Nothing should be drawn in this function!
    //////////////////////////////////////////////////////////////////////////
	
    //============================ADDED============================
    m_head_angle = joint_rot_t * NECK_MIN + (1 - joint_rot_t) * NECK_MAX;
    m_leg_angle = joint_rot_t * LEG_MIN + (1 - joint_rot_t) * LEG_MAX;
    m_foot_angle = joint_rot_t * FOOT_MIN + (1 - joint_rot_t) * FOOT_MAX;
    m_beak = joint_rot_t * BEAK_MAX + (1 - joint_rot_t) * BEAK_MIN;
    m_x_move = joint_rot_t * X_MIN + (1 - joint_rot_t) * X_MAX;
    m_y_move = joint_rot_t * Y_MAX + (1 - joint_rot_t) * Y_MIN;
    //============================ADDED============================
	
	
	
    // Tell this widget to redraw itself.
    update();
}

void GLWidget::paintGL()
{
    // This method gets called by the event handler to draw the scene, so
    // this is where you need to build your scene -- make your changes and
    // additions here.  All rendering happens in this function.

    checkForGLErrors();

    // Clear the screen with the background colour.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  

    // Setup the model-view transformation matrix stack.
    transformStack().loadIdentity();
    checkForGLErrors();

    //////////////////////////////////////////////////////////////////////////
    // TODO:
    //   Modify this function draw the scene.  This should include function
    //   calls to pieces that apply the appropriate transformation matrices
    //   and render the individual body parts.
    //////////////////////////////////////////////////////////////////////////

    // Draw our hinged object
    
    //const float BODY_WIDTH = 60.0f;
    //const float BODY_LENGTH = 100.0f;
    //const float ARM_LENGTH = 100.0f;
    //const float ARM_WIDTH = 20.0f;

	//============================ADDED============================
	const float BODY_WIDTH = 100.0f;
    const float BODY_LENGTH = 200.0f;
    const float ARM_LENGTH = 120.0f;
    const float ARM_WIDTH = 60.0f;
	const float HEAD_LENGTH = 60.0f;
    const float HEAD_WIDTH = 50.0f;
    const float LEG_WIDTH = 20.0f;
    const float LEG_LENGTH = 80.0f;
    const float BEAK_WIDTH = 5.0f;
    const float BEAK_LENGTH = 40.0f;
    
    // Note that successive transformations are applied *before* the previous
    // ones.

    // Push the current transformation matrix on the stack
    transformStack().pushMatrix();
    
    	//move penguin left to right
        transformStack().translate(m_x_move, 0.0);
        
        //move penguin up and down
		transformStack().translate(0.0, m_y_move);
        
        // Draw the 'body'
        transformStack().pushMatrix();
            // Scale square to size of body
            transformStack().scale(BODY_WIDTH, BODY_LENGTH);

            // Set the colour to white
            m_gl_state.setColor(1.0, 1.0,1.0);

            // Draw the body
	    	m_hexagon.draw();
        transformStack().popMatrix();

        //Head objects 
        transformStack().pushMatrix();
    		
        	transformStack().translate(0.0, BODY_LENGTH + HEAD_LENGTH/4);

        	// Rotate along the hinge
        	transformStack().rotateInDegrees(m_head_angle);
        	transformStack().translate(0.0, 2*HEAD_LENGTH/4);
        		
        	//draw the head shape
			transformStack().pushMatrix();
        		// Scale the size of the head
        		transformStack().scale(HEAD_WIDTH, HEAD_LENGTH);
        		
        		m_gl_state.setColor(0.0, 0.0, 0.3);
	    		m_pentagon.draw();
	
       		// Retrieve the previous state of the transformation stack
        	transformStack().popMatrix();
                
        	//Lower beak (moves up and down)
        	transformStack().pushMatrix();
				transformStack().translate(-HEAD_LENGTH, -HEAD_LENGTH/2);
                        
                //move beak up and down
                transformStack().translate(0.0, m_beak);
                        
                //draw "beak"
				transformStack().pushMatrix();
                    // Scale the size of the beak
        			transformStack().scale(BEAK_LENGTH, BEAK_WIDTH);
        			
        			// Draw the square for the beak
        			m_gl_state.setColor(1.0, 1.0, 1.0);
	    			m_unit_square.draw();
	    			
				transformStack().popMatrix();
			
			transformStack().popMatrix();
			
			//Upper beak (doeasn't move)
			transformStack().pushMatrix();
				transformStack().translate(-HEAD_LENGTH, -HEAD_LENGTH/2 + 2*BEAK_WIDTH);
        		//transformStack().translate(-HEAD_LENGTH, -HEAD_LENGTH/2 + 2*BEAK_WIDTH);
        		// Scale the size of the beak
        		transformStack().scale(BEAK_LENGTH, 2*BEAK_WIDTH);
        			
        		// Draw the square for the beak
        		m_gl_state.setColor(1.0, 1.0, 1.0);
	    		m_unit_square.draw();
			
			transformStack().popMatrix();
			
			//Eye
			transformStack().pushMatrix();
			
            	transformStack().translate(-HEAD_WIDTH/2, 0.0);
				transformStack().pushMatrix();
					transformStack().scale(6.0f, 6.0f);
        			m_gl_state.setColor(1.0, 1.0, 1.0);	
        			m_unit_circle.draw();
        		transformStack().popMatrix();
        		
        		transformStack().scale(3.0f, 3.0f);
        		m_gl_state.setColor(0.0, 0.0, 0.0);	
        		m_unit_circle.draw();
        		
			transformStack().popMatrix();
			
       	// Retrieve the previous state of the transformation stack
        transformStack().popMatrix();
    	
    	//draw the joint of a head and body
    	transformStack().pushMatrix();
   
   			transformStack().translate(0.0, BODY_LENGTH);
			transformStack().scale(5.0f, 5.0f);
        	m_gl_state.setColor(0.0, 1.0, 1.0);	
        	m_unit_circle.draw();
   
    	transformStack().popMatrix();
    	
    	
    	
    	//Draw the right leg
    	transformStack().pushMatrix();
    		// Move the leg to the joint hinge
        	transformStack().translate(BODY_WIDTH/2, -BODY_LENGTH/2 + LEG_WIDTH/2);
        	
        	// Rotate along the hinge
        	transformStack().rotateInDegrees(m_leg_angle);
        	
        	// Move to center location of the leg
			transformStack().translate(0.0, -LEG_LENGTH/2 + LEG_WIDTH/2);
			
			transformStack().pushMatrix();
				transformStack().pushMatrix();
			
					transformStack().scale(LEG_WIDTH, LEG_LENGTH);
                	//transformStack().translate(0.0, -0.5);
                	         
        			// Draw the square for the leg
        			m_gl_state.setColor(0.0, 0.0, 0.3);
	    			m_unit_square.draw();
        	
                // Retrieve the previous state of the transformation stack
            	transformStack().popMatrix();
            	
            	transformStack().translate(0.0, -LEG_LENGTH/2 + LEG_WIDTH/2);
			
        		// Rotate along the hinge
        		transformStack().rotateInDegrees(m_foot_angle);
        		
				transformStack().translate(-LEG_LENGTH/2 + LEG_WIDTH/2, 0.0);
                
                transformStack().scale(LEG_LENGTH, LEG_WIDTH);
        			 
        		// Draw the square for the foot
        		m_gl_state.setColor(0.0, 0.0, 0.3);
	    		m_unit_square.draw();
            
             // Retrieve the previous state of the transformation stack	
        	transformStack().popMatrix();	
        	
        	//draw the ankle joint 
        	transformStack().translate(0.0, -LEG_LENGTH/2 + 10.0f);
			transformStack().scale(5.0f, 5.0f);
        	m_gl_state.setColor(0.0, 1.0, 1.0);	
        	m_unit_circle.draw();
            	
        // Retrieve the previous state of the transformation stack    	 
		transformStack().popMatrix();
         
        //draw the joint of a body and a right leg          
   		transformStack().pushMatrix();
   
   			transformStack().translate(BODY_WIDTH/2, -BODY_LENGTH/2 - LEG_LENGTH/4);
   			transformStack().translate(0.0, LEG_LENGTH/2 - LEG_WIDTH/2);
			transformStack().scale(5.0f, 5.0f);
        	m_gl_state.setColor(0.0, 1.0, 1.0);	
        	m_unit_circle.draw();
   
    	transformStack().popMatrix();
   
    	
    	
    	//Draw left leg
    	transformStack().pushMatrix();
    		// Move the leg to the joint hinge
        	transformStack().translate(-BODY_WIDTH/2, -BODY_LENGTH/2 + LEG_WIDTH/2);
        	
        	// Rotate along the hinge
        	transformStack().rotateInDegrees(m_leg_angle);
			
			// Move to center location of the leg
			transformStack().translate(0.0, -LEG_LENGTH/2 + LEG_WIDTH/2);
			
			transformStack().pushMatrix();
				transformStack().pushMatrix();
			
					transformStack().scale(LEG_WIDTH, LEG_LENGTH);
                	//transformStack().translate(0.0, -0.5);
                	         
        			// Draw the square for the leg
        			m_gl_state.setColor(0.0, 0.0, 0.3);
	    			m_unit_square.draw();
        	
                // Retrieve the previous state of the transformation stack
            	transformStack().popMatrix();
            	
            	transformStack().translate(0.0, -LEG_LENGTH/2 + LEG_WIDTH/2);
			
        		// Rotate along the hinge
        		transformStack().rotateInDegrees(m_foot_angle);
        		
				transformStack().translate(-LEG_LENGTH/2 + LEG_WIDTH/2, 0.0);
                
                transformStack().scale(LEG_LENGTH, LEG_WIDTH);
        			 
        		// Draw the square for the foot
        		m_gl_state.setColor(0.0, 0.0, 0.3);
	    		m_unit_square.draw();
            
             // Retrieve the previous state of the transformation stack	
        	transformStack().popMatrix();	
        	
        	//draw the ankle joint 
        	transformStack().translate(0.0, -LEG_LENGTH/2 + 10.0f);
			transformStack().scale(5.0f, 5.0f);
        	m_gl_state.setColor(0.0, 1.0, 1.0);	
        	m_unit_circle.draw();
            	
        // Retrieve the previous state of the transformation stack    	 
		transformStack().popMatrix();
        
        //draw the joint ob a body and a left leg         
   		transformStack().pushMatrix();
   
   			transformStack().translate(-BODY_WIDTH/2, -BODY_LENGTH/2 - LEG_LENGTH/4);
   			transformStack().translate(0.0, LEG_LENGTH/2 - LEG_WIDTH/2);
			transformStack().scale(5.0f, 5.0f);
        	m_gl_state.setColor(0.0, 1.0, 1.0);	
        	m_unit_circle.draw();
   
    	transformStack().popMatrix();
    	
    	
    	
        // Draw the 'arm'
      	transformStack().pushMatrix();
        	// Move the arm to the joint hinge
        	transformStack().translate(0.0, BODY_LENGTH/2  - 10.0f);

       		 // Rotate along the hinge
        	transformStack().rotateInDegrees(m_joint_angle);
			
			// Move to center location of arm, under previous rotation
			transformStack().translate(0.0, -ARM_LENGTH/2 + 10.0f);
			
			transformStack().pushMatrix();
        		// Scale the size of the arm
        		transformStack().scale(ARM_WIDTH, ARM_LENGTH);

        		// Move to center location of arm, under previous rotation
        		//transformStack().translate(0.0, -0.5);

        		// Draw the square for the arm
        		m_gl_state.setColor(0.0, 0.0, 0.3);
        		m_tetragon.draw();

		 	transformStack().popMatrix();
		transformStack().popMatrix(); 
		
		//draw the arm joint
		transformStack().translate(0.0, BODY_LENGTH/2 - 10.0f);
		transformStack().scale(5.0f, 5.0f);
        m_gl_state.setColor(0.0, 1.0, 1.0);	
        m_unit_circle.draw();
        //transformStack().popMatrix();

    // Retrieve the previous state of the transformation stack
    transformStack().popMatrix();
	 
	//============================ADDED============================ 
	 
    // Execute any GL functions that are in the queue just to be safe
    glFlush();
    checkForGLErrors();
}

