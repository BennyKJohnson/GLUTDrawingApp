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

using namespace std;

struct Color {
    std::string name;
    CGColor color;
    Color(std::string colorName, CGColor colour) {
        name = colorName;
        color = colour;
    }
};

int mainWindow;
Toolbar *toolbar;
Toolpanel *shapePanel;
ColorPalette *colorPalette;
CGView *contentView;
Canvas *canvas;
std::vector<Color> colors;

enum ContextMenu {
    Clear,
    Exit
};



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
 
    setOGLProjection(width, height);
}




void render(void){
    
    // Set background color to white and opaque
    CGColor backgroundColor = CGColorDarkGray();
    glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    
    // Clear the buffer
    glClear(GL_COLOR_BUFFER_BIT);
    
    contentView->draw();
  
    glFlush();
    
}
void contextMenuHandler(int value) {
    
    ContextMenu option = static_cast<ContextMenu>(value);
    switch (option) {
        case Clear:
            canvas->clear();
            windowShouldRedraw();
            break;
        case Exit:
            exit(0);
    }
}

void lineWidthMenuHandler(int value) {
    canvas->lineWidth = value;
}

void colorMenuHandler(int value) {
    colorPalette->selectColorAtIndex(value);
}

void didChangePointSize(int value) {
    canvas->pointSize = value;

}

void addColor(Color color) {
    colors.push_back(color);
}

void createContextMenu() {

    int colorMenu = glutCreateMenu(colorMenuHandler);
    // Create Color Menu
    for (int i = 0; i < colors.size(); i++) {
        glutAddMenuEntry(colors[i].name.c_str(), i);
    }
    
    int lineWidthMenu = glutCreateMenu(lineWidthMenuHandler);
    glutAddMenuEntry("1", 1);
    glutAddMenuEntry("2", 2);
    glutAddMenuEntry("3", 3);
    glutAddMenuEntry("4", 4);
    glutAddMenuEntry("5", 5);

    int pointSizeMenu = glutCreateMenu(didChangePointSize);
    glutAddMenuEntry("1", 1);
    glutAddMenuEntry("2", 2);
    glutAddMenuEntry("4", 4);
    glutAddMenuEntry("8", 8);
    glutAddMenuEntry("16", 16);
    
    glutCreateMenu(contextMenuHandler);
    glutAddSubMenu("Colors", colorMenu);
    glutAddSubMenu("Line width", lineWidthMenu);
    glutAddSubMenu("Point Size", pointSizeMenu);

    glutAddMenuEntry("Clear", ContextMenu::Clear);
    glutAddMenuEntry("Exit", ContextMenu::Exit);

    // Set the menu to right click
    glutAttachMenu(GLUT_RIGHT_BUTTON);

}


// Called by the color palette when user selects a different color
void selectedColorDidChange(CGColor color) {
    std::cout << "Color did change" << std::endl;
    canvas->color = color;
    windowShouldRedraw();
    
}

// Canvas notifies when user have selected a color using color picker
void canvasDidPickCustomColor(CGColor color) {
    std::cout << "Canvas Picked custom color" << endl;
    colorPalette->setCustomColor(color);
}

// Toolpanel notifies when a button was selected by user, this event is handle here
void selectedShapeToolDidChange(Toolpanel *toolPanel,int index, CGButton *button) {
    std::cout << "Selected Shape Tool changed " << index << endl;
    if (index < 10) {
        // Notify the canvas about selected drawing tool
        DrawingTool selectedTool = static_cast<DrawingTool>(index);
        canvas->setDrawingTool(selectedTool);
    } else if (index == 10) {
        // Clear canvas
        canvas->clear();
    } else if(index == 11) {
        // Exit Program
        exit(0);
    }
  
}

// Setup available colors for the user to select from with provided labels
void setupColors() {
    colors.push_back(Color("Blue", CGColorSimpleBlue()));
    colors.push_back(Color("Orange", CGColorSimpleOrange()));
    colors.push_back(Color("Yellow", CGColorSimpleYellow()));
    colors.push_back(Color("Green", CGColorSimpleGreen()));
    colors.push_back(Color("Cyan", CGColorSimpleCyan()));
    colors.push_back(Color("Pink", CGColorSimpleRed()));
    colors.push_back(Color("Red", CGColorRed()));
    colors.push_back(Color("Custom Color", CGColorDarkGray()));
}

