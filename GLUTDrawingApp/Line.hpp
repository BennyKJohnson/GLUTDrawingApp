//
//  Line.hpp
//  GLUTDrawingApp
//
//  Created by Ben Johnson on 13/04/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#ifndef Line_hpp
#define Line_hpp

#include <stdio.h>
#include "Drawable.hpp"
#include "CGGeometry.hpp"

class Line: public Drawable {
    
public:
    CGPoint fromPoint;
    CGPoint toPoint;
    Line(CGPoint fromPoint, CGPoint toPoint) : Drawable() {
        this->fromPoint = fromPoint;
        this->toPoint = toPoint;
    }
    void draw();
    
};
#endif /* Line_hpp */
