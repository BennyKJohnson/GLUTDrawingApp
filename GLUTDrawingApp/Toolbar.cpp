//
//  Toolbar.cpp
//  GLUTDrawingApp
//
//  Created by Ben Johnson on 14/04/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#include "Toolbar.hpp"



void Toolbar::draw() {
    drawRect(frame, CGColorMakeWithRGB(60, 60, 60));
    CGView::draw();
}