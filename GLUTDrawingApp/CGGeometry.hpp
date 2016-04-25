//
//  CGGeometry.hpp
//  GLUTGraphApplication
//  Helper structs and methods for 2D drawing in OpenGL
//  Created by Benjamin Johnson on 19/03/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#ifndef CGGeometry_hpp
#define CGGeometry_hpp

#include <stdio.h>
#include <string>
#include <vector>

// Simple struct for a rectangle area represented by x,y and width and height

// struct to represent a coordinate
typedef struct CGPoint {
    float x;
    float y;
    bool operator<(const CGPoint& rhs) const
    {
        return y <= rhs.y;
    }
    
} CGPoint;

typedef struct CGSize {
    float width;
    float height;
} CGSize;

typedef struct CGRect {
    CGPoint origin;
    CGSize size;
} CGRect;

// Returns a rectangle with the coordinate and size
CGRect CGRectMake(float x, float y, float width, float height);


CGPoint CGPointMake(float x, float y);

// Simple struct for color rgba values
typedef struct CGColor {
    float r;
    float g;
    float b;
    float a;
    bool operator==(const CGColor& rhs) const
    {
        return r == rhs.r && g == rhs.g && b == rhs.b;
    }
    bool operator!=(const CGColor& rhs) const
    {
        return !operator==(rhs);
    }
    
} CGColor;

// Convenience Constructor with rgb
CGColor CGColorMakeWithRGB(int r,int g,int b);
CGColor CGColorMakeWithRGB(char r,char g, char b);

// Sets OpenGL current color to CGColor values
void setContextColor(CGColor color);

// Convenience Init for colors
// Basic colors
CGColor CGColorRed();
CGColor CGColorBlue();
CGColor CGColorGreen();
CGColor CGColorBlack();
CGColor CGColorWhite();
CGColor CGColorClearColor();
CGColor CGColorDarkGray();

CGColor statusBarColor();
// Colors for main color scheme
CGColor CGColorSimpleCyan();
CGColor CGColorSimpleYellow();
CGColor CGColorSimpleOrange();
CGColor CGColorSimpleGreen();
CGColor CGColorSimpleRed();
CGColor CGColorSimpleBlue();

std::vector<CGColor> simpleColorScheme();

// Converts degrees to radians
float degreesToRadians(float degree);

CGPoint getCenter(CGRect rect);

// Moves rect to center on its original origin
CGRect offsetRectToCenterOnOrigin(CGRect rect);
bool hitTestWithRect(CGRect rect, CGPoint point);
void setDrawingModeToLine();
void setDrawingModeToFilled();
// Draw Helper Methods
void drawPoint(CGPoint point, CGColor color, float pointSize);
void drawPoint(CGPoint point);
void setLineWidth(float width);
void drawLine(CGPoint fromPoint, CGPoint toPoint, float lineWidth);
// Draws Circle within rect with color
void drawCircle(CGPoint center, float radius, CGColor color);
void drawCircle(CGRect rect, CGColor color);
// Draws rectangle of color within the coordinate and size
void drawRect(CGRect rect, CGColor color);
void drawTriangle(CGRect rect, bool filled);
// Draws string at x,y with font
void renderBitmapString(int x, int y, std::string *string, void *font);
void renderBitmapString(int x, int y, std::string *string);
CGRect getWindowRect();
CGRect centerAtPoint(CGPoint center, CGRect rect);
void drawLineCircle(CGPoint center, float radius, CGColor color);

CGColor colorOfPixelAtPoint(CGPoint point);


#endif /* CGGeometry_hpp */
