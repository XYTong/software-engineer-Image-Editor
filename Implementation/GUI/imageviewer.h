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
#include "InteractionTool.h"

#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QMainWindow>
#include <QImage>
#include <vector>
#include <QToolButton>
#include <QPushButton>
#include <QGridLayout>
#include <QSlider>
#include <QSpinBox>
#include <QLabel>
#include <QCheckBox>

#ifndef QT_NO_PRINTER
#include <QPrinter>
#endif

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
QT_END_NAMESPACE

typedef enum drawModus {pencil, lines, notFilledRect, filledRect} drawModus_e;

//! [0]
class ImageViewer : public QMainWindow
{
    Q_OBJECT

public:
    ImageViewer(QWidget *parent = nullptr);
    bool loadFile(const QString &);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void open();
    void saveAs();
    void print();
    void copy();
    void paste();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();
    void about();
    void draw();
    void translate();
    void calcTranslation();
    void doTranslation();
    void pencil();
    void startDraw();
    void lines();
    void notFilledRect();
    void filledRect();
    void existingColor();
    void newColor();
    void setNewColor();
    void setDrawColor();
    void changeColor();
    void changeCurrentLayer();
    void updateVisible();
    void makeShaped();
    void newLayer();
    void addNewLayer();
    void setWidth(int w);
    void setNewLayerX(int w);
    void setNewLayerY(int w);

private:
    void createActions();
    void createColorDock();
    void createLayerDock();
    void createTranslateDock();
    void createDrawDock();
    void createMenus();
    void createNewLayerDock();
    void addColor(QColor col, int pos);
    void updateColors();
    void updateLayers();
    void updateLayerCount();
    void updateActions();
    bool saveFile(const QString &fileName);
    void setImage(QImage newImage);
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
    void calculateVisible();

    QImage image;
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    QScrollArea *ColorScrollArea;
    QScrollArea *layerScrollArea;
    QWidget *colors;
    QWidget *layers;
    QMenu *viewMenu;
    QDockWidget *colorDock;
    QDockWidget *layerDock;
    QGridLayout* colorLayout;
    QGridLayout* layerLayout;
    std::vector<QToolButton*> colorButtons;
    std::vector<QPushButton*> layerButtons;
    std::vector<QCheckBox*> layerCheckboxes;
    QVector<QRgb> colorVect;
    QList<QAction*> colorAct;
    QPushButton *colorButton;
    QSlider *drawSlider;
    QSpinBox *drawSpinbox;
    QSlider *newLayerXSlider;
    QSpinBox *newLayerXSpinbox;
    QSlider *newLayerYSlider;
    QSpinBox *newLayerYSpinbox;
    QPushButton *drawStartButton;
    QMenu *colorMenu;
    QCheckBox *mirrorCheckbox;
    QLineEdit *zoomXInp;
    QLineEdit *zoomYInp;
    QLineEdit *rotInp;
    QLabel *translationLabelA;
    QLabel *translationLabelB;
    QLabel *translationLabelC;
    QLabel *translationLabelD;
    QMatrix *transMat;
    QPushButton *newColorButton;
    drawModus_e actDrawModus = drawModus_e::pencil;
    QRgb newLayerColor;
    QGridLayout *newLayerLayout;
    QPixmap *pixmap;
    bool isNewLayerColor = false;
    double scaleFactor = 1.0;
    bool isDraw=false;
    int drawWidth=3;
    int newLayerX = 100;
    int newLayerY = 100;
    int drawColorIndex=0;
    bool drawStart=false;
    bool hasLayer=false;
    toolParameters_t *param = nullptr;
    InteractionTool interactionTool;

#ifndef QT_NO_PRINTER
    QPrinter printer;
#endif

    QAction *saveAsAct;
    QAction *printAct;
    QAction *copyAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;
    QAction *showColorsAct;
};
//! [0]

#endif
