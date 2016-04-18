//
//  Circle.cpp
//  GLUTDrawingApp
//
//  Created by Ben Johnson on 18/04/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#include "Circle.hpp"
#ifdef __APPLE__
#include <GLUT/GLUT.h> //GLUT Library, will make you life easier
#include <OpenGL/OpenGL.h> //OpenGL Library
#elif defined _WIN32 || defined _WIN64
#include <glut.h>
#endif

void Circle::draw() {
    drawCircle(center, radius, color);
}