#include "ManipulationTool.h"

#include "tools/newLayer.h"
#include "tools/drawTool.h"
#include "tools/translationTool.h"
#include "tools/merge.h"
#include "tools/polygon.h"
#include "tools/movetool.h"

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
    case translationTool:{
        TranslationTool tool = TranslationTool(pic);
        tool.initTool(param);
        tool.useTool();
        return true;
    }
    case merge:{
        MergeTool tool = MergeTool(pic);
        tool.initTool(param);
        tool.useTool();
        return true;
    }
    case polygon:{
        PolygonTool tool = PolygonTool(pic);
        tool.initTool(param);
        tool.useTool();
        return true;
    }
    case tools_e::move:{
        MoveTool tool = MoveTool(pic);
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
