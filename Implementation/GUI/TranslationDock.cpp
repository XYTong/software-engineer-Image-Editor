#include "TranslationDock.h"

TranslationDock::TranslationDock(InteractionTool *interaction):QObject(){
    translationLabelA = new QLabel("a");
    translationLabelB = new QLabel("b");
    translationLabelC = new QLabel("c");
    translationLabelD = new QLabel("d");
    mirrorCheckbox = new QCheckBox();
    zoomXInp = new QLineEdit();
    zoomYInp = new QLineEdit();
    rotInp = new QLineEdit();
    interactionTool = interaction;
    createTranslateDock();
}
TranslationDock::~TranslationDock(){
    delete translationLabelA;
    delete translationLabelB;
    delete translationLabelC;
    delete translationLabelD;
    delete mirrorCheckbox;
    delete zoomXInp;
    delete zoomYInp;
    delete rotInp;
    delete dockWidget;
}
QDockWidget *TranslationDock::createTranslateDock(){
    dockWidget = new QDockWidget(tr("Translation"));
    dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    QGridLayout *translationLayout = new QGridLayout();
    QLabel *label1 = new QLabel("zoom-x:");
    translationLayout->addWidget(label1,0,0,1,3);

    translationLayout->addWidget(zoomXInp,1,0,1,3);
    QLabel *label2 = new QLabel("zoom-y:");
    translationLayout->addWidget(label2,2,0,1,3);

    translationLayout->addWidget(zoomYInp,3,0,1,3);
    QLabel *label3 = new QLabel("rotate\nclockwise:");
    translationLayout->addWidget(label3,4,0,1,3);

    translationLayout->addWidget(rotInp,5,0,1,3);
    QLabel *label4 = new QLabel("mirrored:");
    translationLayout->addWidget(label4,6,0,1,1);

    translationLayout->addWidget(mirrorCheckbox,6,1,1,2);
    QPushButton *input5 = new QPushButton("Calculate");
    connect(input5, SIGNAL(clicked()), this, SLOT(calcTranslation()));
    //translationLayout->addWidget(input5,7,0,1,3);
    QLabel *label5 = new QLabel("Matrix entries:");

    //translationLayout->addWidget(label5,8,0,2,1);

    //translationLayout->addWidget(translationLabelA,8,1,1,1);

    //translationLayout->addWidget(translationLabelB,8,2,1,1);

    //translationLayout->addWidget(translationLabelC,9,1,1,1);

    //translationLayout->addWidget(translationLabelD,9,2,1,1);
    QPushButton *input6 = new QPushButton("Apply");
    connect(input6, SIGNAL(clicked()), this, SLOT(doTranslationI()));
    translationLayout->addWidget(input6,10,0,1,3);
    QSpacerItem *spacer = new QSpacerItem(1,300,QSizePolicy::Maximum,QSizePolicy::Maximum);
    translationLayout->addItem(spacer,11,1,1,3);
    QWidget *drawControl = new QWidget(dockWidget);
    drawControl->setLayout(translationLayout);
    dockWidget->setWidget(drawControl);
    //addDockWidget(Qt::LeftDockWidgetArea, translationDock);
    //mainWindow->addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
    return dockWidget;
}

