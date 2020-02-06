#ifndef NEWLAYERDOCK_H
#define NEWLAYERDOCK_H
#include "InteractionTool.h"
#include <QGridLayout>
#include <QRadioButton>
#include <QPushButton>
#include <QSpinBox>
#include <QSlider>
#include <QDockWidget>
#include <QAction>
#include <QLabel>
#include <QButtonGroup>
#include <QColorDialog>
#include <QMenu>
#include <QPainter>


class NewLayerDock : public QObject
{
    Q_OBJECT
public:
    NewLayerDock(InteractionTool *interaction);
    ~NewLayerDock();
    void setColorVect(QVector<QRgb> colorVect);
    QDockWidget *createNewLayerDock();

signals:
    void updateHasLayer(bool b);
    void update();
    void setNewColorVect(QVector<QRgb> colorVect);

private slots:
    void existingColor();
    void newColor();
    void actualColorVect();
    void standartColorVect();
    void smallColorVect();
    void customColorVect();
    void addNewLayer();
    void setNewColor();
    void setNewLayerX(int w);
    void setNewLayerY(int w);
    void setNewLayerColor();

private:
    toolParameters_t *param;
    QDockWidget *dockWidget;
    int drawColorIndex=0;
    QVector<QRgb> newColorVect;
    QList<QAction*> colorAct;
    QPushButton *colorButton;
    QSlider *newLayerXSlider;
    QSpinBox *newLayerXSpinbox;
    QSlider *newLayerYSlider;
    QSpinBox *newLayerYSpinbox;
    QMenu *colorMenu;
    QPushButton *newColorButton;
    QRgb newLayerColor;
    QRadioButton *newColormap[4];
    QGridLayout *newLayerLayout;
    QVector<QRgb> colorVect;
    bool isNewLayerColor = false;
    bool actualColor = true;
    int newLayerX = 100;
    int newLayerY = 100;
    InteractionTool *interactionTool;
};

#endif // NEWLAYERDOCK_H
