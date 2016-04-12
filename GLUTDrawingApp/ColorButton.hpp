//
//  ColorButton.hpp
//  GLUTDrawingApp
//
//  Created by Benjamin Johnson on 12/04/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#ifndef ColorButton_hpp
#define ColorButton_hpp

#include <stdio.h>
#include "CGButton.hpp"

class ColorButton: public CGButton {
    
public:    
    ColorButton(CGRect rec);
    void draw();
   void wasClicked();

};


#endif /* ColorButton_hpp */
