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
    int xOffset;
    int yOffset;
    if (pic->xOffset(layerIndex1)>pic->xOffset(layerIndex2)){
        xOffset=pic->xOffset(layerIndex2);
    } else {
        xOffset=pic->xOffset(layerIndex1);
    }
    if (pic->yOffset(layerIndex1)>pic->yOffset(layerIndex2)){
        yOffset = pic->yOffset(layerIndex2);
    } else {
        yOffset = pic->yOffset(layerIndex1);
    }
    int p1xa = pic->xOffset(layerIndex1)-xOffset;
    int p1xe = p1xa+pic->getLayerAsQ(layerIndex1)->width();
    int p1ya = pic->yOffset(layerIndex1)-yOffset;
    int p1ye = p1ya+pic->getLayerAsQ(layerIndex1)->height();
    int p2xa = pic->xOffset(layerIndex2)-xOffset;
    int p2xe = p2xa+pic->getLayerAsQ(layerIndex2)->width();
    int p2ya = pic->yOffset(layerIndex2)-yOffset;
    int p2ye = p2ya+pic->getLayerAsQ(layerIndex2)->height();
    int maxX;
    int maxY;
    if (p1xe>p2xe){
        maxX=p1xe;
    } else {
        maxX=p2xe;
    }
    if (p1ye>p2ye){
        maxY = p1ye;
    } else {
        maxY = p2ye;
    }
    bool s1=pic->isShaped(layerIndex1);
    bool s2=pic->isShaped(layerIndex2);
    bool shaped = false;
    QImage *p1 = pic->getLayerAsQ(layerIndex1);
    QImage *p2 = pic->getLayerAsQ(layerIndex2);
    QImage *newPic = new QImage(maxX,maxY,QImage::Format_ARGB32);
    QPainter painter(newPic);
    painter.drawImage(p1xa,p1ya,*pic->getLayerAsQ(layerIndex1));
    painter.drawImage(p2xa,p2ya,*pic->getLayerAsQ(layerIndex2));

    FloydSteiberg fs = FloydSteiberg();
    painter.end();
    QImage *newPic2 = fs.getIndexed(newPic,pic->getLayerAsQ(layerIndex1)->colorTable());
    for (int i = 0; i < maxX; i++){
        for (int j = 0; j < maxY; j++){
            if(i<p1xa||i>=p1xe||j<p1ya||j>=p1ye){
                if (i<p2xa||i>=p2xe||j<p2ya||j>=p2ye){
                    newPic2->setPixel(i,j,255);
                    shaped=true;
                } else {
                    if(s2&&p2->pixelIndex(i-p2xa,j-p2ya)==255){
                        newPic2->setPixel(i,j,255);
                        shaped=true;
                    }
                }

            } else {
                if(i<p2xa||i>=p2xe||j<p2ya||j>=p2ye){
                    if (s1&&p1->pixelIndex(i-p1xa,j-p1ya)==255){
                        newPic2->setPixel(i,j,255);
                        shaped=true;
                    }
                } else {
                    if (s1&&p1->pixelIndex(i-p1xa,j-p1ya)==255&&s2&&p2->pixelIndex(i-p2xa,j-p2ya)==255){
                        newPic2->setPixel(i,j,255);
                        shaped=true;
                    }
                }
            }
        }
    }
    pic->addCurrentLayer(newPic2);
    pic->setCurrentXOffset(xOffset);
    pic->setCurrentYOffset(yOffset);
    if(shaped){
        pic->makeCurrentLayerShaped();
    }

    return true;
}
