#include "NewLayerDock.h"

NewLayerDock::NewLayerDock(InteractionTool *interaction){
    newLayerXSpinbox = new QSpinBox();
    newLayerXSpinbox->setRange(1,1000);
    newLayerXSpinbox->setValue(100);
    connect(newLayerXSpinbox, QOverload<int>::of(&QSpinBox::valueChanged),this, &NewLayerDock::setNewLayerX);
    newLayerXSlider = new QSlider(Qt::Horizontal);
    newLayerXSlider->setRange(1,1000);
    newLayerXSlider->setValue(100);
    connect(newLayerXSlider, QOverload<int>::of(&QSlider::valueChanged),this, &NewLayerDock::setNewLayerX);
    newLayerYSpinbox = new QSpinBox();
    newLayerYSpinbox->setRange(1,1000);
    newLayerYSpinbox->setValue(100);
    connect(newLayerYSpinbox, QOverload<int>::of(&QSpinBox::valueChanged),this, &NewLayerDock::setNewLayerY);
    newLayerYSlider = new QSlider(Qt::Horizontal);
    newLayerYSlider->setRange(1,1000);
    newLayerYSlider->setValue(100);
    connect(newLayerYSlider, QOverload<int>::of(&QSlider::valueChanged),this, &NewLayerDock::setNewLayerY);
    newColorButton = new QPushButton();
    newLayerColor = QColor(255,255,255,255).rgba();
    newColorButton->setStyleSheet(QString("background-color: qlineargradient(stop:0 #FFFFFF);"));
    connect(newColorButton, SIGNAL(clicked()), this, SLOT(setNewColor()));
    interactionTool = interaction;
    colorButton = new QPushButton();
    colorMenu = new QMenu();
    for(int i = 0; i <256; i++){
        colorVect.append(QColor(255,255,255,255).rgba());
        //px.fill(colorVect[i]);
        //colorButtons[i]->setIcon(px);
        QString str,str2;
        QPixmap px(20,20);
        //str.append(qRed(colorVect[i]));
        //str.append(";");
        str.sprintf("background-color: qlineargradient(stop:0 #%02x%02x%02x);",qRed(colorVect[i]),qGreen(colorVect[i]),qBlue(colorVect[i]));
        //printf("background-color: #%02x%02x%02x;\n",qRed(colorVect[i]),qGreen(colorVect[i]),qBlue(colorVect[i]));
        if(i==drawColorIndex){
            colorButton->setStyleSheet(str);
        }
        //connect(colorButtons[i], SIGNAL(clicked()),colorButtons[i], SLOT(toggle()));
        str2.sprintf("Color %d",i);
        px.fill(colorVect[i]);
        //QAction *act = new QAction(px,str);
        //act->setCheckable(true);
        //connect(act, SIGNAL(clicked()),this, SLOT(setDrawColor()));
        colorMenu->addAction(px,str2,this,&NewLayerDock::setNewLayerColor);
    }
    colorButton->setMenu(colorMenu);
    colorAct=colorMenu->actions();
    for (int i = 0; i < 256; i++) {
        colorAct[i]->setCheckable(true);
        //connect(act[i], SIGNAL(toggled()),this, SLOT(setDrawColor()));
    }
    newColorVect = QVector<QRgb>();
    //for (int i = 0; i < 256; i++) {
        newColorVect.append(colorVect);
    //}
    actualColorVect();
    createNewLayerDock();
}
NewLayerDock::~NewLayerDock(){

}
void NewLayerDock::existingColor(){
    isNewLayerColor = false;
}
void NewLayerDock::newColor(){
    isNewLayerColor = true;
}
void NewLayerDock::actualColorVect(){
    //newColorVect = QVector<QRgb>();
    for (int i = 0; i < 256; i++) {
        newColorVect[i]=colorVect[i];
    }
    QPixmap px(20, 20);
    for(int i = 0; i <256; i++){

        QPainter p(&px);
        QBrush br1(QColor(100,100,100));
        QBrush br2(QColor(200,200,200));
        QBrush br3(QColor(qRed(newColorVect[i]),qGreen(newColorVect[i]),qBlue(newColorVect[i]),qAlpha(newColorVect[i])));
        p.fillRect(0,0,10,10,br1);
        p.fillRect(10,10,10,10,br1);
        p.fillRect(0,10,10,10,br2);
        p.fillRect(10,0,10,10,br2);
        p.fillRect(0,0,20,20,br3);
        p.end();
        if(i==drawColorIndex){
            QString str;
            str.sprintf("background-color: qlineargradient(stop:0 #%02x%02x%02x);",qRed(newColorVect[i]),qGreen(newColorVect[i]),qBlue(newColorVect[i]));
            colorButton->setStyleSheet(str);
        }

        colorAct[i]->setIcon(px);
    }
    actualColor = true;
    emit setNewColorVect(newColorVect);
}
void NewLayerDock::standartColorVect(){
    newColorVect = QVector<QRgb>();
    newColorVect.append(colorVect);
    newColorVect[0]=QColor(0,0,0,255).rgba();
    newColorVect[1]=QColor(0,0,63,255).rgba();
    newColorVect[2]=QColor(0,0,127,255).rgba();
    newColorVect[3]=QColor(0,0,191,255).rgba();
    newColorVect[4]=QColor(0,0,255,255).rgba();
    newColorVect[5]=QColor(0,63,0,255).rgba();
    newColorVect[6]=QColor(0,63,63,255).rgba();
    newColorVect[7]=QColor(0,63,127,255).rgba();
    newColorVect[8]=QColor(0,63,191,255).rgba();
    newColorVect[9]=QColor(0,63,255,255).rgba();
    newColorVect[10]=QColor(0,127,0,255).rgba();
    newColorVect[11]=QColor(0,127,63,255).rgba();
    newColorVect[12]=QColor(0,127,127,255).rgba();
    newColorVect[13]=QColor(0,127,191,255).rgba();
    newColorVect[14]=QColor(0,127,255,255).rgba();
    newColorVect[15]=QColor(0,191,0,255).rgba();
    newColorVect[16]=QColor(0,191,63,255).rgba();
    newColorVect[17]=QColor(0,191,127,255).rgba();
    newColorVect[18]=QColor(0,191,191,255).rgba();
    newColorVect[19]=QColor(0,191,255,255).rgba();
    newColorVect[20]=QColor(0,255,0,255).rgba();
    newColorVect[21]=QColor(0,255,63,255).rgba();
    newColorVect[22]=QColor(0,255,127,255).rgba();
    newColorVect[23]=QColor(0,255,191,255).rgba();
    newColorVect[24]=QColor(0,255,255,255).rgba();
    newColorVect[25]=QColor(63,0,0,255).rgba();
    newColorVect[26]=QColor(63,0,63,255).rgba();
    newColorVect[27]=QColor(63,0,127,255).rgba();
    newColorVect[28]=QColor(63,0,191,255).rgba();
    newColorVect[29]=QColor(63,0,255,255).rgba();
    newColorVect[30]=QColor(63,63,0,255).rgba();
    newColorVect[31]=QColor(63,63,63,255).rgba();
    newColorVect[32]=QColor(63,63,127,255).rgba();
    newColorVect[33]=QColor(63,63,191,255).rgba();
    newColorVect[34]=QColor(63,63,255,255).rgba();
    newColorVect[35]=QColor(63,127,0,255).rgba();
    newColorVect[36]=QColor(63,127,63,255).rgba();
    newColorVect[37]=QColor(63,127,127,255).rgba();
    newColorVect[38]=QColor(63,127,191,255).rgba();
    newColorVect[39]=QColor(63,127,255,255).rgba();
    newColorVect[40]=QColor(63,191,0,255).rgba();
    newColorVect[41]=QColor(63,191,63,255).rgba();
    newColorVect[42]=QColor(63,191,127,255).rgba();
    newColorVect[43]=QColor(63,191,191,255).rgba();
    newColorVect[44]=QColor(63,191,255,255).rgba();
    newColorVect[45]=QColor(63,255,0,255).rgba();
    newColorVect[46]=QColor(63,255,63,255).rgba();
    newColorVect[47]=QColor(63,255,127,255).rgba();
    newColorVect[48]=QColor(63,255,191,255).rgba();
    newColorVect[49]=QColor(63,255,255,255).rgba();
    newColorVect[50]=QColor(127,0,0,255).rgba();
    newColorVect[51]=QColor(127,0,63,255).rgba();
    newColorVect[52]=QColor(127,0,127,255).rgba();
    newColorVect[53]=QColor(127,0,191,255).rgba();
    newColorVect[54]=QColor(127,0,255,255).rgba();
    newColorVect[55]=QColor(127,63,0,255).rgba();
    newColorVect[56]=QColor(127,63,63,255).rgba();
    newColorVect[57]=QColor(127,63,127,255).rgba();
    newColorVect[58]=QColor(127,63,191,255).rgba();
    newColorVect[59]=QColor(127,63,255,255).rgba();
    newColorVect[60]=QColor(127,127,0,255).rgba();
    newColorVect[61]=QColor(127,127,63,255).rgba();
    newColorVect[62]=QColor(127,127,127,255).rgba();
    newColorVect[63]=QColor(127,127,191,255).rgba();
    newColorVect[64]=QColor(127,127,255,255).rgba();
    newColorVect[65]=QColor(127,191,0,255).rgba();
    newColorVect[66]=QColor(127,191,63,255).rgba();
    newColorVect[67]=QColor(127,191,127,255).rgba();
    newColorVect[68]=QColor(127,191,191,255).rgba();
    newColorVect[69]=QColor(127,191,255,255).rgba();
    newColorVect[70]=QColor(127,255,0,255).rgba();
    newColorVect[71]=QColor(127,255,63,255).rgba();
    newColorVect[72]=QColor(127,255,127,255).rgba();
    newColorVect[73]=QColor(127,255,191,255).rgba();
    newColorVect[74]=QColor(127,255,255,255).rgba();
    newColorVect[75]=QColor(191,0,0,255).rgba();
    newColorVect[76]=QColor(191,0,63,255).rgba();
    newColorVect[77]=QColor(191,0,127,255).rgba();
    newColorVect[78]=QColor(191,0,191,255).rgba();
    newColorVect[79]=QColor(191,0,255,255).rgba();
    newColorVect[80]=QColor(191,63,0,255).rgba();
    newColorVect[81]=QColor(191,63,63,255).rgba();
    newColorVect[82]=QColor(191,63,127,255).rgba();
    newColorVect[83]=QColor(191,63,191,255).rgba();
    newColorVect[84]=QColor(191,63,255,255).rgba();
    newColorVect[85]=QColor(191,127,0,255).rgba();
    newColorVect[86]=QColor(191,127,63,255).rgba();
    newColorVect[87]=QColor(191,127,127,255).rgba();
    newColorVect[88]=QColor(191,127,191,255).rgba();
    newColorVect[89]=QColor(191,127,255,255).rgba();
    newColorVect[90]=QColor(191,191,0,255).rgba();
    newColorVect[91]=QColor(191,191,63,255).rgba();
    newColorVect[92]=QColor(191,191,127,255).rgba();
    newColorVect[93]=QColor(191,191,191,255).rgba();
    newColorVect[94]=QColor(191,191,255,255).rgba();
    newColorVect[95]=QColor(191,255,0,255).rgba();
    newColorVect[96]=QColor(191,255,63,255).rgba();
    newColorVect[97]=QColor(191,255,127,255).rgba();
    newColorVect[98]=QColor(191,255,191,255).rgba();
    newColorVect[99]=QColor(191,255,255,255).rgba();
    newColorVect[100]=QColor(255,0,0,255).rgba();
    newColorVect[101]=QColor(255,0,63,255).rgba();
    newColorVect[102]=QColor(255,0,127,255).rgba();
    newColorVect[103]=QColor(255,0,191,255).rgba();
    newColorVect[104]=QColor(255,0,255,255).rgba();
    newColorVect[105]=QColor(255,63,0,255).rgba();
    newColorVect[106]=QColor(255,63,63,255).rgba();
    newColorVect[107]=QColor(255,63,127,255).rgba();
    newColorVect[108]=QColor(255,63,191,255).rgba();
    newColorVect[109]=QColor(255,63,255,255).rgba();
    newColorVect[110]=QColor(255,127,0,255).rgba();
    newColorVect[111]=QColor(255,127,63,255).rgba();
    newColorVect[112]=QColor(255,127,127,255).rgba();
    newColorVect[113]=QColor(255,127,191,255).rgba();
    newColorVect[114]=QColor(255,127,255,255).rgba();
    newColorVect[115]=QColor(255,191,0,255).rgba();
    newColorVect[116]=QColor(255,191,63,255).rgba();
    newColorVect[117]=QColor(255,191,127,255).rgba();
    newColorVect[118]=QColor(255,191,191,255).rgba();
    newColorVect[119]=QColor(255,191,255,255).rgba();
    newColorVect[120]=QColor(255,255,0,255).rgba();
    newColorVect[121]=QColor(255,255,63,255).rgba();
    newColorVect[122]=QColor(255,255,127,255).rgba();
    newColorVect[123]=QColor(255,255,191,255).rgba();
    newColorVect[124]=QColor(255,255,255,255).rgba();
    newColorVect[125]=QColor(0,0,0,127).rgba();
    newColorVect[126]=QColor(0,0,63,127).rgba();
    newColorVect[127]=QColor(0,0,127,127).rgba();
    newColorVect[128]=QColor(0,0,191,127).rgba();
    newColorVect[129]=QColor(0,0,255,127).rgba();
    newColorVect[130]=QColor(0,63,0,127).rgba();
    newColorVect[131]=QColor(0,63,63,127).rgba();
    newColorVect[132]=QColor(0,63,127,127).rgba();
    newColorVect[133]=QColor(0,63,191,127).rgba();
    newColorVect[134]=QColor(0,63,255,127).rgba();
    newColorVect[135]=QColor(0,127,0,127).rgba();
    newColorVect[136]=QColor(0,127,63,127).rgba();
    newColorVect[137]=QColor(0,127,127,127).rgba();
    newColorVect[138]=QColor(0,127,191,127).rgba();
    newColorVect[139]=QColor(0,127,255,127).rgba();
    newColorVect[140]=QColor(0,191,0,127).rgba();
    newColorVect[141]=QColor(0,191,63,127).rgba();
    newColorVect[142]=QColor(0,191,127,127).rgba();
    newColorVect[143]=QColor(0,191,191,127).rgba();
    newColorVect[144]=QColor(0,191,255,127).rgba();
    newColorVect[145]=QColor(0,255,0,127).rgba();
    newColorVect[146]=QColor(0,255,63,127).rgba();
    newColorVect[147]=QColor(0,255,127,127).rgba();
    newColorVect[148]=QColor(0,255,191,127).rgba();
    newColorVect[149]=QColor(0,255,255,127).rgba();
    newColorVect[150]=QColor(63,0,0,127).rgba();
    newColorVect[151]=QColor(63,0,63,127).rgba();
    newColorVect[152]=QColor(63,0,127,127).rgba();
    newColorVect[153]=QColor(63,0,191,127).rgba();
    newColorVect[154]=QColor(63,0,255,127).rgba();
    newColorVect[155]=QColor(63,63,0,127).rgba();
    newColorVect[156]=QColor(63,63,63,127).rgba();
    newColorVect[157]=QColor(63,63,127,127).rgba();
    newColorVect[158]=QColor(63,63,191,127).rgba();
    newColorVect[159]=QColor(63,63,255,127).rgba();
    newColorVect[160]=QColor(63,127,0,127).rgba();
    newColorVect[161]=QColor(63,127,63,127).rgba();
    newColorVect[162]=QColor(63,127,127,127).rgba();
    newColorVect[163]=QColor(63,127,191,127).rgba();
    newColorVect[164]=QColor(63,127,255,127).rgba();
    newColorVect[165]=QColor(63,191,0,127).rgba();
    newColorVect[166]=QColor(63,191,63,127).rgba();
    newColorVect[167]=QColor(63,191,127,127).rgba();
    newColorVect[168]=QColor(63,191,191,127).rgba();
    newColorVect[169]=QColor(63,191,255,127).rgba();
    newColorVect[170]=QColor(63,255,0,127).rgba();
    newColorVect[171]=QColor(63,255,63,127).rgba();
    newColorVect[172]=QColor(63,255,127,127).rgba();
    newColorVect[173]=QColor(63,255,191,127).rgba();
    newColorVect[174]=QColor(63,255,255,127).rgba();
    newColorVect[175]=QColor(127,0,0,127).rgba();
    newColorVect[176]=QColor(127,0,63,127).rgba();
    newColorVect[177]=QColor(127,0,127,127).rgba();
    newColorVect[178]=QColor(127,0,191,127).rgba();
    newColorVect[179]=QColor(127,0,255,127).rgba();
    newColorVect[180]=QColor(127,63,0,127).rgba();
    newColorVect[181]=QColor(127,63,63,127).rgba();
    newColorVect[182]=QColor(127,63,127,127).rgba();
    newColorVect[183]=QColor(127,63,191,127).rgba();
    newColorVect[184]=QColor(127,63,255,127).rgba();
    newColorVect[185]=QColor(127,127,0,127).rgba();
    newColorVect[186]=QColor(127,127,63,127).rgba();
    newColorVect[187]=QColor(127,127,127,127).rgba();
    newColorVect[188]=QColor(127,127,191,127).rgba();
    newColorVect[189]=QColor(127,127,255,127).rgba();
    newColorVect[190]=QColor(127,191,0,127).rgba();
    newColorVect[191]=QColor(127,191,63,127).rgba();
    newColorVect[192]=QColor(127,191,127,127).rgba();
    newColorVect[193]=QColor(127,191,191,127).rgba();
    newColorVect[194]=QColor(127,191,255,127).rgba();
    newColorVect[195]=QColor(127,255,0,127).rgba();
    newColorVect[196]=QColor(127,255,63,127).rgba();
    newColorVect[197]=QColor(127,255,127,127).rgba();
    newColorVect[198]=QColor(127,255,191,127).rgba();
    newColorVect[199]=QColor(127,255,255,127).rgba();
    newColorVect[200]=QColor(191,0,0,127).rgba();
    newColorVect[201]=QColor(191,0,63,127).rgba();
    newColorVect[202]=QColor(191,0,127,127).rgba();
    newColorVect[203]=QColor(191,0,191,127).rgba();
    newColorVect[204]=QColor(191,0,255,127).rgba();
    newColorVect[205]=QColor(191,63,0,127).rgba();
    newColorVect[206]=QColor(191,63,63,127).rgba();
    newColorVect[207]=QColor(191,63,127,127).rgba();
    newColorVect[208]=QColor(191,63,191,127).rgba();
    newColorVect[209]=QColor(191,63,255,127).rgba();
    newColorVect[210]=QColor(191,127,0,127).rgba();
    newColorVect[211]=QColor(191,127,63,127).rgba();
    newColorVect[212]=QColor(191,127,127,127).rgba();
    newColorVect[213]=QColor(191,127,191,127).rgba();
    newColorVect[214]=QColor(191,127,255,127).rgba();
    newColorVect[215]=QColor(191,191,0,127).rgba();
    newColorVect[216]=QColor(191,191,63,127).rgba();
    newColorVect[217]=QColor(191,191,127,127).rgba();
    newColorVect[218]=QColor(191,191,191,127).rgba();
    newColorVect[219]=QColor(191,191,255,127).rgba();
    newColorVect[220]=QColor(191,255,0,127).rgba();
    newColorVect[221]=QColor(191,255,63,127).rgba();
    newColorVect[222]=QColor(191,255,127,127).rgba();
    newColorVect[223]=QColor(191,255,191,127).rgba();
    newColorVect[224]=QColor(191,255,255,127).rgba();
    newColorVect[225]=QColor(255,0,0,127).rgba();
    newColorVect[226]=QColor(255,0,63,127).rgba();
    newColorVect[227]=QColor(255,0,127,127).rgba();
    newColorVect[228]=QColor(255,0,191,127).rgba();
    newColorVect[229]=QColor(255,0,255,127).rgba();
    newColorVect[230]=QColor(255,63,0,127).rgba();
    newColorVect[231]=QColor(255,63,63,127).rgba();
    newColorVect[232]=QColor(255,63,127,127).rgba();
    newColorVect[233]=QColor(255,63,191,127).rgba();
    newColorVect[234]=QColor(255,63,255,127).rgba();
    newColorVect[235]=QColor(255,127,0,127).rgba();
    newColorVect[236]=QColor(255,127,63,127).rgba();
    newColorVect[237]=QColor(255,127,127,127).rgba();
    newColorVect[238]=QColor(255,127,191,127).rgba();
    newColorVect[239]=QColor(255,127,255,127).rgba();
    newColorVect[240]=QColor(255,191,0,127).rgba();
    newColorVect[241]=QColor(255,191,63,127).rgba();
    newColorVect[242]=QColor(255,191,127,127).rgba();
    newColorVect[243]=QColor(255,191,191,127).rgba();
    newColorVect[244]=QColor(255,191,255,127).rgba();
    newColorVect[245]=QColor(255,255,0,127).rgba();
    newColorVect[246]=QColor(255,255,63,127).rgba();
    newColorVect[247]=QColor(255,255,127,127).rgba();
    newColorVect[248]=QColor(255,255,191,127).rgba();
    newColorVect[249]=QColor(255,255,255,127).rgba();
    newColorVect[250]=QColor(25,25,25,127).rgba();
    //Bis hier äquidistant, dann noch paar random Farben
    newColorVect[251]=QColor(100,100,100,255).rgba();
    newColorVect[252]=QColor(170,170,170,255).rgba();
    newColorVect[253]=QColor(225,225,225,225).rgba();
    newColorVect[254]=QColor(25,25,25,255).rgba();
    newColorVect[255]=QColor(255,255,255,0).rgba();
    QPixmap px(20, 20);
    for(int i = 0; i <256; i++){
        QPainter p(&px);
        QBrush br1(QColor(100,100,100));
        QBrush br2(QColor(200,200,200));
        QBrush br3(QColor(qRed(newColorVect[i]),qGreen(newColorVect[i]),qBlue(newColorVect[i]),qAlpha(newColorVect[i])));
        p.fillRect(0,0,10,10,br1);
        p.fillRect(10,10,10,10,br1);
        p.fillRect(0,10,10,10,br2);
        p.fillRect(10,0,10,10,br2);
        p.fillRect(0,0,20,20,br3);
        p.end();
        //px.fill(newColorVect[i]);
        if(i==drawColorIndex){
            QString str;
            str.sprintf("background-color: qlineargradient(stop:0 #%02x%02x%02x);",qRed(newColorVect[i]),qGreen(newColorVect[i]),qBlue(newColorVect[i]));
            colorButton->setStyleSheet(str);
        }

        colorAct[i]->setIcon(px);
        //colorAct[i]->setIcon(px);
    }
    actualColor = false;
    emit setNewColorVect(newColorVect);
}
void NewLayerDock::smallColorVect(){
    newColorVect = QVector<QRgb>();
    newColorVect.append(colorVect);
    newColorVect[0]=QColor(255,255,255,255).rgba();
    newColorVect[1]=QColor(127,127,127,255).rgba();
    newColorVect[2]=QColor(0,0,0,255).rgba();
    newColorVect[3]=QColor(0,255,255,255).rgba();
    newColorVect[4]=QColor(0,127,127,255).rgba();
    newColorVect[5]=QColor(127,255,255,255).rgba();
    newColorVect[6]=QColor(127,0,0,255).rgba();
    newColorVect[7]=QColor(255,127,127,255).rgba();
    newColorVect[8]=QColor(255,0,0,255).rgba();
    newColorVect[9]=QColor(255,0,255,255).rgba();
    newColorVect[10]=QColor(127,0,127,255).rgba();
    newColorVect[11]=QColor(255,127,255,255).rgba();
    newColorVect[12]=QColor(0,127,0,255).rgba();
    newColorVect[13]=QColor(127,255,127,255).rgba();
    newColorVect[14]=QColor(0,255,0,255).rgba();
    newColorVect[15]=QColor(255,255,0,255).rgba();
    newColorVect[16]=QColor(127,127,0,255).rgba();
    newColorVect[17]=QColor(255,255,127,255).rgba();
    newColorVect[18]=QColor(0,0,127,255).rgba();
    newColorVect[19]=QColor(127,127,255,255).rgba();
    newColorVect[20]=QColor(0,0,255,255).rgba();
    for (int i = 21; i < 255; i++) {
        newColorVect[i]=QColor(255,255,255,255).rgba();
    }
    newColorVect[255]=QColor(255,255,255,0).rgba();
    QPixmap px(20, 20);
    for(int i = 0; i <256; i++){

        QPainter p(&px);
        QBrush br1(QColor(100,100,100));
        QBrush br2(QColor(200,200,200));
        QBrush br3(QColor(qRed(newColorVect[i]),qGreen(newColorVect[i]),qBlue(newColorVect[i]),qAlpha(newColorVect[i])));
        p.fillRect(0,0,10,10,br1);
        p.fillRect(10,10,10,10,br1);
        p.fillRect(0,10,10,10,br2);
        p.fillRect(10,0,10,10,br2);
        p.fillRect(0,0,20,20,br3);
        p.end();
        if(i==drawColorIndex){
            QString str;
            str.sprintf("background-color: qlineargradient(stop:0 #%02x%02x%02x);",qRed(newColorVect[i]),qGreen(newColorVect[i]),qBlue(newColorVect[i]));
            colorButton->setStyleSheet(str);
        }

        //colorAct[i]->setIcon(px);
        colorAct[i]->setIcon(px);
    }
    actualColor = false;
    emit setNewColorVect(newColorVect);
}
void NewLayerDock::customColorVect(){
    newColorVect = QVector<QRgb>();
    newColorVect.append(colorVect);

    QPixmap px(20, 20);
    for(int i = 0; i <256; i++){

        QPainter p(&px);
        QBrush br1(QColor(100,100,100));
        QBrush br2(QColor(200,200,200));
        QBrush br3(QColor(qRed(newColorVect[i]),qGreen(newColorVect[i]),qBlue(newColorVect[i]),qAlpha(newColorVect[i])));
        p.fillRect(0,0,10,10,br1);
        p.fillRect(10,10,10,10,br1);
        p.fillRect(0,10,10,10,br2);
        p.fillRect(10,0,10,10,br2);
        p.fillRect(0,0,20,20,br3);
        p.end();
        if(i==drawColorIndex){
            QString str;
            str.sprintf("background-color: qlineargradient(stop:0 #%02x%02x%02x);",qRed(newColorVect[i]),qGreen(newColorVect[i]),qBlue(newColorVect[i]));
            colorButton->setStyleSheet(str);
        }

        colorAct[i]->setIcon(px);
        //colorAct[i]->setIcon(px);
    }
    actualColor = false;
    emit setNewColorVect(newColorVect);
}
void NewLayerDock::addNewLayer(){
    QImage *newImage = nullptr;
    //QVector<QRgb> newColorVect;//TODO: make color vectorsto pointer
    if(newColormap[0]->isChecked()){
        newColorVect = QVector<QRgb>();
        newColorVect.append(colorVect);
    }
    if (isNewLayerColor){
        newImage = new QImage(newLayerX,newLayerY,QImage::Format_ARGB32);
        newImage->fill(QColor(newLayerColor));
        param = new toolParameters_t;
        param->tool = tools_e::newLayer;
        param->pic = newImage;

        param->colorVect = newColorVect;
        interactionTool->useTool(param);
        param = nullptr;
        newImage=interactionTool->getPicture()->getCurrentLayerAsQ();
    } else{
        newImage = new QImage(newLayerX,newLayerY,QImage::Format_Indexed8);
        newImage->setColorTable(newColorVect);
        newImage->fill(drawColorIndex);
        interactionTool->getPicture()->addCurrentLayer(newImage);
    }

    //

    //if (newImage==nullptr){
    //    return;
    //}
    //setImage(*newImage);
    //setImage(*interactionTool->getPicture()->getCurrentLayerAsQ());
    //updateColors();
    //updateLayerCount();
    //updateVisible();
    emit updateHasLayer(true);
    emit update();
    newColorVect = QVector<QRgb>();
    newColorVect.append(colorVect);
    //statusBar()->showMessage(message);
    //hasLayer=true;

}
void NewLayerDock::setNewColor(){
    newLayerColor=QColorDialog().getColor(Qt::white,nullptr,QString(""),QColorDialog::ShowAlphaChannel).rgba();
    QString str;
    //str.append(qRed(colorVect[i]));
    //str.append(";");
    //str.sprintf("#%02x%02x%02x",qRed(colorVect[i]),qGreen(colorVect[i]),qBlue(colorVect[i]));
    str.sprintf("background-color: qlineargradient(stop:0.5 #%02x%02x%02x);",qRed(newLayerColor),qGreen(newLayerColor),qBlue(newLayerColor));
    //printf("background-color: #%02x%02x%02x;\n",qRed(colorVect[i]),qGreen(colorVect[i]),qBlue(colorVect[i]));
    newColorButton->setStyleSheet(str);
}
void NewLayerDock::setNewLayerX(int w){
    newLayerXSpinbox->setValue(w);
    newLayerXSlider->setValue(w);
    newLayerX=w;
}
void NewLayerDock::setNewLayerY(int w){
    newLayerYSpinbox->setValue(w);
    newLayerYSlider->setValue(w);
    newLayerY=w;
}
QDockWidget *NewLayerDock::createNewLayerDock(){
    dockWidget = new QDockWidget(tr("New layer"));
    dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    newLayerLayout = new QGridLayout(); //TODO: make private
    QLabel *label1 = new QLabel("Size-x:");
    newLayerLayout->addWidget(label1,0,0,1,1);
    newLayerLayout->addWidget(newLayerXSpinbox,0,1,1,1);
    newLayerLayout->addWidget(newLayerXSlider,1,0,1,2);
    QLabel *label2 = new QLabel("Size-y:");
    newLayerLayout->addWidget(label2,2,0,1,1);
    newLayerLayout->addWidget(newLayerYSpinbox,2,1,1,1);
    newLayerLayout->addWidget(newLayerYSlider,3,0,1,2);
    QLabel *label3 = new QLabel("Color:");
    newLayerLayout->addWidget(label3,9,0,1,1);

    QRadioButton *button1 = new QRadioButton("Existing Color");
    button1->setChecked(true);
    connect(button1, SIGNAL(clicked()),this, SLOT(existingColor()));
    newLayerLayout->addWidget(button1,10,0,1,1);
    QRadioButton *button2 = new QRadioButton("New Color");
    connect(button2, SIGNAL(clicked()),this, SLOT(newColor()));
    newLayerLayout->addWidget(button2,11,0,1,1);
    newLayerLayout->addWidget(colorButton,10,1,1,1);
    newLayerLayout->addWidget(newColorButton,11,1,1,1);
    QLabel *label4 = new QLabel("Colormap:");
    newLayerLayout->addWidget(label4,4,0,1,2);
    QButtonGroup *buttonGroup = new QButtonGroup();

    newColormap[0] = new QRadioButton("actual");
    newColormap[0]->setChecked(true);
    buttonGroup->addButton(newColormap[0]);
    connect(newColormap[0], SIGNAL(clicked()),this, SLOT(actualColorVect()));
    newLayerLayout->addWidget(newColormap[0],5,0,1,2);
    newColormap[1] = new QRadioButton("standart");
    buttonGroup->addButton(newColormap[1]);
    connect(newColormap[1], SIGNAL(clicked()),this, SLOT(standartColorVect()));
    newLayerLayout->addWidget(newColormap[1],6,0,1,2);
    newColormap[2] = new QRadioButton("small");
    buttonGroup->addButton(newColormap[2]);
    connect(newColormap[2], SIGNAL(clicked()),this, SLOT(smallColorVect()));
    newLayerLayout->addWidget(newColormap[2],7,0,1,2);
    newColormap[3] = new QRadioButton("modificated");
    buttonGroup->addButton(newColormap[3]);
    connect(newColormap[3], SIGNAL(clicked()),this, SLOT(customColorVect()));
    newLayerLayout->addWidget(newColormap[3],8,0,1,2);

    QPushButton *button3 = new QPushButton("Add new layer");
    connect(button3, SIGNAL(clicked()),this, SLOT(addNewLayer()));
    newLayerLayout->addWidget(button3,12,0,1,2);

    QSpacerItem *spacer = new QSpacerItem(1,300,QSizePolicy::Maximum,QSizePolicy::Maximum);
    newLayerLayout->addItem(spacer,13,1,1,3);

    QWidget *drawControl = new QWidget(dockWidget);
    drawControl->setLayout(newLayerLayout);
    dockWidget->setWidget(drawControl);
    //addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
    return dockWidget;
}
void NewLayerDock::setColorVect(QVector<QRgb> colorVect){

    for (int i = 0; i < 256; i++) {
        newColorVect[i]=colorVect[i];
        this->colorVect[i]=colorVect[i];
    }
    QPixmap px(20, 20);
    //colorVect = interactionTool->getPicture()->getCurrentLayerAsQ()->colorTable();
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

        //colorButtons[i]->setIcon(px);
        QString str;
        //str.append(qRed(colorVect[i]));
        //str.append(";");
        str.sprintf("background-color: qlineargradient(stop:0 #%02x%02x%02x);",qRed(colorVect[i]),qGreen(colorVect[i]),qBlue(colorVect[i]));
        //printf("background-color: #%02x%02x%02x;\n",qRed(colorVect[i]),qGreen(colorVect[i]),qBlue(colorVect[i]));
        if(i==drawColorIndex){
            QString str;
            str.sprintf("background-color: qlineargradient(stop:0 #%02x%02x%02x);",qRed(newColorVect[i]),qGreen(newColorVect[i]),qBlue(newColorVect[i]));
            colorButton->setStyleSheet(str);
        }

        colorAct[i]->setIcon(px);
    }
    if(actualColor){
        newColorVect = QVector<QRgb>();
        //for (int i = 0; i < 256; i++) {
        newColorVect.append(colorVect);
    }

    //}
}
//void NewLayerDock::setDrawColorIndex(int i){
//    drawColorIndex = i;
//}
//QDockWidget *NewLayerDock::getDockWidget(){
//    return dockWidget;
//}
void NewLayerDock::setNewLayerColor(){
    for (int i = 0; i < 256; i++) {
        if (colorAct[i]->isChecked()){
            colorAct[i]->setChecked(false);
            drawColorIndex = i;
            QString str;
            //str.append(qRed(colorVect[i]));
            //str.append(";");
            str.sprintf("background-color: qlineargradient(stop:0 #%02x%02x%02x);",qRed(newColorVect[i]),qGreen(newColorVect[i]),qBlue(newColorVect[i]));
            //printf("background-color: #%02x%02x%02x;\n",qRed(colorVect[i]),qGreen(colorVect[i]),qBlue(colorVect[i]));
            colorButton->setStyleSheet(str);
            //QString str;
            //str.sprintf("%d",i);
            //statusBar()->showMessage(str);
        }
    }
}
