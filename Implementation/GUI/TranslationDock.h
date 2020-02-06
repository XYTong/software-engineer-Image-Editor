#ifndef TRANSLATIONDOCK_H
#define TRANSLATIONDOCK_H

#include "InteractionTool.h"
#include <QDockWidget>
#include <QCheckBox>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>



class TranslationDock : public QObject
{
    Q_OBJECT
public:
    TranslationDock(InteractionTool *interaction);
    ~TranslationDock();
    void doTranslationII(toolParameters_t *param);
    QDockWidget *createTranslateDock();

signals:
    void getParams(toolParameters_t *param);
    void update();


private slots:
    void calcTranslation();
    void doTranslationI();

private:


    toolParameters_t *param;
    QDockWidget *dockWidget;
    InteractionTool *interactionTool;
    QCheckBox *mirrorCheckbox;
    QLineEdit *zoomXInp;
    QLineEdit *zoomYInp;
    QLineEdit *rotInp;
    QLabel *translationLabelA;
    QLabel *translationLabelB;
    QLabel *translationLabelC;
    QLabel *translationLabelD;
    QMatrix *transMat;
    bool isRot;
};
#endif // TRANSLATIONDOCK_H
