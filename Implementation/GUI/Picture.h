#include <QImage>
#include <string>
#include <vector>

#ifndef PICTURE_H
#define PICTURE_H

typedef struct layer_t {
    QImage *qImage;
    bool isShaped;
    bool isVisible;
    int xOffset;
    int yOffset;
} layer_t;

/*!
 * \class Picture
 * \brief Koordiniert dei Layer eines Bildes, deren Größe, deren Offset, deren Sichtbarkeit. Kann Layer hinzufügen, löschen und tauschen. Kann sich einen Layer als aktiven Merken.
 */
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
        void makeShaped(unsigned int index);
        void makeCurrentLayerShaped();
        bool isShaped(unsigned int index);
        bool isShaped();
        void makeVisible(unsigned int index, bool visible);
        bool isVisible(unsigned int index);
        QSize getMaxSize();
        QSize getMinOffset();
        unsigned int getLayerCount();
        unsigned int getCurrentLayerIndex();
        int currentXOffset();
        int currentYOffset();
        int xOffset(unsigned int index);
        int yOffset(unsigned int index);
        void setCurrentXOffset(int offset);
        void setCurrentYOffset(int offset);
        void setXOffset(unsigned int index, int offset);
        void setYOffset(unsigned int index, int offset);
        void moveLayer(int i,int j);
        bool hasLayer();
        Picture(std::string name = "Unbenannt");
        ~Picture();
	
    private:
        std::string name;
        std::vector<layer_t*> layers;
        layer_t *currentLayer;
        int maxX;
        int maxY;
        int minX;
        int minY;
};

#endif /* !PICTURE_H */
