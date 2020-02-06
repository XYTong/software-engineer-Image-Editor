#include "InteractionTool.h"
#include "TranslationDock.h"
#include "NewLayerDock.h"
#include "DrawDock.h"
#include "LayerDock.h"
#include "ColorDock.h"

#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H



#include <QMainWindow>
#include <QImage>
#include <vector>
#include <QToolButton>
#include <QPushButton>
#include <QRadioButton>
#include <QGridLayout>
#include <QSlider>
#include <QSpinBox>
#include <QLabel>
#include <QCheckBox>

class ImageViewer : public QMainWindow
{
    Q_OBJECT

public:
    ImageViewer(QWidget *parent = nullptr);
    bool loadFile(const QString &);
    bool getHasLayer();
    QVector<QRgb> getColorVect();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void open();
    void saveAs();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();
    void about();
    void draw();
    void translate();
    void setTranslationParams(toolParameters_t * param);
    void setMergeParams(toolParameters_t * param);
    void updateHasLayer(bool b);
    void updateall();
    void updateWithoutLayer();
    void updateVisible();
    void makeShaped();
    void newLayer();
    void drawShowI(para1 p);
    void drawShowII(para2 p);
    void updateLayerDock();
    void updateColorVector(QVector<QRgb> colorVect);
    void updateNewColorVector(QVector<QRgb> colorVect);

private:
    void createActions();
    void createMenus();
    void updateActions();
    bool saveFile(const QString &fileName);
    void setImage(QImage newImage);
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
    void calculateVisible();

    QImage image;
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    QMenu *viewMenu;
    QDockWidget *layerDockW;
    QVector<QRgb> colorVect;
    QVector<QRgb> newColorVect;
    QPixmap *pixmap;
    QPoint move;
    bool moveStart = false;
    double scaleFactor = 1.0;
    bool hasLayer=false;
    toolParameters_t *param = nullptr;
    InteractionTool *interactionTool;
    QAction *makeToShaped;
    QAction *drawTool;
    QAction *newLayerAct;
    QAction *translateAct;
    QAction *drawToolAct;
    TranslationDock *transLationDock;
    NewLayerDock *newLayerDock;
    DrawDock *drawDock;
    LayerDock *layerDock;
    ColorDock *colorDock;
    QAction *saveAsAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;
    QAction *showColorsAct;
};

#endif
