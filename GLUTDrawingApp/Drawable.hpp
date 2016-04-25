//
//  Drawable.hpp
//  GLUTDrawingApp
//
//  Created by Ben Johnson on 13/04/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#ifndef Drawable_hpp
#define Drawable_hpp

#include <stdio.h>
#include "CGGeometry.hpp"

typedef enum ShapeType {
   ShapeTypeLine,
    ShapeTypeFilled
} ShapeType;

// A class that defines properties of a drawable element for the canvas
class Drawable {
    
public:
    CGColor color;
    ShapeType type;
    Drawable();
    float borderWidth;
    virtual void draw();
};


#endif /* Drawable_hpp */
