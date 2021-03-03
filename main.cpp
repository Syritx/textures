//
//  main.cpp
//  opengl-app
//
//  Created by Syritx on 2021-01-29.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include "shader.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "screen.h"
#include "map.h"

using namespace std;


int main() {
    
    if (!glfwInit()) glfwTerminate();
        
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
    
    GLFWwindow* window = glfwCreateWindow(1200, 800, "2030", NULL, NULL);
    if (!window) glfwTerminate();
    
    int panelWidth = 1100, panelHeight = 700;
    FrameSize f = pixelSizeToScreenSize(panelWidth, panelHeight, 1200, 800);
    cout << "w:" << f.w << " h:" << f.h << "\n";
    
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();
    
    glEnable(GL_DEPTH_TEST);
    start_map();
    
    std::ifstream input( "terrainFragmentShader.glsl" );
    for( std::string line; getline( input, line ); )
    {
        cout << line;
    }
            
    
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                
        render_map();
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    glfwTerminate();
}

