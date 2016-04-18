//
//  Polygon.hpp
//  GLUTDrawingApp
//
//  Created by Ben Johnson on 13/04/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#ifndef Polygon_hpp
#define Polygon_hpp

#include <stdio.h>
#include "Drawable.hpp"
#include "CGGeometry.hpp"

class Polygon: public Drawable {
    
public:
    CGPoint* corners;
    int numberOfPoints;
    Polygon(CGPoint *corners, int numberOfPoints) : Drawable() {
        this->corners = corners;
        this->numberOfPoints = numberOfPoints;
    }
    void draw();
    
};

#endif /* Polygon_hpp */
