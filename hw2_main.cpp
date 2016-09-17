//
//  main.cpp
//  OpenGL4Test
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
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// glfw includes
#include <GLFW/glfw3.h>


// include local files
#include "controls.h"
#include "HCI557Common.h"
#include "CoordSystem.h"

// this line tells the compiler to use the namespace std.
// Each object, command without a namespace is assumed to be part of std. 
using namespace std;




static const string vs_string =
"#version 410 core                                                 \n"
"                                                                   \n"
"uniform mat4 projectionMatrix;                                    \n"
"uniform mat4 viewMatrix;                                           \n"
"uniform mat4 modelMatrix;                                          \n"
"in vec3 in_Position;                                               \n"
"                                                                   \n"
"in vec3 in_Color;                                                  \n"
"out vec3 pass_Color;                                               \n"
"                                                                  \n"
"void main(void)                                                   \n"
"{                                                                 \n"
"    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0);  \n"
"    pass_Color = in_Color;                                         \n"
"}                                                                 \n";

// Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the inside of our triangle specified by our vertex shader.
static const string fs_string  =
"#version 410 core                                                 \n"
"                                                                  \n"
"in vec3 pass_Color;                                                 \n"
"out vec4 color;                                                    \n"
"void main(void)                                                   \n"
"{                                                                 \n"
"    color = vec4(pass_Color, 1.0);                               \n"
"}                                                                 \n";




/// Camera control matrices
glm::mat4 projectionMatrix; // Store the projection matrix
glm::mat4 viewMatrix; // Store the view matrix
glm::mat4 modelMatrix; // Store the model matrix




// The handle to the window object
GLFWwindow*         window;


// Define some of the global variables we're using for this sample
GLuint program;







///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// Fill this functions with your model code.

// USE THESE vertex array objects to define your objects
unsigned int vaoID[2];

unsigned int vboID[2],vboID1[2];

/*!
 ADD YOUR CODE TO CREATE A MODEL USING PRIMITIVES OF YOUR CHOISE TO THIS FUNCTION
 */
