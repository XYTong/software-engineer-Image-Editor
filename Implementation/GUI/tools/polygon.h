#include "../Tool.h"

#ifndef POLYGON_H
#define POLYGON_H

class PolygonTool : public Tool{
    public:
        bool initTool(toolParameters_t *param);
        bool useTool();
        PolygonTool(Picture *pict) : Tool(pict){}
    private:
        QPolygon poly;
        bool isInverse;
        int colorIndex;
};

#endif // POLYGON_H
