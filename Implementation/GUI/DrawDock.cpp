#include "DrawDock.h"

DrawDock::DrawDock(InteractionTool *interaction){
    colorMenu = new QMenu();
    colorButton = new QPushButton();
    for(int i = 0; i <256; i++){
        colorVect.append(QColor(255,255,255,255).rgba());
        QString str,str2;
        QPixmap px(20,20);
        str.sprintf("padding:0px;background-color: qlineargradient(stop:0 #%02x%02x%02x);",qRed(colorVect[i]),qGreen(colorVect[i]),qBlue(colorVect[i]));
        if(i==drawColorIndex){
            QPixmap px(40, 20);
            px.fill(QColor(0,0,0,0));
            QPainter p(&px);
            QBrush *br1 = new QBrush(QColor(100,100,100));
            QBrush *br2 = new QBrush(QColor(200,200,200));
            br1->setColor(QColor(100,100,100,255-qAlpha(colorVect[i])));
            br2->setColor(QColor(200,200,200,255-qAlpha(colorVect[i])));
            p.fillRect(0,0,10,10,*br1);
            p.fillRect(10,10,10,10,*br1);
            p.fillRect(0,10,10,10,*br2);
            p.fillRect(10,0,10,10,*br2);
            p.fillRect(20,0,10,10,*br1);
            p.fillRect(30,10,10,10,*br1);
            p.fillRect(20,10,10,10,*br2);
            p.fillRect(30,0,10,10,*br2);
            p.end();
            colorButton->setStyleSheet(str);
        }
        str2.sprintf("Color %d",i);
        px.fill(colorVect[i]);
        colorMenu->addAction(px,str2,this,&DrawDock::setDrawColor);
    }
    colorAct = colorMenu->actions();
    for (int i = 0; i < 256; i++) {
        colorAct[i]->setCheckable(true);
    }
    colorButton->setMenu(colorMenu);
    drawSpinbox = new QSpinBox();
    drawSpinbox->setValue(3);
    connect(drawSpinbox, QOverload<int>::of(&QSpinBox::valueChanged),this, &DrawDock::setWidth);
    drawSlider = new QSlider(Qt::Horizontal);
    drawSlider->setRange(1,99);
    drawSlider->setValue(3);
    connect(drawSlider, QOverload<int>::of(&QSlider::valueChanged),this, &DrawDock::setWidth);
    drawStartButton = new QPushButton("Start");
    drawStartButton->setCheckable(true);
    connect(drawStartButton, SIGNAL(clicked()),this, SLOT(startDraw()));
    ignoreShaped = new QCheckBox("Ignore Shape");
    interactionTool=interaction;
    param=nullptr;
}