unsigned int createTriangleStripModel(void)
{
    // use the vertex array object vaoID[1] for this model representation
    
    //TODO:
    // vaoID[0];
    float* vertices = new float[108];  // Vertices for our square
    float *colors = new float[108]; // Colors for our vertices
    
    //Manifold mesh 1
    vertices[0] = 0; vertices[1] = 0; vertices[2] = 0; // Bottom left corner
    colors[0] = 0.0; colors[1] = 0.0; colors[2] = 1.0; // Bottom left corner
    
    vertices[3] = 0; vertices[4] = 0; vertices[5] = 1.0; // Top left corner
    colors[3] = 0.0; colors[4] = 0.0; colors[5] = 1.0; // Top left corner
    
    vertices[6] = -1.0; vertices[7] = 0 ; vertices[8] = 0; // Top Right corner
    colors[6] = 0.0; colors[7] = 0.0; colors[8] = 1.0; // Top Right corner
    
    vertices[9] = -1; vertices[10] = 0; vertices[11] = 1.0; // Bottom right corner
    colors[9] = 0.0; colors[10] = 0.0; colors[11] = 1.0; // Bottom right corner
    
    vertices[12] = -1.0; vertices[13] = -2.0; vertices[14] = 0; // Bottom left corner
    colors[12] = 0; colors[13] = 0.0; colors[14] = 1.0; // Bottom left corner
    
    vertices[15] = -1; vertices[16] = -2.0; vertices[17] = 1.0; // Top Right corner
    colors[15] = 0.0; colors[16] = 0.0; colors[17] = 1.0; // Top Right corner
    
    vertices[18]=0.0; vertices[19]=-2.0; vertices[20]=0.0;
    colors[18]=0.0; colors[19]=0.0; colors[20]=1.0;
    
    vertices[21]=0; vertices[22]=-2.0; vertices[23]=1.0;
    colors[21]=0.0; colors[22]=0.0; colors[23]=1.0;
    
    //Manifold mesh 2
    vertices[24]=-1.0; vertices[25]=-2.0; vertices[26]=1.0;
    colors[24] =0.0; colors[25]=0.0; colors[26]=1.0;
    
    vertices[27]=-1.0; vertices[28]=0.0; vertices[29] = 1.0;
    colors[27] =0.0; colors[28]=0.0; colors[29]=1.0;
    
    vertices[30] = 0.0; vertices[31] = -2.0; vertices[32]=1.0;
    colors[30] =0.0; colors[31]=0.0; colors[32]=1.0;
    
    vertices[33]= 0.0; vertices[34] = 0.0; vertices[35] = 1.0;
    colors[33] =0.0; colors[34]=0.0; colors[35]=1.0;
    
    vertices[36]= 0.0; vertices[37] = -2.0; vertices[38] = 0.0;
    colors[36] =0.0; colors[37]=0.0; colors[38]=1.0;
    
    vertices[39] = 0.0; vertices[40]= 0.0; vertices[41] =0.0;
    colors[39] =0.0; colors[40]=0.0; colors[41]=1.0;
    
    vertices[42] = -1.0; vertices[43]=-2.0; vertices[44]=0.0;
    colors[42] =0.0; colors[43]=0.0; colors[44]=1.0;
    
    vertices[45] = -1.0; vertices[46] = 0.0; vertices[47] =0.0;
    colors[45] =0.0; colors[46]=0.0; colors[47]=1.0;
    
    
    //Manifold mesh 3
    vertices[48]=-1.0; vertices[49]=0.0; vertices[50]=0.0;
    colors[48]=0.0; colors[49]=0.0; colors[50]=1.0;
    
    vertices[51]=-1.0; vertices[52]=0.0; vertices[53]=2.0;
    colors[51]=0.0; colors[52]=0.0; colors[53]=1.0;
    
    vertices[54]=2.0; vertices[55]=0.0; vertices[56]=0.0;
    colors[54] =0.0; colors[55]=0.0; colors[56]=1.0;
    
    vertices[57]=0.0; vertices[58]=0.0; vertices[59] = 2.0;
    colors[57] =0.0; colors[58]=0.0; colors[59]=1.0;
    
    vertices[60] = 2.0; vertices[61] = 0.0; vertices[62]=1.0;
    colors[60] =0.0; colors[61]=0.0; colors[62]=1.0;
    
    vertices[63]= 0.0; vertices[64] = 1.0; vertices[65] = 2.0;
    colors[63] =0.0; colors[64]=0.0; colors[65]=1.0;
    
    vertices[66]= 2.0; vertices[67] = 1.0; vertices[68] = 1.0;
    colors[66] =0.0; colors[67]=0.0; colors[68]=1.0;
    
    vertices[69] = -1.0; vertices[70]= 1.0; vertices[71] =2.0;
    colors[69] =0.0; colors[70]=0.0; colors[71]=1.0;
    
    vertices[72] = 2.0; vertices[73]=1.0; vertices[74]=0.0;
    colors[72] =0.0; colors[73]=0.0; colors[74]=1.0;
    
    vertices[75] = -1.0; vertices[76] = 1.0; vertices[77] =0.0;
    colors[75] =0.0; colors[76]=0.0; colors[77]=1.0;
    
    //Manifold mesh 4
    vertices[78]=0.0; vertices[79]=0.0; vertices[80]=2.0;
    colors[78]=0.0; colors[79]=0.0; colors[80]=1.0;
    
    vertices[81]=0.0; vertices[82]=1.0; vertices[83]=2.0;
    colors[81]=0.0; colors[82]=0.0; colors[83]=1.0;
    
    vertices[84]=-1.0; vertices[85]=0.0; vertices[86]=2.0;
    colors[84] =0.0; colors[85]=0.0; colors[86]=1.0;
    
    vertices[87]=-1.0; vertices[88]=1.0; vertices[89] = 2.0;
    colors[87] =0.0; colors[88]=0.0; colors[89]=1.0;
    
    vertices[90] = -1.0; vertices[91] = 0.0; vertices[92]=0.0;
    colors[90] =0.0; colors[91]=0.0; colors[92]=1.0;
    
    vertices[93]= -1.0; vertices[94] = 1.0; vertices[95] = -0.0;
    colors[93] =0.0; colors[94]=0.0; colors[95]=1.0;
    
    vertices[96]= 2.0; vertices[97] = 0.0; vertices[98] = 0.0;
    colors[96] =0.0; colors[97]=0.0; colors[98]=1.0;
    
    vertices[99] = 2.0; vertices[100]= 1.0; vertices[101] =0.0;
    colors[99] =0.0; colors[100]=0.0; colors[101]=1.0;
    
    vertices[102] = 2.0; vertices[103]=0.0; vertices[104]=1.0;
    colors[102] =0.0; colors[103]=0.0; colors[104]=1.0;
    
    vertices[105] = 2.0; vertices[106] = 1.0; vertices[107] =1.0;
    colors[105] =0.0; colors[106]=0.0; colors[107]=1.0;
    
    
    
    glGenVertexArrays(2, &vaoID[0]); // Create our Vertex Array Object
    glBindVertexArray(vaoID[0]); // Bind our Vertex Array Object so we can use it
    
    
    glGenBuffers(2, vboID); // Generate our Vertex Buffer Object
    
    // vertices
    glBindBuffer(GL_ARRAY_BUFFER, vboID[0]); // Bind our Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, 108* sizeof(GLfloat), vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
    
    glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
    glEnableVertexAttribArray(0); // Disable our Vertex Array Object
    
    
    //Color
    glBindBuffer(GL_ARRAY_BUFFER, vboID[1]); // Bind our second Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, 108* sizeof(GLfloat), colors, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
    
    glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
    glEnableVertexAttribArray(1); // Enable the second vertex attribute array
    
    glBindVertexArray(0); // Disable our Vertex Buffer Object
    
    
    delete [] vertices; // Delete our vertices from memory
    delete [] colors;
    
    return 1;
}

