//
//  GLYellowSphere.hpp
//  03_makeshpere
//
//  Created by Xiaoqian Mu on 10/7/16.
//
//

#ifndef GLYellowSphere_h
#define GLYellowSphere_h

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// locals
#include "GLObject.h"
#include "GLSphere.h"
#include "Shaders.h"

#include "HCI557Datatypes.h"





class GLSphereYellow : public GLSphere
{
public:
    
    GLSphereYellow(float center_x, float center_y, float center_z, float radius, int rows = 10, int segments = 10 );
    ~GLSphereYellow();
    
    
protected:
    
    
    
    /*
     Inits the shader program for this object
     */
    virtual void initShader(void);
    
    
    // The spotlight object
    GLSpotLightSource           _light_source1;
    GLSpotLightSource           _light_source2;
    GLSpotLightSource           _light_source3;
    GLLightSource           _light_source0;
    
    
    
};


#endif /* GLYellowSphere_h */
