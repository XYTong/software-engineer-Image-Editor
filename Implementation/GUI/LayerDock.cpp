#include "LayerDock.h"

LayerDock::LayerDock(InteractionTool *interaction){
    interactionTool = interaction;
    createLayerDock();
}
LayerDock::~LayerDock(){

}
void LayerDock::updateLayers(){
    for (unsigned int i = 0; i < interactionTool->getPicture()->getLayerCount(); i++) {
        QPixmap pic;
        pic.convertFromImage(*interactionTool->getPicture()->getLayerAsQ(i));
        layerButtons[i*5+1]->setIcon(pic);
        layerButtons[i*5+1]->setChecked(false);
    }
    layerButtons[interactionTool->getPicture()->getCurrentLayerIndex()*5+1]->setChecked(true);
    if(interactionTool->getPicture()->getLayerCount()>1){
        layerButtons[interactionTool->getPicture()->getCurrentLayerIndex()*5+3]->setEnabled(false);
    }

}
void LayerDock::updateLayerCount(){

    layerButtons = std::vector<QPushButton*>(); //TODO vector zu Qvector ändern
    layerCheckboxes = std::vector<QCheckBox*>();
    layerDock = new QDockWidget(tr("Layers"));
    layerDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    layerLayout = new QGridLayout();
    layerButtons.push_back(new QPushButton("+"));
    layerLayout->addWidget(layerButtons[0],0,0,2,2);
    layerButtons[0]->setMaximumWidth(25);
    layerButtons[0]->setCheckable(true);
    connect(layerButtons[0], SIGNAL(clicked()),this, SLOT(changeCurrentLayer()));
    for (unsigned int i = 0; i < interactionTool->getPicture()->getLayerCount(); i++) {
        layerButtons.push_back(new QPushButton);
        QPixmap pic(100,100);
        pic.convertFromImage(*interactionTool->getPicture()->getLayerAsQ(i));
        layerButtons[i*5+1]->setIconSize(QSize(100,100));
        layerButtons[i*5+1]->setIcon(pic);
        layerLayout->addWidget(layerButtons[i*5+1],i*5+1,2,5,1);
        layerButtons[i*5+1]->setCheckable(true);
        connect(layerButtons[i*5+1], SIGNAL(clicked()),this, SLOT(changeCurrentLayer()));
        layerButtons.push_back(new QPushButton("^"));
        layerLayout->addWidget(layerButtons[i*5+2],i*5+2,0,1,2);
        layerButtons[i*5+2]->setMaximumWidth(25);
        layerButtons[i*5+2]->setCheckable(true);
        if (i==0){
            layerButtons[i*5+2]->setEnabled(false);
        }
        connect(layerButtons[i*5+2], SIGNAL(clicked()),this, SLOT(changeCurrentLayer()));
        layerButtons.push_back(new QPushButton("-"));
        layerLayout->addWidget(layerButtons[i*5+3],i*5+3,0,1,1);
        layerButtons[i*5+3]->setMaximumWidth(25);
        layerButtons[i*5+3]->setCheckable(true);
        connect(layerButtons[i*5+3], SIGNAL(clicked()),this, SLOT(changeCurrentLayer()));
        layerCheckboxes.push_back(new QCheckBox());
        layerLayout->addWidget(layerCheckboxes[i],i*5+3,1,1,1);
        layerCheckboxes[i]->setChecked(true);
        connect(layerCheckboxes[i], SIGNAL(clicked()),this, SLOT(updateVisible()));
        layerButtons.push_back(new QPushButton("v"));
        layerLayout->addWidget(layerButtons[i*5+4],i*5+4,0,1,2);
        layerButtons[i*5+4]->setMaximumWidth(25);
        layerButtons[i*5+4]->setCheckable(true);
        if (i+1==interactionTool->getPicture()->getLayerCount()){
            layerButtons[i*5+4]->setEnabled(false);
        }
        connect(layerButtons[i*5+4], SIGNAL(clicked()),this, SLOT(changeCurrentLayer()));
        layerButtons.push_back(new QPushButton("+"));
        layerLayout->addWidget(layerButtons[i*5+5],i*5+5,0,2,2);
        layerButtons[i*5+5]->setMaximumWidth(25);
        layerButtons[i*5+5]->setCheckable(true);
        connect(layerButtons[i*5+5], SIGNAL(clicked()),this, SLOT(changeCurrentLayer()));
    }
    layerButtons[interactionTool->getPicture()->getCurrentLayerIndex()*5+1]->setChecked(true);
        layerButtons[interactionTool->getPicture()->getCurrentLayerIndex()*5+3]->setEnabled(false);
    //}
    layers = new QWidget(layerDock);
    layers->setLayout(layerLayout);
    layerScrollArea = new QScrollArea();
    layerScrollArea->setWidget(layers);
    layerDock->setWidget(layerScrollArea);
    emit updateLayerDock();
    layerDock->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable);
}
void LayerDock::changeCurrentLayer(){
    if (layerButtons[0]->isChecked()){
        emit newLayer();
        layerButtons[0]->setChecked(false);
    }
    for (int i = 0; i < interactionTool->getPicture()->getLayerCount(); i++) {
        if (layerButtons[i*5+1]->isChecked()&&i!=interactionTool->getPicture()->getCurrentLayerIndex()){
            layerButtons[interactionTool->getPicture()->getCurrentLayerIndex()*5+1]->setChecked(false);
            layerButtons[interactionTool->getPicture()->getCurrentLayerIndex()*5+3]->setEnabled(true);
            interactionTool->getPicture()->setCurrentLayer(i);
            emit update();
            layerButtons[interactionTool->getPicture()->getCurrentLayerIndex()*5+3]->setEnabled(false);
        } else if(layerButtons[i*5+2]->isChecked()){
            interactionTool->getPicture()->moveLayer(i,i-1);
            updateLayers();
            layerButtons[i*5+2]->setChecked(false);
            //updateVisible();
            emit update();
        } else if(layerButtons[i*5+3]->isChecked()){
            layerButtons[i*5+3]->setChecked(false);
            interactionTool->getPicture()->removeLayer(i);
            if(interactionTool->getPicture()->getLayerCount()==0){//TODO

            }
            updateLayerCount();
            emit update();
        } else if(layerButtons[i*5+4]->isChecked()){
            interactionTool->getPicture()->moveLayer(i+1,i);
            updateLayers();
            layerButtons[i*5+4]->setChecked(false);
            emit update();
        } else if(layerButtons[i*5+5]->isChecked()&&i+1!=interactionTool->getPicture()->getLayerCount()){
            layerButtons[i*5+5]->setChecked(false);
            param = new toolParameters_t;
            param->tool = merge;
            param->layerIndex1 = i;
            param->layerIndex2 = i+1;
            this->i=i;

            emit getParams(param);

        } else if(layerButtons[i*5+5]->isChecked()&&i+1==interactionTool->getPicture()->getLayerCount()){
            newLayer();
            layerButtons[i*5+5]->setChecked(false);
        }
    }
}
void LayerDock::createLayerDock(){
    layerDock = new QDockWidget(tr("Layers"));
    layerDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    layerLayout = new QGridLayout();
    layerButtons.push_back(new QPushButton("+"));
    layerLayout->addWidget(layerButtons[0],0,0,2,1);
    layerButtons[0]->setMaximumWidth(25);
    layerButtons[0]->setCheckable(true);
    connect(layerButtons[0], SIGNAL(clicked()),this, SLOT(changeCurrentLayer()));
    layers = new QWidget(layerDock);
    layers->setLayout(layerLayout);
    layerScrollArea = new QScrollArea();
    layerScrollArea->setWidget(layers);
    layerDock->setWidget(layerScrollArea);
    layerDock->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable);
}

QDockWidget *LayerDock::getDockWidget(){
    return layerDock;
}
bool LayerDock::isLayerCheckboxChecked(int i){
    return layerCheckboxes[i]->isChecked();
}
void LayerDock::doMergeII(toolParameters_t *param){
    interactionTool->useTool(param);
    interactionTool->getPicture()->removeLayer(i+1);
    interactionTool->getPicture()->removeLayer(i);
    param = nullptr;
    updateLayerCount();
    emit update();
}
void LayerDock::updateVisible(){
    emit update();
}
