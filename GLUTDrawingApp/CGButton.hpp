//
//  BarButtonItem.hpp
//  GLUTDrawingApp
//
//  Created by Benjamin Johnson on 12/04/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#ifndef BarButtonItem_hpp
#define BarButtonItem_hpp

#include <stdio.h>
#include "CGGeometry.hpp"
#include <vector>
#include "CGView.hpp"

typedef enum ControlState {
    ControlStateNormal,
    ControlStateSelected
} ControlState;

typedef enum ButtonType {
    ButtonTypeLight,
    ButtonTypeDark
} ButtonType;


typedef enum ShapeIcon {
    ShapeIconNone,
    ShapeIconPoint,
    ShapeIconLine,
    ShapeIconTriangle,
    ShapeIconTriangleFilled,
    ShapeIconRectangle,
    ShapeIconRectangleFilled,
    ShapeIconCircle,
    ShapeIconCircleFilled
} ShapeIcon;

class CGButton;
typedef void (*ActionFunction)(CGButton);

class CGButton: public CGView {
    
public:
    ControlState controlState;
    ActionFunction handler;
    std::string *title;
    CGButton(CGRect rect) : CGView(rect) {
        title = NULL;
        type = ButtonTypeLight;
        icon = ShapeIconNone;
        tintColor = CGColorWhite();
    };
    ButtonType type;
    ShapeIcon icon;
    CGColor tintColor;
    void draw();
    
};

#endif /* BarButtonItem_hpp */
