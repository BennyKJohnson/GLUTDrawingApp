//
//  Polygon.cpp
//  GLUTDrawingApp
//
//  Created by Ben Johnson on 13/04/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#include "Polygon.hpp"
#ifdef __APPLE__
#include <GLUT/GLUT.h> //GLUT Library, will make you life easier
#include <OpenGL/OpenGL.h> //OpenGL Library
#elif defined _WIN32 || defined _WIN64
#include <glut.h>
#endif

void Polygon::draw() {
    setContextColor(color);
    
    
    
    glBegin(GL_POLYGON);// Begin drawing of polygon

    for (int i = 0; i < numberOfPoints; i++) {
        CGPoint point = corners[i];
        glVertex2f(point.x, point.y);
    }
    
    glEnd();// End drawing of polygon
 
}