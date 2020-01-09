#include "../Tool.h"

#ifndef DRAWTOOL_H
#define DRAWTOOL_H

class DrawTool : public Tool{
    public:
        bool initTool(toolParameters_t *param);
        bool useTool();
        DrawTool(Picture *pict) : Tool(pict){}
    private:
        QPoint sPoint;
        QPoint ePoint;
        int w;
        int colorIndex;
};

#endif // DRAWTOOL_H
