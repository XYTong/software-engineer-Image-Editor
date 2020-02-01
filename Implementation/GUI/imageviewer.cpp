/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "imageviewer.h"
#include <QtWidgets>
#include <cstdlib>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrintDialog>
#endif
#endif

//! [0]
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
    //scrollArea->setVisible(false);
    setCentralWidget(scrollArea);
    createActions();

    //colorButtons = std::vector<QToolButton*>(); //TODO vector zu Qvector ändern
    colorVect = QVector<QRgb>();
    QPixmap px(20, 20);
    QString str2;
    newLayerDock = new NewLayerDock(interactionTool);
    connect(newLayerDock,&NewLayerDock::update,this,&ImageViewer::updateall);
    connect(newLayerDock,QOverload<bool>::of(&NewLayerDock::updateHasLayer),this,&ImageViewer::updateHasLayer);

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
    //createColorDock();

    layerDockW = layerDock->getDockWidget();

    //resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
    resize(QGuiApplication::primaryScreen()->availableSize() * 4 / 5);
}

bool ImageViewer::loadFile(const QString &fileName)
{

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
//! [2]
    param = new toolParameters_t;
    param->tool=tools_e::newLayer;
    param->pic = newImage;
    param->colorVect = newColorVect;
    interactionTool->useTool(param);
    param = nullptr;
    newImage = interactionTool->getPicture()->getCurrentLayerAsQ();
    //colorVect = interactionTool->getPicture()->getCurrentLayerAsQ()->colorTable();
    if (newImage==nullptr){
        return false;
    }

    hasLayer=true;
    return true;
}

void ImageViewer::setImage(QImage newImage)//remove Parameter
{
    image = newImage;
    //updateVisible();
    //imageLabel->setPixmap(*pixmap);
    imageLabel->setPixmap(QPixmap::fromImage(image));
//! [4]
    //scaleFactor = 1.0;

    //scrollArea->setVisible(true);
    printAct->setEnabled(true);
    fitToWindowAct->setEnabled(true);
    updateActions();

    if (!fitToWindowAct->isChecked())
        imageLabel->adjustSize();
}

//! [4]

