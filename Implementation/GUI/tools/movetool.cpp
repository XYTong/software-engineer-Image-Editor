#include "movetool.h"

bool MoveTool::initTool(toolParameters_t *param){
    offsetX = param->offsetX;
    offsetY = param->offsetY;
    delete param;
    param = nullptr;
    return true;
}

bool MoveTool::useTool(){
    pic->setCurrentXOffset(offsetX);
    pic->setCurrentYOffset(offsetY);

    return true;
}
