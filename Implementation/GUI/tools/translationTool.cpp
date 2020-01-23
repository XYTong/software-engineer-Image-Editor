#include "translationTool.h"
#include "stdio.h"

bool TranslationTool::initTool(toolParameters_t *param){
    mat = param->mat;
    colorVect = param->colorVect;
    isRot=param->isRot;
    delete param;
    param = nullptr;
    return true;
}

bool TranslationTool::useTool(){
    QImage *qPic = new QImage(pic->getCurrentLayerAsQ()->transformed(mat));
    //qPic->setColorTable(colorVect);
    bool shaped = pic->isShaped();
    int xOffset=pic->currentXOffset();
    int yOffset=pic->currentYOffset();
    if(shaped){
        colorVect[255]=QColor(255,255,255,0).rgba();
    }

    QImage *qPic2 = new QImage(qPic->convertToFormat(QImage::Format_Indexed8,colorVect));
    //qPic2->setColorTable(colorVect);
    if(isRot){
        QPolygon poly = mat.mapToPolygon(QRect(0,0,pic->getCurrentLayerAsQ()->width(),pic->getCurrentLayerAsQ()->height()));
        int x[4]={poly.point(0).x(),poly.point(1).x(),poly.point(2).x(),poly.point(3).x()};
        int y[4]={poly.point(0).y(),poly.point(1).y(),poly.point(2).y(),poly.point(3).y()};
        int xmin=x[0],ymin=y[0];
        for (int i = 1; i < 4; i++){
            if(x[i]<xmin){
                xmin=x[i];
            }
            if(y[i]<ymin){
                ymin=y[i];
            }
        }
        for (int i = 0; i < 4; i++){
            poly[i]=QPoint(x[i]-xmin,y[i]-ymin);
        }
        for (int i = 0; i < qPic2->width(); i++){
            for (int j = 0; j < qPic2->height(); j++){
                if (!poly.containsPoint(QPoint(i,j),Qt::FillRule::OddEvenFill)||qPic->pixelColor(i,j).alpha()==0){//TODO: nur sperrpixel sperren!
                    qPic2->setPixel(i,j,255);
                }
            }
        }
    }
    pic->addCurrentLayer(qPic2);
    pic->setCurrentXOffset(xOffset);
    pic->setCurrentYOffset(yOffset);
    if(isRot||shaped){
        pic->makeCurrentLayerShaped();
    }
    return true;
}