DrawDock::~DrawDock(){

}
bool DrawDock::mouseEvent(QMouseEvent *event, eventType_e type, int w1, int w2, int h1, int h2){
    switch (type) {
    case press:{
        if (isDraw&& event->button() == Qt::LeftButton) {
            switch (actDrawModus) {
            case drawModus_e::pencil:{
                drawStart = true;
                param = new toolParameters_t;
                param->tool = paint;
                param->i = drawWidth;
                param->ignoreShape = ignoreShaped->isChecked();
                param->colorIndex =drawColorIndex;
                param->startPoint = event->pos()-QPoint(w1-w2,h1-h2);
                break;
            }
            case drawModus_e::lines:{
                drawStart = true;
                param = new toolParameters_t;
                param->tool = paint;
                param->i = drawWidth;
                param->ignoreShape = ignoreShaped->isChecked();
                param->colorIndex =drawColorIndex;
                param->startPoint = event->pos()-QPoint(w1-w2,h1-h2);
                break;
            }
            case drawModus_e::filledRect:{
                if (param==nullptr){
                    param = new toolParameters_t;
                    param->tool = polygon;
                    param->ignoreShape = ignoreShaped->isChecked();
                    param->poly = QPolygon();
                    polyVis = QPolygon();
                }
                param->isInverse = false;
                param->startPoint = event->pos()-QPoint(w1-w2+interactionTool->getPicture()->currentXOffset(),h1-h2+interactionTool->getPicture()->currentYOffset());
                break;
            }
            case drawModus_e::notFilledRect:{
                if (param==nullptr){
                    param = new toolParameters_t;
                    param->tool = polygon;
                    param->ignoreShape = ignoreShaped->isChecked();
                    param->poly = QPolygon();
                    polyVis = QPolygon();
                }
                param->isInverse = true;
                param->startPoint = event->pos()-QPoint(w1-w2+interactionTool->getPicture()->currentXOffset(),h1-h2+interactionTool->getPicture()->currentYOffset());
                break;
            }
            default:{
                break;
            }
            }
        return true;
        }
        return false;
    }

    case movee:{
        if (drawStart) {
            switch (actDrawModus) {
            case drawModus_e::pencil:{
                param->endPoint = event->pos()-QPoint(w1-w2,h1-h2);
                interactionTool->useTool(param);
                param = nullptr;
                emit updateLayer();
                emit updateVisible();
                param = new toolParameters_t;
                param->tool = paint;
                param->ignoreShape = ignoreShaped->isChecked();
                param->i = drawWidth;
                param->colorIndex =drawColorIndex;
                param->startPoint = event->pos()-QPoint(w1-w2,h1-h2);
                break;
            }
            case drawModus_e::lines:{
                emit updateLayer();
                emit updateVisible();
                para1 p;
                p.i=drawColorIndex;
                p.p=event->pos()-QPoint(w1-w2,h1-h2);
                p.q=param->startPoint;
                p.w=drawWidth;
                emit drawShowI(p);
                break;
            }
            default:{
                break;
            }
            }

        return true;
        }
        return false;
    }
    case release:{
        if (isDraw && event->button() == Qt::LeftButton) {
            switch (actDrawModus) {
            case drawModus_e::pencil:{
                drawStart = false;
                param->endPoint = event->pos()-QPoint(w1-w2,h1-h2);
                interactionTool->useTool(param);
                param = nullptr;
                emit updateLayer();
                emit updateVisible();
                break;
            }
            case drawModus_e::lines:{
                drawStart = false;
                param->endPoint = event->pos()-QPoint(w1-w2,h1-h2);
                interactionTool->useTool(param);
                param = nullptr;
                emit updateLayer();
                emit updateVisible();
                break;
            }
            case drawModus_e::filledRect:{
                //if () TODO: Start & Endpkt vergleichen
                param->poly.push_back(event->pos()-QPoint(w1-w2+interactionTool->getPicture()->currentXOffset(),h1-h2+interactionTool->getPicture()->currentYOffset()));
                polyVis.push_back(event->pos()-QPoint(w1-w2,h1-h2));
                emit updateLayer();
                emit updateVisible();
                para2 p;
                p.i=drawColorIndex;
                p.p=polyVis;
                emit drawShowII(p);

                break;
            }
            case drawModus_e::notFilledRect:{
                //if () TODO: Start & Endpkt vergleichen
                param->poly.push_back(event->pos()-QPoint(w1-w2+interactionTool->getPicture()->currentXOffset(),h1-h2+interactionTool->getPicture()->currentYOffset()));
                polyVis.push_back(event->pos()-QPoint(w1-w2,h1-h2));
                emit updateLayer();
                emit updateVisible();
                para2 p;
                p.i=drawColorIndex;
                p.p=polyVis;
                emit drawShowII(p);
                break;
            }
            default:{
                break;
            }
            }
        return true;
        } else if (isDraw && event->button() == Qt::RightButton){
            switch (actDrawModus) {
            case drawModus_e::filledRect:{
                //if () TODO: Start & Endpkt vergleichen
                param->colorIndex=drawColorIndex;
                interactionTool->useTool(param);
                param = nullptr;
                emit updateLayer();
                emit updateVisible();
                break;
            }
            case drawModus_e::notFilledRect:{
                //if () TODO: Start & Endpkt vergleichen
                param->colorIndex=drawColorIndex;
                interactionTool->useTool(param);
                param = nullptr;
                emit updateLayer();
                emit updateVisible();
                break;
            }
            default:{
                break;
            }
            }
            return true;
        }
        return false;
    }
    }
}
void DrawDock::pencil(){
    actDrawModus = drawModus_e::pencil;
}
void DrawDock::startDraw(){
    if(isDraw){
        isDraw = false;
        drawStartButton->setText("Start");
        param = nullptr;
        emit updateLayer();
        emit updateVisible();
    } else {
        isDraw = true;
        drawStartButton->setText("Stop");
    }
}
void DrawDock::lines(){
    actDrawModus = drawModus_e::lines;
}
void DrawDock::notFilledRect(){
    actDrawModus = drawModus_e::notFilledRect;
}
void DrawDock::filledRect(){
    actDrawModus = drawModus_e::filledRect;
}
void DrawDock::setDrawColor(){
    for (int i = 0; i < 256; i++) {
        if (colorAct[i]->isChecked()){
            colorAct[i]->setChecked(false);
            drawColorIndex = i;
            QString str;
            str.sprintf("padding:0px;background-color: qlineargradient(stop:0 #%02x%02x%02x);",qRed(colorVect[i]),qGreen(colorVect[i]),qBlue(colorVect[i]));
            colorButton->setStyleSheet(str);
            QPixmap px(40, 20);
            px.fill(QColor(0,0,0,0));
            QPainter p(&px);
            QBrush *br1 = new QBrush(QColor(100,100,100));
            QBrush *br2 = new QBrush(QColor(200,200,200));
            br1->setColor(QColor(100,100,100,255-qAlpha(colorVect[i])));
            br2->setColor(QColor(200,200,200,255-qAlpha(colorVect[i])));
            p.fillRect(0,0,10,10,*br1);
            p.fillRect(10,10,10,10,*br1);
            p.fillRect(0,10,10,10,*br2);
            p.fillRect(10,0,10,10,*br2);
            p.fillRect(20,0,10,10,*br1);
            p.fillRect(30,10,10,10,*br1);
            p.fillRect(20,10,10,10,*br2);
            p.fillRect(30,0,10,10,*br2);
            p.end();
        }
    }
}
void DrawDock::setWidth(int w){
    drawSpinbox->setValue(w);
    drawSlider->setValue(w);
    drawWidth=w;
}
QDockWidget *DrawDock::createDrawDock(){
    drawDock = new QDockWidget(tr("Draw"));
    drawDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    QGridLayout *drawLayout = new QGridLayout();
    QRadioButton *button1 = new QRadioButton("Pencil");
    button1->setChecked(true);
    drawLayout->addWidget(button1,0,0,1,2);
    connect(button1, SIGNAL(clicked()),this, SLOT(pencil()));
    QRadioButton *button2 = new QRadioButton("Lines");
    drawLayout->addWidget(button2,1,0,1,2);
    connect(button2, SIGNAL(clicked()),this, SLOT(lines()));
    QRadioButton *button3 = new QRadioButton("Filled polygon");
    drawLayout->addWidget(button3,2,0,1,2);
    connect(button3, SIGNAL(clicked()),this, SLOT(filledRect()));
    QRadioButton *button4 = new QRadioButton("Inverse polygon");
    drawLayout->addWidget(button4,3,0,1,2);
    connect(button4, SIGNAL(clicked()),this, SLOT(notFilledRect()));
    QLabel *color = new QLabel();
    color->setText("Color:");
    drawLayout->addWidget(color,4,0);
    drawLayout->addWidget(colorButton,4,1);
    drawLayout->addWidget(ignoreShaped,5,0,1,2);
    QLabel *width = new QLabel();
    width->setText("Width:");
    drawLayout->addWidget(width,6,0);
    drawLayout->addWidget(drawSpinbox,6,1);
    QDialog *text = new QDialog();
    drawLayout->addWidget(text,8,1,1,2);
    drawLayout->addWidget(drawSlider,7,0,1,2);
    drawLayout->addWidget(drawStartButton,8,0,1,2);
    QWidget *drawControl = new QWidget(drawDock);
    drawControl->setLayout(drawLayout);
    drawDock->setWidget(drawControl);
    return drawDock;
}
void DrawDock::setColorVect(QVector<QRgb> colorVect){
    this->colorVect=colorVect;
    QPixmap px(20, 20);
    for(int i = 0; i <256; i++){
        QPainter p(&px);
        QBrush br1(QColor(100,100,100));
        QBrush br2(QColor(200,200,200));
        QBrush br3(QColor(qRed(colorVect[i]),qGreen(colorVect[i]),qBlue(colorVect[i]),qAlpha(colorVect[i])));
        p.fillRect(0,0,10,10,br1);
        p.fillRect(10,10,10,10,br1);
        p.fillRect(0,10,10,10,br2);
        p.fillRect(10,0,10,10,br2);
        p.fillRect(0,0,20,20,br3);
        p.end();
        QString str;
        str.sprintf("padding:0px;background-color: qlineargradient(stop:0 #%02x%02x%02x);",qRed(colorVect[i]),qGreen(colorVect[i]),qBlue(colorVect[i]));
        if(i==drawColorIndex){
            QString str;
            str.sprintf("padding:0px;background-color: qlineargradient(stop:0 #%02x%02x%02x);",qRed(colorVect[i]),qGreen(colorVect[i]),qBlue(colorVect[i]));
            QPixmap px(40, 20);
            px.fill(QColor(0,0,0,0));
            QPainter p(&px);
            QBrush *br1 = new QBrush(QColor(100,100,100));
            QBrush *br2 = new QBrush(QColor(200,200,200));
            br1->setColor(QColor(100,100,100,255-qAlpha(colorVect[i])));
            br2->setColor(QColor(200,200,200,255-qAlpha(colorVect[i])));
            p.fillRect(0,0,10,10,*br1);
            p.fillRect(10,10,10,10,*br1);
            p.fillRect(0,10,10,10,*br2);
            p.fillRect(10,0,10,10,*br2);
            p.fillRect(20,0,10,10,*br1);
            p.fillRect(30,10,10,10,*br1);
            p.fillRect(20,10,10,10,*br2);
            p.fillRect(30,0,10,10,*br2);
            p.end();
            colorButton->setStyleSheet(str);
        }
        colorAct[i]->setIcon(px);
    }
    if(interactionTool->getPicture()->isShaped()){
        px.fill(QColor(255,255,255,0));
        QPainter p(&px);
        QPen pen(QColor(255,0,0,255));
        pen.setWidth(2);
        p.setPen(pen);
        p.drawLine(1,1,19,1);
        p.drawLine(19,1,19,19);
        p.drawLine(19,19,1,19);
        p.drawLine(1,19,1,1);
        p.drawLine(1,19,19,1);
        p.drawLine(19,19,1,1);
        colorAct[255]->setIcon(px);
    } else {
        colorAct[255]->setEnabled(true);
        px.fill(QColor(255,255,255,0));
        colorAct[255]->setIcon(px);
    }
    colorButton->setMenu(colorMenu);
}
