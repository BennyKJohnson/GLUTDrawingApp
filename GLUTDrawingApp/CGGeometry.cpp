//
//  CGGeometry.cpp
//  GLUTGraphApplication
//
//  Created by Benjamin Johnson on 19/03/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#include "CGGeometry.hpp"
#include <string>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/GLUT.h> //GLUT Library, will make you life easier
#include <OpenGL/OpenGL.h> //OpenGL Library
#elif defined _WIN32 || defined _WIN64
#    include <glut.h>
#endif


CGRect CGRectMake(float x, float y, float width, float height) {
    CGRect rect;
    
    // Create Origin
    CGPoint origin;
    origin.x = x;
    origin.y = y;
    
    // Create Size
    CGSize size;
    size.width = width;
    size.height = height;
    
    rect.origin = origin;
    rect.size = size;
    
    return rect;
}

float degreesToRadians(float degree) {
    return degree * 0.0174533;
    
}

CGPoint getCenter(CGRect rect) {
    return CGPointMake(rect.origin.x + rect.size.width / 2, rect.origin.y + rect.size.height / 2);
}

void setContextColor(CGColor color) {
    glColor4f(color.r, color.g,color.b,  color.a);
}

CGColor CGColorWhite() {
    CGColor color;
    color.r = 1;
    color.b = 1;
    color.g = 1;
    color.a = 1;
    
    return color;
}

CGColor statusBarColor() {
    return CGColorMakeWithRGB(246, 246, 246);
}


// Modified code from http://slabode.exofire.net/circle_draw.shtml
void drawCircle(CGPoint center, float radius, CGColor color) {
    setContextColor(color);
    
    glPushMatrix();
    glTranslatef(center.x, center.y,0);
    
    glBegin(GL_TRIANGLE_FAN);
    // int numVectices = sweepAngleOuter - startAngleOuter;
    
    glVertex2f(0, 0);
    
    for (int i = 0; i <= 360; i++) {
        float x = radius * cosf(degreesToRadians(i));
        float y = radius * sinf(degreesToRadians(i));
        glVertex2f(x,y);//output vertex
    }
    
    glEnd();
    glPopMatrix();
}

void drawLineCircle(CGPoint center, float radius, CGColor color) {
    setContextColor(color);
    
    glPushMatrix();
    glTranslatef(center.x, center.y,0);
    
    glBegin(GL_LINE_LOOP);
    
    for (int i = 0; i <= 360; i++) {
        float x = radius * cosf(degreesToRadians(i));
        float y = radius * sinf(degreesToRadians(i));
        glVertex2f(x,y);//output vertex
    }
    
    glEnd();
    glPopMatrix();
}

void drawCircle(CGRect rect, CGColor color)
{
    
    float radius = fmin(rect.size.width, rect.size.height) / 2;
    CGPoint center = getCenter(rect);

    drawCircle(center, radius, color);
}

void drawPoint(CGPoint point, CGColor color, float pointSize) {
    glPointSize(pointSize);
    setContextColor(color);
    
    glBegin(GL_POINTS);
    glVertex2f(point.x, point.y);
    glEnd();
    
}

void drawPoint(CGPoint point) {
    glBegin(GL_POINTS);
    glVertex2f(point.x, point.y);
    glEnd();
}

void drawTriangle(CGRect rect, bool filled) {
    
    // Get Points
    CGPoint center = getCenter(rect);
    
    CGPoint top = CGPointMake(center.x, rect.origin.y);
    CGPoint left = CGPointMake(rect.origin.x, rect.origin.y + rect.size.height);
    CGPoint right = CGPointMake(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height);

    // Draw Points
    if(filled) {
        glBegin(GL_POLYGON);// Begin drawing of polygon
    } else {
        glBegin(GL_LINE_LOOP);
    }
    glVertex2f(top.x, top.y);
    glVertex2f(left.x, left.y);
    glVertex2f(right.x, right.y);
    glEnd();// End drawing of polygon

}

bool hitTestWithRect(CGRect rect, CGPoint point) {
    
    return (point.x >= rect.origin.x && point.x <= rect.origin.x + rect.size.width &&
        point.y >= rect.origin.y && point.y <= rect.origin.y + rect.size.height
            );
}

void drawRect(CGRect rect, CGColor color) {
    
    glColor4f(color.r, color.g,color.b,  color.a);
    
    glPushMatrix();
    glTranslatef(rect.origin.x, rect.origin.y, 0);
   
    glBegin(GL_QUADS); //Begin quadrilateral coordinates
    //Trapezoid
    glVertex2i(0, 0); //Upper left
    
    
    glVertex2i(0, rect.size.height); //Lower left
    
    glVertex2i(rect.size.width, rect.size.height); //Lower right
    
    glVertex2i(rect.size.width, 0); //Upper Right
    
    glEnd(); //End quadrilateral coordinates
    
    glPopMatrix();
    
}

