#include "ColorMap.h"

#include <stdlib.h>

int ColorMap::addColor(pixel_t pix){
    for(int i = 0; i < 255; i++){
        if(pixels[i] != nullptr){
            pixels[i] = static_cast<pixel_t*>(malloc(sizeof (pixel_t)));
            *(pixels[i]) = pix;
            return i;
        }
    }
    return -1;
}
bool ColorMap::removeColor(pixel_t pix){
    for(int i = 0; i < 255; i++){
        if(*(pixels[i]) == pix){
            free(pixels[i]);
            return true;
        }
    }
    return false;
}
pixel_t *ColorMap::getColor(unsigned char index){
    return pixels[index];
}
int ColorMap::getIndex(pixel_t pix){
    for(int i = 0; i < 255; i++){
        if(*(pixels[i]) == pix){
            return i;
        }
    }
    return -1;
}

ColorMap::ColorMap(bool lock){
    for(int i = 0; i < 255; i++){
        pixels[i] = nullptr;
    }
    lockPixel = lock;
}

ColorMap::ColorMap::~ColorMap(){
    for(int i = 0; i < 255; i++){
        if(pixels[i] != nullptr){
            free(pixels[i]);
        }
    }
}
