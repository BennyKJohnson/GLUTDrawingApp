//
//  Toolpanel.cpp
//  GLUTDrawingApp
//
//  Created by Benjamin Johnson on 12/04/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#include "Toolpanel.hpp"

#ifdef __APPLE__
#include <GLUT/GLUT.h> //GLUT Library, will make you life easier
#include <OpenGL/OpenGL.h> //OpenGL Library
#elif defined _WIN32 || defined _WIN64
#    include <glut.h>
#endif




 void Toolpanel::draw() {
    drawRect(frame, CGColorMakeWithRGB(50, 50, 50));
     CGView::draw();
}