/*!
 ADD YOUR CODE TO CREATE THE TRIANGLE STRIP MODEL TO THIS FUNCTION
 */
unsigned int createPolygonModel(void)
{
    // use the vertex array object vaoID[0] for this model representation

    //TODO:
    float* vertices = new float[162];  // Vertices for our square
    float *colors = new float[162]; // Colors for our vertices
    
    vertices[0] = 0; vertices[1] = 0; vertices[2] = 0; // Bottom left corner
    colors[0] = 0.0; colors[1] = 1.0; colors[2] = 1.0; // Bottom left corner
    
    vertices[3] = 0; vertices[4] = 0; vertices[5] = 1.0; // Top left corner
    colors[3] = 0.0; colors[4] = 1.0; colors[5] = 1.0; // Top left corner
    
    vertices[6] = 0.0; vertices[7] = -2.0 ; vertices[8] = 1.0; // Top Right corner
    colors[6] = 0.0; colors[7] = 1.0; colors[8] = 1.0; // Top Right corner
    
    vertices[9] = 0; vertices[10] = -2; vertices[11] = 0; // Bottom right corner
    colors[9] = 0.0; colors[10] = 1.0; colors[11] = 1.0; // Bottom right corner
    
    
    vertices[12] = 0; vertices[13] = 0; vertices[14] = 1.0; // Bottom left corner
    colors[12] = 0; colors[13] = 1.0; colors[14] = 1.0; // Bottom left corner
    
    vertices[15] = -1; vertices[16] = 0; vertices[17] = 1.0; // Top Right corner
    colors[15] = 0.0; colors[16] = 1.0; colors[17] = 1.0; // Top Right corner
    
    vertices[18]=-1.0; vertices[19]=-2.0; vertices[20]=1.0;
    colors[18]=0.0; colors[19]=1.0; colors[20]=1.0;
    
    vertices[21]=0; vertices[22]=-2.0; vertices[23]=1.0;
    colors[21]=0.0; colors[22]=1.0; colors[23]=1.0;
    
    
    vertices[24]=-1.0; vertices[25]=0.0; vertices[26]=1.0;
    colors[24] =0.0; colors[25]=1.0; colors[26]=1.0;
    
    vertices[27]=-1.0; vertices[28]=0.0; vertices[29] = 0.0;
    colors[27] =0.0; colors[28]=1.0; colors[29]=1.0;
    
    vertices[30] = -1.0; vertices[31] = -2.0; vertices[32]=0.0;
    colors[30] =0.0; colors[31]=1.0; colors[32]=1.0;
    
    vertices[33]= -1.0; vertices[34] = -2.0; vertices[35] = 1.0;
    colors[33] =0.0; colors[34]=1.0; colors[35]=1.0;
    
    
    vertices[36]= -1.0; vertices[37] = 0.0; vertices[38] = 0.0;
    colors[36] =0.0; colors[37]=1.0; colors[38]=1.0;
    
    vertices[39] = 0.0; vertices[40]= 0.0; vertices[41] =0.0;
    colors[39] =0.0; colors[40]=1.0; colors[41]=1.0;
    
    vertices[42] = 0.0; vertices[43]=-2.0; vertices[44]=0.0;
    colors[42] =0.0; colors[43]=1.0; colors[44]=1.0;
    
    vertices[45] = -1.0; vertices[46] = -2.0; vertices[47] =0.0;
    colors[45] =0.0; colors[46]=1.0; colors[47]=1.0;
    
    
    vertices[48]=0.0; vertices[49]=-2.0; vertices[50]=0.0;
    colors[48]=0.0; colors[49]=1.0; colors[50]=1.0;
    
    vertices[51]=0; vertices[52]=-2.0; vertices[53]=1.0;
    colors[51]=0.0; colors[52]=1.0; colors[53]=1.0;
    
    vertices[54]=-1.0; vertices[55]=-2.0; vertices[56]=1.0;
    colors[54] =0.0; colors[55]=1.0; colors[56]=1.0;
    
    vertices[57]=-1.0; vertices[58]=-2.0; vertices[59] = 0.0;
    colors[57] =0.0; colors[58]=1.0; colors[59]=1.0;
    
    
    vertices[60] = 0.0; vertices[61] = 0.0; vertices[62]=0.0;
    colors[60] =0.0; colors[61]=1.0; colors[62]=1.0;
    
    vertices[63]= 0.0; vertices[64] = 0.0; vertices[65] = 1.0;
    colors[63] =0.0; colors[64]=1.0; colors[65]=1.0;
    
    vertices[66]= -1.0; vertices[67] = 0.0; vertices[68] = 1.0;
    colors[66] =0.0; colors[67]=1.0; colors[68]=1.0;
    
    vertices[69] = -1.0; vertices[70]= 0.0; vertices[71] =0.0;
    colors[69] =0.0; colors[70]=1.0; colors[71]=1.0;
    
    
    vertices[72] = 0.0; vertices[73]=0.0; vertices[74]=2.0;
    colors[72] =0.0; colors[73]=1.0; colors[74]=1.0;
    
    vertices[75] = 0.0; vertices[76] = 1.0; vertices[77] =2.0;
    colors[75] =0.0; colors[76]=1.0; colors[77]=1.0;
    
    vertices[78]=2.0; vertices[79]=1.0; vertices[80]=1.0;
    colors[78]=0.0; colors[79]=1.0; colors[80]=1.0;
    
    vertices[81]=2; vertices[82]=0.0; vertices[83]=1.0;
    colors[81]=0.0; colors[82]=1.0; colors[83]=1.0;
    
    
    vertices[84]=2.0; vertices[85]=0.0; vertices[86]=1.0;
    colors[84] =0.0; colors[85]=1.0; colors[86]=1.0;
    
    vertices[87]=2.0; vertices[88]=1.0; vertices[89] = 1.0;
    colors[87] =0.0; colors[88]=1.0; colors[89]=1.0;
    
    vertices[90] = 2.0; vertices[91] = 1.0; vertices[92]=0.0;
    colors[90] =0.0; colors[91]=1.0; colors[92]=1.0;
    
    vertices[93]= 2.0; vertices[94] = 0.0; vertices[95] = 0.0;
    colors[93] =0.0; colors[94]=1.0; colors[95]=1.0;
    
    
    vertices[96]= 2.0; vertices[97] = 0.0; vertices[98] = 0.0;
    colors[96] =0.0; colors[97]=1.0; colors[98]=1.0;
    
    vertices[99] = 2.0; vertices[100]= 1.0; vertices[101] =0.0;
    colors[99] =0.0; colors[100]=1.0; colors[101]=1.0;
    
    vertices[102] = -1.0; vertices[103]=1.0; vertices[104]=0.0;
    colors[102] =0.0; colors[103]=1.0; colors[104]=1.0;
    
    vertices[105] = -1.0; vertices[106] = 0.0; vertices[107] =0.0;
    colors[105] =0.0; colors[106]=1.0; colors[107]=1.0;
    

    vertices[108]=-1.0; vertices[109]=0.0; vertices[110]=0.0;
    colors[108]=0.0; colors[109]=1.0; colors[110]=1.0;
    
    vertices[111]=-1; vertices[112]=1.0; vertices[113]=0.0;
    colors[111]=0.0; colors[112]=1.0; colors[113]=1.0;
    
    vertices[114]=-1.0; vertices[115]=1.0; vertices[116]=2.0;
    colors[114] =0.0; colors[115]=1.0; colors[116]=1.0;
    
    vertices[117]=-1.0; vertices[118]=0.0; vertices[119] = 2.0;
    colors[117] =0.0; colors[118]=1.0; colors[119]=1.0;
    
    
    vertices[120] = -1.0; vertices[121] = 0.0; vertices[122]=2.0;
    colors[120] =0.0; colors[121]=1.0; colors[122]=1.0;
    
    vertices[123]= -1.0; vertices[124] = 1.0; vertices[125] = 2.0;
    colors[123] =0.0; colors[124]=1.0; colors[125]=1.0;
    
    vertices[126]= 0.0; vertices[127] = 1.0; vertices[128] = 2.0;
    colors[126] =0.0; colors[127]=1.0; colors[128]=1.0;
    
    vertices[129] = 0.0; vertices[130]= 0.0; vertices[131] =2.0;
    colors[129] =0.0; colors[130]=1.0; colors[131]=1.0;
    
    
    vertices[132] = -1.0; vertices[133]=0.0; vertices[134]=0.0;
    colors[132] =0.0; colors[133]=1.0; colors[134]=1.0;
    
    vertices[135] = -1.0; vertices[136] = 0.0; vertices[137] =2.0;
    colors[135] =0.0; colors[136]=1.0; colors[137]=1.0;
    
    vertices[138]=0.0; vertices[139]=0.0; vertices[140]=2.0;
    colors[138]=0.0; colors[139]=1.0; colors[140]=1.0;
    
    vertices[141]=2.0; vertices[142]=0.0; vertices[143]=1.0;
    colors[141]=0.0; colors[142]=1.0; colors[143]=1.0;
    
    vertices[144]=2.0; vertices[145]=0.0; vertices[146]=0.0;
    colors[144] =0.0; colors[145]=1.0; colors[146]=1.0;
    
    
    vertices[147]=-1.0; vertices[148]=1.0; vertices[149] = 0.0;
    colors[147] =0.0; colors[148]=1.0; colors[149]=1.0;
    
    vertices[150] = -1.0; vertices[151] = 1.0; vertices[152]=2.0;
    colors[150] =0.0; colors[151]=1.0; colors[152]=1.0;
    
    vertices[153]= 0.0; vertices[154] = 1.0; vertices[155] = 2.0;
    colors[153] =0.0; colors[154]=1.0; colors[155]=1.0;
    
    vertices[156]= 2.0; vertices[157] = 1.0; vertices[158] = 1.0;
    colors[156] =0.0; colors[157]=1.0; colors[158]=1.0;
    
    vertices[159] = 2.0; vertices[160]= 1.0; vertices[161] =0.0;
    colors[159] =0.0; colors[160]=1.0; colors[161]=1.0;
    
    
    glGenVertexArrays(2, &vaoID[1]); // Create our Vertex Array Object
    glBindVertexArray(vaoID[1]); // Bind our Vertex Array Object so we can use it
    
    
    glGenBuffers(2, vboID1); // Generate our Vertex Buffer Object
    
    // vertices
    glBindBuffer(GL_ARRAY_BUFFER, vboID1[0]); // Bind our Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, 162* sizeof(GLfloat), vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
    
    glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
    glEnableVertexAttribArray(0); // Disable our Vertex Array Object
    
    
    //Color
    glBindBuffer(GL_ARRAY_BUFFER, vboID1[1]); // Bind our second Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, 162* sizeof(GLfloat), colors, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
    
    glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
    glEnableVertexAttribArray(1); // Enable the second vertex attribute array
    
    glBindVertexArray(0); // Disable our Vertex Buffer Object
    
    
    delete [] vertices; // Delete our vertices from memory
    delete [] colors;
    
    return 1;
    
   
}

