//
//  main_spotlight.cpp
//  HCI 557 Spotlight example
//
//  Created by Rafael Radkowski on 5/28/15.
//  Copyright (c) 2015 -. All rights reserved.
//

// stl include
#include <iostream>
#include <string>

// GLEW include
#include <GL/glew.h>

// GLM include files
//#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>


// glfw includes
#include <GLFW/glfw3.h>


// include local files
#include "controls.h"
#include "HCI557Common.h"
#include "CoordSystem.h"
#include "Sphere3D.h"


#include "ChessGame.h"

using namespace std;


// The handle to the window object
GLFWwindow*         window;

// Define some of the global variables we're using for this sample
GLuint program;

/* A trackball to move and rotate the camera view */
extern Trackball trackball;

// game instance
ChessGame* game;

bool key_flag = true;




void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////
    // Translation
    if( (key == 87 && action == GLFW_REPEAT) || (key == 87 && action == GLFW_PRESS) ) // key w
    {
        key_flag = true;
    }
    else if((key == 83 && action == GLFW_REPEAT) || (key == 83 && action == GLFW_PRESS)) // key s
    {
        key_flag = false;
	}
}


void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
    // button: The mouse button that was pressed or released.
    // action: One of GLFW_PRESS or GLFW_RELEASE.
    // mods: Bit field describing which modifier keys were held down.

    if(action == GLFW_RELEASE) {
        game->handleMouseRelease();
    }

}


int main(int argc, const char * argv[])
{


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Init glfw, create a window, and init glew

    // Init the GLFW Window
    window = initWindow();


    // Init the glew api
    initGlew();
    SetCameraManipulator(CameraTypes::CAMERA_MANIPULATOR);



    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Create some models

    // coordinate system
    CoordSystem* cs = new CoordSystem(40.0);


    // create an apperance object.


    // GLObjectObj* loadedModel1 = new GLObjectObj("../../data/chess_board_all.obj");

    game = new ChessGame();

    game->initPicking();
    // GLObjectObj* loadedModel1 = new GLObjectObj("../../data/chessobj.obj");


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Main render loop

    // Set up our background color
    static const GLfloat clear_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    // This sets the camera to a new location
    // the first parameter is the eye position, the second the center location, and the third the up vector.
    // SetViewAsLookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));


    SetViewAsLookAt(glm::vec3(32.0f, 22.0f, 65.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));


    // Enable depth test
    // ignore this line, it allows us to keep the distance value after we proejct each object to a 2d canvas.
    glEnable(GL_DEPTH_TEST);


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Blending

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // glfwSetMouseButtonCallback(window, mouse_callback);
    glfwSetKeyCallback(window, keyboard_callback);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Main render loop

    // This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
    int last_state = -1;
    while(!glfwWindowShouldClose(window))
    {

        int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
        if (last_state == GLFW_PRESS && state == GLFW_RELEASE) {
            game->handleMouseRelease();
        }
        last_state = state;

        // Clear the entire buffer with our green color (sets the background to be green).
        glClearBufferfv(GL_COLOR , 0, clear_color);
        glClearBufferfv(GL_DEPTH , 0, clear_depth);


        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //// This renders the objects

        // Set the trackball locatiom
        // SetTrackballLocation(GetCurrentCameraMatrix(), GetCurrentCameraTranslation());

        // draw the objects
        //cs->draw();
        /////////////////////////////////////////////////////
        // For selection.
        // FIRST, RENDER IN SELECT MODE

        // 1. start the scissor test
        glEnable(GL_SCISSOR_TEST);

        // 2. Set the window with window size 1x1
        // 600 is the size of the frame, make sure you know it.
		int pxToPt = 2;
        glScissor(GetMouseX() * pxToPt, (600 - GetMouseY()) * pxToPt, 1, 1);

        game->preDrawPicking();


        glUseProgram(0);

        // AT THIS LOCATION, WE HAVE TO RENDER ANY ADDITIONAL OBJECT IN "SELECT"-MODE
        // NOTE, GLSL, OPENGL 4.5 DOES NOT PROVIDE A SELECT MODE ANYMORE, WE SIMULATE THIS MODE.

        // 5. Disable the scissor test.
        glDisable(GL_SCISSOR_TEST);
        float col[4];
        glReadPixels(GetMouseX() * pxToPt, (600 - GetMouseY()) * pxToPt, 1, 1, GL_RGB,GL_FLOAT,&col);


        // cout << col[0] << col[1] <<col[2]<<endl;
        game->handleSelectedColor(col);


        game->draw();


        if(key_flag){
            SetViewAsLookAt(glm::vec3(20.0f, 50.0f, -20.0f), glm::vec3(20.0f, 0.0f, 20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        }else{
            SetViewAsLookAt(glm::vec3(20.0f, 50.0f, 60.0f), glm::vec3(20.0f, 0.0f, 20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

    }


    delete cs;


}
