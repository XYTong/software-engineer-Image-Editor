#include "imageviewer.h"
#include <QtWidgets>
#include <cstdlib>

ImageViewer::ImageViewer(QWidget *parent)
   : QMainWindow(parent), imageLabel(new QLabel),
     scrollArea(new QScrollArea), scaleFactor(1)
{
    interactionTool = new InteractionTool();
    imageLabel->setBackgroundRole(QPalette::Dark);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    setCentralWidget(scrollArea);
    createActions();
    colorVect = QVector<QRgb>();
    newLayerDock = new NewLayerDock(interactionTool);
    connect(newLayerDock,&NewLayerDock::update,this,&ImageViewer::updateall);
    connect(newLayerDock,QOverload<bool>::of(&NewLayerDock::updateHasLayer),this,&ImageViewer::updateHasLayer);
    connect(newLayerDock,QOverload<QVector<QRgb>>::of(&NewLayerDock::setNewColorVect),this,&ImageViewer::updateNewColorVector);
    drawDock = new DrawDock(interactionTool);
    connect(drawDock,&DrawDock::updateVisible,this,&ImageViewer::updateVisible);
    connect(drawDock,QOverload<para1>::of(&DrawDock::drawShowI),this,&ImageViewer::drawShowI);
    connect(drawDock,QOverload<para2>::of(&DrawDock::drawShowII),this,&ImageViewer::drawShowII);
    transLationDock = new TranslationDock(interactionTool);
    connect(transLationDock,QOverload<toolParameters_t*>::of(&TranslationDock::getParams),this,&ImageViewer::setTranslationParams);
    connect(transLationDock,&TranslationDock::update,this,&ImageViewer::updateall);
    colorDock = new ColorDock(interactionTool);
    connect(colorDock,&ColorDock::updateVisible,this,&ImageViewer::updateVisible);
    connect(colorDock,QOverload<QVector<QRgb>>::of(&ColorDock::updateColorVect),this,&ImageViewer::updateColorVector);
    addDockWidget(Qt::BottomDockWidgetArea, colorDock->getDockWidget());
    layerDock = new LayerDock(interactionTool);
    connect(layerDock,&LayerDock::updateLayerDock,this,&ImageViewer::updateLayerDock);
    connect(layerDock,&LayerDock::newLayer,this,&ImageViewer::newLayer);
    connect(layerDock,&LayerDock::update,this,&ImageViewer::updateWithoutLayer);
    connect(layerDock,QOverload<toolParameters_t*>::of(&LayerDock::getParams),this,&ImageViewer::setMergeParams);
    addDockWidget(Qt::RightDockWidgetArea, layerDock->getDockWidget());
    connect(colorDock,&ColorDock::updateLayers,layerDock,&LayerDock::updateLayers);
    connect(drawDock,&DrawDock::updateLayer,layerDock,&LayerDock::updateLayers);
    newColorVect = QVector<QRgb>();
    colorVect = colorDock->getColorVect();
    newColorVect.append(colorVect);
    newLayerDock->setColorVect(colorVect);
    drawDock->setColorVect(colorVect);
    colorDock->setColorVect(colorVect);
    layerDockW = layerDock->getDockWidget();
    resize(QGuiApplication::primaryScreen()->availableSize() * 4 / 5);
}

bool ImageViewer::loadFile(const QString &fileName){
    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    QImage *newImage = new QImage;
    *newImage = reader.read();
    if (newImage->isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName), reader.errorString()));
        return false;
    }
    param = new toolParameters_t;
    param->tool=tools_e::newLayer;
    param->pic = newImage;
    param->colorVect = newColorVect;
    interactionTool->useTool(param);
    param = nullptr;
    newImage = interactionTool->getPicture()->getCurrentLayerAsQ();
    if (newImage==nullptr){
        return false;
    }

    return true;
}

void ImageViewer::setImage(QImage newImage){//remove Parameter
    image = newImage;
    imageLabel->setPixmap(QPixmap::fromImage(image));
    fitToWindowAct->setEnabled(true);
    updateActions();
    if (!fitToWindowAct->isChecked())
        imageLabel->adjustSize();
}

