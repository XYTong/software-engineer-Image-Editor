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
    //newPic->fill(QColor(0,0,0,0));
    //newPic->setColorTable(pic->getLayerAsQ(layerIndex1)->colorTable());
    QPainter painter(newPic);
    painter.drawImage(p2xa,p2ya,*pic->getLayerAsQ(layerIndex2));
    painter.drawImage(p1xa,p1ya,*pic->getLayerAsQ(layerIndex1));
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


    /*int width1;
    int height1;
    int width2;
    int height2;
    int w0=0;
    int h0=0;
    int w2=0;
    int h2=0;
    int w1=0;
    int h1=0;

    bool shaped = false;

    width1=pic->getLayerAsQ(layerIndex1)->width();
    height1=pic->getLayerAsQ(layerIndex1)->height();
    width2=pic->getLayerAsQ(layerIndex2)->width();
    height2=pic->getLayerAsQ(layerIndex2)->height();
    if (pic->xOffset(layerIndex1)>pic->xOffset(layerIndex2)){
        w0=pic->xOffset(layerIndex2);
        w2=pic->xOffset(layerIndex1);
    } else {
        w0=pic->xOffset(layerIndex1);
        w2=pic->xOffset(layerIndex2);
    }
    if (pic->yOffset(layerIndex1)>pic->yOffset(layerIndex2)){
        h0 = pic->yOffset(layerIndex2);
        h2 = pic->yOffset(layerIndex1);
    } else {
        h0 = pic->yOffset(layerIndex1);
        h2 = pic->yOffset(layerIndex2);
    }
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
    QImage *newPic = new QImage(w1+w2-w0,h1+h2-h0,QImage::Format_ARGB32);
    newPic->fill(QColor(0,0,0,0));
    //newPic->setColorTable(pic->getLayerAsQ(layerIndex1)->colorTable());
    QPainter painter(newPic);
    painter.drawImage(pic->xOffset(layerIndex2)-w0,pic->yOffset(layerIndex2)-h0,*pic->getLayerAsQ(layerIndex2));
    painter.drawImage(pic->xOffset(layerIndex1)-w0,pic->yOffset(layerIndex1)-h0,*pic->getLayerAsQ(layerIndex1));
    FloydSteiberg fs = FloydSteiberg();
    painter.end();
    QImage *newPic2 = fs.getIndexed(newPic,pic->getLayerAsQ(layerIndex1)->colorTable());
    /*if(width1>width2&&height1<height2){
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
    }*/
    /*int p1xa = pic->xOffset(layerIndex1)-w0;
    int p1xe = p1xa+width1;
    int p1ya = pic->yOffset(layerIndex1)-h0;
    int p1ye = p1ya+height1;
    int p2xa = pic->xOffset(layerIndex2)-w0;
    int p2xe = p2xa+width2;
    int p2ya = pic->yOffset(layerIndex2)-h0;
    int p2ye = p2ya+height2;
    QImage *p1 = pic->getLayerAsQ(layerIndex1);
    QImage *p2 = pic->getLayerAsQ(layerIndex2);
    bool s1=pic->isShaped(layerIndex1);
    bool s2=pic->isShaped(layerIndex2);
    QColor trans(0,0,0,0);
    for (int i = 0; i < w1+w2-w0; i++){
        for (int j = 0; j < h1+h2-h0; j++){
            /*if (newPic->pixelColor(i,j)==trans){
                newPic2->setPixel(i,j,255);
                shaped=true;
            }
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
    //shaped=true;
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
    pic->setCurrentXOffset(xOffset);
    pic->setCurrentYOffset(yOffset);
    if(shaped){
        pic->makeCurrentLayerShaped();
    }

    return true;
}
