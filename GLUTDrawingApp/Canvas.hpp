//
//  Canvas.hpp
//  GLUTDrawingApp
//
//  Created by Ben Johnson on 13/04/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#ifndef Canvas_hpp
#define Canvas_hpp

#include <stdio.h>
#include "CGGeometry.hpp"
#include "CGView.hpp"
#include <vector>
#include "Drawable.hpp"


typedef enum DrawingTool {
    DrawingToolPoint,
    DrawingToolLine,
    DrawingToolTriangle,
    DrawingToolTriangleFilled,
    DrawingToolRectangle,
    DrawingToolRectangleFilled,
    DrawingToolCircle,
    DrawingToolCircleFilled,
    DrawingToolColorPicker,
    DrawingToolFill
} DrawingTool;

typedef void (*ColorChangeFunction)(CGColor);

class Canvas: public CGView {
    void addPosition(CGPoint point);
    DrawingTool currentTool;
public:
    std::vector<Drawable*> elements;
    Canvas(CGRect rect) : CGView(rect) {
        shouldHandleMouseEvent = true;
        currentTool = DrawingToolLine;
        lineWidth = 5;
    };
    int lineWidth;
    int pointSize;
    void draw();
    void wasClicked(CGPoint point);
    void setDrawingTool(DrawingTool tool);
    void boundaryFill(CGPoint point, CGColor color, CGColor boundaryColor);
    void clear();
    CGColor color;
    ColorChangeFunction colorDelegate;

    
    std::vector<CGPoint> positions;
};


#endif /* Canvas_hpp */
