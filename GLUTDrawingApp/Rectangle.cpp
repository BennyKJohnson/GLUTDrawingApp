//
//  Rectangle.cpp
//  GLUTDrawingApp
//
//  Created by Ben Johnson on 13/04/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#include "Rectangle.hpp"

void Rectangle::draw() {
    
    if (type == ShapeTypeLine) {
        setDrawingModeToLine();
        setLineWidth(borderWidth);
    }
    
    drawRect(rect, color);
    setDrawingModeToFilled();
    
    
}