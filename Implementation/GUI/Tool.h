#include <QImage>

#include "Picture.h"

#ifndef TOOL_H
#define TOOL_H

typedef enum tools {paint, newLayer, translationTool, merge} tools_e;

#define TOOL_ANZ 9

typedef struct toolParameters {
    tools_e tool;
    QMatrix mat;
    int i;
    int colorIndex;
    int layerIndex1;
    int layerIndex2;
    QImage *pic;
    QPoint startPoint;
    QPoint endPoint;
    QVector<QRgb> colorVect;
} toolParameters_t;


class Tool{
	public:
        bool useTool(){return false;}
        bool initTool(toolParameters_t *param){return false;}
        Tool(Picture *pic){this->pic = pic;}

    protected:
        Picture *pic;
};

#endif /* !TOOL_H */
