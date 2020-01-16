#include "drawTool.h"
#include <qpainter.h>

bool DrawTool::initTool(toolParameters_t *param){
    sPoint = param->startPoint;
    ePoint = param->endPoint;
    w = param->i;
    colorIndex = param->colorIndex;
    delete param;
    param = nullptr;
    return true;
}

bool DrawTool::useTool(){
    //QPainter painter(pic->getCurrentLayerAsQ());
    QImage tempImage = QImage(pic->getCurrentLayerAsQ()->width(), pic->getCurrentLayerAsQ()->height(), QImage::Format_ARGB32);
    tempImage.fill(QColor(0,0,0,0));
    QPainter painter(&tempImage);
    QImage *qPic = pic->getCurrentLayer()->qImage;
    /*for(int i = -5; i <= 5; i++){
        for(int j = -5; j <= 5; j++){
            qPic->setPixel(point+QPoint(i,j),2);
        }
    }*/
    QPen pen(QColor(255,255,255,255));
    pen.setWidth(w);
    painter.setPen(pen);
    painter.drawLine(sPoint, ePoint);

    for(int i = 0; i < qPic->width(); i++){
        for(int j = 0; j < qPic->height(); j++){
            if (tempImage.pixelColor(QPoint(i,j))==QColor(255,255,255,255)&&(!pic->isShaped()||qPic->pixelIndex(i,j)!=255)){
                qPic->setPixel(QPoint(i,j),colorIndex);
            }
        }
    }

    return true;
}