bool ImageViewer::saveFile(const QString &fileName)
{
    QImageWriter writer(fileName);
    QPixmap *px = new QPixmap(interactionTool->getPicture()->getMaxSize());
    QPainter *painter= new QPainter(px);
    for (int i = 0; i < interactionTool->getPicture()->getLayerCount(); i++) {
        if (layerDock->isLayerCheckboxChecked(i)){
            painter->drawImage(interactionTool->getPicture()->xOffset(i),interactionTool->getPicture()->yOffset(i),*interactionTool->getPicture()->getLayerAsQ(i));
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

//! [1]

static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
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

void ImageViewer::open()
{
    QFileDialog dialog(this, tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
    //updateColors();
    colorDock->updateColors();
    //updateLayerCount();
    layerDock->updateLayerCount();
    updateVisible();
}
//! [1]

void ImageViewer::saveAs()
{
    QFileDialog dialog(this, tr("Save File As"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptSave);

    while (dialog.exec() == QDialog::Accepted && !saveFile(dialog.selectedFiles().first())) {}
}

//! [5]
void ImageViewer::print()
//! [5] //! [6]
{
    Q_ASSERT(imageLabel->pixmap());
#if QT_CONFIG(printdialog)
//! [6] //! [7]
    QPrintDialog dialog(&printer, this);
//! [7] //! [8]
    if (dialog.exec()) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = imageLabel->pixmap()->size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(imageLabel->pixmap()->rect());
        painter.drawPixmap(0, 0, *imageLabel->pixmap());
    }
#endif
}
//! [8]

void ImageViewer::copy()
{
#ifndef QT_NO_CLIPBOARD
    QGuiApplication::clipboard()->setImage(image);
#endif // !QT_NO_CLIPBOARD
}

#ifndef QT_NO_CLIPBOARD
static QImage clipboardImage()
{
    if (const QMimeData *mimeData = QGuiApplication::clipboard()->mimeData()) {
        if (mimeData->hasImage()) {
            const QImage image = qvariant_cast<QImage>(mimeData->imageData());
            if (!image.isNull())
                return image;
        }
    }
    return QImage();
}
#endif // !QT_NO_CLIPBOARD

void ImageViewer::paste()
{
#ifndef QT_NO_CLIPBOARD
    const QImage newImage = clipboardImage();
    if (newImage.isNull()) {
        statusBar()->showMessage(tr("No image in clipboard"));
    } else {
        setImage(newImage);
        setWindowFilePath(QString());
        const QString message = tr("Obtained image from clipboard, %1x%2, Depth: %3")
            .arg(newImage.width()).arg(newImage.height()).arg(newImage.depth());
        statusBar()->showMessage(message);
    }
#endif // !QT_NO_CLIPBOARD
}

//! [9]
void ImageViewer::zoomIn()
//! [9] //! [10]
{
    scaleImage(1.25);
}

void ImageViewer::zoomOut()
{
    scaleImage(0.8);
}

//! [10] //! [11]
void ImageViewer::normalSize()
//! [11] //! [12]
{
    imageLabel->adjustSize();
    scaleFactor = 1.0;
}
//! [12]

//! [13]
void ImageViewer::fitToWindow()
//! [13] //! [14]
{
    bool fitToWindow = fitToWindowAct->isChecked();
    scrollArea->setWidgetResizable(fitToWindow);
    if (!fitToWindow)
        normalSize();
    updateActions();
}
//! [14]


//! [15]
void ImageViewer::about()
//! [15] //! [16]
{
    QMessageBox::about(this, tr("About Image Viewer"),"");
}
//! [16]

//! [17]
void ImageViewer::createActions()
//! [17] //! [18]
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *openAct = fileMenu->addAction(tr("&Open..."), this, &ImageViewer::open);
    openAct->setShortcut(QKeySequence::Open);

    saveAsAct = fileMenu->addAction(tr("&Save As..."), this, &ImageViewer::saveAs);
    saveAsAct->setEnabled(false);

    printAct = fileMenu->addAction(tr("&Print..."), this, &ImageViewer::print);
    printAct->setShortcut(QKeySequence::Print);
    printAct->setEnabled(false);

    fileMenu->addSeparator();

    QAction *exitAct = fileMenu->addAction(tr("E&xit"), this, &QWidget::close);
    exitAct->setShortcut(tr("Ctrl+Q"));

    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));

    copyAct = editMenu->addAction(tr("&Copy"), this, &ImageViewer::copy);
    copyAct->setShortcut(QKeySequence::Copy);
    copyAct->setEnabled(false);

    QAction *pasteAct = editMenu->addAction(tr("&Paste"), this, &ImageViewer::paste);
    pasteAct->setShortcut(QKeySequence::Paste);

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

    fitToWindowAct = viewMenu->addAction(tr("&Fit to Window"), this, &ImageViewer::fitToWindow);
    fitToWindowAct->setEnabled(false);
    fitToWindowAct->setCheckable(true);
    fitToWindowAct->setShortcut(tr("Ctrl+F"));

    QMenu *toolMenu = menuBar()->addMenu(tr("&Tools"));

    QAction *drawTool = toolMenu->addAction(tr("&Draw"), this, &ImageViewer::draw);
    QAction *newLayer = toolMenu->addAction(tr("&New Layer"), this, &ImageViewer::newLayer);
    QAction *translate = toolMenu->addAction(tr("&Translate"), this, &ImageViewer::translate);
    QAction *makeToShaped = toolMenu->addAction(tr("&Make Shaped"), this, &ImageViewer::makeShaped);

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));

    helpMenu->addAction(tr("&About"), this, &ImageViewer::about);
    helpMenu->addAction(tr("About &Qt"), &QApplication::aboutQt);
}
//! [18]

//! [21]
void ImageViewer::updateActions()
//! [21] //! [22]
{
    saveAsAct->setEnabled(!image.isNull());
    copyAct->setEnabled(!image.isNull());
    zoomInAct->setEnabled(!fitToWindowAct->isChecked());
    zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
    normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
}
//! [22]

