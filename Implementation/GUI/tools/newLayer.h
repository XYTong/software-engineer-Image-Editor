#include "../Tool.h"

#ifndef NEWLAYER_H
#define NEWLAYER_H

class NewLayer : public Tool{
    public:
        bool initTool(toolParameters_t *param);
        bool useTool();
        NewLayer(Picture *pict) : Tool(pict){}
        ~NewLayer();
    private:
        QImage *qPic;
        QVector<QRgb> colorVect;
};

#endif // NEWLAYER_H
