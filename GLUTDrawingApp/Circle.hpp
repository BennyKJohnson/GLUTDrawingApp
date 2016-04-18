//
//  Circle.hpp
//  GLUTDrawingApp
//
//  Created by Ben Johnson on 18/04/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#ifndef Circle_hpp
#define Circle_hpp

#include <stdio.h>
#include "Drawable.hpp"
#include "CGGeometry.hpp"

class Circle: public Drawable {
    
public:
    CGPoint center;
    float radius;
    
    Circle(CGPoint center, float radius) : Drawable() {
        this->center = center;
        this->radius = radius;
    }
    void draw();
    
};


#endif /* Circle_hpp */
