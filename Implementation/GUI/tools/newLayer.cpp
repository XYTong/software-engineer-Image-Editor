#include "newLayer.h"

#include "floydSteinberg.h"


bool NewLayer::initTool(toolParameters_t *param){
    qPic = param->pic;
    colorVect = param->colorVect;
    delete param;
    param = nullptr;
    return true;
}

bool NewLayer::useTool(){
    //qPic->convertTo(QImage::Format_Indexed8,Qt::OrderedAlphaDither);
    //qPic->convertTo(QImage::Format_ARGB32,Qt::OrderedAlphaDither);

    //*qPic = qPic->convertToFormat(QImage::Format_Indexed8, colorVect, Qt::PreferDither);
    FloydSteiberg fs = FloydSteiberg();
    QImage *qPic2 = fs.getIndexed(qPic,colorVect);
    delete qPic;
    pic->addCurrentLayer(qPic2);
    return true;
}
