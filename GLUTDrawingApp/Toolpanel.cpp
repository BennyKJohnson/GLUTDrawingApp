//
//  Toolpanel.cpp
//  GLUTDrawingApp
//
//  Created by Benjamin Johnson on 12/04/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#include "Toolpanel.hpp"

#ifdef __APPLE__
#include <GLUT/GLUT.h> //GLUT Library, will make you life easier
#include <OpenGL/OpenGL.h> //OpenGL Library
#elif defined _WIN32 || defined _WIN64
#    include <glut.h>
#endif

void Toolpanel::addButton(CGButton* button) {
    
    
    int numberOfButtons = (int)buttons.size();
    int rowNumber = numberOfButtons / itemsPerRow;
    int colNumber = numberOfButtons % itemsPerRow;
    
    float yPosition = frame.origin.y + topPadding + (rowNumber * (button->frame.size.height + 10));
    float xPostion = frame.origin.x;

    if (colNumber > 0) {
        // Get Last Button
        CGButton *button = buttons[numberOfButtons - 1];
        xPostion = button->frame.origin.x + button->frame.size.width;
    }
    
    xPostion += padding;
    
    button->frame.origin.x = xPostion;
    button->frame.origin.y = yPosition;
    
    buttons.push_back(button);
    addSubview(button);
}

void Toolpanel::setSelectedButtonAtIndex(int index) {
      std::vector<CGButton*>::iterator iterator = buttons.begin();
    for (iterator = buttons.begin(); iterator != buttons.end(); iterator++) {
        (*iterator)->controlState = ControlStateNormal;

    }
    
    CGButton *selectedButton = buttons[index];
    if (selectedButton != NULL) {
        selectedButton->controlState = ControlStateSelected;
        action(this, index, selectedButton);
    }
    
    
}
void Toolpanel::wasClicked(CGPoint point) {
    
    std::vector<CGButton*>::iterator iterator = buttons.begin();
    CGButton *selectedColorButton = NULL;
    int index = 0;
    int selectedIndex = -1;
    for (iterator = buttons.begin(); iterator != buttons.end(); iterator++) {
        CGView *clickedView = (*iterator)->hitTest(point);
        (*iterator)->controlState = ControlStateNormal;
        
        if (clickedView != NULL) {
            try {
                selectedColorButton = dynamic_cast<CGButton*>(clickedView);
                selectedIndex = index;
            } catch (std::exception& e) {
            }
        } else {
            
        }
        
        index++;
    }
    
    if (selectedColorButton != NULL) {
        selectedColorButton->controlState = ControlStateSelected;
        action(this, selectedIndex, selectedColorButton);
        //selectedColorDidChange(selectedColorButton->backgroundColor);
        
    }
}

 void Toolpanel::draw() {
    drawRect(frame, backgroundColor);
     CGView::draw();
}
