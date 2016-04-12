//
//  BarButtonItem.hpp
//  GLUTDrawingApp
//
//  Created by Benjamin Johnson on 12/04/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#ifndef BarButtonItem_hpp
#define BarButtonItem_hpp

#include <stdio.h>
#include "CGGeometry.hpp"
#include <vector>
#include "CGView.hpp"

typedef enum ControlState {
    ControlStateNormal,
    ControlStateSelected
} ControlState;


class CGButton: public CGView {
    
public:
    ControlState controlState;
    
    CGButton(CGRect rect) : CGView(rect) {
        
    };
    void draw();
    
};

#endif /* BarButtonItem_hpp */
