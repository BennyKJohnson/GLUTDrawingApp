//
//  BarButtonItem.cpp
//  GLUTDrawingApp
//
//  Created by Benjamin Johnson on 12/04/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#include "CGButton.hpp"



void CGButton::draw() {
    
    drawRect(frame, backgroundColor);
    
    if (title != NULL) {
        // Draw Title
        setContextColor(CGColorBlack());
        renderBitmapString(frame.origin.x, frame.origin.y + 18, title);
    }
    
    // Once drawn the text is no longer required. So cleanup memory
}
