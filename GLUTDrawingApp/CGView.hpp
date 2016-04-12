//
//  CGView.hpp
//  GLUTDrawingApp
//
//  Created by Benjamin Johnson on 12/04/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#ifndef CGView_hpp
#define CGView_hpp

#include <stdio.h>
#include "CGGeometry.hpp"
#include <vector>
class CGView;
typedef int (*Handler) (CGView *sender);

class CGView {
    
public:
    CGRect frame;
    CGView(CGRect rect);
    CGColor backgroundColor;
    CGView* superview;
    
    int tag;
    virtual void draw();
    bool shouldHandleMouseEvent;
    CGView* viewWithTag(int viewTag);
    CGView* hitTest(CGPoint point);
    void addSubview(CGView* view);
    std::vector<CGView*> subViews;
    virtual void wasClicked(CGPoint point);
    Handler mouseHandler;
};


#endif /* CGView_hpp */
