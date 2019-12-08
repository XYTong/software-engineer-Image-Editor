#include "RasterImage.h"

#include <stdlib.h>

bool RasterImage::changePixel(size_t x, size_t y, pixel_t pix){
    if (x > width || y > height){
        return false;
    }
    int index;
    if((index = colormap.getIndex(pix)) == -1){
        if((index = colormap.getIndex(pix)) == -1){
            return false;
        }
    }
    pixels[y][x] = static_cast<unsigned char>(index);
    return true;
}
pixel_t* RasterImage::getPixel(size_t x, size_t y){
    return colormap.getColor(pixels[y][x]);
}

RasterImage::RasterImage(size_t width, size_t height, pixel_t background){
    this->width = width;
    this->height = height;
    pixels = static_cast<unsigned char**>(malloc(height * sizeof(unsigned char*)));
    for(size_t i = 0; i < height; i++){
        pixels[i] = static_cast<unsigned char*>(calloc(width,sizeof(unsigned char)));
    }
    colormap = ColorMap();
    colormap.addColor(background);
}

RasterImage::RasterImage::~RasterImage(){
    for(size_t i = 0; i < height; i++){
        free(pixels[i]);
    }
    free(pixels);
}
