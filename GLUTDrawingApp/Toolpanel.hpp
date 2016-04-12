//
//  Toolpanel.hpp
//  GLUTDrawingApp
//
//  Created by Benjamin Johnson on 12/04/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#ifndef Toolpanel_hpp
#define Toolpanel_hpp

#include <stdio.h>
#include "CGGeometry.hpp"
#include "CGView.hpp"

class Toolpanel: public CGView {
    
public:
    void draw();
    Toolpanel(CGRect rect) : CGView(rect) {
        
    };
};



#endif /* Toolpanel_hpp */
