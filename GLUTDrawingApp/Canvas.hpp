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
    // Elements on the canvas that the user has drawn
    std::vector<Drawable*> elements;
    Canvas(CGRect rect) : CGView(rect) {
        shouldHandleMouseEvent = true;
        currentTool = DrawingToolLine;
        lineWidth = 5;
    };
    // Current line width used by canvas for drawing
    int lineWidth;
    // Current point size used by canvas for drawing
    int pointSize;
    void draw();
    void wasClicked(CGPoint point);
    void setDrawingTool(DrawingTool tool);
    // Clear the canvas by removing drawn elements
    void clear();
    // Current color used by canvas
    CGColor color;
    // Delegate for receiving custom color selected messages
    ColorChangeFunction colorDelegate;
    // Array of positions where the user has clicked the canvas
    std::vector<CGPoint> positions;
};


#endif /* Canvas_hpp */
