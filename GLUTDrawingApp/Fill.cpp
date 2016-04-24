//
//  Fill.cpp
//  GLUTDrawingApp
//
//  Created by Benjamin Johnson on 24/04/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#include "Fill.hpp"
#ifdef __APPLE__
#include <GLUT/GLUT.h> //GLUT Library, will make you life easier
#include <OpenGL/OpenGL.h> //OpenGL Library
#elif defined _WIN32 || defined _WIN64
#    include <glut.h>
#endif

void Fill::draw() {
    setContextColor(color);
    glPointSize(1);
    glDisable(GL_POINT_SMOOTH);
    boundaryFill(location, color, boundColor);
}

void Fill::boundaryFill(CGPoint point, CGColor fillColor, CGColor boundaryColor) {
    CGColor currentColor = colorOfPixelAtPoint(point);
    
    drawPoint(point);
    
     if (currentColor == boundaryColor) {
     drawPoint(point);
     
     CGPoint rightPoint = point;
     rightPoint.x += 1;
     
     CGPoint leftPoint = point;
     leftPoint.x -= 1;
     
     CGPoint topPoint = point;
     topPoint.y -= 1;
     
     CGPoint bottomPoint = point;
     bottomPoint.y += 1;
     
     boundaryFill(leftPoint, fillColor, boundaryColor);
     boundaryFill(rightPoint, fillColor, boundaryColor);
     boundaryFill(bottomPoint, fillColor, boundaryColor);
     boundaryFill(topPoint, fillColor, boundaryColor);
     
     }

}