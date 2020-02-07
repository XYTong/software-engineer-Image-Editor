#include "Picture.h"

#include <string>
#include <vector>
#include <stdlib.h>

void Picture::addLayer(layer_t *layer){
    layers.push_back(layer);
    if(maxX<layer->qImage->size().width()+layer->xOffset){
        maxX=layer->qImage->size().width()+layer->xOffset;
    }
    if(maxY<layer->qImage->size().height()+layer->yOffset){
        maxY=layer->qImage->size().height()+layer->yOffset;
    }
    if(minX>layer->xOffset||minX==-1){
        minX=layer->xOffset;
    }
    if(minY>layer->yOffset||minY==-1){
        minY=layer->yOffset;
    }
    return;
}
void Picture::addLayer(QImage *qImage){
    layer_t *layer = new layer_t;
    layer->qImage = qImage;
    layer->isShaped = false;
    layer->isVisible = true;
    layer->xOffset = 0;
    layer->yOffset = 0;
    if(maxX<qImage->size().width()){
        maxX=qImage->size().width();
    }
    if(maxY<qImage->size().height()){
        maxY=qImage->size().height();
    }
    minX=0;
    minY=0;
    addLayer(layer);
    return;
}
void Picture::addLayer(int width, int height){
    layer_t *layer = new layer_t;
    layer->qImage = new QImage(width,height, QImage::Format_Indexed8);
    layer->isShaped =false;
    layer->isVisible = true;
    layer->xOffset = 0;
    layer->yOffset = 0;
    if(maxX<width){
        maxX=width;
    }
    if(maxY<height){
        maxY=height;
    }
    minX=0;
    minY=0;
    addLayer(layer);
    return;
}
void Picture::removeLayer(unsigned int index){
    if (layers[index]==currentLayer){
        currentLayer=nullptr;
    }
    layers.erase(layers.begin()+index);
    maxX=0;
    maxY=0;
    minX=-1;
    minY=-1;
    for (int i = 0; i < layers.size(); i++){
        if(maxX<layers[i]->qImage->size().width()+layers[i]->xOffset){
            maxX=layers[i]->qImage->size().width()+layers[i]->xOffset;
        }
        if(maxY<layers[i]->qImage->size().height()+layers[i]->yOffset){
            maxY=layers[i]->qImage->size().height()+layers[i]->yOffset;
        }
        if(minX>layers[i]->xOffset||minX==-1){
            minX=layers[i]->xOffset;
        }
        if(minY>layers[i]->yOffset||minY==-1){
            minY=layers[i]->yOffset;
        }
    }
    return;
}
QImage* Picture::getLayerAsQ(unsigned int index){
    if (currentLayer==nullptr){
        return nullptr;
    }
    return layers[index]->qImage;
}
void Picture::moveLayer(int i, int j){
    layer_t *layer = layers[i];
    layers[i] = layers[j];
    layers[j] = layer;
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
    currentLayer->isVisible=true;
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
unsigned int Picture::getCurrentLayerIndex(){
    unsigned int i;
    for (i = 0; i < layers.size(); i++){
        if (layers[i]==currentLayer){
            return i;
        }
    }
    return 0;
}
void Picture::makeShaped(unsigned int index){
    layers[index]->isShaped=true;
    return;
}
void Picture::makeCurrentLayerShaped(){
    currentLayer->isShaped = true;
    return;
}
bool Picture::isShaped(unsigned int index){
    return layers[index]->isShaped;
}
bool Picture::isShaped(){
    if (currentLayer==nullptr){
        return false;
    }
    return currentLayer->isShaped;
}
void Picture::makeVisible(unsigned int index, bool visible){
    layers[index]->isVisible=visible;
    return;
}
bool Picture::isVisible(unsigned int index){
    return layers[index]->isVisible;
}
QSize Picture::getMaxSize(){
    return QSize(maxX,maxY);
}
QSize Picture::getMinOffset(){
    return QSize(minX,minY);
}
int Picture::currentXOffset(){
    return currentLayer->xOffset;
}
int Picture::currentYOffset(){
    return currentLayer->yOffset;
}
int Picture::xOffset(unsigned int index){
    return layers[index]->xOffset;
}
int Picture::yOffset(unsigned int index){
    return layers[index]->yOffset;
}
void Picture::setCurrentXOffset(int offset){
    currentLayer->xOffset+=offset;
    maxX=0;
    minX=-1;
    for (int i = 0; i < layers.size(); i++){
        if(maxX<layers[i]->qImage->size().width()+layers[i]->xOffset){
            maxX=layers[i]->qImage->size().width()+layers[i]->xOffset;
        }
        if(minX>layers[i]->xOffset||minX==-1){
            minX=layers[i]->xOffset;
        }
    }
    return;
}
void Picture::setCurrentYOffset(int offset){
    currentLayer->yOffset+=offset;
    maxY=0;
    minY=-1;
    for (int i = 0; i < layers.size(); i++){
        if(maxY<layers[i]->qImage->size().height()+layers[i]->yOffset){
            maxY=layers[i]->qImage->size().height()+layers[i]->yOffset;
        }
        if(minY>layers[i]->yOffset||minY==-1){
            minY=layers[i]->yOffset;
        }
    }
    return;
}
void Picture::setXOffset(unsigned int index, int offset){
    layers[index]->xOffset+=offset;
    maxX=0;
    minX=-1;
    for (int i = 0; i < layers.size(); i++){
        if(maxX<layers[i]->qImage->size().width()+layers[i]->xOffset){
            maxX=layers[i]->qImage->size().width()+layers[i]->xOffset;
        }
        if(minX>layers[i]->xOffset||minX==-1){
            minX=layers[i]->xOffset;
        }
    }
    return;
}
void Picture::setYOffset(unsigned int index, int offset){
    layers[index]->yOffset+=offset;
    maxY=0;
    minY=-1;
    for (int i = 0; i < layers.size(); i++){
        if(maxY<layers[i]->qImage->size().height()+layers[i]->yOffset){
            maxY=layers[i]->qImage->size().height()+layers[i]->yOffset;
        }
        if(minY>layers[i]->yOffset||minY==-1){
            minY=layers[i]->yOffset;
        }
    }
    return;
}
bool Picture::hasLayer(){
    return (layers.size()!=0);
}
Picture::Picture(std::string name){
    this->name = name;
    currentLayer = nullptr;
    layers = std::vector<layer_t*>();
    maxX=0;
    maxY=0;
    minX=-1;
    minY=-1;
}
Picture::~Picture(){
   for (unsigned int i = 0; i < layers.size(); i++){
       delete layers[i];
   }
}

