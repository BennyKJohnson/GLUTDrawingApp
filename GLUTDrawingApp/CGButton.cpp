//
//  BarButtonItem.cpp
//  GLUTDrawingApp
//
//  Created by Benjamin Johnson on 12/04/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#include "CGButton.hpp"



void CGButton::draw() {
    
    if (controlState == ControlStateSelected && type != ButtonTypeDark) {
        CGRect selectedRect = CGRectMake(0, 0, frame.size.width + 5, frame.size.height  + 5);
        selectedRect = centerAtPoint(getCenter(frame), selectedRect);
        
        // Draw White Circle Border
        drawRect(selectedRect, CGColorWhite());
    }
    
    
    switch (type) {
        case ButtonTypeLight:
            drawRect(frame, backgroundColor);
            setContextColor(CGColorBlack());
            break;
        case ButtonTypeDark:
            setDrawingModeToLine();
            setLineWidth(1);
            drawRect(frame, backgroundColor);
            setDrawingModeToFilled();
            setContextColor(CGColorWhite());
        default:
            break;
    }
    
    // Draw Icon
    CGRect iconRect = CGRectMake(0, 0, frame.size.width - 12, frame.size.height - 12);
    CGPoint center = getCenter(frame);
    iconRect = centerAtPoint(getCenter(frame), iconRect);
    setContextColor(tintColor);

    switch (icon) {
        case ShapeIconPoint:
            drawPoint(getCenter(frame), tintColor, 8);
            break;
        case ShapeIconLine:
            drawLine(CGPointMake(center.x, iconRect.origin.y), CGPointMake(center.x, iconRect.origin.y + iconRect.size.height), 2);
            break;
        case ShapeIconTriangle:
            setLineWidth(2);

            setContextColor(tintColor);
            drawTriangle(iconRect, false);
            break;
        case ShapeIconTriangleFilled:
            drawTriangle(iconRect, true);
            break;
        case ShapeIconRectangle:
            setDrawingModeToLine();
            setLineWidth(2);

            drawRect(iconRect, tintColor);
            setDrawingModeToFilled();
            break;
        case ShapeIconRectangleFilled:
            drawRect(iconRect, tintColor);
            break;

        case ShapeIconCircle:
            drawLineCircle(getCenter(iconRect), iconRect.size.width / 2, tintColor);

            break;
        case ShapeIconCircleFilled:
            drawCircle(iconRect, tintColor);

            break;
        case ShapeIconNone:
            break;
    }
    
    
    if (title != NULL) {
        // Draw Title
        renderBitmapString(frame.origin.x, frame.origin.y + 18, title);
    }
    
    // Once drawn the text is no longer required. So cleanup memory
}
