#include "../Tool.h"

#ifndef TRANSLATIONTOOL_H
#define TRANSLATIONTOOL_H

class TranslationTool : public Tool{
    public:
        bool initTool(toolParameters_t *param);
        bool useTool();
        TranslationTool(Picture *pict) : Tool(pict){}
    private:
        QMatrix mat;
        QVector<QRgb> colorVect;
};

#endif // TRANSLATIONTOOL_H
