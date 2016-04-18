//
//  ColorButton.cpp
//  GLUTDrawingApp
//
//  Created by Benjamin Johnson on 12/04/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#include "ColorButton.hpp"
#include <iostream>

ColorButton::ColorButton(CGRect rect) : CGButton(rect){
    backgroundColor = CGColorWhite();
    
}


void ColorButton::draw() {
  
  
    if (controlState == ControlStateSelected) {
        CGRect selectedCircleRect = CGRectMake(0, 0, frame.size.width + 5, frame.size.width  + 5);
        selectedCircleRect = centerAtPoint(getCenter(frame), selectedCircleRect);
        
        // Draw White Circle Border
        drawCircle(selectedCircleRect, CGColorWhite());
    }
    
    drawCircle(frame, backgroundColor);
    
   // CGButton::draw();
}
void ColorButton::wasClicked() {
    std::cout << "Color button was clicked";
    
}