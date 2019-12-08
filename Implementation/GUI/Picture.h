#include "RasterImage.h"

#include <string>
#include <vector>

#ifndef PICTURE_H
#define PICTURE_H

class Picture{
	public:
        void addLayer(RasterImage layer);
        void addLayer(size_t width, size_t height);
        void removeLayer(unsigned int index);
        RasterImage getLayer(unsigned int index);
        RasterImage* getCurrentLayer();
        void addCurrentLayer(RasterImage *layer);
        void setCurrentLayer(unsigned int index);
        Picture(std::string name = "Unbenannt");
	
	private:
        void setCurrentLayer(RasterImage *layer);
        std::string name;
        std::vector<RasterImage> layers;
        RasterImage *currentLayer;
};

#endif /* !PICTURE_H */
