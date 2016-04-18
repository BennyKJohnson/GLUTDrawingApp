//
//  main.cpp
//  GLUTDrawingApp
//
//  Created by Benjamin Johnson on 12/04/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#include <iostream>
#include <string>

#ifdef __APPLE__
#include <GLUT/GLUT.h> //GLUT Library, will make you life easier
#include <OpenGL/OpenGL.h> //OpenGL Library
#elif defined _WIN32 || defined _WIN64
#include <glut.h>
#endif

#include "CGGeometry.hpp"
#include "Toolbar.hpp"
#include "ColorPalette.hpp"
#include "CGView.hpp"
#include "Canvas.hpp"
#include "Toolpanel.hpp"


int mainWindow;
Toolbar *toolbar;
Toolpanel *shapePanel;
ColorPalette *colorPalette;
CGView *contentView;
Canvas *canvas;


void setOGLProjection(int width, int height) {
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glOrtho(0, width, height, 0, -1, 1);
    
    //Back to the modelview so we can draw stuff
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
}

void windowShouldRedraw() {
    glutSetWindow(mainWindow);
    glutPostRedisplay();
}

void mouseHandler(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        //Get selected View
        CGView *selectedView = contentView->hitTest(CGPointMake(x, y));
        selectedView->wasClicked(CGPointMake(x, y));
        windowShouldRedraw();

    }
}

void resize(int width, int height) {
    
    //  int width = glutGet(GLUT_WINDOW_WIDTH);
    // int height = glutGet(GLUT_WINDOW_HEIGHT);
    
    setOGLProjection(width, height);
}


CGRect getWindowRect() {
    int x = glutGet(GLUT_WINDOW_X);
    int y = glutGet(GLUT_WINDOW_Y);
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    
    return CGRectMake((float)x, (float)y, (float)width, (float)height);
}

void render(void){
    
    // Set background color to white and opaque
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    // Clear the buffer
    glClear(GL_COLOR_BUFFER_BIT);
    
    contentView->draw();
  
    glFlush();
    
}




void selectedColorDidChange(CGColor color) {
    std::cout << "Color did change" << std::endl;
    canvas->color = color;
    windowShouldRedraw();
    
}

void selectedShapeToolDidChange(Toolpanel *toolPanel,int index, CGButton *button) {
    std::cout << "Selected Shape Tool changed " << index;
    
    DrawingTool selectedTool = static_cast<DrawingTool>(index);
    canvas->setDrawingTool(selectedTool);
}

void initOpenGL() {
    
    CGRect windowRect = getWindowRect();
    int statusBarHeight = 100;
    float yPosition = windowRect.size.height - statusBarHeight;
    CGRect statusBarRect = CGRectMake(0, yPosition, windowRect.size.width, statusBarHeight);
    contentView = new CGView(CGRectMake(0, 0, windowRect.size.width, windowRect.size.height));
    toolbar = new Toolbar(statusBarRect);
    
    colorPalette = new ColorPalette(CGRectMake(0, yPosition, 200,100));
    colorPalette->shouldHandleMouseEvent = true;
    colorPalette->delegate = selectedColorDidChange;
    
    colorPalette->addColor(CGColorSimpleBlue());
    colorPalette->addColor(CGColorSimpleOrange());
    colorPalette->addColor(CGColorSimpleYellow());
    colorPalette->addColor(CGColorSimpleGreen());
    colorPalette->addColor(CGColorSimpleCyan());
    colorPalette->addColor(CGColorSimpleRed());
    colorPalette->addColor(CGColorRed());

    // ToolPalette
    Toolpanel *toolPanel = new Toolpanel(CGRectMake(200, yPosition, 300, 100));
    toolPanel->backgroundColor = CGColorMakeWithRGB(60, 60, 60);
    toolPanel->action = selectedShapeToolDidChange;
    
    int buttonSize = 35;
    CGRect buttonRect = CGRectMake(0, 0, buttonSize, buttonSize);
    
    // Create Tool Buttons
    CGButton *pointButton = new CGButton(buttonRect);
    pointButton->backgroundColor = CGColorWhite();
    
    CGButton *lineButton = new CGButton(buttonRect);
    lineButton->backgroundColor = CGColorBlue();
    
    CGButton *triangleButton = new CGButton(buttonRect);
    triangleButton->backgroundColor = CGColorGreen();
    
    CGButton *rectangleButton = new CGButton(buttonRect);
    rectangleButton->backgroundColor = CGColorSimpleCyan();
    
    CGButton *circleButton = new CGButton(buttonRect);
    circleButton->backgroundColor = CGColorSimpleOrange();
    
    toolPanel->addButton(pointButton);
    toolPanel->addButton(lineButton);
    toolPanel->addButton(triangleButton);
    toolPanel->addButton(rectangleButton);
    toolPanel->addButton(circleButton);
    
    toolbar->addSubview(colorPalette);
    toolbar->addSubview(toolPanel);
    
    CGButton *colorPickerTool = new CGButton(buttonRect);
    

    canvas = new Canvas(CGRectMake(0, 0, windowRect.size.width, windowRect.size.height - 100));
    canvas->backgroundColor = CGColorWhite();
    
    // Add Views
    contentView->addSubview(canvas);
    contentView->addSubview(toolbar);

    glutDisplayFunc(render);
    glutReshapeFunc(resize);
    glutMouseFunc(mouseHandler);
}


int main(int argc, char * argv[]) {
    
#ifdef __APPLE__
    //Init glut passing some args
    glutInit(&argc, argv);
#endif
    
    //Specify the Display Mode, this one means there is a single buffer and uses RGB to specify colors
    // glutInitDisplayMode(GLUT_DEPTH| GLUT_DOUBLE |GLUT_RGB);
    
    //Set the window size
    glutInitWindowSize(800, 600);
    
    //Where do we want to place the window initially?
    glutInitWindowPosition(100,100);
    
    //Name the window and create it
    mainWindow = glutCreateWindow("Canvas");

    initOpenGL();
    
    //Start the main loop running, nothing after this will execute for all eternity (right now)
    glutMainLoop();
    
    return 0;
}