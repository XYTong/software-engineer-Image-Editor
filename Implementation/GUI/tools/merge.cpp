#include "merge.h"

bool MergeTool::initTool(toolParameters_t *param){
    layerIndex1 = param->layerIndex1;
    delete param;
    return true;
}

bool MergeTool::useTool(){


    return true;
}
