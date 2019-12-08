#include "ColorMap.h"

#include <stdlib.h>

#ifndef RASTER_IMAGE_H
#define RASTER_IMAGE_H

class RasterImage{
    public:
        bool changePixel(size_t x, size_t y, pixel_t pix);
        pixel_t* getPixel(size_t x, size_t y);
        RasterImage(size_t width, size_t height, pixel_t background = DEFAULTCOLOR);
        ~RasterImage();
		
	private:
        size_t width;
        size_t height;
        unsigned char** pixels;
        ColorMap colormap;
};

#endif /* !RASTER_IMAGE_H */
