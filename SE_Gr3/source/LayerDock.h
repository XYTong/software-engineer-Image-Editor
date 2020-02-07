#ifndef LAYERDOCK_H
#define LAYERDOCK_H
#include "InteractionTool.h"
#include <QDockWidget>
#include <QScrollArea>
#include <QGridLayout>
#include <QPushButton>
#include <QCheckBox>

/*!
 * \brief LayerDock
 * \brief Verwaltet den LayerDock und die sichtbarkeit der einzelnen Layer. Kann das mergen, tauschen und Löschen von Layern initiieren.
 */
class LayerDock : public QObject
{
    Q_OBJECT

public:
    LayerDock(InteractionTool *interaction);
    ~LayerDock();
    void updateLayers();
    void updateLayerCount();
    QDockWidget *getDockWidget();
    bool isLayerCheckboxChecked(int i);
    void doMergeII(toolParameters_t *param);

signals:
    void updateLayerDock();
    void newLayer();
    void update();
    void getParams(toolParameters_t *param);

private slots:
    void changeCurrentLayer();
    void updateVisible();

private:
    void createLayerDock();

    QScrollArea *layerScrollArea;
    QWidget *layers;
    QDockWidget *layerDock;
    QGridLayout* layerLayout;
    std::vector<QPushButton*> layerButtons;
    std::vector<QCheckBox*> layerCheckboxes;
    toolParameters_t *param;
    InteractionTool *interactionTool;
    int i;

};

#endif // LAYERDOCK_H
