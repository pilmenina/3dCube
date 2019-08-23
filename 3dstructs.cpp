#include "3dstructs.h"
#include <cmath>
#include <numeric>
#include <vector>

float const PI = 4*atan(1); // Pi=3.14

vec4 operator*(const mat4& aMatrix, const vec4& aVector){
    vec4 result = {0};
    result.x = aMatrix.matrix[0][0] * aVector.x +
               aMatrix.matrix[0][1] * aVector.y +
               aMatrix.matrix[0][2] * aVector.z +
               aMatrix.matrix[0][3] * aVector.w;

    result.y = aMatrix.matrix[1][0] * aVector.x +
               aMatrix.matrix[1][1] * aVector.y +
               aMatrix.matrix[1][2] * aVector.z +
               aMatrix.matrix[1][3] * aVector.w;

    result.z = aMatrix.matrix[2][0] * aVector.x +
               aMatrix.matrix[2][1] * aVector.y +
               aMatrix.matrix[2][2] * aVector.z +
               aMatrix.matrix[2][3] * aVector.w;

    result.w = aMatrix.matrix[3][0] * aVector.x +
               aMatrix.matrix[3][1] * aVector.y +
               aMatrix.matrix[3][2] * aVector.z +
               aMatrix.matrix[3][3] * aVector.w;

    return result;
}

mat4 operator*(const mat4& matrix1, const mat4& matrix2){
    mat4 resultMatrix = {0};
    float mulResult;

    for(int i = 0 ; i< 4;i++){
        for(int j=0;j<4;j++){
            mulResult = 0;
            mulResult += matrix1.matrix[i][0] * matrix2.matrix[0][j];
            mulResult += matrix1.matrix[i][1] * matrix2.matrix[1][j];
            mulResult += matrix1.matrix[i][2] * matrix2.matrix[2][j];
            mulResult += matrix1.matrix[i][3] * matrix2.matrix[3][j];
            resultMatrix.matrix[i][j] = mulResult;
        }
    }

    return resultMatrix;
}



const mat4 buildProjectionMatrix(float width, float height, float angle, float zFar, float zNear){
    mat4 projection;
    // row 0
    projection.matrix[0][0] = (height/width) * (1/tan(toRadians(angle/2)));
    projection.matrix[0][1] = 0;
    projection.matrix[0][2] = 0;
    projection.matrix[0][3] = 0;

    // row 1
    projection.matrix[1][0] = 0;
    projection.matrix[1][1] = 1/tan(toRadians(angle/2));
    projection.matrix[1][2] = 0;
    projection.matrix[1][3] = 0;

    // row 2
    projection.matrix[2][0] = 0;
    projection.matrix[2][1] = 0;
    projection.matrix[2][2] = zFar / (zFar - zNear);
    projection.matrix[2][3] = 1;

    // row 3
    projection.matrix[3][0] = 0;
    projection.matrix[3][1] = 0;
    projection.matrix[3][2] = ((-zFar) * zNear) / (zFar - zNear);
    projection.matrix[3][3] = 0;

    return projection;
}


const mat4 buildViewMatrix(const vec3 camera, float pitch, float yaw){
    float cosPitch = cos(toRadians(pitch));
    float sinPitch = sin(toRadians(pitch));
    float cosYaw = cos(toRadians(yaw));
    float sinYaw = sin(toRadians(yaw));


    vec3 xaxis =  {cosYaw , 0 , -sinYaw};
    vec3 yaxis =  {sinYaw * sinPitch , cosPitch , cosYaw * sinPitch};
    vec3 zaxis =  {sinYaw * cosPitch , -sinPitch , cosPitch * cosYaw};

    mat4 viewMatrix = {
        xaxis.x, yaxis.x, zaxis.x, 0,
        xaxis.y, yaxis.y, zaxis.y, 0,
        xaxis.z, yaxis.z, zaxis.z, 0,
        -dot(xaxis,camera), -dot(yaxis,camera), -dot(zaxis,camera), 1
    };

    return viewMatrix;
}

float dot(vec3 vector1 ,vec3 vector2){
    std::vector<float> a {vector1.x, vector1.y, vector1.z};
    std::vector<float> b {vector2.x, vector2.y, vector2.z};

    return std::inner_product(std::begin(a), std::end(a), std::begin(b), 0.0);
}

std::ostream& operator<<(const std::ostream &out,const mat4& mat){


    for (int i=0; i< 4 ;i++){
        for (int j = 0 ; j < 4 ; j++){
            if( j < 3)
                std::cout << mat.matrix[i][j] << " ,";
            else
                std::cout << mat.matrix[i][j];
        }
        std::cout << std::endl;
    }
}
std::ostream& operator<<(const std::ostream &out,const vec4& mat){
    std::cout << "( " << mat.x << " , " << mat.y << " , " << mat.z << " ) ";
}

float toRadians(float angle){
    float converter = 180 / PI ;
    return angle * converter;
}

vec4 translateToWorld(vec4 translate){
    mat4 _toWorld = {
        1,0,0,-0.5,
        0,1,0,-0.5,
        0,0,1,0.5,
        0,0,0,1
    };
    return _toWorld * translate;
}

vec4 rotateX(vec4 rotateMe,float angle){
    mat4 xRotation = {
        1,0,0,0,
        0,cos(toRadians(angle)),-sin(toRadians(angle)),0,
        0,sin(toRadians(angle)),cos(toRadians(angle)),0,
        0,0,0,1
    };
    return xRotation * rotateMe;
}

vec4 rotateY(vec4 rotateMe,float angle){
    mat4 yRotation = {
        cos(toRadians(angle)),0,sin(toRadians(angle)),0,
        0,1,0,0,
        -sin(toRadians(angle)),0,cos(toRadians(angle)),0,
        0,0,0,1
    };
    return yRotation*rotateMe;
}

const mesh buildCube(){
    mesh cube;

    //t1 -- yellow
    cube.trianglesMesh.push_back({0,0,0,1,
                                  1,1,0,1,
                                  1,0,0,1});

    //t2 -- light green
    cube.trianglesMesh.push_back({0,0,0,1,
                                  0,1,0,1,
                                  1,1,0,1});

    //t3 -- red
    cube.trianglesMesh.push_back({0,0,0,1,
                                  0,1,1,1,
                                  0,1,0,1});

    //t4 -- light blue
    cube.trianglesMesh.push_back({0,0,0,1,
                                  0,0,1,1,
                                  0,1,1,1});

    //t5 -- purple
    cube.trianglesMesh.push_back({0,0,0,1,
                                  1,0,0,1,
                                  1,0,1,1});

    //t6 -- brown
    cube.trianglesMesh.push_back({0,0,0,1,
                                  1,0,1,1,
                                  0,0,1,1});

    //t7 -- blue
    cube.trianglesMesh.push_back({1,0,0,1,
                                  1,1,1,1,
                                  1,0,1,1});

    //t8 -- green
    cube.trianglesMesh.push_back({1,0,0,1,
                                  1,1,0,1,
                                  1,1,1,1});

    //t9 -- gray
    cube.trianglesMesh.push_back({1,1,1,1,
                                  0,1,1,1,
                                  0,0,1,1});

    //t10 -- orange
    cube.trianglesMesh.push_back({1,1,1,1,
                                  0,0,1,1,
                                  1,0,1,1});

    // t11 -- black1
    cube.trianglesMesh.push_back({0,1,0,1,
                                  0,1,1,1,
                                  1,1,1,1});

    // t12 -- black2
    cube.trianglesMesh.push_back({0,1,0,1,
                                  1,1,1,1,
                                  1,1,0,1});

    return cube;
}
