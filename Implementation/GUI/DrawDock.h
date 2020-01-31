#ifndef DRAWDOCK_H
#define DRAWDOCK_H
#include "InteractionTool.h"
#include <QDockWidget>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QCheckBox>
#include <QMenu>
#include <QGridLayout>
#include <QRadioButton>
#include <QLabel>
#include <QDialog>
#include <QMouseEvent>
#include <QScrollArea>
#include <QPainter>

typedef enum drawModus {pencil, lines, notFilledRect, filledRect} drawModus_e;
typedef enum eventType {press,movee, release} eventType_e;
typedef struct para1{
    QPoint p;
    QPoint q;
    int w;
    int i;
} para1;
typedef struct para2{
    QPolygon p;
    int i;
} para2;

class DrawDock : public QObject
{
    Q_OBJECT
public:
    DrawDock(InteractionTool *interaction);
    ~DrawDock();
    QDockWidget *getDockWidget();
    bool mouseEvent(QMouseEvent *event,eventType_e type,int w1,int w2,int h1,int h2);
    void setColorVect(QVector<QRgb> colorVect);

signals:
    void update();
    void drawShowI(para1);
    void drawShowII(para2);

private slots:
    void pencil();
    void startDraw();
    void lines();
    void notFilledRect();
    void filledRect();
    void setDrawColor();
    void setWidth(int w);

private:
    void createDrawDock();

    QDockWidget *drawDock;
    QList<QAction*> colorAct;
    QPushButton *colorButton;
    QSlider *drawSlider;
    QSpinBox *drawSpinbox;
    QPushButton *drawStartButton;
    QMenu *colorMenu;
    drawModus_e actDrawModus = drawModus_e::pencil;
    QCheckBox *ignoreShaped;
    QPolygon polyVis;
    QVector<QRgb> colorVect;
    bool isDraw=false;
    int drawWidth=3;
    int drawColorIndex=0;
    bool drawStart=false;
    toolParameters_t *param;
    InteractionTool *interactionTool;
};


#endif // DRAWDOCK_H
