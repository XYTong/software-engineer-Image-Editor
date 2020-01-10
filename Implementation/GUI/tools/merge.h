#include "../Tool.h"

#ifndef MERGE_H
#define MERGE_H

class MergeTool : public Tool{
    public:
        bool initTool(toolParameters_t *param);
        bool useTool();
        MergeTool(Picture *pict) : Tool(pict){}
    private:
        int layerIndex1;
};

#endif // MERGE_H
