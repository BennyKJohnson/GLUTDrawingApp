//
//  ColorPalette.cpp
//  GLUTDrawingApp
//
//  Created by Benjamin Johnson on 12/04/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#include "ColorPalette.hpp"
#include "ColorButton.hpp"
#include <exception>

ColorPalette::ColorPalette(CGRect rect): CGView(rect) {
    selectedColorIndex = 0;
    
     colorWidth = 35;
     padding = colorWidth + 10;
     yPadding = 10;
    
}

void ColorPalette::selectedColorDidChange(CGColor color) {
    delegate(color);
}

void ColorPalette::addColor(CGColor color) {
    
    colors.push_back(color);
    
    int numberOfColors = (int)colors.size();
    int xPosition = frame.origin.x + (padding * numberOfColors);
    int yPosition = frame.origin.y + yPadding;
    
    // Create Color Button
    CGRect colorButtonRect = CGRectMake(xPosition, yPosition, colorWidth, colorWidth);
    
    ColorButton *colorButton = new ColorButton(colorButtonRect);
    colorButton->backgroundColor = color;
    addSubview(colorButton);
    colorButtons.push_back(colorButton);
    
    
}

void ColorPalette::wasClicked(CGPoint point) {
    std::vector<ColorButton*>::iterator iterator = colorButtons.begin();
    ColorButton *selectedColorButton = NULL;
    
    for (iterator = colorButtons.begin(); iterator != colorButtons.end(); iterator++) {
        CGView *clickedView = (*iterator)->hitTest(point);
        (*iterator)->controlState = ControlStateNormal;

        if (clickedView != NULL) {
            try {
                selectedColorButton = dynamic_cast<ColorButton*>(clickedView);
            } catch (std::exception& e) {
            }
        } else {
            
        }
    }
    if (selectedColorButton != NULL) {
        selectedColorButton->controlState = ControlStateSelected;
        selectedColorDidChange(selectedColorButton->backgroundColor);
        
    }

    
    
    
    
    
}

void ColorPalette::draw() {
    
    drawRect(frame, CGColorMakeWithRGB(60, 60, 60));
    
    /*
    std::vector<CGColor>::iterator iterator = colors.begin();
    
    int colorIndex = 0;
    int colorWidth = 35;
    int padding = colorWidth + 10;
    int yPadding = 10;
    
    
    int xPosition = frame.origin.x + padding;
    int yPosition = frame.origin.y + yPadding;
    
    for (iterator = colors.begin(); iterator != colors.end(); iterator++) {
        // Draw Circle to represent Color
        CGRect circleRect = CGRectMake(xPosition, yPosition, colorWidth, colorWidth);
        if (selectedColorIndex == colorIndex) {
            CGRect selectedCircleRect = CGRectMake(xPosition, yPosition, colorWidth + 5, colorWidth + 5);
            selectedCircleRect = centerAtPoint(getCenter(circleRect), selectedCircleRect);
            
            // Draw White Circle Border
            drawCircle(selectedCircleRect, CGColorWhite());
        }

        drawCircle(circleRect, *iterator);
        
        colorIndex++;
        xPosition += padding;
    }
    */
    CGView::draw();
    
    // Once drawn the text is no longer required. So cleanup memory
}
