#include "polygon.h"
#include <qpainter.h>
#include <sys/time.h>
#include <stdio.h>

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
    timeval t1;
    timeval t2;
    gettimeofday(&t1,nullptr);
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
    gettimeofday(&t2,nullptr);
    printf("Polygon: %ld usec\n",(t2.tv_sec-t1.tv_sec)*1000000+t2.tv_usec-t1.tv_usec);
    return true;
}
