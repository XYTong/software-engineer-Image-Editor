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
    interactionTool = InteractionTool();
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    //scrollArea->setVisible(false);
    setCentralWidget(scrollArea);
    createActions();

    colorButtons = std::vector<QToolButton*>(); //TODO vector zu Qvector ändern
    colorVect = QVector<QRgb>();
    QPixmap px(20, 20);
    QString str2;
    colorMenu = new QMenu();
    colorButton = new QPushButton();
    for(int i = 0; i <256; i++){
        colorVect.append(QColor(255,255,255,255).rgba());
        colorButtons.push_back(new QToolButton());
        //px.fill(colorVect[i]);
        //colorButtons[i]->setIcon(px);
        QString str;
        //str.append(qRed(colorVect[i]));
        //str.append(";");
        str.sprintf("background-color: qlineargradient(stop:0 #%02x%02x%02x);",qRed(colorVect[i]),qGreen(colorVect[i]),qBlue(colorVect[i]));
        //printf("background-color: #%02x%02x%02x;\n",qRed(colorVect[i]),qGreen(colorVect[i]),qBlue(colorVect[i]));
        if(i==drawColorIndex){
            colorButton->setStyleSheet(str);
        }

        colorButtons[i]->setStyleSheet(str);
        colorButtons[i]->setCheckable(true);

        connect(colorButtons[i], SIGNAL(clicked()),this, SLOT(changeColor()));
        //connect(colorButtons[i], SIGNAL(clicked()),colorButtons[i], SLOT(toggle()));
        str2.sprintf("Color %d",i);
        px.fill(colorVect[i]);
        //QAction *act = new QAction(px,str);
        //act->setCheckable(true);
        //connect(act, SIGNAL(clicked()),this, SLOT(setDrawColor()));
        colorMenu->addAction(px,str2,this,&ImageViewer::setDrawColor);
    }
    colorAct = colorMenu->actions();
    for (int i = 0; i < 256; i++) {
        colorAct[i]->setCheckable(true);
        //connect(act[i], SIGNAL(toggled()),this, SLOT(setDrawColor()));
    }

    colorButton->setMenu(colorMenu);
    drawSpinbox = new QSpinBox();
    drawSpinbox->setValue(3);
    connect(drawSpinbox, QOverload<int>::of(&QSpinBox::valueChanged),this, &ImageViewer::setWidth);
    drawSlider = new QSlider(Qt::Horizontal);
    drawSlider->setRange(1,99);
    drawSlider->setValue(3);
    connect(drawSlider, QOverload<int>::of(&QSlider::valueChanged),this, &ImageViewer::setWidth);

    drawStartButton = new QPushButton("Start");
    drawStartButton->setCheckable(true);
    connect(drawStartButton, SIGNAL(clicked()),this, SLOT(startDraw()));
    translationLabelA = new QLabel("a");
    translationLabelB = new QLabel("b");
    translationLabelC = new QLabel("c");
    translationLabelD = new QLabel("d");
    mirrorCheckbox = new QCheckBox();
    //connect(mirrorCheckbox,SIGNAL(checked()),this, SLOT(mirror()));

    zoomXInp = new QLineEdit();
    zoomYInp = new QLineEdit();
    rotInp = new QLineEdit();
    addColor(QColor(0,0,0,255),1);
    addColor(QColor(255,255,255,255),0);
    addColor(QColor(255,0,0,255),2);
    addColor(QColor(0,255,0,255),3);
    addColor(QColor(0,0,255,255),4);
    addColor(QColor(255,255,0,255),5);
    addColor(QColor(0,255,255,255),6);
    addColor(QColor(255,0,255,255),7);
    createColorDock();
    createLayerDock();
    //connect(layerDock, SIGNAL(dockLocationChanged(Qt::DockWidgetArea area)),this, SLOT(dockSizeChanged()));
    //viewMenu->addAction(colorDock->toggleViewAction());

    resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
}

//! [0]
//! [2]

