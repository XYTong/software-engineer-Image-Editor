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
        NewLayer *tool = new NewLayer(pic);
        tool->initTool(param);
        tool->useTool();
        delete tool;
        return true;
    }
    case paint:{
        DrawTool *tool = new DrawTool(pic);
        tool->initTool(param);
        tool->useTool();
        delete tool;
        return true;
    }
    case translationTool:{
        TranslationTool *tool = new TranslationTool(pic);
        tool->initTool(param);
        tool->useTool();
        delete tool;
        return true;
    }
    case merge:{
        MergeTool *tool = new MergeTool(pic);
        tool->initTool(param);
        tool->useTool();
        delete tool;
        return true;
    }
    case polygon:{
        PolygonTool *tool = new PolygonTool(pic);
        tool->initTool(param);
        tool->useTool();
        delete tool;
        return true;
    }
    case tools_e::move:{
        MoveTool *tool = new MoveTool(pic);
        tool->initTool(param);
        tool->useTool();
        delete tool;
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