//! [23]
void ImageViewer::scaleImage(double factor)
//! [23] //! [24]
{
    Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);

    zoomInAct->setEnabled(scaleFactor < 3.0);
    zoomOutAct->setEnabled(scaleFactor > 0.333);
}
//! [24]

//! [25]
void ImageViewer::adjustScrollBar(QScrollBar *scrollBar, double factor)
//! [25] //! [26]
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}
//! [26]
void ImageViewer::draw(){
    //createDrawDock();
    addDockWidget(Qt::LeftDockWidgetArea, drawDock->createDrawDock());
}

void ImageViewer::mousePressEvent(QMouseEvent *event)
{
    if(drawDock->mouseEvent(event,press,scrollArea->x(),scrollArea->horizontalScrollBar()->value(),scrollArea->y(),scrollArea->verticalScrollBar()->value())){

    } else
    if (event->button() == Qt::LeftButton && interactionTool->getPicture()->hasLayer()){
        moveStart=true;

        move = event->pos()-QPoint(scrollArea->x()-scrollArea->horizontalScrollBar()->value(),scrollArea->y()-scrollArea->verticalScrollBar()->value());
    }
}
void ImageViewer::mouseMoveEvent(QMouseEvent *event)
{
    if(drawDock->mouseEvent(event,movee,scrollArea->x(),scrollArea->horizontalScrollBar()->value(),scrollArea->y(),scrollArea->verticalScrollBar()->value())){

    } else if (moveStart){
        move -= event->pos()-QPoint(scrollArea->x()-scrollArea->horizontalScrollBar()->value(),scrollArea->y()-scrollArea->verticalScrollBar()->value());
        param = new toolParameters_t;
        param->tool = tools_e::move;
        param->offsetX = (-1)*move.x();
        param->offsetY = (-1)*move.y();
        interactionTool->useTool(param);
        param = nullptr;
        //setImage(*interactionTool->getPicture()->getCurrentLayerAsQ());
        updateVisible();
        move = event->pos()-QPoint(scrollArea->x()-scrollArea->horizontalScrollBar()->value(),scrollArea->y()-scrollArea->verticalScrollBar()->value());
    }
}
void ImageViewer::mouseReleaseEvent(QMouseEvent *event)
{
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
        //setImage(*interactionTool->getPicture()->getCurrentLayerAsQ());
        updateVisible();
    }
}

void ImageViewer::newLayer(){
    //param = new toolParameters_t;
    //param->tool=tools_e::newLayer;
    addDockWidget(Qt::LeftDockWidgetArea, newLayerDock->createNewLayerDock());
    //createNewLayerDock();
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
    //QBrush *br3 = new QBrush(QColor(0,0,0,0));
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
    //painter->fillRect(0,0,px->size().width(),ms.height(),*br3);
    //painter->fillRect(0,0,ms.width(),px->size().height(),*br3);
    for (int i = 0; i < interactionTool->getPicture()->getLayerCount(); i++) {
        if (layerDock->isLayerCheckboxChecked(i)){
            painter->drawImage(interactionTool->getPicture()->xOffset(i),interactionTool->getPicture()->yOffset(i),*interactionTool->getPicture()->getLayerAsQ(i));
            //painter->drawI
        }
    }
    pixmap=px;
    setImage(px->toImage());
    painter->end();
    delete px;
}
void ImageViewer::makeShaped(){
    if(hasLayer){
        interactionTool->getPicture()->makeCurrentLayerShaped();
        //updateColors();
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
    //updateLayerCount();
    layerDock->updateLayerCount();
    //updateColors();
    colorDock->updateColors();
    //setImage(*interactionTool.getPicture()->getCurrentLayerAsQ());
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
    //updateColors();
    colorDock->updateColors();
    //setImage(*interactionTool.getPicture()->getCurrentLayerAsQ());
    updateVisible();
}
void ImageViewer::updateColorVector(QVector<QRgb> colorVect){
    this->colorVect = colorVect;
    newLayerDock->setColorVect(colorVect);
    drawDock->setColorVect(colorVect);
}
