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
#include "Toolpanel.hpp"
#include "ColorPalette.hpp"
#include "CGView.hpp"

int mainWindow;
Toolpanel *toolpanel;
ColorPalette *colorPalette;
CGView *contentView;


void setOGLProjection(int width, int height) {
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glOrtho(0, width, height, 0, -1, 1);
    
    //Back to the modelview so we can draw stuff
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
}

void mouseHandler(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON) {
        //Get selected View
        CGView *selectedView = contentView->hitTest(CGPointMake(x, y));
        selectedView->wasClicked(CGPointMake(x, y));
        // Call function on view
        
    }
}

void resize(int width, int height) {
    
    //  int width = glutGet(GLUT_WINDOW_WIDTH);
    // int height = glutGet(GLUT_WINDOW_HEIGHT);
    
    setOGLProjection(width, height);
}

void selectedColorChanged(CGColor color) {
    
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
    
    // Draw Status Bar
    /*
    toolpanel->draw();
    colorPalette->draw();
*/
    glFlush();
    

    
  //  cout << "Did render" << endl;
}

void windowShouldRedraw() {
    glutSetWindow(mainWindow);
    glutPostRedisplay();
}


void selectedColorDidChange(CGColor color) {
    std::cout << "Color did change" << std::endl;
    windowShouldRedraw();
    
}


void initOpenGL() {
    
    CGRect windowRect = getWindowRect();
    int statusBarHeight = 100;
    float yPosition = windowRect.size.height - statusBarHeight;
    CGRect statusBarRect = CGRectMake(0, yPosition, windowRect.size.width, statusBarHeight);
    contentView = new CGView(CGRectMake(0, 0, windowRect.size.width, windowRect.size.height));
    
    
    toolpanel = new Toolpanel(statusBarRect);
    
    colorPalette = new ColorPalette(CGRectMake(0, yPosition, 200,100));
    colorPalette->shouldHandleMouseEvent = true;
    colorPalette->delegate = selectedColorDidChange;
    
    colorPalette->addColor(CGColorSimpleBlue());
    colorPalette->addColor(CGColorSimpleOrange());
    colorPalette->addColor(CGColorSimpleGreen());
    toolpanel->addSubview(colorPalette);

    contentView->addSubview(toolpanel);

    glutDisplayFunc(render);
    glutReshapeFunc(resize);
    glutMouseFunc(mouseHandler);
  //  glutKeyboardFunc(keyboardHandler);
  //  glutSpecialFunc(specialKeyboardHandler);
    
    //  Setup Menu
 
    
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