#include "../Tool.h"

#ifndef DRAWTOOL_H
#define DRAWTOOL_H

/*!
 * \class DrawTool
 * \brief Zum Zeichnen auf dem aktuellen Layer.
 */
class DrawTool : public Tool{
    public:
        bool initTool(toolParameters_t *param);
        bool useTool();
        DrawTool(Picture *pict) : Tool(pict){}
        ~DrawTool();
    private:
        QPoint sPoint;
        QPoint ePoint;
        int w;
        int colorIndex;
        bool ignoreShape;
};

#endif // DRAWTOOL_H
