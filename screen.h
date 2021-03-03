//
//  screen.h
//  opengl-app
//
//  Created by Syritx on 2021-03-03.
//

#ifndef screen_h
#define screen_h

struct FrameSize {
    float w;
    float h;
};


struct FrameSize pixelSizeToScreenSize(int px, int py, int w, int h) {
    float width = (float)px/(float)w;
    float height = (float)py/(float)h;
    
    FrameSize frame;
    frame.w = width;
    frame.h = height;
    return frame;
}


#endif /* screen_h */
