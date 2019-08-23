#ifndef H3DSTRUCTS_H_INCLUDED
#define H3DSTRUCTS_H_INCLUDED

#include <vector>
#include <iostream>

// structs

/// structure for a vector with 4 axis
struct vec4{
    float x;
    float y;
    float z;
    float w;
};

struct vec3{
    float x;
    float y;
    float z;
};


/// structure of a triangle holds 3 vec4 points
struct triangle{
    vec4 p[3];
};

/// structure of a mesh - holds an array of triangles
struct mesh{
    std::vector<triangle> trianglesMesh;
};

/// structure of a 4 by 4 matrix
struct mat4{
    float matrix[4][4];
};

// functions

/// a function for matrix multiplication
mat4 operator*(const mat4& matrix1, const mat4& matrix2);

/// a function for vector multiplication against a matrix
vec4 operator*(const mat4& aMatrix, const vec4& aVector);

/// a function that builds the Projection Matrix
const mat4 buildProjectionMatrix(float,float,float,float,float);

/// a function that builds the cube mesh
const mesh buildCube();

/// a function that build the view matrix
const mat4 buildViewMatrix(const vec3,float ,float );

/// a function that prints the 4x4 matrix
std::ostream& operator<<(const std::ostream &out, const mat4& mat);

std::ostream& operator<<(const std::ostream &out,const vec4& mat);

/// a function that converts angle to radians
float toRadians(float angle);

float dot(vec3,vec3);

vec4 translateToWorld(vec4);

vec4 rotateX(vec4,float);

vec4 rotateY(vec4,float);

#endif // H3DSTRUCTS_H_INCLUDED
