//
//  Fill.hpp
//  GLUTDrawingApp
//
//  Created by Benjamin Johnson on 24/04/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#ifndef Fill_hpp
#define Fill_hpp

#include <stdio.h>
#include "Drawable.hpp"
#include "CGGeometry.hpp"

class Fill: public Drawable {
    void boundaryFill(CGPoint point, CGColor fillColor, CGColor boundaryColor);
public:
    CGPoint location;
    CGColor boundColor;
    
    Fill(CGPoint point) : Drawable() {
        location = point;
    }
    
    void draw();
    
};



#endif /* Fill_hpp */