CGRect getWindowRect() {
    int x = glutGet(GLUT_WINDOW_X);
    int y = glutGet(GLUT_WINDOW_Y);
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    
    return CGRectMake((float)x, (float)y, (float)width, (float)height);
}

CGColor colorOfPixelAtPoint(CGPoint point) {
   // CGRect window = getWindowRect();
    
    // Get Color
    glReadBuffer(GL_FRONT);
    unsigned char color[3];
    glReadPixels((int)point.x,600 - (int)point.y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
    return CGColorMakeWithRGB((int)color[0], (int)color[1], (int)color[2]);
}



// Helper function that returns a rect which origin will ensure that the rect is at the center of xy
CGRect offsetRectToCenterOnOrigin(CGRect rect) {
    CGRect newRect;
    newRect.size = rect.size;
    
    newRect.size.width = rect.size.width;
    newRect.size.height = rect.size.height;
    
    newRect.origin.x = rect.origin.x - (rect.size.width / 2);
    newRect.origin.y =  rect.origin.y - (rect.size.height / 2);
    return newRect;
}

// Returns new rect which is center point equals the center point of rect
CGRect centerAtPoint(CGPoint center, CGRect rect) {
    rect.origin.x = center.x - (rect.size.width / 2);
    rect.origin.y = center.y - (rect.size.height / 2);
    
    return rect;
}

void renderBitmapString(int x, int y, std::string *string, void *font) {
    // Set point to draw string
    glRasterPos2i(x, y);
    
    // Copy string into new CString
    char *c = new char[256];
    strcpy(c, string->c_str());
    
    // Iterate through each character of string
    while (*c != '\0') {
        // Draw individual character
        glutBitmapCharacter(font, *c);
        c++;
    }
}


void renderBitmapString(int x, int y, std::string *string) {
    renderBitmapString(x, y, string, GLUT_BITMAP_HELVETICA_18);
}


CGPoint CGPointMake(float x, float y) {
    CGPoint point;
    point.x = x;
    point.y = y;
    
    return point;
}

void setDrawingModeToLine() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

}
void setDrawingModeToFilled() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

void setLineWidth(float width) {
    glLineWidth(width);
}

void drawLine(CGPoint fromPoint, CGPoint toPoint, float width) {
    // Set line width
    glLineWidth(width);
    
    // Draw line
    glBegin(GL_LINES);
    glVertex2f(fromPoint.x, fromPoint.y);
    glVertex2f(toPoint.x, toPoint.y);
    glEnd();
}

CGColor CGColorMakeWithRGB(int r,int g,int b) {
    
    CGColor color;
    color.r = r / 255.0;
    color.b = b / 255.0;
    color.g = g / 255.0;
    color.a = 1;
    
    return color;
}

CGColor CGColorMakeWithRGB(char r,char g, char b) {
    
    CGColor color;
    color.r = r / 255.0;
    color.b = b / 255.0;
    color.g = g / 255.0;
    color.a = 1;
    
    return color;
}

CGColor CGColorSimpleYellow() {
    return CGColorMakeWithRGB(255,244,127);
}

CGColor CGColorSimpleCyan() {
    return CGColorMakeWithRGB(190,255,129);
}

CGColor CGColorSimpleGreen() {
    return CGColorMakeWithRGB(96,241,163);
}


CGColor CGColorSimpleBlue() {
    return CGColorMakeWithRGB(128,232,255);
}

CGColor CGColorSimpleRed() {
    return  CGColorMakeWithRGB(255,131,145);
}

CGColor CGColorSimpleOrange() {
    return CGColorMakeWithRGB(255,205,129);
}

CGColor CGColorDarkGray() {
    return CGColorMakeWithRGB(50, 50, 50);
}

CGColor CGColorRed() {
    CGColor color;
    color.r = 1;
    color.b = 0;
    color.g = 0;
    color.a = 1;
    
    return color;
}

CGColor CGColorClearColor() {
    CGColor color;
    color.r = 0;
    color.b = 0;
    color.g = 0;
    color.a = 0;
    
    return color;
}

CGColor CGColorBlack() {
    CGColor color;
    color.r = 0;
    color.b = 0;
    color.g = 0;
    color.a = 1;
    
    return color;
}

CGColor CGColorGreen() {
    CGColor color;
    color.r = 0;
    color.b = 0;
    color.g = 1;
    color.a = 1;
    
    return color;
}

CGColor CGColorBlue() {
    CGColor color;
    color.r = 0;
    color.b = 1;
    color.g = 0;
    color.a = 1;
    
    return color;
}

std::vector<CGColor> simpleColorScheme() {
    
    std::vector<CGColor> colors;
    
    colors.push_back(CGColorSimpleOrange());
    colors.push_back(CGColorSimpleBlue());
    colors.push_back(CGColorSimpleCyan());
    colors.push_back(CGColorSimpleRed());
    colors.push_back(CGColorSimpleYellow());
    colors.push_back(CGColorSimpleGreen());
    
    return colors;
}

