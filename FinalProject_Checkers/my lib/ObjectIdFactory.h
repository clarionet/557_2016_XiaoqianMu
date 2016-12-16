#pragma once


// stl include
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// GLEW include
#include <GL/glew.h>

// GLM include files
//#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// locals
#include "GLObject.h"
#include "GLSphere.h"
#include "Shaders.h"

#include "HCI557Datatypes.h"

struct ObjectId {
    float r;
    float g;
    float b;
    int id; // 1-999
};

static int current_id = 1;

class ObjectIdFactory {
public:
    static ObjectId* getId();
    static int getIdFromColor(float col[4]);
};
