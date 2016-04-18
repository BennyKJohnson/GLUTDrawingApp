//
//  Canvas.cpp
//  GLUTDrawingApp
//
//  Created by Ben Johnson on 13/04/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#include "Canvas.hpp"
#include <iostream>
#include "Polygon.hpp"
#include "Line.hpp"
#include "Circle.hpp"
#include "Point.hpp"
#include <math.h>

void Canvas::draw() {
    drawRect(frame, backgroundColor);
    
    // Iterate through shapes
    std::vector<Drawable*>::iterator iterator = elements.begin();
    for (iterator = elements.begin(); iterator != elements.end(); iterator++) {
        (*iterator)->draw();
    }
}

int drawingToolPointsRequired(DrawingTool tool) {
    switch (tool) {
        case DrawingToolPoint:
            return 1;
            break;
        case DrawingToolLine:
            return 2;
            break;
        case DrawingToolTriangle:
            return 3;
            break;
        case DrawingToolRectangle:
            return 2;
            break;
        case DrawingToolCircle:
            return 2;
    }
}

void Canvas::setDrawingTool(DrawingTool tool) {
    currentTool = tool;
    // Reset Points
    positions.clear();
}

CGPoint* copyPointsToArray(std::vector<CGPoint> points) {
    CGPoint *pointsArray = new CGPoint[(int)points.size()];
    
    for (int i = 0; i < points.size(); i++) {
        CGPoint point = points[i];
        pointsArray[i] = point;
    }
    return pointsArray;
}

void Canvas::boundaryFill(CGPoint point, CGColor fillColor, CGColor boundaryColor) {
    
    CGColor currentColor = colorOfPixelAtPoint(point);
    
    if (currentColor != boundaryColor) {
        drawPoint(point, fillColor);
        
        CGPoint rightPoint = point;
        rightPoint.x += 1;
        
        CGPoint leftPoint = point;
        leftPoint.x -= 1;
        
        CGPoint topPoint = point;
        topPoint.y -= 1;
        
        CGPoint bottomPoint = point;
        bottomPoint.y += 1;
        
        boundaryFill(leftPoint, fillColor, boundaryColor);
        boundaryFill(rightPoint, fillColor, boundaryColor);
        boundaryFill(bottomPoint, fillColor, boundaryColor);
        boundaryFill(topPoint, fillColor, boundaryColor);

    }
}

void Canvas::addPosition(CGPoint point) {
    
    // Add Position
    positions.push_back(point);
    
    if (positions.size() == drawingToolPointsRequired(currentTool)) {

    

        switch (currentTool) {
            case DrawingToolPoint:
            {
                
                Point *drawPoint = new Point(point);
                drawPoint->color = color;
                elements.push_back(drawPoint);
                
                /*
                // Get color at point
                CGColor color = colorOfPixelAtPoint(point);
                std::cout << "Picked color " << color.r << " " << color.g << " " << color.b << std::endl;
                
                */
               // int i = 0;
                break;
            }
            case DrawingToolLine:
            {
                Line *line = new Line(positions[0], positions[1]);
                line->color = color;
                elements.push_back(line);
                
                break;
            }
            case DrawingToolTriangle:
            {
                // Create Triangle
                Polygon *triangle = new Polygon(copyPointsToArray(positions), 3);
                triangle->color = color;
                elements.push_back(triangle);
                
                break;
            }
            case DrawingToolRectangle:
                break;
                
            case DrawingToolCircle:
            {
                // Get center
                CGPoint center = positions[0];
                CGPoint outerPoint = positions[1];
                
                float distance = sqrtf(powf((outerPoint.x - center.y), 2) + powf((outerPoint.y - center.y), 2));
                Circle *circle = new Circle(center, distance);
                elements.push_back(circle);
            }

        }
        positions.clear();
    
        
        
    }
    
    
}

void Canvas::wasClicked(CGPoint point) {
    
    std::cout << "Canvas was clicked";
    
    addPosition(point);
    /*
    // Add triangle
    CGPoint v1 = CGPointMake(0, 100);
    CGPoint v2 = CGPointMake(0, 200);
    CGPoint v3 = CGPointMake(100, 200);
    
    CGPoint *trianglePoints = new CGPoint[3];
    trianglePoints[0] = v1;
    trianglePoints[1] = v2;
    trianglePoints[2] = v3;
    */

}
