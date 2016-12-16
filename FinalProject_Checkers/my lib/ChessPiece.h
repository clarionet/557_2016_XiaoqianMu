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
#include <glm/gtx/transform.hpp>

#include "GLObjectObj.h"
#include "ObjectIdFactory.h"

using namespace std;

class ChessPiece : public GLObjectObj
{
    // Ray intersection test has access to protected functions
    friend class RayIntersectionTest;

public:
	ChessPiece(string filename, string type);
    ChessPiece();
    ~ChessPiece();


    /*!
     Draw the objects
     */
    void draw(void);


    /*!
     Init the geometry object
     */
    void init(void);


    /*!
    Returns the number of vertices
    */
    int size(void);


    /*!
    Returns a reference too the vertices.
    */
    vector<glm::vec3>& getVertices(void){return  _vertices; };

    /*!
    To update the vertices.
    This function takes a vector of vertices and replaces the current vector.
    */
    void updateVertices(float* vertices);

    ObjectId* getObjectId();

    string getType();
	
	void setPlayer(int);
	int getPlayer();
    void  setKing(bool);
    bool isKing();
	
	void setLocation(glm::vec3);
    void moveToLocation(glm::vec3);
    glm::mat4 getMatrix();
	glm::vec3 getLocation();
	
	void translatePiece(glm::vec3);
	
	bool intersect(const glm::vec3& ray_start, const glm::vec3&  ray_stop, vector<glm::vec3>& intersect_list);

private:

    /*!
     Load an obj model from a file
     */
    bool load_obj(const char* filename, vector<glm::vec3> &vertices, vector<glm::vec3> &normals, vector<GLuint> &elements);



    /*!
     Extract one obj face coded as:f v/vt/vn v/vt/vn v/vt/vn
     */
    bool extractNextFace3(string& in, string& out, int& pointIdx, int& texIdx, int& normalIdx );
    bool extractNextFace1(string& in, string& out, int& pointIdx0, int& pointIdx1, int& pointIdx2  );

    /*!
     Create the vertex buffer object for this element
     */
    virtual void initVBO(void);

    /*
     Inits the shader program for this object
     */
    virtual void initShader(void);


    // the program
    GLuint                  _program;


    // file and path of the loaded object
    string                  _file_and_path;
    bool                    _file_ok;
    ObjectId*               _object_id;
    string _model_path;
	string                  _object_type;
	int						_object_player;
	glm::vec3				_object_location;
    bool                    _object_king;

private:
    // obj file data
    string                  _material_file;
    string                  _model_name;


    int                     _num_vertices;

    unsigned int            _vaoID[1]; // Our Vertex Array Object

    unsigned int            _vboID[3]; // Our Vertex Buffer Object

    GLuint                  _elementbuffer;
	
};
