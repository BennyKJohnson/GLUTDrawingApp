//
//  Toolbar.hpp
//  GLUTDrawingApp
//
//  Created by Ben Johnson on 14/04/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#ifndef Toolbar_hpp
#define Toolbar_hpp

#include <stdio.h>
#include "CGGeometry.hpp"
#include "CGView.hpp"

class Toolbar: public CGView {
    
public:
    
    void draw();
    Toolbar(CGRect rect) : CGView(rect) {
        backgroundColor =  CGColorMakeWithRGB(50, 50, 50);
    };
};



#endif /* Toolbar_hpp */