void initOpenGL() {
    setupColors();
    
    CGRect windowRect = getWindowRect();
    int statusBarHeight = 100;
    float yPosition = windowRect.size.height - statusBarHeight;
    CGRect statusBarRect = CGRectMake(0, yPosition, windowRect.size.width, statusBarHeight);
    contentView = new CGView(CGRectMake(0, 0, windowRect.size.width, windowRect.size.height));
    toolbar = new Toolbar(statusBarRect);
    
    colorPalette = new ColorPalette(CGRectMake(0, yPosition, 200,100));
    colorPalette->shouldHandleMouseEvent = true;
    colorPalette->delegate = selectedColorDidChange;

    for (int i = 0; i < colors.size(); i++) {
        colorPalette->addColor(colors[i].color);
    }

    
    // ToolPalette
    Toolpanel *toolPanel = new Toolpanel(CGRectMake(200, yPosition, 400, 100));
    toolPanel->backgroundColor = CGColorMakeWithRGB(60, 60, 60);
    toolPanel->action = selectedShapeToolDidChange;
    
    CGColor toolPanelColor = CGColorMakeWithRGB(60, 60, 60);
    int buttonSize = 35;
    CGRect buttonRect = CGRectMake(0, 0, buttonSize, buttonSize);
    
    // Create Tool Buttons
    CGButton *pointButton = new CGButton(buttonRect);
    pointButton->backgroundColor = toolPanelColor;
    pointButton->icon = ShapeIconPoint;
    
    CGButton *lineButton = new CGButton(buttonRect);
    lineButton->backgroundColor = toolPanelColor;
    lineButton->icon = ShapeIconLine;
    
    CGButton *triangleLineButton = new CGButton(buttonRect);
    triangleLineButton->backgroundColor = toolPanelColor;
    triangleLineButton->icon = ShapeIconTriangle;
    
    CGButton *triangleButton = new CGButton(buttonRect);
    triangleButton->backgroundColor = toolPanelColor;
    triangleButton->icon = ShapeIconTriangleFilled;
    
    CGButton *rectangleButton = new CGButton(buttonRect);
    rectangleButton->backgroundColor = toolPanelColor;
    rectangleButton->icon = ShapeIconRectangle;
    
    CGButton *rectangleFilledButton = new CGButton(buttonRect);
    rectangleFilledButton->backgroundColor = toolPanelColor;
    rectangleFilledButton->icon = ShapeIconRectangleFilled;
    
    CGButton *circleButton = new CGButton(buttonRect);
    circleButton->backgroundColor = toolPanelColor;
    circleButton->icon = ShapeIconCircle;
    
    CGButton *circleFilledButton = new CGButton(buttonRect);
    circleFilledButton->backgroundColor = toolPanelColor;
    circleFilledButton->icon = ShapeIconCircleFilled;

    CGButton *colorPickerButton = new CGButton(CGRectMake(0, 0, 80, buttonSize));
    colorPickerButton->title = new std::string("PICKER");
    colorPickerButton->backgroundColor = CGColorSimpleBlue();
    
    CGButton *fillButton = new CGButton(CGRectMake(0, 0, 80, buttonSize));
    fillButton->title = new std::string("FILL");
    fillButton->backgroundColor = CGColorSimpleCyan();
    
    CGButton *clearButton = new CGButton(CGRectMake(0, 0, 80, buttonSize));
    clearButton->title = new std::string("CLEAR");
    clearButton->type = ButtonTypeDark;
    clearButton->backgroundColor = CGColorSimpleBlue();
    
    CGButton *exitButton = new CGButton(CGRectMake(0, 0, 80, buttonSize));
    exitButton->title = new std::string("EXIT");
    exitButton->type = ButtonTypeDark;
    exitButton->backgroundColor = CGColorSimpleGreen();
    
    toolPanel->addButton(pointButton);
    toolPanel->addButton(lineButton);
    toolPanel->addButton(triangleLineButton);
    toolPanel->addButton(triangleButton);
    toolPanel->addButton(rectangleButton);
    toolPanel->addButton(rectangleFilledButton);
    toolPanel->addButton(circleButton);
    toolPanel->addButton(circleFilledButton);
    toolPanel->addButton(colorPickerButton);
    toolPanel->addButton(fillButton);
    
    toolPanel->addButton(clearButton);
    toolPanel->addButton(exitButton);
    
    toolbar->addSubview(colorPalette);
    toolbar->addSubview(toolPanel);

    canvas = new Canvas(CGRectMake(0, 0, windowRect.size.width, windowRect.size.height - 100));
    canvas->backgroundColor = CGColorWhite();
    canvas->colorDelegate = canvasDidPickCustomColor;
    
    // Add Views
    contentView->addSubview(canvas);
    contentView->addSubview(toolbar);

    glutDisplayFunc(render);
    glutReshapeFunc(resize);
    glutMouseFunc(mouseHandler);
    createContextMenu();
    
    // Set Default Color
    colorPalette->selectColorAtIndex(0);
    // Set Default Drawing Tool
    toolPanel->setSelectedButtonAtIndex(0);

    
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