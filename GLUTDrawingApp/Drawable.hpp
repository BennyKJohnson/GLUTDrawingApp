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

class Drawable {
    
public:
    CGColor color;
    Drawable();
    virtual void draw();
};


#endif /* Drawable_hpp */
