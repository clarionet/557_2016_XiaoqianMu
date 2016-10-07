//
//  main.cpp
//  03_makeshpere
//
//  Created by Xiaoqian Mu on 10/7/16.
//
//
#include <iostream>
#include <string>

#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>


// glfw includes
#include <GLFW/glfw3.h>


// include local files
#include "controls.h"
#include "HCI557Common.h"
#include "CoordSystem.h"
#include "GLRedSphere.h"
#include "GLYellowSphere.h"
#include "GLBlueSphere.h"
#include "GLGreenSphere.h"
#include "CoordSystem.h"



using namespace std;

GLFWwindow*         window;

GLuint program;


int main(int argc, const char * argv[])
{
    window = initWindow();
    
    initGlew();
    
    CoordSystemRenderer* cs = new CoordSystemRenderer(50.0);
    
    
    GLSphereRed* sphereRed = new GLSphereRed(0.0, 0.0, -6.0, 2.0, 100, 100);
    GLSphereBlue* sphereBlue = new GLSphereBlue(0.0, 0.0, -2.0, 2.0, 100, 100);
    GLSphereGreen* sphereGreen = new GLSphereGreen(0.0, 0.0, 2.0, 2.0, 1000, 1000);
    GLSphereYellow* sphereYellow = new GLSphereYellow(0.0, 0.0, 6.0, 2.0, 100, 100);
  
    static const GLfloat clear_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    

    SetViewAsLookAt(glm::vec3(-20.0f, -1.0f, -1.0f), glm::vec3(4.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
  
    glEnable(GL_DEPTH_TEST);
    
  
    while(!glfwWindowShouldClose(window))
    {
       
        glClearBufferfv(GL_COLOR , 0, clear_color);
        glClearBufferfv(GL_DEPTH , 0, clear_depth);
        
        cs->draw();
        
        sphereRed->draw();
        sphereBlue->draw();
        sphereGreen->draw();
        sphereYellow->draw();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
    
    delete cs;
    
    
}
