#include "RasterImage.h"

#include <QImage>
#include <string>
#include <vector>

#ifndef PICTURE_H
#define PICTURE_H

typedef struct layer_t {
    RasterImage *rImage;
    QImage *qImage;
} layer_t;

class Picture{
	public:
        void addLayer(RasterImage* rImage);
        void addLayer(QImage* qImage);
        void addLayer(layer_t* layer);
        void addLayer(size_t width, size_t height);
        void removeLayer(unsigned int index);
        RasterImage* getLayerAsR(unsigned int index);
        RasterImage* getCurrentLayerAsR();
        QImage* getLayerAsQ(unsigned int index);
        QImage* getCurrentLayerAsQ();
        layer_t* getLayer(unsigned int index);
        layer_t* getCurrentLayer();
        void addCurrentLayer(RasterImage *rImage);
        void addCurrentLayer(QImage *qImage);
        void addCurrentLayer(layer_t *layer);
        void setCurrentLayer(unsigned int index);
        Picture(std::string name = "Unbenannt");
        ~Picture();
	
    private:
        RasterImage* qtor(QImage *qImage);
        QImage* rtoq(RasterImage *rImage);
        std::string name;
        std::vector<layer_t*> layers;
        layer_t *currentLayer;
};

#endif /* !PICTURE_H */