bool ImageViewer::saveFile(const QString &fileName){
    QImageWriter writer(fileName);
    QPixmap *px = new QPixmap(interactionTool->getPicture()->getMaxSize()-interactionTool->getPicture()->getMinOffset());
    px->fill(QColor(0,0,0,0));
    QPainter *painter= new QPainter(px);
    for (int i = 0; i < interactionTool->getPicture()->getLayerCount(); i++) {
        if (layerDock->isLayerCheckboxChecked(i)){
            painter->drawImage(interactionTool->getPicture()->xOffset(i)-interactionTool->getPicture()->getMinOffset().width(),interactionTool->getPicture()->yOffset(i)-interactionTool->getPicture()->getMinOffset().height(),*interactionTool->getPicture()->getLayerAsQ(i));
            //painter->drawI
        }
    }
    if (!writer.write(px->toImage())) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot write %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName)), writer.errorString());
        return false;
    }
    const QString message = tr("Wrote \"%1\"").arg(QDir::toNativeSeparators(fileName));
    statusBar()->showMessage(message);
    return true;
}

static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode){
    static bool firstDialog = true;
    if (firstDialog) {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }
    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
        ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();
    for (const QByteArray &mimeTypeName : supportedMimeTypes)
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");
    if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix("jpg");
}

void ImageViewer::open(){
    QFileDialog dialog(this, tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);
    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
    hasLayer=true;
    colorDock->updateColors();
    layerDock->updateLayerCount();
    updateVisible();
}

void ImageViewer::saveAs(){
    QFileDialog dialog(this, tr("Save File As"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptSave);
    while (dialog.exec() == QDialog::Accepted && !saveFile(dialog.selectedFiles().first())) {}
}

void ImageViewer::zoomIn(){
    scaleImage(1.25);
}

void ImageViewer::zoomOut(){
    scaleImage(0.8);
}

void ImageViewer::normalSize(){
    imageLabel->adjustSize();
    scaleFactor = 1.0;
}

void ImageViewer::fitToWindow(){
    bool fitToWindow = fitToWindowAct->isChecked();
    scrollArea->setWidgetResizable(fitToWindow);
    if (!fitToWindow)
        normalSize();
    updateActions();
}

void ImageViewer::about(){
    QMessageBox::about(this, tr("About Image Viewer"),"");
}

void ImageViewer::createActions(){
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QAction *openAct = fileMenu->addAction(tr("&Open..."), this, &ImageViewer::open);
    openAct->setShortcut(QKeySequence::Open);
    saveAsAct = fileMenu->addAction(tr("&Save As..."), this, &ImageViewer::saveAs);
    saveAsAct->setEnabled(false);
    fileMenu->addSeparator();
    QAction *exitAct = fileMenu->addAction(tr("E&xit"), this, &QWidget::close);
    exitAct->setShortcut(tr("Ctrl+Q"));
    QMenu *viewMenu = menuBar()->addMenu(tr("&View"));
    zoomInAct = viewMenu->addAction(tr("Zoom &In (25%)"), this, &ImageViewer::zoomIn);
    zoomInAct->setShortcut(QKeySequence::ZoomIn);
    zoomInAct->setEnabled(false);
    zoomOutAct = viewMenu->addAction(tr("Zoom &Out (25%)"), this, &ImageViewer::zoomOut);
    zoomOutAct->setShortcut(QKeySequence::ZoomOut);
    zoomOutAct->setEnabled(false);
    normalSizeAct = viewMenu->addAction(tr("&Normal Size"), this, &ImageViewer::normalSize);
    normalSizeAct->setShortcut(tr("Ctrl+S"));
    normalSizeAct->setEnabled(false);
    viewMenu->addSeparator();
    //fitToWindowAct = viewMenu->addAction(tr("&Fit to Window"), this, &ImageViewer::fitToWindow);
    //fitToWindowAct->setEnabled(false);
    //fitToWindowAct->setCheckable(true);
    //fitToWindowAct->setShortcut(tr("Ctrl+F"));
    QMenu *toolMenu = menuBar()->addMenu(tr("&Tools"));
    drawToolAct = toolMenu->addAction(tr("&Draw"), this, &ImageViewer::draw);
    drawToolAct->setEnabled(false);
    newLayerAct = toolMenu->addAction(tr("&New Layer"), this, &ImageViewer::newLayer);
    translateAct = toolMenu->addAction(tr("&Translate"), this, &ImageViewer::translate);
    translateAct->setEnabled(false);
    makeToShaped = toolMenu->addAction(tr("&Make Shaped"), this, &ImageViewer::makeShaped);
    makeToShaped->setEnabled(false);
    makeToShaped->setCheckable(true);
    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(tr("&About"), this, &ImageViewer::about);
    helpMenu->addAction(tr("About &Qt"), &QApplication::aboutQt);
}

void ImageViewer::updateActions(){
    zoomInAct->setEnabled(!fitToWindowAct->isChecked());
    zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
    normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
    drawToolAct->setEnabled(hasLayer);
    translateAct->setEnabled(hasLayer);
    makeToShaped->setEnabled(hasLayer);
}

void ImageViewer::scaleImage(double factor){
    Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());
    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);
    zoomInAct->setEnabled(scaleFactor < 3.0);
    zoomOutAct->setEnabled(scaleFactor > 0.333);
}

