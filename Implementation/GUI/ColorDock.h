#ifndef COLORDOCK_H
#define COLORDOCK_H
#include "InteractionTool.h"
#include <QDockWidget>
#include <QScrollArea>
#include <QGridLayout>
#include <QToolButton>
#include <QPainter>
#include <QColorDialog>

class ColorDock : public QObject
{
    Q_OBJECT
    
public:
    ColorDock(InteractionTool *interaction);
    ~ColorDock();
    QDockWidget *getDockWidget();
    void updateColors();
    void setColorVect(QVector<QRgb> colorVect);
    QVector<QRgb> getColorVect();

signals:
    void updateVisible();
    void updateLayers();
    void updateColorVect(QVector<QRgb> colorVect);
    
private slots:
    void changeColor();
    
private:
    void createColorDock();
    void addColor(QColor col, int pos);
    
    QScrollArea *ColorScrollArea;
    QWidget *colors;
    QDockWidget *colorDock;
    QGridLayout* colorLayout;
    std::vector<QToolButton*> colorButtons;
    QVector<QRgb> colorVect;
    InteractionTool *interactionTool;
    
};

#endif // COLORDOCK_H
