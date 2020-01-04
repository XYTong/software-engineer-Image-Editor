#include "Picture.h"

#include <string>
#include <vector>
#include <stdlib.h>

void Picture::addLayer(layer_t *layer){
    layers.push_back(layer);
    return;
}
void Picture::addLayer(QImage *qImage){
    layer_t *layer = new layer_t;
    layer->qImage = qImage;
    addLayer(layer);
    return;
}
void Picture::addLayer(int width, int height){
    layer_t *layer = new layer_t;
    layer->qImage = new QImage(width,height, QImage::Format_Indexed8);
    addLayer(layer);
    return;
}
void Picture::removeLayer(unsigned int index){
    layers.erase(layers.begin()+index);
    return;
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
    setCurrentLayer(layers.size()-1);
    return;
}
void Picture::addCurrentLayer(QImage *layer){
    addLayer(layer);
    setCurrentLayer(layers.size()-1);
    return;
}
unsigned int Picture::getLayerCount(){
    return static_cast<unsigned int>(layers.size());
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
