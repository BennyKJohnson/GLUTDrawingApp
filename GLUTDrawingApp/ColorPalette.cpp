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
     buttonsPerRow = 4;
    
}

void ColorPalette::selectedColorDidChange(CGColor color) {
    delegate(color);
}

void ColorPalette::selectColorAtIndex(int index) {
    std::vector<ColorButton*>::iterator iterator = colorButtons.begin();
    
    for (iterator = colorButtons.begin(); iterator != colorButtons.end(); iterator++) {
        (*iterator)->controlState = ControlStateNormal;
    }
    
    ColorButton *button = colorButtons[index];
    button->controlState = ControlStateSelected;
    selectedColorDidChange(button->backgroundColor);
}

void ColorPalette::setCustomColor(CGColor color) {
    // Get Last button
    int buttonIndex = (int)colorButtons.size() - 1;
    ColorButton *customColorButton = colorButtons[buttonIndex];
    customColorButton->backgroundColor = color;
    
    selectColorAtIndex(buttonIndex);
}

void ColorPalette::addColor(CGColor color) {
    int numberOfColors = (int)colors.size();

    int rowNumber = numberOfColors / buttonsPerRow;
    int colNumber = (numberOfColors) % buttonsPerRow;
    colors.push_back(color);
    

    
    int xPosition = frame.origin.x + 10 + (padding * colNumber);
    int yPosition = frame.origin.y + yPadding + (rowNumber * (colorWidth + yPadding));
    
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
    CGView::draw();
    
    // Once drawn the text is no longer required. So cleanup memory
}
