#include "drawTool.h"

bool DrawTool::initTool(toolParameters_t *param){
    point = param->point;
    delete param;
    return true;
}

bool DrawTool::useTool(){
    pic->getCurrentLayer()->qImage->setPixel(point,QColor(255,255,255,255).rgba());
    return true;
}
