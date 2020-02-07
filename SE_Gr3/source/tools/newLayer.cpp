#include "newLayer.h"
#include <sys/time.h>
#include <stdio.h>

#include "floydSteinberg.h"


bool NewLayer::initTool(toolParameters_t *param){
    qPic = param->pic;
    colorVect = param->colorVect;
    delete param;
    param = nullptr;
    return true;
}

bool NewLayer::useTool(){
    timeval t1;
    timeval t2;
    gettimeofday(&t1,nullptr);
    FloydSteiberg fs = FloydSteiberg();
    QImage *qPic2 = fs.getIndexed(qPic,colorVect);
    delete qPic;
    pic->addCurrentLayer(qPic2);
    gettimeofday(&t2,nullptr);
    printf("New layer: %ld usec\n",(t2.tv_sec-t1.tv_sec)*1000000+t2.tv_usec-t1.tv_usec);
    return true;
}
NewLayer::~NewLayer(){

}
