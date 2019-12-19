#include "newLayer.h"

bool NewLayer::initTool(toolParameters_t *param){
    qPic = param->pic;
    delete param;
    return true;
}

bool NewLayer::useTool(){
    //qPic->convertTo(QImage::Format_Indexed8,Qt::OrderedAlphaDither);
    //qPic->convertTo(QImage::Format_ARGB32,Qt::OrderedAlphaDither);
    QVector<QRgb> qVec;
    for(int i = 0; i < 156; i++){
        qVec.append(QColor(0,0,0,0).rgba());
    }

    qVec[0]=QColor(0,0,0,255).rgba();
    qVec[1]=QColor(255,0,0,255).rgba();
    qVec[2]=QColor(0,255,0,255).rgba();
    qVec[3]=QColor(0,0,255,255).rgba();
    qVec[4]=QColor(255,255,0,255).rgba();
    qVec[5]=QColor(255,0,255,255).rgba();
    qVec[6]=QColor(0,255,255,255).rgba();
    qVec[7]=QColor(255,255,255,255).rgba();

    *qPic = qPic->convertToFormat(QImage::Format_Indexed8, qVec, Qt::PreferDither);


    pic->addCurrentLayer(qPic);
    return true;
}
