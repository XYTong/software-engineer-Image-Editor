#include "Picture.h"

#include <string>
#include <vector>
#include <stdlib.h>

void Picture::addLayer(layer_t *layer){
    layers.push_back(layer);
    return;
}
void Picture::addLayer(RasterImage *rImage){
    layer_t *layer = new layer_t;
    layer->rImage = rImage;
    layer->qImage = rtoq(rImage);
    addLayer(layer);
    return;
}
void Picture::addLayer(QImage *qImage){
    layer_t *layer = new layer_t;
    layer->qImage = qImage;
    layer->rImage = qtor(qImage);
    addLayer(layer);
    return;
}
void Picture::addLayer(size_t width, size_t height){
    layer_t *layer = new layer_t;
    layer->rImage = new RasterImage(width,height);
    layer->qImage = rtoq(layer->rImage);
    addLayer(layer);
    return;
}
void Picture::removeLayer(unsigned int index){
    layers.erase(layers.begin()+index);
    return;
}
RasterImage* Picture::getLayerAsR(unsigned int index){
    return layers[index]->rImage;
}
RasterImage* Picture::getCurrentLayerAsR(){
    if (currentLayer==nullptr){
        return nullptr;
    }
    return currentLayer->rImage;
}
QImage* Picture::getLayerAsQ(unsigned int index){
    if (currentLayer==nullptr){
        return nullptr;
    }
    return layers[index]->qImage;
}
QImage* Picture::getCurrentLayerAsQ(){
    if (currentLayer==nullptr){
        return nullptr;
    }
    return currentLayer->qImage;
}
layer_t* Picture::getLayer(unsigned int index){
    return layers[index];
}
layer_t* Picture::getCurrentLayer(){
    if (currentLayer==nullptr){
        return nullptr;
    }
    return currentLayer;
}
void Picture::setCurrentLayer(unsigned int index){
    currentLayer = getLayer(index);
    return;
}
void Picture::addCurrentLayer(layer_t *layer){
    addLayer(layer);
    setCurrentLayer(0);
    return;
}
void Picture::addCurrentLayer(QImage *layer){
    addLayer(layer);
    setCurrentLayer(0);
    return;
}
void Picture::addCurrentLayer(RasterImage *layer){
    addLayer(layer);
    setCurrentLayer(0);
    return;
}
RasterImage* Picture::qtor(QImage *qImage){
    RasterImage *rImage = new RasterImage(static_cast<size_t>(qImage->width()), static_cast<size_t>(qImage->height()));

    //TODO

    return rImage;
}
QImage* Picture::rtoq(RasterImage *rImage){
    QImage *qImage = new QImage(static_cast<int>(rImage->getWidth()), static_cast<int>(rImage->getHeight()),QImage::Format_ARGB32);

    //TODO

    return qImage;
}
Picture::Picture(std::string name){
    this->name = name;
    currentLayer = nullptr;
    layers = std::vector<layer_t*>();
}
Picture::~Picture(){
   for (unsigned int i = 0; i < layers.size(); i++){
       delete layers[i];
   }
}