void ImageViewer::createColorDock(){
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
        if(i==drawColorIndex){
            colorButton->setStyleSheet(str);
        }
        connect(colorButtons[i], SIGNAL(clicked()),this, SLOT(changeColor()));
        //connect(colorButtons[i], SIGNAL(clicked()),colorButtons[i], SLOT(toggle()));
    }

    colorDock = new QDockWidget(tr("Colortable"), this);
    colorDock->setAllowedAreas(Qt::BottomDockWidgetArea);

    colorLayout = new QGridLayout();
    for (int i = 0; i < 128; i++) {
        colorLayout->addWidget(colorButtons[2*i],0,i);
        colorLayout->addWidget(colorButtons[2*i+1],1,i);
    }

    colors = new QWidget(colorDock);
    colors->setLayout(colorLayout);
    ColorScrollArea = new QScrollArea();
    ColorScrollArea->setWidget(colors);
    colorDock->setWidget(ColorScrollArea);
    //QString str;
    //str.sprintf("height: %dpx;",colorDock->height()*2-colors->height());
    //printf("%d,%d,%d\n",colorDock->height(),colors->height(),ColorScrollArea->height());
    //str.sprintf("height: 30px;");
    //colorDock->setStyleSheet(str);
    addDockWidget(Qt::BottomDockWidgetArea, colorDock);
    colorDock->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable);

    //

}
void ImageViewer::createTranslateDock(){
    QDockWidget *translationDock = new QDockWidget(tr("Translation"), this);
    translationDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
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
    translationLayout->addWidget(input5,7,0,1,3);
    QLabel *label5 = new QLabel("Matrix entries:");

    translationLayout->addWidget(label5,8,0,2,1);

    translationLayout->addWidget(translationLabelA,8,1,1,1);

    translationLayout->addWidget(translationLabelB,8,2,1,1);

    translationLayout->addWidget(translationLabelC,9,1,1,1);

    translationLayout->addWidget(translationLabelD,9,2,1,1);
    QPushButton *input6 = new QPushButton("Apply");
    connect(input6, SIGNAL(clicked()), this, SLOT(doTranslation()));
    translationLayout->addWidget(input6,10,0,1,3);
    QSpacerItem *spacer = new QSpacerItem(1,300,QSizePolicy::Maximum,QSizePolicy::Maximum);
    translationLayout->addItem(spacer,11,1,1,3);
    /*
    QRadioButton *button1 = new QRadioButton("Pencil");
    button1->setChecked(true);
    translationLayout->addWidget(button1,0,0,1,2);
    connect(button1, SIGNAL(clicked()),this, SLOT(pencil()));
    QRadioButton *button2 = new QRadioButton("Lines");
    translationLayout->addWidget(button2,1,0,1,2);
    connect(button2, SIGNAL(clicked()),this, SLOT(lines()));
    QRadioButton *button3 = new QRadioButton("Rect");
    translationLayout->addWidget(button3,2,0,1,2);
    connect(button3, SIGNAL(clicked()),this, SLOT(notFilledRect()));
    QRadioButton *button4 = new QRadioButton("Filled Rect");
    translationLayout->addWidget(button4,3,0,1,2);
    connect(button4, SIGNAL(clicked()),this, SLOT(filledRect()));
    QLabel *color = new QLabel();
    color->setText("Color:");
    translationLayout->addWidget(color,4,0);
    translationLayout->addWidget(colorButton,4,1);
    QLabel *width = new QLabel();
    width->setText("Width:");
    translationLayout->addWidget(width,5,0);
    translationLayout->addWidget(drawSpinbox,5,1);
    QDialog *text = new QDialog();
    translationLayout->addWidget(text,8,1,1,2);
    translationLayout->addWidget(drawSlider,6,0,1,2);
    translationLayout->addWidget(drawStartButton,7,0,1,2);
    */
    QWidget *drawControl = new QWidget(translationDock);
    drawControl->setLayout(translationLayout);
    translationDock->setWidget(drawControl);
    addDockWidget(Qt::LeftDockWidgetArea, translationDock);
}
void ImageViewer::createDrawDock(){
    QDockWidget *drawDock = new QDockWidget(tr("Draw"), this);
    drawDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    QGridLayout *drawLayout = new QGridLayout();
    QRadioButton *button1 = new QRadioButton("Pencil");
    button1->setChecked(true);
    drawLayout->addWidget(button1,0,0,1,2);
    connect(button1, SIGNAL(clicked()),this, SLOT(pencil()));
    QRadioButton *button2 = new QRadioButton("Lines");
    drawLayout->addWidget(button2,1,0,1,2);
    connect(button2, SIGNAL(clicked()),this, SLOT(lines()));
    QRadioButton *button3 = new QRadioButton("Rect");
    drawLayout->addWidget(button3,2,0,1,2);
    connect(button3, SIGNAL(clicked()),this, SLOT(notFilledRect()));
    QRadioButton *button4 = new QRadioButton("Filled Rect");
    drawLayout->addWidget(button4,3,0,1,2);
    connect(button4, SIGNAL(clicked()),this, SLOT(filledRect()));
    QLabel *color = new QLabel();
    color->setText("Color:");
    drawLayout->addWidget(color,4,0);
    drawLayout->addWidget(colorButton,4,1);
    QLabel *width = new QLabel();
    width->setText("Width:");
    drawLayout->addWidget(width,5,0);


    drawLayout->addWidget(drawSpinbox,5,1);
    QDialog *text = new QDialog();
    drawLayout->addWidget(text,8,1,1,2);

    drawLayout->addWidget(drawSlider,6,0,1,2);

    drawLayout->addWidget(drawStartButton,7,0,1,2);
    QWidget *drawControl = new QWidget(drawDock);
    drawControl->setLayout(drawLayout);
    //layerScrollArea = new QScrollArea();
    //layerScrollArea->setWidget(layers);
    drawDock->setWidget(drawControl);
    addDockWidget(Qt::LeftDockWidgetArea, drawDock);
}
void ImageViewer::createLayerDock(){

    layerDock = new QDockWidget(tr("Layers"), this);
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
    addDockWidget(Qt::RightDockWidgetArea, layerDock);
    layerDock->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable);
}

