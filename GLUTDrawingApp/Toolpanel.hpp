//
//  Toolpanel.hpp
//  GLUTDrawingApp
//  Manages the layout of buttons
//  Created by Benjamin Johnson on 12/04/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#ifndef Toolpanel_hpp
#define Toolpanel_hpp

#include <stdio.h>
#include "CGGeometry.hpp"
#include "CGView.hpp"
#include <vector>
#include "CGButton.hpp"

class Toolpanel;
typedef void (*ButtonHandlerFunction)(Toolpanel*,int, CGButton*);

class Toolpanel: public CGView {
    
public:
    int padding;
    int topPadding;
    std::vector<CGButton*> buttons;
    void addButton(CGButton* button);
    void draw();
    Toolpanel(CGRect rect) : CGView(rect) {
        topPadding = 10;
        padding = 20;
        itemsPerRow = 5;
        shouldHandleMouseEvent = true;
    };
    ButtonHandlerFunction action;
    void wasClicked(CGPoint point);
    int itemsPerRow;

};



#endif /* Toolpanel_hpp */
