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
#include "Rectangle.hpp"
#include "Fill.hpp"

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
        case DrawingToolTriangleFilled:
            return 3;
            break;
        case DrawingToolRectangle:
            return 2;
            break;
        case DrawingToolRectangleFilled:
            return 2;
            break;
        case DrawingToolCircle:
            return 2;
            break;
        case DrawingToolCircleFilled:
            return 2;
            break;
        case DrawingToolColorPicker:
            return 1;
        case DrawingToolFill:
            return 1;
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
    drawPoint(point, fillColor, 40);
    /*
    if (currentColor == boundaryColor) {
        drawPoint(point, fillColor,1);
        
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
     */
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
                drawPoint->borderWidth = (float)pointSize;
                elements.push_back(drawPoint);
              
                break;
            }
            case DrawingToolLine:
            {
                Line *line = new Line(positions[0], positions[1], lineWidth);
                line->color = color;
                elements.push_back(line);
                
                break;
            }
            case DrawingToolTriangle:
            {
                // Create Triangle
                Polygon *triangle = new Polygon(copyPointsToArray(positions), 3);
                triangle->color = color;
                triangle->borderWidth = (float)lineWidth;
                elements.push_back(triangle);
                
                break;
            }
            case DrawingToolTriangleFilled:
            {
                Polygon *triangle = new Polygon(copyPointsToArray(positions), 3);
                triangle->color = color;
                triangle->type = ShapeTypeFilled;
                triangle->borderWidth = (float)lineWidth;
                elements.push_back(triangle);
                break;
            }
            case DrawingToolRectangle:
            {
                Rectangle *rectangle = new Rectangle(positions[0], positions[1]);
                rectangle->color = color;
                rectangle->borderWidth = (float)lineWidth;

                elements.push_back(rectangle);
                
                break;
            }
            case DrawingToolRectangleFilled:
            {
                Rectangle *rectangle = new Rectangle(positions[0], positions[1]);
                rectangle->color = color;
                rectangle->type = ShapeTypeFilled;
                rectangle->borderWidth = (float)lineWidth;
                
                elements.push_back(rectangle);
                
                break;
                
                
            }
            case DrawingToolCircle:
            {
                // Get center
                CGPoint center = positions[0];
                CGPoint outerPoint = positions[1];
                
                float distance = sqrtf(powf((outerPoint.x - center.x), 2) + powf((outerPoint.y - center.y), 2));
                Circle *circle = new Circle(center, distance);
                circle->borderWidth = (float)lineWidth;
                circle->color = color;
                elements.push_back(circle);
                break;
            }
            case DrawingToolCircleFilled:
            {
                // Get center
                CGPoint center = positions[0];
                CGPoint outerPoint = positions[1];
                
                float distance = sqrtf(powf((outerPoint.x - center.x), 2) + powf((outerPoint.y - center.y), 2));
                Circle *circle = new Circle(center, distance);
                circle->borderWidth = (float)lineWidth;
                circle->color = color;
                circle->type = ShapeTypeFilled;
                elements.push_back(circle);
            }
            case DrawingToolColorPicker:
            {
                // Get color at point
                CGColor color = colorOfPixelAtPoint(point);
                std::cout << "Picked color " << color.r << " " << color.g << " " << color.b << std::endl;
                
                if(colorDelegate != NULL) {
                    colorDelegate(color);
                }
                break;
            }
            case DrawingToolFill:
            {
                Fill *fill = new Fill(positions[0]);
                fill->color = color;
                fill->boundColor = colorOfPixelAtPoint(positions[0]);
                elements.push_back(fill);
                //boundaryFill(positions[0], color, colorOfPixelAtPoint(positions[0]));
                
                break;
            }

        }
        positions.clear();
    
        
        
    }
    
    
}

void Canvas::clear() {
    // Clear elements on canvas
    elements.clear();
}

void Canvas::wasClicked(CGPoint point) {
    addPosition(point);
}