/*void  TranslationDock::translate(){
    createTranslateDock();
};*/
void TranslationDock::calcTranslation(){
    translationLabelA->setText("a");
    translationLabelB->setText("b");
    translationLabelC->setText("c");
    translationLabelD->setText("d");
    double zx=0,zy=0,rot=0;
    bool *ok = new bool;
    zx = zoomXInp->text().toDouble(ok);
    if(!zoomXInp->text().compare("")){
        *ok = true;
        zx=1;
    }
    if (!*ok){
        return;
    }
    zy = zoomYInp->text().toDouble(ok);
    if(!zoomYInp->text().compare("")){
        *ok = true;
        zy=1;
    }
    if (!*ok){
        return;
    }
    rot = rotInp->text().toDouble(ok);
    if(!rotInp->text().compare("")){
        *ok = true;
        rot=0;
    }
    if (!*ok){
        return;
    }
    transMat = new QMatrix(zx,0,0,zy,0,0);
    QMatrix mat;
    mat.rotate(rot);
    if(rot!=0){
        isRot=true;
    }else{
        isRot=false;
    }
    *transMat = *transMat *mat;
    if (mirrorCheckbox->isChecked()){
        mat.setMatrix(0,1,1,0,0,0);
        *transMat *= mat;
    }
    QString str;
    str.sprintf("%lf",transMat->m11());
    translationLabelA->setText(str);
    str.sprintf("%lf",transMat->m12());
    translationLabelB->setText(str);
    str.sprintf("%lf",transMat->m21());
    translationLabelC->setText(str);
    str.sprintf("%lf",transMat->m22());
    translationLabelD->setText(str);
}
void TranslationDock::doTranslationI(){
    //unsigned int i = interactionTool->getPicture()->getCurrentLayerIndex();
    translationLabelA->setText("a");
    translationLabelB->setText("b");
    translationLabelC->setText("c");
    translationLabelD->setText("d");
    double zx=0,zy=0,rot=0;
    bool *ok = new bool;
    zx = zoomXInp->text().toDouble(ok);
    if(!zoomXInp->text().compare("")){
        *ok = true;
        zx=1;
    }
    if (!*ok){
        return;
    }
    zy = zoomYInp->text().toDouble(ok);
    if(!zoomYInp->text().compare("")){
        *ok = true;
        zy=1;
    }
    if (!*ok){
        return;
    }
    rot = rotInp->text().toDouble(ok);
    if(!rotInp->text().compare("")){
        *ok = true;
        rot=0;
    }
    if (!*ok){
        return;
    }
    transMat = new QMatrix(zx,0,0,zy,0,0);
    QMatrix mat;
    mat.rotate(rot);
    if(rot!=0){
        isRot=true;
    }else{
        isRot=false;
    }
    *transMat = *transMat *mat;
    if (mirrorCheckbox->isChecked()){
        mat.setMatrix(0,1,1,0,0,0);
        *transMat *= mat;
    }
    QString str;
    str.sprintf("%lf",transMat->m11());
    translationLabelA->setText(str);
    str.sprintf("%lf",transMat->m12());
    translationLabelB->setText(str);
    str.sprintf("%lf",transMat->m21());
    translationLabelC->setText(str);
    str.sprintf("%lf",transMat->m22());
    translationLabelD->setText(str);
    param = new toolParameters_t;
    param->tool = translationTool;
    param->mat = *transMat;
    param->isRot = isRot;
    emit getParams(param);
    //param->colorVect = mainWindow->getColorVect();
    //interactionTool->useTool(param);
    //param = nullptr;
    //interactionTool->getPicture()->removeLayer(i);
    //mainWindow->updateLayerCount();
    //mainWindow->updateColors();
    //setImage(*interactionTool.getPicture()->getCurrentLayerAsQ());
    //mainWindow->updateVisible();
    //emit update();
}
//void TranslationDock::init(ImageViewer *mainWindow){
//    this->mainWindow = mainWindow;
//}
//QDockWidget *TranslationDock::getDockWidget(){
//    return dockWidget;
//}
void TranslationDock::doTranslationII(toolParameters_t *param){
    this->param = param;
    unsigned int i = interactionTool->getPicture()->getCurrentLayerIndex();
    interactionTool->useTool(param);
    param = nullptr;
    interactionTool->getPicture()->removeLayer(i);
    //mainWindow->updateLayerCount();
    //mainWindow->updateColors();
    //setImage(*interactionTool.getPicture()->getCurrentLayerAsQ());
    //mainWindow->updateVisible();
    emit update();
}
