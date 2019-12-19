#include "ManipulationTool.h"

#include "tools/newLayer.h"
#include "tools/drawTool.h"

#include <stdlib.h>

bool ManipulationTool::useTool(toolParameters_t *param){
    switch (param->tool) {
    case newLayer:{
        NewLayer tool = NewLayer(pic);
        tool.initTool(param);
        tool.useTool();
        return true;
    }
    case paint:{
        DrawTool tool = DrawTool(pic);
        tool.initTool(param);
        tool.useTool();
        return true;
    }
    default:{
        return false;
    }
    }
}
ManipulationTool::ManipulationTool(Picture *pic){
    this->pic = pic;
}
ManipulationTool::~ManipulationTool(){

}
