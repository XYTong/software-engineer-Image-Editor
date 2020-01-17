#include "merge.h"
#include "floydSteinberg.h"
#include <QPainter>

bool MergeTool::initTool(toolParameters_t *param){
    layerIndex1 = param->layerIndex1;
    layerIndex2 = param->layerIndex2;
    colorVect = param->colorVect;
    delete param;
    param = nullptr;
    return true;
}

bool MergeTool::useTool(){
    int width1;
    int height1;
    int width2;
    int height2;
    int w1=0;
    int h1=0;
    bool shaped = false;

    width1=pic->getLayerAsQ(layerIndex1)->width();
    height1=pic->getLayerAsQ(layerIndex1)->height();
    width2=pic->getLayerAsQ(layerIndex2)->width();
    height2=pic->getLayerAsQ(layerIndex2)->height();
    if (pic->isShaped(layerIndex1)){
        shaped= true;
    }
    if (width1>width2){
        w1=width1;
    } else {
        w1=width2;
    }
    if (height1>height2){
        h1 = height1;
    } else {
        h1 = height2;
    }
    //QImage tempImage = QImage(pic->getCurrentLayerAsQ()->width(), pic->getCurrentLayerAsQ()->height(), QImage::Format_ARGB32);
    //tempImage.fill(QColor(0,0,0,0));
    //QPainter painter(&tempImage);
    QImage *newPic = new QImage(w1,h1,QImage::Format_ARGB32);
    //newPic->setColorTable(pic->getLayerAsQ(layerIndex1)->colorTable());
    QPainter painter(newPic);
    painter.drawImage(0,0,*pic->getLayerAsQ(layerIndex2));
    painter.drawImage(0,0,*pic->getLayerAsQ(layerIndex1));
    FloydSteiberg fs = FloydSteiberg();
    painter.end();
    QImage *newPic2 = fs.getIndexed(newPic,pic->getLayerAsQ(layerIndex1)->colorTable());
    if(width1>width2&&height1<height2){
        for (int i = width2; i < w1; i++){
            for (int j = height1; j < h1; j++){
                newPic2->setPixel(i,j,255);
            }
        }
        shaped=true;
    }
    if(width1<width2&&height1>height2){
        for (int i = width1; i < w1; i++){
            for (int j = height2; j < h1; j++){
                newPic2->setPixel(i,j,255);
            }
        }
        shaped=true;
    }
    /*if(width1>width2){
        if(height1>height2){
            //newPic = new QImage(*pic->getLayerAsQ(layerIndex1));
            //newPic->setColorTable(colorVect);
            newPic = new QImage(width1,height2,QImage::Format_Indexed8);
            newPic->setColorTable(colorVect);
            for (int i = 0; i < width1; i++){
                for (int j = 0; j < height1; j++){
                    newPic->setPixel(i,j,pic->getLayerAsQ(layerIndex1)->pixelIndex(i,j));
                    if(pic->getLayerAsQ(layerIndex1)->pixelIndex(i,j)==255&&(i<=width2&&j<height2)){
                        newPic->setPixel(i,j,pic->getLayerAsQ(layerIndex2)->pixelIndex(i,j));
                    }
                }
            }
        } else {
            shaped=true;
            newPic = new QImage(width1,height2,QImage::Format_Indexed8);
            newPic->setColorTable(colorVect);
            for (int i = 0; i < width1; i++){
                for (int j = 0; j < height1; j++){
                    newPic->setPixel(i,j,pic->getLayerAsQ(layerIndex1)->pixelIndex(i,j));
                    if(pic->getLayerAsQ(layerIndex1)->pixelIndex(i,j)==255&&i<=width2){
                        newPic->setPixel(i,j,pic->getLayerAsQ(layerIndex2)->pixelIndex(i,j));
                    }
                }
                for (int j = height1; j < height2; j++){
                    newPic->setPixel(i,j,pic->getLayerAsQ(layerIndex2)->pixelIndex(i,j));
                    if (i>=width2){
                        newPic->setPixel(i,j,255);
                    }
                }
            }
        }
    } else {
        if(height1>height2){
            newPic = new QImage(width2,height1,QImage::Format_Indexed8);
            newPic->setColorTable(colorVect);
            shaped=true;
            for (int j = 0; j < height1; j++){
                for (int i = 0; i < width1; i++){
                    newPic->setPixel(i,j,pic->getLayerAsQ(layerIndex1)->pixelIndex(i,j));
                    if(pic->getLayerAsQ(layerIndex1)->pixelIndex(i,j)==255&&j<=height2){
                        newPic->setPixel(i,j,pic->getLayerAsQ(layerIndex2)->pixelIndex(i,j));
                    }
                }
                for (int i = width1; i < width2; i++){
                    newPic->setPixel(i,j,pic->getLayerAsQ(layerIndex2)->pixelIndex(i,j));
                    if (j>=height2){
                        newPic->setPixel(i,j,255);
                    }
                }

            }
        } else {
            newPic = new QImage(width2,height2,QImage::Format_Indexed8);
            newPic->setColorTable(colorVect);
            for (int i = 0; i < width2; i++){
                for (int j = 0; j < height2; j++){
                    if(i >=width1||j>=height1){
                        newPic->setPixel(i,j,pic->getLayerAsQ(layerIndex2)->pixelIndex(i,j));

                    } else {
                        newPic->setPixel(i,j,pic->getLayerAsQ(layerIndex1)->pixelIndex(i,j));
                        if(pic->getLayerAsQ(layerIndex1)->pixelIndex(i,j)==255){
                            newPic->setPixel(i,j,pic->getLayerAsQ(layerIndex2)->pixelIndex(i,j));
                        }
                    }
                }
            }
        }
    }*/
    //QImage *newPic2 = new QImage(newPic->convertToFormat(QImage::Format_Indexed8,colorVect));
    pic->addCurrentLayer(newPic2);
    if(shaped){
        pic->makeCurrentLayerShaped();
    }

    return true;
}
