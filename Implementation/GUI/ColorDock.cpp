#include "ColorDock.h"

ColorDock::ColorDock(InteractionTool *interaction){
    interactionTool = interaction;
    colorButtons = std::vector<QToolButton*>(); //TODO vector zu Qvector ändern
    for(int i = 0; i <256; i++){
        colorVect.append(QColor(255,255,255,255).rgba());
        colorButtons.push_back(new QToolButton());
        QString str;
        str.sprintf("background-color: qlineargradient(stop:0 #%02x%02x%02x);",qRed(colorVect[i]),qGreen(colorVect[i]),qBlue(colorVect[i]));

        colorButtons[i]->setStyleSheet(str);
        colorButtons[i]->setCheckable(true);

        connect(colorButtons[i], SIGNAL(clicked()),this, SLOT(changeColor()));
    }
    
    addColor(QColor(255,255,255,255),0);
    addColor(QColor(127,127,127,255),1);
    addColor(QColor(0,0,0,255),2);
    addColor(QColor(0,255,255,255),3);
    addColor(QColor(0,127,127,255),4);
    addColor(QColor(127,255,255,255),5);
    addColor(QColor(127,0,0,255),6);
    addColor(QColor(255,127,127,255),7);
    addColor(QColor(255,0,0,255),8);
    addColor(QColor(255,0,255,255),9);
    addColor(QColor(127,0,127,255),10);
    addColor(QColor(255,127,255,255),11);
    addColor(QColor(0,127,0,255),12);
    addColor(QColor(127,255,127,255),13);
    addColor(QColor(0,255,0,255),14);
    addColor(QColor(255,255,0,255),15);
    addColor(QColor(127,127,0,255),16);
    addColor(QColor(255,255,127,255),17);
    addColor(QColor(0,0,127,255),18);
    addColor(QColor(127,127,255,255),19);
    addColor(QColor(0,0,255,255),20);

    addColor(QColor(0,0,0,0),255);
    
    createColorDock();
    emit updateColorVect(colorVect);

}
ColorDock::~ColorDock(){
    
}
void ColorDock::changeColor(){
    for (int i = 0; i < colorButtons.size(); i++) {
        if (colorButtons[i]->isChecked()){
            QPixmap px(20, 20);
            QString str2;
            str2.sprintf("Color %d",i);
            colorVect[i]=QColorDialog().getColor(Qt::white,nullptr,str2,QColorDialog::ShowAlphaChannel).rgba();
            emit updateColorVect(colorVect);
            px.fill(colorVect[i]);
            //colorButtons[i]->setIcon(px);
            //colorAct[i]->setIcon(px);
            QString str;
            //str.append(qRed(colorVect[i]));
            //str.append(";");
            //str.sprintf("#%02x%02x%02x",qRed(colorVect[i]),qGreen(colorVect[i]),qBlue(colorVect[i]));
            str.sprintf("background-color: qlineargradient(stop:0.5 #%02x%02x%02x);",qRed(colorVect[i]),qGreen(colorVect[i]),qBlue(colorVect[i]));
            //printf("background-color: #%02x%02x%02x;\n",qRed(colorVect[i]),qGreen(colorVect[i]),qBlue(colorVect[i]));
            colorButtons[i]->setStyleSheet(str);
            //if(i==drawColorIndex){
            //    colorButton->setStyleSheet(str);
            //}
            colorButtons[i]->setChecked(false);
            if (interactionTool->getPicture()->hasLayer()){
                interactionTool->getPicture()->getCurrentLayerAsQ()->setColor(i,colorVect[i]);
                //setImage(*interactionTool->getPicture()->getCurrentLayerAsQ());
                //updateLayers();
                emit updateLayers();
                emit updateVisible();

            }
            //colorButton->setMenu(colorMenu);
        }
    }
}
void ColorDock::createColorDock(){
    colorButtons = std::vector<QToolButton*>();
    //QPixmap px(20, 20);
    for(int i = 0; i <256; i++){

        colorButtons.push_back(new QToolButton());
        //px.fill(colorVect[i]);
        //colorButtons[i]->setIcon(px);
        colorButtons[i]->setCheckable(true);
        QString str;
        //str.append(qRed(colorVect[i]));
        //str.append(";");
        str.sprintf("background-color: qlineargradient(stop:0 #%02x%02x%02x);",qRed(colorVect[i]),qGreen(colorVect[i]),qBlue(colorVect[i]));
        //printf("background-color: #%02x%02x%02x;\n",qRed(colorVect[i]),qGreen(colorVect[i]),qBlue(colorVect[i]));
        colorButtons[i]->setStyleSheet(str);
        //if(i==drawColorIndex){
        //    colorButton->setStyleSheet(str);
        //}
        connect(colorButtons[i], SIGNAL(clicked()),this, SLOT(changeColor()));
        //connect(colorButtons[i], SIGNAL(clicked()),colorButtons[i], SLOT(toggle()));
    }

    colorDock = new QDockWidget(tr("Colortable"));
    colorDock->setAllowedAreas(Qt::BottomDockWidgetArea);

    colorLayout = new QGridLayout();
    for (int i = 0; i < 64; i++) {
        colorLayout->addWidget(colorButtons[4*i],0,i);
        colorLayout->addWidget(colorButtons[4*i+1],1,i);
        colorLayout->addWidget(colorButtons[4*i+2],2,i);
        colorLayout->addWidget(colorButtons[4*i+3],3,i);
    }

    colors = new QWidget(colorDock);
    colors->setLayout(colorLayout);
    ColorScrollArea = new QScrollArea();
    ColorScrollArea->setWidget(colors);
    colorDock->setWidget(ColorScrollArea);

    //addDockWidget(Qt::BottomDockWidgetArea, colorDock);
    colorDock->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable);
}
void ColorDock::addColor(QColor col, int pos){
    QPixmap px(20, 20);
    colorVect[pos]=col.rgba();

    px.fill(colorVect[pos]);
    //colorButtons[i]->setIcon(px);
    QString str;
    //str.append(qRed(colorVect[i]));
    //str.append(";");
    //str.sprintf("#%02x%02x%02x",qRed(colorVect[i]),qGreen(colorVect[i]),qBlue(colorVect[i]));
    str.sprintf("background-color: qlineargradient(stop:0.5 #%02x%02x%02x);",qRed(colorVect[pos]),qGreen(colorVect[pos]),qBlue(colorVect[pos]));
    //printf("background-color: #%02x%02x%02x;\n",qRed(colorVect[i]),qGreen(colorVect[i]),qBlue(colorVect[i]));
    colorButtons[pos]->setStyleSheet(str);

    colorButtons[pos]->setChecked(false);
    if (interactionTool->getPicture()->hasLayer()){
        interactionTool->getPicture()->getCurrentLayerAsQ()->setColor(pos,colorVect[pos]);
        //setImage(*interactionTool->getPicture()->getCurrentLayerAsQ());
        //updateLayers();
        emit updateLayers();
        emit updateVisible();

    }
    emit updateColorVect(colorVect);
}
void ColorDock::updateColors(){
    QPixmap px(20, 20);
    colorVect = interactionTool->getPicture()->getCurrentLayerAsQ()->colorTable();
    for(int i = 0; i <256; i++){

        px.fill(colorVect[i]);

        //colorButtons[i]->setIcon(px);
        QString str;
        //str.append(qRed(colorVect[i]));
        //str.append(";");
        str.sprintf("background-color: qlineargradient(stop:0 #%02x%02x%02x);",qRed(colorVect[i]),qGreen(colorVect[i]),qBlue(colorVect[i]));
        //printf("background-color: #%02x%02x%02x;\n",qRed(colorVect[i]),qGreen(colorVect[i]),qBlue(colorVect[i]));
        colorButtons[i]->setStyleSheet(str);

    }
    emit updateColorVect(colorVect);
    if(interactionTool->getPicture()->isShaped()){
        addColor(QColor(255,255,255,0),255);
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
        //colorAct[255]->setIcon(px);
        //colorAct[255]->setEnabled(false);
        colorButtons[255]->setStyleSheet("background-color: #FFFFFF;\n");
        colorButtons[255]->setIcon(px);
        colorButtons[255]->setEnabled(false);
    } else {
        //colorAct[255]->setEnabled(true);
        colorButtons[255]->setEnabled(true);
        px.fill(QColor(255,255,255,0));
        colorButtons[255]->setIcon(px);
    }
}
QDockWidget *ColorDock::getDockWidget(){
    return colorDock;
}
void ColorDock::setColorVect(QVector<QRgb> colorVect){
    this->colorVect=colorVect;
}
QVector<QRgb> ColorDock::getColorVect(){
    return colorVect;
}