void ImageViewer::adjustScrollBar(QScrollBar *scrollBar, double factor){
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}

void ImageViewer::draw(){
    addDockWidget(Qt::LeftDockWidgetArea, drawDock->createDrawDock());
}

void ImageViewer::mousePressEvent(QMouseEvent *event){
    if(drawDock->mouseEvent(event,press,scrollArea->x(),scrollArea->horizontalScrollBar()->value(),scrollArea->y(),scrollArea->verticalScrollBar()->value())){
    } else
    if (event->button() == Qt::LeftButton && interactionTool->getPicture()->hasLayer()){
        moveStart=true;

        move = event->pos()-QPoint(scrollArea->x()-scrollArea->horizontalScrollBar()->value(),scrollArea->y()-scrollArea->verticalScrollBar()->value());
    }
}

void ImageViewer::mouseMoveEvent(QMouseEvent *event){
    if(drawDock->mouseEvent(event,movee,scrollArea->x(),scrollArea->horizontalScrollBar()->value(),scrollArea->y(),scrollArea->verticalScrollBar()->value())){
    } else if (moveStart){
        move -= event->pos()-QPoint(scrollArea->x()-scrollArea->horizontalScrollBar()->value(),scrollArea->y()-scrollArea->verticalScrollBar()->value());
        param = new toolParameters_t;
        param->tool = tools_e::move;
        param->offsetX = (-1)*move.x();
        param->offsetY = (-1)*move.y();
        interactionTool->useTool(param);
        param = nullptr;
        updateVisible();
        move = event->pos()-QPoint(scrollArea->x()-scrollArea->horizontalScrollBar()->value(),scrollArea->y()-scrollArea->verticalScrollBar()->value());
    }
}

void ImageViewer::mouseReleaseEvent(QMouseEvent *event){
    if(drawDock->mouseEvent(event,release,scrollArea->x(),scrollArea->horizontalScrollBar()->value(),scrollArea->y(),scrollArea->verticalScrollBar()->value())){
    } else if (event->button() == Qt::LeftButton && moveStart){
        move -= event->pos()-QPoint(scrollArea->x()-scrollArea->horizontalScrollBar()->value(),scrollArea->y()-scrollArea->verticalScrollBar()->value());
        param = new toolParameters_t;
        param->tool = tools_e::move;
        param->offsetX = (-1)*move.x();
        param->offsetY = (-1)*move.y();
        interactionTool->useTool(param);
        moveStart=false;
        param = nullptr;
        updateVisible();
    }
}

void ImageViewer::newLayer(){
    addDockWidget(Qt::LeftDockWidgetArea, newLayerDock->createNewLayerDock());
}

void  ImageViewer::translate(){
    addDockWidget(Qt::LeftDockWidgetArea, transLationDock->createTranslateDock());
};

void ImageViewer::updateVisible(){
    //for (int i = 0; i < interactionTool->getPicture()->getLayerCount(); i++) {
    //    if (layerCheckboxes[i]->isChecked()){
            //TODO: Syncronisieren vom Bild
    //    }
    //}
    updateActions();
    makeToShaped->setChecked(interactionTool->getPicture()->isShaped());
    makeToShaped->setEnabled(!interactionTool->getPicture()->isShaped());
    QString message;
    message.sprintf("Dimensions: %dx%d",interactionTool->getPicture()->getCurrentLayerAsQ()->width(),interactionTool->getPicture()->getCurrentLayerAsQ()->height());
    statusBar()->showMessage(message);
    calculateVisible();
}

