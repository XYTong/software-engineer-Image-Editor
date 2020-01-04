#include <QImage>
#include <string>
#include <vector>

#ifndef PICTURE_H
#define PICTURE_H

typedef struct layer_t {
    QImage *qImage;
} layer_t;

class Picture{
    public:
        void addLayer(QImage* qImage);
        void addLayer(layer_t* layer);
        void addLayer(int width, int height);
        void removeLayer(unsigned int index);
        QImage* getLayerAsQ(unsigned int index);
        QImage* getCurrentLayerAsQ();
        layer_t* getLayer(unsigned int index);
        layer_t* getCurrentLayer();
        void addCurrentLayer(QImage *qImage);
        void addCurrentLayer(layer_t *layer);
        void setCurrentLayer(unsigned int index);
        unsigned int getLayerCount();
        Picture(std::string name = "Unbenannt");
        ~Picture();
	
    private:
        std::string name;
        std::vector<layer_t*> layers;
        layer_t *currentLayer;
};

#endif /* !PICTURE_H */
