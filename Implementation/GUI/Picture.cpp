#include "Picture.h"

#include <string>
#include <vector>

void Picture::addLayer(RasterImage layer){
    layers.push_back(layer);
    return;
}
void Picture::addLayer(size_t width, size_t height){
    layers.push_back(RasterImage(width, height));
    return;
}
void Picture::removeLayer(unsigned int index){
    layers.erase(layers.begin()+index);
    return;
}
RasterImage Picture::getLayer(unsigned int index){
    return layers[index];
}
RasterImage *Picture::getCurrentLayer(){
    return currentLayer;
}
void Picture::setCurrentLayer(RasterImage *layer){
    currentLayer = layer;
    return;
}
void Picture::addCurrentLayer(RasterImage *layer){
    addLayer(*layer);
    setCurrentLayer(layer);
    return;
}
void Picture::setCurrentLayer(unsigned int index){
    RasterImage layer = getLayer(index);
    currentLayer = &layer;
    return;
}

Picture::Picture(std::string name){
    this->name = name;
    currentLayer = nullptr;
    layers = std::vector<RasterImage>();
}