void ImageViewer::calculateVisible(){
    QPixmap *px = new QPixmap(interactionTool->getPicture()->getMaxSize());
    px->fill(QColor(0,0,0,0));
    QSize ms = interactionTool->getPicture()->getMinOffset();
    int mdx=ms.width()%10;
    int mdy=ms.height()%10;
    bool c=true;
    bool ug=(px->size().height()/10+1-ms.height()/10)%2==1;
    QPainter *painter= new QPainter(px);
    QBrush *br1 = new QBrush(QColor(100,100,100));
    QBrush *br2 = new QBrush(QColor(200,200,200));
    for (int i = ms.width()/10; i < px->size().width()/10+1;i++){
        if(!ug&&i>ms.width()/10){
            c=!c;
        }
        for (int j = ms.height()/10; j < px->size().height()/10+1;j++){
            if(c){
                painter->fillRect(i*10+mdx,j*10+mdy,10,10,*br1);
                c=!c;
            } else {
                painter->fillRect(i*10+mdx,j*10+mdy,10,10,*br2);
                c=!c;
            }
        }
    }
    for (int i = 0; i < interactionTool->getPicture()->getLayerCount(); i++) {
        if (layerDock->isLayerCheckboxChecked(i)){
            painter->drawImage(interactionTool->getPicture()->xOffset(i),interactionTool->getPicture()->yOffset(i),*interactionTool->getPicture()->getLayerAsQ(i));
        }
    }
    pixmap=px;
    setImage(px->toImage());
    painter->end();
    delete px;
}

void ImageViewer::makeShaped(){
    if(hasLayer){
        makeToShaped->setEnabled(false);
        interactionTool->getPicture()->makeCurrentLayerShaped();
        colorDock->updateColors();
    }
}

bool ImageViewer::getHasLayer(){
    return hasLayer;
}

QVector<QRgb> ImageViewer::getColorVect(){
    return colorVect;
}

void ImageViewer::setTranslationParams(toolParameters_t *param){
    param->colorVect = colorVect;
    transLationDock->doTranslationII(param);
}

void ImageViewer::updateall(){
    layerDock->updateLayerCount();
    colorDock->updateColors();
    updateVisible();
}

void ImageViewer::updateHasLayer(bool b){
    hasLayer = b;
}

void ImageViewer::drawShowI(para1 p){
    QPixmap *px = new QPixmap(*imageLabel->pixmap());
    QPainter *painter= new QPainter(px);
    QPen *pen = new QPen(QColor(colorVect[p.i]));
    pen->setWidth(p.w);
    painter->setPen(*pen);
    painter->drawLine(p.q, p.p);
    imageLabel->setPixmap(*px);
}

void ImageViewer::drawShowII(para2 p){
    QPixmap *px = new QPixmap(*imageLabel->pixmap());
    QPainter *painter= new QPainter(px);
    QBrush *pen = new QBrush(QColor(colorVect[p.i]));
    painter->setBrush(*pen);
    QPainterPath path;
    path.addPolygon(p.p);
    painter->fillPath(path,*pen);
    imageLabel->setPixmap(*px);
}

void ImageViewer::updateLayerDock(){
    layerDockW->close();
    layerDockW=layerDock->getDockWidget();
    addDockWidget(Qt::RightDockWidgetArea, layerDockW);
}

void ImageViewer::setMergeParams(toolParameters_t *param){
    param->colorVect = colorVect;
    layerDock->doMergeII(param);
}

void ImageViewer::updateWithoutLayer(){
    colorDock->updateColors();
    updateVisible();


}
void ImageViewer::updateColorVector(QVector<QRgb> colorVect){
    this->colorVect = colorVect;
    newColorVect = colorVect;
    newLayerDock->setColorVect(colorVect);
    drawDock->setColorVect(colorVect);
}

void ImageViewer::updateNewColorVector(QVector<QRgb> colorVect){
    newColorVect = colorVect;
}
