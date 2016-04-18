//
//  Line.cpp
//  GLUTDrawingApp
//
//  Created by Ben Johnson on 13/04/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#include "Line.hpp"

void Line::draw() {
    setContextColor(color);
    drawLine(fromPoint, toPoint, 5);
}