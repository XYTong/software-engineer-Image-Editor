#include "InteractionTool.h"

bool InteractionTool::useTool(toolParameters_t *param){
    return tools->useTool(param);
}

Picture *InteractionTool::getPicture(){
    return pic;
}

InteractionTool::InteractionTool(){
    pic = new Picture();
    tools = new ManipulationTool(pic);
}
