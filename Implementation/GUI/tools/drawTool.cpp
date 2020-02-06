#include "drawTool.h"
#include <qpainter.h>

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
    return true;
}
DrawTool::~DrawTool(){

}
