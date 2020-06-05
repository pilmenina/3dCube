#include <SFML/Graphics.hpp>
#include "3dstructs.h"
#include <iostream>
#include <time.h>
#include <math.h>

#define fps 1000/60

// functions
void drawCube(sf::RenderWindow& window);

// global variables
const float width  = 800;
const float height = 500;
const mat4 projectionMatrix = buildProjectionMatrix(width,height,130,100,0.1); // DONE
const mesh cubeMesh = buildCube(); // DONE
const vec3 cameraCoordinates = {0,0,-3};
const mat4 viewMatrix = buildViewMatrix(cameraCoordinates,12,12);

const mat4 scale = {
    1000,0,0,0,
    0,1000,0,0,
    0,0,1000,0,
    0,0,0,1
};

float _rotationXANGLE = 0;
float _rotationYANGLE = 0;

int main()
{
    clock_t t;
    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!");
    t = clock();

    std::cout << viewMatrix << std::endl;
    std::cout << projectionMatrix << std::endl;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if(clock()-t > fps){
            drawCube(window);
            t = clock();
        }
    }
    return 0;
}

void drawCube(sf::RenderWindow& window){
    window.clear();
    vec4 point1 = {0};
    vec4 point2 = {0};
    vec4 point3 = {0};
    for(triangle t : cubeMesh.trianglesMesh){ // draw the lines of each triangle
        // translate the points of the triangle with MVP
        point1 = translateToWorld(t.p[0]);
        point2 = translateToWorld(t.p[1]);
        point3 = translateToWorld(t.p[2]);

        point1 = scale * point1;
        point2 = scale * point2;
        point3 = scale * point3;



        point1 = rotateY(point1,_rotationYANGLE);
        point2 = rotateY(point2,_rotationYANGLE);
        point3 = rotateY(point3,_rotationYANGLE);

        point1 = rotateX(point1,_rotationXANGLE);
        point2 = rotateX(point2,_rotationXANGLE);
        point3 = rotateX(point3,_rotationXANGLE);

        point1 = viewMatrix * point1;
        point2 = viewMatrix * point2;
        point3 = viewMatrix * point3;

        point1 = projectionMatrix * point1;
        point2 = projectionMatrix * point2;
        point3 = projectionMatrix * point3;


        // draw the lines with x and y only
        sf::Vertex line1[] = {
            sf::Vertex(sf::Vector2f(point1.x + width/2,point1.y + height/2),sf::Color::White),
            sf::Vertex(sf::Vector2f(point2.x + width/2,point2.y + height/2),sf::Color::White)
        };

        sf::Vertex line2[] = {
            sf::Vertex(sf::Vector2f(point2.x + width/2,point2.y + height/2),sf::Color::White),
            sf::Vertex(sf::Vector2f(point3.x + width/2,point3.y + height/2),sf::Color::White)
        };

        sf::Vertex line3[] = {
            sf::Vertex(sf::Vector2f(point3.x + width/2,point3.y + height/2),sf::Color::White),
            sf::Vertex(sf::Vector2f(point1.x + width/2,point1.y + height/2),sf::Color::White)
        };

        window.draw(line1,2,sf::Lines);
        window.draw(line2,2,sf::Lines);
        window.draw(line3,2,sf::Lines);
    }
    _rotationXANGLE+=0.0001;
    _rotationYANGLE+=0.0001;


    window.display();
}
