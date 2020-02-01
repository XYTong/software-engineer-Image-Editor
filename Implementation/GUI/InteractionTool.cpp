#include "InteractionTool.h"

bool InteractionTool::useTool(toolParameters_t *param){
    return tools->useTool(param);
}

Picture *InteractionTool::getPicture(){
    return pic;
}

//bool InteractionTool::hasPic(){
//    return (pic!=nullptr&&pic->hasLayer());
//}

InteractionTool::InteractionTool(){
    pic = new Picture();
    tools = new ManipulationTool(pic);
}
