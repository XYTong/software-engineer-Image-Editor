#include "drawTool.h"
#include <qpainter.h>
#include <sys/time.h>
#include <stdio.h>


bool DrawTool::initTool(toolParameters_t *param){
    sPoint = param->startPoint-QPoint(pic->currentXOffset(),pic->currentYOffset());
    ePoint = param->endPoint-QPoint(pic->currentXOffset(),pic->currentYOffset());
    w = param->i;
    colorIndex = param->colorIndex;
    ignoreShape = param->ignoreShape;
    delete param;
    param = nullptr;
    return true;
}

bool DrawTool::useTool(){
    timeval t1;
    timeval t2;
    gettimeofday(&t1,nullptr);
    QImage *tempImage = new QImage(pic->getCurrentLayerAsQ()->width(), pic->getCurrentLayerAsQ()->height(), QImage::Format_ARGB32);
    tempImage->fill(QColor(0,0,0,0));
    QPainter painter(tempImage);
    QImage *qPic = pic->getCurrentLayer()->qImage;
    QColor white(255,255,255,255);
    QPen pen(white);
    pen.setWidth(w);
    painter.setPen(pen);
    painter.drawLine(sPoint, ePoint);
    QRgb whiteRgba = white.rgba();
    for(int i = 0; i < qPic->width(); i++){
        for(int j = 0; j < qPic->height(); j++){
            if (tempImage->pixel(i,j)==whiteRgba&&(!pic->isShaped()||qPic->pixelIndex(i,j)!=255||ignoreShape)){
                qPic->setPixel(QPoint(i,j),colorIndex);
            }
        }
    }
    painter.end();
    delete tempImage;
    gettimeofday(&t2,nullptr);
    printf("Draw: %ld usec\n",(t2.tv_sec-t1.tv_sec)*1000000+t2.tv_usec-t1.tv_usec);
    return true;
}
DrawTool::~DrawTool(){

}
