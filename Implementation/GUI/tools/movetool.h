#include "../Tool.h"

#ifndef MOVETOOL_H
#define MOVETOOL_H


class MoveTool : public Tool{
    public:
        bool initTool(toolParameters_t *param);
        bool useTool();
        MoveTool(Picture *pict) : Tool(pict){}
    private:
        int offsetX;
        int offsetY;
};

#endif // MOVETOOL_H
