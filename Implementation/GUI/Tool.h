#include <QImage>

#include "Picture.h"

#ifndef TOOL_H
#define TOOL_H

typedef enum tools {resize, rotate, changeResolution, paint, light, contrast, color, newPicture, newLayer} tools_e;

#define TOOL_ANZ 9

typedef struct toolParameters {
    tools_e tool;
    int i;
    int colorIndex;
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
