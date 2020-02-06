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
    FloydSteiberg fs = FloydSteiberg();
    QImage *qPic2 = fs.getIndexed(qPic,colorVect);
    delete qPic;
    pic->addCurrentLayer(qPic2);
    return true;
}
NewLayer::~NewLayer(){

}
