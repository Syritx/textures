//
//  map.h
//  opengl-app
//
//  Created by Syritx on 2021-03-03.
//

#ifndef map_h
#define map_h
#include "screen.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int width = 1100, height = 700;

float vertices[] = {
   0.0f,  0.5f,  0.0f,
   0.5f, -0.5f,  0.0f,
  -0.5f, -0.5f,  0.0f
};

const char* vertexShaderSource =
"#version 330 core \n"
"layout (location = 0) in vec3 vp;"
"layout (location = 1) in vec2 aTexCoord;"
"out vec2 TexCoord;"
" "
"void main() {"
"  TexCoord = aTexCoord;"
"  gl_Position = vec4(vp, 1.0);"
"}";

const char* fragmentShaderSource =
"#version 330 core \n"
"out vec4 FragColor;"
"in vec2 TexCoord;"
"uniform sampler2D ourTexture;"
" "
"void main() {"
"  FragColor = texture(ourTexture, TexCoord) * vec4(0.0, 0.5, 0, 1.0);"
"}";

GLuint vao, vbo;

int iwidth, iheight, nrChannels;
unsigned char *data = stbi_load("map.jpg", &iwidth, &iheight, &nrChannels, 0);
unsigned int texture;

FrameSize map = pixelSizeToScreenSize(width, height, 1200, 800);
bool init = false;

float verts[] = {
    -map.w/2, -map.h/2, 0, 0.0f, 1.0f,
     map.w/2, -map.h/2, 0, 1.0f, 1.0f,
    -map.w/2,  map.h/2, 0, 0.0f, 0.0f,
    
     map.w/2,  map.h/2, 0, 1.0f, 0.0f,
     map.w/2, -map.h/2, 0, 1.0f, 1.0f,
    -map.w/2,  map.h/2, 0, 0.0f, 0.0f
};

void start_map() {
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iwidth, iheight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        cout << "failed to load image\n";
    }
    stbi_image_free(data);
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts)/sizeof(verts[0]) * sizeof(float), verts, GL_STATIC_DRAW);
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), NULL);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
}

void render_map() {
    Shader shader = Shader(vertexShaderSource, fragmentShaderSource);
    
    shader.use_shader();
    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glDrawArrays(GL_TRIANGLES, 0, sizeof(verts)/sizeof(verts[0])/3);
}



#endif /* map_h */
