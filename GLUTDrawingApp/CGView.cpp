//
//  CGView.cpp
//  GLUTDrawingApp
//
//  Created by Benjamin Johnson on 12/04/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#include "CGView.hpp"
#ifdef __APPLE__
#include <GLUT/GLUT.h> //GLUT Library, will make you life easier
#include <OpenGL/OpenGL.h> //OpenGL Library
#elif defined _WIN32 || defined _WIN64
#    include <glut.h>
#endif

CGView::CGView(CGRect rect) {
    
    // Set View Frame
    frame = rect;
    
    // Set Default Tag
    tag = 0;
    
    mouseHandler = NULL;
    shouldHandleMouseEvent = false;
    
  //  backgroundColor =  CGColorClearColor();
    
}

void CGView::draw() {
    
    // Draw background color
    //drawRect(frame, backgroundColor);
    
    // Draw All SubViews
    std::vector<CGView*>::iterator iterator = subViews.begin();
    for (iterator = subViews.begin(); iterator != subViews.end(); iterator++) {
        (*iterator)->draw();
    }
    
}

CGView* CGView::viewWithTag(int viewTag) {
    
    std::vector<CGView*>::iterator iterator = subViews.begin();
    for (iterator = subViews.begin(); iterator != subViews.end(); iterator++) {
        CGView *currentView = *iterator;
        if (currentView->tag == viewTag) {
            return currentView;
        }
    }
    
    if (tag == viewTag) {
        return this;
    } else {
        return NULL;
    }
}

CGView* CGView::hitTest(CGPoint point) {
    
    std::vector<CGView*>::iterator iterator = subViews.begin();
    for (iterator = subViews.begin(); iterator != subViews.end(); iterator++) {
        CGView *currentView = *iterator;
        if (hitTestWithRect(currentView->frame, point)) {
            CGView *subViewAtPoint = currentView->hitTest(point);
            if (subViewAtPoint != NULL && subViewAtPoint->shouldHandleMouseEvent) {
                return subViewAtPoint;
            }
            return currentView;
        }
    }
    
    // Test currentView
    if(hitTestWithRect(frame, point)) {
        return this;
    } else {
        return NULL;
    }
}

void CGView::wasClicked(CGPoint point) {
    if (mouseHandler != NULL) {
        mouseHandler(this);

    }
}

void CGView::addSubview(CGView* view) {
    
    subViews.push_back(view);
    
}

