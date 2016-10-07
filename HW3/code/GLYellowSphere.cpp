//
//  GLYellowSphere.cpp
//  03_makeshpere
//
//  Created by Xiaoqian Mu on 10/7/16.
//
//

#include "GLYellowSphere.h"

GLSphereYellow::GLSphereYellow(float center_x, float center_y, float center_z, float radius, int rows, int segments )
{
    
    _center.x() = center_x;
    _center.y() = center_y;
    _center.z() = center_z;
    
    
    _radius = radius;
    _rows = rows;
    _segments = segments;
    
    _render_normal_vectors = false;
    
    initShader();
    initVBO();
    
    initShaderNormal();
    initVBONormals();
    
}


GLSphereYellow::~GLSphereYellow()
{
    
    // Program clean up when the window gets closed.
    glDeleteVertexArrays(1, _vaoID);
    glDeleteVertexArrays(1, _vaoIDNormals);
    glDeleteProgram(_program);
    glDeleteProgram(_program_normals);
}





/*
 Inits the shader program for this object
 */
void GLSphereYellow::initShader(void)
{
#ifdef _WIN32
    // This loads the shader program from a file
    _program = LoadAndCreateShaderProgram("../data/shaders/ass3p2yellow.vs", "../data/shaders/ass3p2red.fs");
#else
    // This loads the shader program from a file
    _program = LoadAndCreateShaderProgram("../../data/shaders/ass3p2yellow.vs", "../../data/shaders/ass3p2red.fs");
#endif
    glUseProgram(_program);
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Vertex information / names
    
    glBindAttribLocation(_program, 0, "in_Position");
    glBindAttribLocation(_program, 1, "in_Normal");
    glBindAttribLocation(_program, 2, "in_Color");
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Define the model view matrix.
    
    
    _modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // Create our model matrix which will halve the size of our model
    
    
    _projectionMatrixLocation = glGetUniformLocation(_program, "projectionMatrixBox"); // Get the location of our projection matrix in the shader
    _viewMatrixLocation = glGetUniformLocation(_program, "viewMatrixBox"); // Get the location of our view matrix in the shader
    _modelMatrixLocation = glGetUniformLocation(_program, "modelMatrixBox"); // Get the location of our model matrix in the shader
    
    
    
    glUniformMatrix4fv(_projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix()[0][0] ); // Send our projection matrix to the shader
    glUniformMatrix4fv(_viewMatrixLocation, 1, GL_FALSE, &viewMatrix()[0][0]); // Send our view matrix to the shader
    glUniformMatrix4fv(_modelMatrixLocation, 1, GL_FALSE, &_modelMatrix[0][0]); // Send our model matrix to the shader
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Material
    _material._diffuse_material = glm::vec3(0.8, 0.8, 0.0);
    _material._ambient_material = glm::vec3(1.0, 1.0, 0.0);
    _material._specular_material = glm::vec3(1.0, 1.0, 1.0);
    _material._shininess = 1.0;
    
    
    _material._ambientColorPos = glGetUniformLocation(_program, "ambient_color");
    _material._diffuseColorPos = glGetUniformLocation(_program, "diffuse_color");
    _material._specularColorPos = glGetUniformLocation(_program, "specular_color");
    _material._shininessIdx = glGetUniformLocation(_program, "shininess");
    
    
    // Send the material to your shader program
    glUniform3fv(_material._ambientColorPos, 1, &_material._ambient_material[0] );
    glUniform3fv(_material._diffuseColorPos, 1, &_material._diffuse_material[0]);
    glUniform3fv(_material._specularColorPos, 1, &_material._specular_material[0]);
    glUniform1f(_material._shininessIdx, _material._shininess);
    
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Light
    
    
    // a normal light
    _light_source0._lightPos = glm::vec4(-15.0f, -7.0f, -7.0,1.0);
    _light_source0._ambient_intensity = 0.0;
    _light_source0._specular_intensity = 0.0;
    _light_source0._diffuse_intensity = 0.8;
    
    
    
    _light_source0._ambientIdx = glGetUniformLocation(_program, "ambient_intensity0");
    _light_source0._diffuseIdx = glGetUniformLocation(_program, "diffuse_intensity0");
    _light_source0._specularIdx = glGetUniformLocation(_program, "specular_intensity0");
    _light_source0._lightPosIdx = glGetUniformLocation(_program, "light_position0");
    
    
    
    // Send the light information to your shader program
    glUniform1f(_light_source0._ambientIdx, _light_source0._ambient_intensity );
    glUniform1f(_light_source0._diffuseIdx, _light_source0._diffuse_intensity);
    glUniform1f(_light_source0._specularIdx, _light_source0._specular_intensity);
    
    glUniform4fv(_light_source0._lightPosIdx, 1, &_light_source0._lightPos[0]);
    
    // Spot light 1
    _light_source1._lightPos = glm::vec4(-25.0, 0.0, 2.0, 0.0);
    _light_source1._ambient_intensity = 0.0;
    _light_source1._specular_intensity = 3.0;
    _light_source1._diffuse_intensity = 2.5;
    _light_source1._attenuation_coeff = 0.02;
    
    _light_source1._cone_angle = 4.5; // in degree
    _light_source1._cone_direction = glm::vec3(25.0, 0.0, -2.0); // this must be aligned with the object and light position.
    
    
    // Read all the index values from the shader program
    _light_source1._ambientIdx = glGetUniformLocation(_program, "ambient_intensity");
    _light_source1._diffuseIdx = glGetUniformLocation(_program, "diffuse_intensity");
    _light_source1._specularIdx = glGetUniformLocation(_program, "specular_intensity");
    _light_source1._attenuation_coeffIdx = glGetUniformLocation(_program, "attenuationCoefficient");
    _light_source1._lightPosIdx = glGetUniformLocation(_program, "light_position");
    
    _light_source1._cone_angleIdx = glGetUniformLocation(_program, "cone_angle");
    _light_source1._cone_directionIdx = glGetUniformLocation(_program, "cone_direction");
    
    // Send the light information to your shader program
    glUniform1f(_light_source1._ambientIdx, _light_source1._ambient_intensity );
    glUniform1f(_light_source1._diffuseIdx, _light_source1._diffuse_intensity);
    glUniform1f(_light_source1._specularIdx, _light_source1._specular_intensity);
    glUniform1f(_light_source1._attenuation_coeffIdx, _light_source1._attenuation_coeff);
    glUniform4fv(_light_source1._lightPosIdx, 1, &_light_source1._lightPos[0]);
    
    glUniform1f(_light_source1._cone_angleIdx, _light_source1._cone_angle);
    glUniform3fv(_light_source1._cone_directionIdx, 1, &_light_source1._cone_direction[0]);
    
    // Spot light 2
    _light_source2._lightPos = glm::vec4(-25.0, -5.0, -3.0, 0.0);
    _light_source2._ambient_intensity = 0.0;
    _light_source2._specular_intensity = 1.0;
    _light_source2._diffuse_intensity = 1.0;
    _light_source2._attenuation_coeff = 0.02;
    
    _light_source2._cone_angle = 4.5; // in degree
    _light_source2._cone_direction = glm::vec3(25.0, 5.0, 3.0); // this must be aligned with the object and light position.
    
    
    // Read all the index values from the shader program
    _light_source2._ambientIdx = glGetUniformLocation(_program, "ambient_intensity2");
    _light_source2._diffuseIdx = glGetUniformLocation(_program, "diffuse_intensity2");
    _light_source2._specularIdx = glGetUniformLocation(_program, "specular_intensity2");
    _light_source2._attenuation_coeffIdx = glGetUniformLocation(_program, "attenuationCoefficient");
    _light_source2._lightPosIdx = glGetUniformLocation(_program, "light_position2");
    
    _light_source2._cone_angleIdx = glGetUniformLocation(_program, "cone_angle2");
    _light_source2._cone_directionIdx = glGetUniformLocation(_program, "cone_direction2");
    
    // Send the light information to your shader program
    glUniform1f(_light_source2._ambientIdx, _light_source2._ambient_intensity );
    glUniform1f(_light_source2._diffuseIdx, _light_source2._diffuse_intensity);
    glUniform1f(_light_source2._specularIdx, _light_source2._specular_intensity);
    glUniform1f(_light_source2._attenuation_coeffIdx, _light_source2._attenuation_coeff);
    glUniform4fv(_light_source2._lightPosIdx, 1, &_light_source2._lightPos[0]);
    
    glUniform1f(_light_source2._cone_angleIdx, _light_source2._cone_angle);
    glUniform3fv(_light_source2._cone_directionIdx, 1, &_light_source2._cone_direction[0]);
    
    
    // Spot light 3
    _light_source3._lightPos = glm::vec4(-43.0, 7.75, 15.5, 0.0);
    _light_source3._ambient_intensity = 0.0;
    _light_source3._specular_intensity = 0.5;
    _light_source3._diffuse_intensity = 6.8;
    _light_source3._attenuation_coeff = 0.02;
    
    _light_source3._cone_angle = 6.75; // in degree
    _light_source3._cone_direction = glm::vec3(27, -4.5, -12.5); // this must be aligned with the object and light position.
    
    
    // Read all the index values from the shader program
    _light_source3._ambientIdx = glGetUniformLocation(_program, "ambient_intensity3");
    _light_source3._diffuseIdx = glGetUniformLocation(_program, "diffuse_intensity3");
    _light_source3._specularIdx = glGetUniformLocation(_program, "specular_intensity3");
    _light_source3._attenuation_coeffIdx = glGetUniformLocation(_program, "attenuationCoefficient");
    _light_source3._lightPosIdx = glGetUniformLocation(_program, "light_position3");
    
    _light_source3._cone_angleIdx = glGetUniformLocation(_program, "cone_angle3");
    _light_source3._cone_directionIdx = glGetUniformLocation(_program, "cone_direction3");
    
    // Send the light information to your shader program
    glUniform1f(_light_source3._ambientIdx, _light_source3._ambient_intensity );
    glUniform1f(_light_source3._diffuseIdx, _light_source3._diffuse_intensity);
    glUniform1f(_light_source3._specularIdx, _light_source3._specular_intensity);
    glUniform1f(_light_source3._attenuation_coeffIdx, _light_source3._attenuation_coeff);
    glUniform4fv(_light_source3._lightPosIdx, 1, &_light_source3._lightPos[0]);
    
    glUniform1f(_light_source3._cone_angleIdx, _light_source3._cone_angle);
    glUniform3fv(_light_source3._cone_directionIdx, 1, &_light_source3._cone_direction[0]);
    
    
    glUseProgram(0);
    
}
