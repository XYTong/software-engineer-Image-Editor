#include "Tool.h"

#ifndef MANIPULATION_TOOL_H
#define MANIPULATION_TOOL_H

class ManipulationTool{
    public:
        bool useTool(toolParameters_t *param);
        ManipulationTool(Picture *pic);
        ~ManipulationTool();

    private:
        Picture *pic;
};

#endif /* !MANIPULATION_TOOL_H */
