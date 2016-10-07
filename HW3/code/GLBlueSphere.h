//
//  GLBlueSphere.hpp
//  03_makeshpere
//
//  Created by Xiaoqian Mu on 10/7/16.
//
//

#ifndef GLBlueSphere_h
#define GLBlueSphere_h

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <GL/glew.h>

#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GLObject.h"
#include "GLSphere.h"
#include "Shaders.h"

#include "HCI557Datatypes.h"



class GLSphereBlue : public GLSphere
{
public:
    
    GLSphereBlue(float center_x, float center_y, float center_z, float radius, int rows = 10, int segments = 10 );
    ~GLSphereBlue();
    
    
protected:
    
    /*
     Inits the shader program for this object
     */
    virtual void initShader(void);
    
    
    // The spotlight object
    GLLightSource _light_source0;
    GLSpotLightSource _light_source1;
    
    
    
};


#endif /* GLBlueSphere_h */