/*!
 ADD YOUR CODE TO RENDER THE TRIANGLE STRIP MODEL TO THIS FUNCTION
 */
void renderTriangleStripModel(void)
{

    // Bind the buffer and switch it to an active buffer
    glBindVertexArray(vaoID[0]);
        
	// HERE: THIS CAUSES AN ERROR BECAUSE I DO NOT KNOW HOW MANY TRIANGLES / VERTICES YOU HAVE.
	// COMPLETE THE LINE
    // Draw the triangle
    glDrawArrays(GL_TRIANGLE_STRIP, 0 , 36);
    // Unbind our Vertex Array Object
    glBindVertexArray(0);

}

/*!
 ADD YOUR CODE TO RENDER THE TRIANGLE STRIP MODEL TO THIS FUNCTION
 */
void renderPolygonModel(void)
{

    // Bind the buffer and switch it to an active buffer
    glBindVertexArray(vaoID[1]);
        

	// HERE: THIS CAUSES AN ERROR BECAUSE I DO NOT KNOW HOW MANY POLYGONS YOU HAVE.
	// COMPLETE THE LINE
    // Draw the triangles
    for(int i=0;i<131;i+=12)
      glDrawArrays(GL_POLYGON, i, 4);
    for(int i=132;i<161;i+=15)
     glDrawArrays(GL_POLYGON, i, 5);
    //glDrawArrays(GL_TRIANGLE_STRIP, 0, 36);
    // Unbind our Vertex Array Object
    glBindVertexArray(0);
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*!
 This function creates the two models
 */
void setupScene(void) {
    
    createTriangleStripModel();
    //renderTriangleStripModel();
    createPolygonModel();
}




int main(int argc, const char * argv[])
{
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Init glfw, create a window, and init glew
    
    // Init the GLFW Window
    window = initWindow();
    
    
    // Init the glew api
    initGlew();
    
	// Prepares some defaults
	CoordSystemRenderer* coordinate_system_renderer = new CoordSystemRenderer(10.0);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// The Shader Program starts here
    
    // Vertex shader source code. This draws the vertices in our window. We have 3 vertices since we're drawing an triangle.
    // Each vertex is represented by a vector of size 4 (x, y, z, w) coordinates.
    static const string vertex_code = vs_string;
    static const char * vs_source = vertex_code.c_str();
    
    // Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the inside of our triangle specified by our vertex shader.
    static const string fragment_code = fs_string;
    static const char * fs_source = fragment_code.c_str();
    
    // This next section we'll generate the OpenGL program and attach the shaders to it so that we can render our triangle.
    program = glCreateProgram();
    
    // We create a shader with our fragment shader source code and compile it.
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_source, NULL);
    glCompileShader(fs);
    
    // We create a shader with our vertex shader source code and compile it.
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_source, NULL);
    glCompileShader(vs);
    
    // We'll attach our two compiled shaders to the OpenGL program.
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    
    glLinkProgram(program);
    
    // We'll specify that we want to use this program that we've attached the shaders to.
    glUseProgram(program);
    
    //// The Shader Program ends here
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    /// IGNORE THE NEXT PART OF THIS CODE
    /// IGNORE THE NEXT PART OF THIS CODE
    /// IGNORE THE NEXT PART OF THIS CODE
    // It controls the virtual camera
    
    // Set up our green background color
    static const GLfloat clear_color[] = { 0.6f, 0.7f, 1.0f, 1.0f };
    static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    
    projectionMatrix = glm::perspective(1.1f, (float)800 / (float)600, 0.1f, 100.f);
    modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // Create our model matrix which will halve the size of our model
    viewMatrix = glm::lookAt(glm::vec3(1.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    int projectionMatrixLocation = glGetUniformLocation(program, "projectionMatrix"); // Get the location of our projection matrix in the shader
    int viewMatrixLocation = glGetUniformLocation(program, "viewMatrix"); // Get the location of our view matrix in the shader
    int modelMatrixLocation = glGetUniformLocation(program, "modelMatrix"); // Get the location of our model matrix in the shader
    
    
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]); // Send our projection matrix to the shader
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]); // Send our view matrix to the shader
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
    
	 //// The Shader Program ends here
    //// START TO READ AGAIN
    //// START TO READ AGAIN
    //// START TO READ AGAIN
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    


    glBindAttribLocation(program, 0, "in_Position");
    glBindAttribLocation(program, 1, "in_Color");
    

    
    // this creates the scene
    setupScene();
    
    int i=0;

    // Enable depth test
    // ignore this line, it allows us to keep the distance value after we proejct each object to a 2d canvas.
    glEnable(GL_DEPTH_TEST);
    
    // This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
    while(!glfwWindowShouldClose(window))
    {
        
        // Clear the entire buffer with our green color (sets the background to be green).
        glClearBufferfv(GL_COLOR , 0, clear_color);
        glClearBufferfv(GL_DEPTH , 0, clear_depth);
        
        // this draws the coordinate system
		coordinate_system_renderer->draw();
        
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //// This generate the object
        // Enable the shader program
        glUseProgram(program);
        
        // this changes the camera location
        glm::mat4 rotated_view = viewMatrix * GetRotationMatrix();
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &rotated_view[0][0]); // send the view matrix to our shader
        

        // This moves the model to the right
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
        

		// This line renders your triangle strip model
        renderTriangleStripModel();
        

        // This moves the model to the left
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, -0.0f, 0.0f));
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
        
		// This line renders your Ppolygon model
        renderPolygonModel();
        //renderTriangleStripModel();
        
		// disable the shader program
        glUseProgram(0);


        //// This generate the object
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        
        // Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
	// delete the coordinate system object
	delete coordinate_system_renderer;

    // Program clean up when the window gets closed.
    glDeleteVertexArrays(2, vaoID);
    glDeleteProgram(program);
}

