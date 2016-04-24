//
//  Rectangle.hpp
//  GLUTDrawingApp
//
//  Created by Ben Johnson on 13/04/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#ifndef Rectangle_hpp
#define Rectangle_hpp

#include <stdio.h>
#include "Drawable.hpp"
#include "CGGeometry.hpp"
#include <math.h>

class Rectangle: public Drawable {
    
public:
    CGRect rect;
    Rectangle(CGPoint fromPoint, CGPoint toPoint) : Drawable() {
       // Get Width
        float width = fabs(toPoint.x - fromPoint.x);
        float height = fabs(toPoint.y - fromPoint.y);
        
        // Get Origin
        float y = fmin(fromPoint.y, toPoint.y);
        float x = fmin(fromPoint.x, toPoint.x);
        
        rect = CGRectMake(x,y, width,height);
        
        
    }
    void draw();
    
};

#endif /* Rectangle_hpp */
