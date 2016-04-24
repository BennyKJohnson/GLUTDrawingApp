//
//  Point.hpp
//  GLUTDrawingApp
//
//  Created by Ben Johnson on 18/04/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#ifndef Point_hpp
#define Point_hpp

#include <stdio.h>
#include "Drawable.hpp"
#include "CGGeometry.hpp"

class Point: public Drawable {
    
public:
    CGPoint location;
    
    Point(CGPoint point) : Drawable() {
        location = point;
    }
    
    void draw();
    
};



#endif /* Point_hpp */
