#include "polygon.h"
#include <qpainter.h>

bool PolygonTool::initTool(toolParameters_t *param){
    poly = param->poly;
    colorIndex = param->colorIndex;
    isInverse = param->isInverse;
    ignoreShape = param->ignoreShape;
    delete param;
    param = nullptr;
    return true;
}

bool PolygonTool::useTool(){
    QImage tempImage = QImage(pic->getCurrentLayerAsQ()->width(), pic->getCurrentLayerAsQ()->height(), QImage::Format_ARGB32);
    tempImage.fill(QColor(0,0,0,0));
    QPainter painter(&tempImage);
    QImage *qPic = pic->getCurrentLayer()->qImage;
    QBrush pen(QColor(255,255,255,255));
    painter.setBrush(pen);
    painter.drawPolygon(poly);
    QPainterPath path;
    path.addPolygon(poly);
    painter.fillPath(path,pen);

    for(int i = 0; i < qPic->width(); i++){
        for(int j = 0; j < qPic->height(); j++){
            if (!pic->isShaped()||qPic->pixelIndex(i,j)!=255||ignoreShape){
                if (tempImage.pixelColor(QPoint(i,j))==QColor(255,255,255,255)&&!isInverse){
                    qPic->setPixel(QPoint(i,j),colorIndex);
                }
                if (tempImage.pixelColor(QPoint(i,j))!=QColor(255,255,255,255)&&isInverse){
                    qPic->setPixel(QPoint(i,j),colorIndex);
                }
            }

        }
    }

    return true;
}
