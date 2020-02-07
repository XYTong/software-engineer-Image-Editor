#include "../Tool.h"

#ifndef MERGE_H
#define MERGE_H
/*!
 * \class MergeTool
 * \brief Vereinigt zwei Layer zu einem neuen. Dieser wird zum Bild als aktiver Layer hinzugefügt und die alten beiden gelöscht.
 */
class MergeTool : public Tool{
    public:
        bool initTool(toolParameters_t *param);
        bool useTool();
        MergeTool(Picture *pict) : Tool(pict){}
    private:
        int layerIndex1;
        int layerIndex2;
        QVector<QRgb> colorVect;
};

#endif // MERGE_H