bool ImageViewer::loadFile(const QString &fileName)
{
    param = new toolParameters_t;
    param->tool=tools_e::newLayer;
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
    param->pic = newImage;
    param->colorVect = colorVect;
    interactionTool.useTool(param);
    newImage = interactionTool.getPicture()->getCurrentLayerAsQ();
    if (newImage==nullptr){
        return false;
    }
    setImage(*newImage);
    updateColors();
    updateLayerCount();
    setWindowFilePath(fileName);

    const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
        .arg(QDir::toNativeSeparators(fileName)).arg(image.width()).arg(image.height()).arg(image.depth());
    statusBar()->showMessage(message);
    hasLayer=true;
    return true;
}

void ImageViewer::setImage(QImage newImage)
{
    image = newImage;
    imageLabel->setPixmap(QPixmap::fromImage(image));
//! [4]
    scaleFactor = 1.0;

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

    if (!writer.write(image)) {
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

    QMenu *window = menuBar()->addMenu(tr("&Window"));

    //showColorsAct = window->addAction(tr("&ShowColorDock"), this, &ImageViewer::ShowColorDock);

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
    createDrawDock();
}

void ImageViewer::mousePressEvent(QMouseEvent *event)
{
    if (isDraw && event->button() == Qt::LeftButton) {
        drawStart = true;
        param = new toolParameters_t;
        param->tool = paint;
        param->i = drawWidth;
        param->colorIndex =drawColorIndex;
        param->startPoint = event->pos()-QPoint(scrollArea->x(),scrollArea->y());
    }
}
void ImageViewer::mouseMoveEvent(QMouseEvent *event)
{
    if (drawStart) {
        param->endPoint = event->pos()-QPoint(scrollArea->x(),scrollArea->y());
        interactionTool.useTool(param);
        setImage(*interactionTool.getPicture()->getCurrentLayerAsQ());
        param = new toolParameters_t;
        param->tool = paint;
        param->i = drawWidth;
        param->colorIndex =drawColorIndex;
        param->startPoint = event->pos()-QPoint(scrollArea->x(),scrollArea->y());
    }
}
void ImageViewer::mouseReleaseEvent(QMouseEvent *event)
{
    if (isDraw && event->button() == Qt::LeftButton) {
        drawStart = false;
        param->endPoint = event->pos()-QPoint(scrollArea->x(),scrollArea->y());
        interactionTool.useTool(param);
        setImage(*interactionTool.getPicture()->getCurrentLayerAsQ());
        updateLayers();
    }
}
void ImageViewer::updateColors(){
    QPixmap px(20, 20);
    colorVect = interactionTool.getPicture()->getCurrentLayerAsQ()->colorTable();
    for(int i = 0; i <256; i++){

        px.fill(colorVect[i]);

        //colorButtons[i]->setIcon(px);
        QString str;
        //str.append(qRed(colorVect[i]));
        //str.append(";");
        str.sprintf("background-color: qlineargradient(stop:0 #%02x%02x%02x);",qRed(colorVect[i]),qGreen(colorVect[i]),qBlue(colorVect[i]));
        //printf("background-color: #%02x%02x%02x;\n",qRed(colorVect[i]),qGreen(colorVect[i]),qBlue(colorVect[i]));
        colorButtons[i]->setStyleSheet(str);
        if(i==drawColorIndex){
            colorButton->setStyleSheet(str);
        }
        colorAct[i]->setIcon(px);
    }
    colorButton->setMenu(colorMenu);
}
void ImageViewer::changeCurrentLayer(){
    if (layerButtons[0]->isChecked()){
        newLayer();
        interactionTool.getPicture()->moveLayer(0,interactionTool.getPicture()->getLayerCount()-1);
        updateLayers();
        layerButtons[0]->setChecked(false);
    }
    for (int i = 0; i < interactionTool.getPicture()->getLayerCount(); i++) {
        if (layerButtons[i*5+1]->isChecked()&&i!=interactionTool.getPicture()->getCurrentLayerIndex()){
            layerButtons[interactionTool.getPicture()->getCurrentLayerIndex()*5+1]->setChecked(false);
            layerButtons[interactionTool.getPicture()->getCurrentLayerIndex()*5+3]->setEnabled(true);
            interactionTool.getPicture()->setCurrentLayer(i);
            setImage(*interactionTool.getPicture()->getCurrentLayerAsQ());
            updateColors();
            layerButtons[interactionTool.getPicture()->getCurrentLayerIndex()*5+3]->setEnabled(false);
        } else if(layerButtons[i*5+2]->isChecked()){
            interactionTool.getPicture()->moveLayer(i,i-1);
            updateLayers();
            layerButtons[i*5+2]->setChecked(false);
        } else if(layerButtons[i*5+3]->isChecked()){
            layerButtons[i*5+3]->setChecked(false);
            interactionTool.getPicture()->removeLayer(i);
            updateLayerCount();

        } else if(layerButtons[i*5+4]->isChecked()){
            interactionTool.getPicture()->moveLayer(i+1,i);
            updateLayers();
            layerButtons[i*5+4]->setChecked(false);
        } else if(layerButtons[i*5+5]->isChecked()&&i+1!=interactionTool.getPicture()->getLayerCount()){
            layerButtons[i*5+5]->setChecked(false);
            param = new toolParameters_t;
            param->tool = merge;
            param->layerIndex1 = i;
            param->layerIndex2 = i+1;
            param->colorVect = colorVect;
            interactionTool.useTool(param);
            updateLayerCount();
            setImage(*interactionTool.getPicture()->getCurrentLayerAsQ());

        } else if(layerButtons[i*5+5]->isChecked()&&i+1==interactionTool.getPicture()->getLayerCount()){
            newLayer();
            //interactionTool.getPicture()->moveLayer(i+1,i);
            updateLayers();
            layerButtons[i*5+5]->setChecked(false);
        }
    }
}
void ImageViewer::addColor(QColor col, int pos){
    QPixmap px(20, 20);
    colorVect[pos]=col.rgba();
    px.fill(colorVect[pos]);
    //colorButtons[i]->setIcon(px);
    colorAct[pos]->setIcon(px);
    QString str;
    //str.append(qRed(colorVect[i]));
    //str.append(";");
    //str.sprintf("#%02x%02x%02x",qRed(colorVect[i]),qGreen(colorVect[i]),qBlue(colorVect[i]));
    str.sprintf("background-color: qlineargradient(stop:0.5 #%02x%02x%02x);",qRed(colorVect[pos]),qGreen(colorVect[pos]),qBlue(colorVect[pos]));
    //printf("background-color: #%02x%02x%02x;\n",qRed(colorVect[i]),qGreen(colorVect[i]),qBlue(colorVect[i]));
    colorButtons[pos]->setStyleSheet(str);
    if(pos==drawColorIndex){
        colorButton->setStyleSheet(str);
    }
    colorButtons[pos]->setChecked(false);
    if (hasLayer){
        interactionTool.getPicture()->getCurrentLayerAsQ()->setColor(pos,colorVect[pos]);
        setImage(*interactionTool.getPicture()->getCurrentLayerAsQ());
        updateLayers();
    }
    colorButton->setMenu(colorMenu);
}
void ImageViewer::changeColor(){
    for (int i = 0; i < colorButtons.size(); i++) {
        if (colorButtons[i]->isChecked()){
            QPixmap px(20, 20);
            QString str2;
            str2.sprintf("Color %d",i);
            colorVect[i]=QColorDialog().getColor(Qt::white,nullptr,str2,QColorDialog::ShowAlphaChannel).rgba();
            px.fill(colorVect[i]);
            //colorButtons[i]->setIcon(px);
            colorAct[i]->setIcon(px);
            QString str;
            //str.append(qRed(colorVect[i]));
            //str.append(";");
            //str.sprintf("#%02x%02x%02x",qRed(colorVect[i]),qGreen(colorVect[i]),qBlue(colorVect[i]));
            str.sprintf("background-color: qlineargradient(stop:0.5 #%02x%02x%02x);",qRed(colorVect[i]),qGreen(colorVect[i]),qBlue(colorVect[i]));
            //printf("background-color: #%02x%02x%02x;\n",qRed(colorVect[i]),qGreen(colorVect[i]),qBlue(colorVect[i]));
            colorButtons[i]->setStyleSheet(str);
            if(i==drawColorIndex){
                colorButton->setStyleSheet(str);
            }
            colorButtons[i]->setChecked(false);
            if (hasLayer){
                interactionTool.getPicture()->getCurrentLayerAsQ()->setColor(i,colorVect[i]);
                setImage(*interactionTool.getPicture()->getCurrentLayerAsQ());
                updateLayers();
            }
            colorButton->setMenu(colorMenu);
        }
    }
}
void ImageViewer::updateLayerCount(){
    layerButtons = std::vector<QPushButton*>(); //TODO vector zu Qvector ändern
    layerDock->close();

    layerDock = new QDockWidget(tr("Layers"), this);
    layerDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    layerLayout = new QGridLayout();
    layerButtons.push_back(new QPushButton("+"));
    layerLayout->addWidget(layerButtons[0],0,0,2,1);
    layerButtons[0]->setMaximumWidth(25);
    layerButtons[0]->setCheckable(true);
    connect(layerButtons[0], SIGNAL(clicked()),this, SLOT(changeCurrentLayer()));
    for (unsigned int i = 0; i < interactionTool.getPicture()->getLayerCount(); i++) {
        layerButtons.push_back(new QPushButton);
        //layerButtons[i]->setStyleSheet("width: 100px;height: 100px;");
        QPixmap pic(100,100);
        pic.convertFromImage(*interactionTool.getPicture()->getLayerAsQ(i));
        layerButtons[i*5+1]->setIconSize(QSize(100,100));
        layerButtons[i*5+1]->setIcon(pic);
        //layerButtons[i]->setMask(pic);
        layerLayout->addWidget(layerButtons[i*5+1],i*5+1,1,5,1);
        layerButtons[i*5+1]->setCheckable(true);
        connect(layerButtons[i*5+1], SIGNAL(clicked()),this, SLOT(changeCurrentLayer()));
        layerButtons.push_back(new QPushButton("^"));
        layerLayout->addWidget(layerButtons[i*5+2],i*5+2,0,1,1);
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
        layerButtons.push_back(new QPushButton("v"));
        layerLayout->addWidget(layerButtons[i*5+4],i*5+4,0,1,1);
        layerButtons[i*5+4]->setMaximumWidth(25);
        layerButtons[i*5+4]->setCheckable(true);
        if (i+1==interactionTool.getPicture()->getLayerCount()){
            layerButtons[i*5+4]->setEnabled(false);
        }
        connect(layerButtons[i*5+4], SIGNAL(clicked()),this, SLOT(changeCurrentLayer()));
        layerButtons.push_back(new QPushButton("+"));
        layerLayout->addWidget(layerButtons[i*5+5],i*5+5,0,2,1);
        layerButtons[i*5+5]->setMaximumWidth(25);
        layerButtons[i*5+5]->setCheckable(true);
        connect(layerButtons[i*5+5], SIGNAL(clicked()),this, SLOT(changeCurrentLayer()));
    }
    layerButtons[interactionTool.getPicture()->getCurrentLayerIndex()*5+1]->setChecked(true);
    if(interactionTool.getPicture()->getLayerCount()>1){
        layerButtons[interactionTool.getPicture()->getCurrentLayerIndex()*5+3]->setEnabled(false);
    }
    layers = new QWidget(layerDock);
    layers->setLayout(layerLayout);
    layerScrollArea = new QScrollArea();
    layerScrollArea->setWidget(layers);
    layerDock->setWidget(layerScrollArea);
    addDockWidget(Qt::RightDockWidgetArea, layerDock);
    layerDock->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable);
}
void ImageViewer::updateLayers(){
    for (unsigned int i = 0; i < interactionTool.getPicture()->getLayerCount(); i++) {
        QPixmap pic;
        pic.convertFromImage(*interactionTool.getPicture()->getLayerAsQ(i));
        layerButtons[i*5+1]->setIcon(pic);
        layerButtons[i*5+1]->setChecked(false);
    }
    layerButtons[interactionTool.getPicture()->getCurrentLayerIndex()*5+1]->setChecked(true);
    if(interactionTool.getPicture()->getLayerCount()>1){
        layerButtons[interactionTool.getPicture()->getCurrentLayerIndex()*5+3]->setEnabled(false);
    }
}
void ImageViewer::newLayer(){
    //param = new toolParameters_t;
    //param->tool=tools_e::newLayer;
    QImage *newImage = new QImage(200,200,QImage::Format_Indexed8);
    newImage->setColorTable(colorVect);
    newImage->fill(0);
    //param->pic = newImage;
    //param->colorVect = colorVect;
    //interactionTool.useTool(param);
    interactionTool.getPicture()->addCurrentLayer(newImage);
    if (newImage==nullptr){
        return;
    }
    setImage(*newImage);
    updateColors();
    updateLayerCount();
    //statusBar()->showMessage(message);
    hasLayer=true;
}
void ImageViewer::pencil(){
    actDrawModus = drawModus_e::pencil;
}
void ImageViewer::lines(){
    actDrawModus = drawModus_e::lines;
}
void ImageViewer::notFilledRect(){
    actDrawModus = drawModus_e::notFilledRect;
}
void ImageViewer::filledRect(){
    actDrawModus = drawModus_e::filledRect;

}
void ImageViewer::setDrawColor(){
    for (int i = 0; i < 256; i++) {
        if (colorAct[i]->isChecked()){
            colorAct[i]->setChecked(false);
            drawColorIndex = i;
            QString str;
            //str.append(qRed(colorVect[i]));
            //str.append(";");
            str.sprintf("background-color: qlineargradient(stop:0 #%02x%02x%02x);",qRed(colorVect[i]),qGreen(colorVect[i]),qBlue(colorVect[i]));
            //printf("background-color: #%02x%02x%02x;\n",qRed(colorVect[i]),qGreen(colorVect[i]),qBlue(colorVect[i]));
            colorButton->setStyleSheet(str);
            //QString str;
            //str.sprintf("%d",i);
            //statusBar()->showMessage(str);
        }
    }
}
void ImageViewer::startDraw(){
    if(isDraw){
        isDraw = false;
        drawStartButton->setText("Start");
        //drawSlider->setEnabled(true);
        //drawSpinbox->setEnabled(true);

    } else {
        isDraw = true;
        drawStartButton->setText("Stop");
        //drawSlider->setEnabled(false);
        //drawSpinbox->setEnabled(false);
    }
}
void ImageViewer::setWidth(int w){
    drawSpinbox->setValue(w);
    drawSlider->setValue(w);
    drawWidth=w;
}
void  ImageViewer::translate(){
    createTranslateDock();
};
void ImageViewer::calcTranslation(){
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
void ImageViewer::doTranslation(){
    param = new toolParameters_t;
    param->tool = translationTool;
    param->mat = *transMat;
    param->colorVect = colorVect;
    interactionTool.useTool(param);
    updateLayerCount();
    setImage(*interactionTool.getPicture()->getCurrentLayerAsQ());
}/*
void ImageViewer::dockSizeChanged(){
    statusBar()->showMessage("str");
}*/
