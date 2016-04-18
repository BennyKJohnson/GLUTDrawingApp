//
//  ColorPalette.hpp
//  GLUTDrawingApp
//
//  Created by Benjamin Johnson on 12/04/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#ifndef ColorPalette_hpp
#define ColorPalette_hpp

#include <stdio.h>
#include "CGGeometry.hpp"
#include <vector>
#include "CGView.hpp"
#include "ColorButton.hpp"


typedef void (*ColorChangeFunction)(CGColor);

class ColorPalette: public CGView {
    void selectedColorDidChange(CGColor sender);
public:
    ColorPalette(CGRect rect);
    void draw();
    int selectedColorIndex;
    std::vector<CGColor> colors;
    std::vector<ColorButton*> colorButtons;
    void addColor(CGColor color);

    int colorWidth;
    int padding;
    int yPadding;
    void wasClicked(CGPoint point);
    int buttonsPerRow;
    ColorChangeFunction delegate;
    
};

#endif /* ColorPalette_hpp */
