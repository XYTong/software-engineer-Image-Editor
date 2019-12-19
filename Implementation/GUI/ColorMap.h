#include "Pixel.h"

#ifndef COLORMAP_H
#define COLORMAP_H

class ColorMap{
	public:
        int addColor(pixel_t pix);
        bool removeColor(pixel_t pix);
        pixel_t* getColor(unsigned char index);
        int getIndex(pixel_t pix);
        ColorMap(bool lock = false);
        ~ColorMap();
	
    private:
        pixel_t *pixels[256];
        bool lockPixel;
};

#endif /* !COLORMAP_H */
