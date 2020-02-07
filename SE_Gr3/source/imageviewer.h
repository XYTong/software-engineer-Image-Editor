#include "InteractionTool.h"
#include "TranslationDock.h"
#include "NewLayerDock.h"
#include "DrawDock.h"
#include "LayerDock.h"
#include "ColorDock.h"

#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H



#include <QMainWindow>
#include <QImage>
#include <vector>
#include <QToolButton>
#include <QPushButton>
#include <QRadioButton>
#include <QGridLayout>
#include <QSlider>
#include <QSpinBox>
#include <QLabel>
#include <QCheckBox>

/*!
 * \class ImageViewer
 * \brief Anzeige & Interaktion
 * Klasse zum Zetralen verwalten und Anzeigen des Hauptfensters. Dies ist die Hauptschnittestelle zwischen dem Benutzer und dem Programm.
 */
class ImageViewer : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief ImageViewer erstelt ImageViewer und führt die anderen notwendigen Constructoren aus.
     * \param parent sollte ein Zeiger zu der Klasse sein die unser Programm öffnet.
     */
    ImageViewer(QWidget *parent = nullptr);
    /*!
     * \brief loadFile versucht die Datei inputFile zu öffnen und als Bild zu importieren.
     * \param inputFile relativer Pfad zu einer zuöffnenden Datei.
     * \return bool gibt an,ob das Öffnen des bildes erfolgreich war.
     */
    bool loadFile(const QString &inputFile);
    /*!
     * \brief getHasLayer testet ob mindestens ein Layer geöffnet ist.
     * \return bool ist Layer vorhanden?
     */
    bool getHasLayer();
    /*!
     * \brief getColorVect gibt einen Vektor mit denakuell verwendeten farben zurück.
     * \return QVector<QRgb> Vektor mit aktuellen Farben;
     */
    QVector<QRgb> getColorVect();

protected:
    /*!
     * \brief mousePressEvent verarbeitet das Event wenn eine Maustaste gedrückt wird.
     * \param event von QT erzeugtes Event.
     * Event wird entweder zum bewegen des aktuellen Layers verwendet oder zum zeichen je nachdem ob das Zeichnen gestartet wurde.
     */
    void mousePressEvent(QMouseEvent *event) override;
    /*!
     * \brief mouseMoveEvent verarbeitet das Event wenn eine Maustaste gedrückt wird.
     * \param event von QT erzeugtes Event.
     * Event wird entweder zum bewegen des aktuellen Layers verwendet oder zum zeichen je nachdem ob das Zeichnen gestartet wurde.
     */
    void mouseMoveEvent(QMouseEvent *event) override;
    /*!
     * \brief mouseReleaseEvent verarbeitet das Event wenn eine Maustaste gedrückt wird.
     * \param event von QT erzeugtes Event.
     * Event wird entweder zum bewegen des aktuellen Layers verwendet oder zum zeichen je nachdem ob das Zeichnen gestartet wurde.
     */
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    /*!
     * \brief open initiiert das Öffnen von Bildern.
     * Wird augeführt wenn der Nutzer im Menu auf Open klickt oder durch den Shortcut Strg+O.
     */
    void open();
    /*!
     * \brief saveAs initiert das Speichern von Bildern.
     * Wird augeführt wenn der Nutzer im Menu auf Save as klickt oder durch den Shortcut Strg+S.
     */
    void saveAs();
    /*!
     * \brief zoomIn initiert das Vergrößern von Bildern.
     * Wird augeführt wenn der Nutzer im Menu auf Zoom in klickt oder durch den Shortcut Strg++.
     */
    void zoomIn();
    /*!
     * \brief zoomOut initiert das Verkleinern von Bildern.
     * Wird augeführt wenn der Nutzer im Menu auf Zoom out klickt oder durch den Shortcut Strg+-.
     */
    void zoomOut();
    /*!
     * \brief normalSize initiert das Setzen der Skalierung auf 100%.
     * Wird augeführt wenn der Nutzer im Menu auf normal size klickt oder durch den Shortcut Strg+0.
     */
    void normalSize();
    /*!
     * \brief fitToWindow initiert das Skalieren auf Fenstergöße.
     * \todo entfernen da diese Funktion nicht mehr verwendet wird.
     * Wird augeführt wenn der Nutzer im Menu auf fit to Window klickt.
     */
    void fitToWindow();
    /*!
     * \brief about initiert das Anzeigen der Hilfe fürunser Programm.
     * Wird augeführt wenn der Nutzer im Menu auf Help an klickt.
     */
    void about();
    /*!
     * \brief draw initiert das Öffnen des DrawDocks.
     * Wird augeführt wenn der Nutzer im Menu auf Draw klickt oder durch den Shortcut Strg+D.
     * \sa DrawDock
     */
    void draw();
    /*!
     * \brief translate initiert das Öffnendes TranslationDocks.
     * Wird augeführt wenn der Nutzer im Menu auf Translate klickt oder durch den Shortcut Strg+T.
     * \sa TranslationDock
     */
    void translate();
    /*!
     * \brief setTranslationParams fügt in param den aktuellen Farbvektor ein und fährt mit der Tanslation des Bildes fort.
     * \param param initialisierte Struktur, in der der aktuelle Farbvektor fehlt.
     */
    void setTranslationParams(toolParameters_t * param);
    /*!
     * \brief setMergeParams fügt in param den aktuellen Farbvektor ein und fährt mit dem mergen der Bilder fort.
     * \param param initialisierte Struktur, in der der aktuelle Farbvektor fehlt.
     */
    void setMergeParams(toolParameters_t * param);
    /*!
     * \brief updateHasLayer aktualiesiert dieInformation, ob Layer vorhanden sind.
     * \param b Information über dasvorhandensein von Layern.
     */
    void updateHasLayer(bool b);
    /*!
     * \brief updateall aktualisiert alle Anzeigeelemente der GUI.
     */
    void updateall();
    /*!
     * \brief updateWithoutLayer aktualisiert alle Anzeigeelemente der GUI, bisauf das LayerDock.
     */
    void updateWithoutLayer();
    /*!
     * \brief updateVisible aktualiesiert den sichtbaren Bereich.
     */
    void updateVisible();
    /*!
     * \brief makeShaped initiert das erzeugen eines ShapedImages.
     * Wird augeführt wenn der Nutzer im Menu auf MakeShaped klickt.
     */
    void makeShaped();
    /*!
     * \brief newLayer initiert das Öffnendes TranslationDocks.
     * Wird augeführt wenn der Nutzer im Menu auf Translate klickt oder durch den Shortcut Strg+T.
     * \sa TranslationDock
     */
    void newLayer();
    /*!
     * \brief drawShowI zeigt beim zeichnen von Linien eine vorschau vor dem loslassen der Maus.
     * \param p Informationen zum Zeichnen.
     */
    void drawShowI(para1 p);
    /*!
     * \brief drawShowII zeigt beim zeichnen von Polygonen eine vorschau vor dem drücken der rechten Maustaste.
     * \param p Informationen zum Zeichnen.
     */
    void drawShowII(para2 p);
    /*!
     * \brief updateLayerDock initiiert das LayerDock sich zu updaten.
     */
    void updateLayerDock();
    /*!
     * \brief updateColorVector Ubdatet die aktuelle Farbtabelle.
     * \param colorVect zu setzende Farbtabelle.
     */
    void updateColorVector(QVector<QRgb> colorVect);
    /*!
     * \brief updateNewColorVector updated die Farbtabelle für ein neu zu öffnendes Bild.
     * \param colorVect zu setzende Farbtabelle.
     */
    void updateNewColorVector(QVector<QRgb> colorVect);

private:
    /*!
     * \brief createActions Erzeugt die Knöpfe im Hauptmenü.
     */
    void createActions();
    /*!
     * \brief createMenus Erzeugt das Menü im Hauptfenster.
     */
    void createMenus();
    /*!
     * \brief updateActions updated die ausführbaren Menüpunkte.
     */
    void updateActions();
    /*!
     * \brief saveFile Speichert aktuell sichtbares Bild.
     * \param fileName Ort zum Speichern.
     * \return Wahr, wenn erfolgreich.
     */
    bool saveFile(const QString &fileName);
    /*!
     * \brief setImage Zeigt Bild newImage.
     * \param newImage Anzuzeigendes Bild.
     */
    void setImage(QImage newImage);
    /*!
     * \brief scaleImage Vergrößert/verkleinert Bild.
     * \param factor Vergrößerungsfaktor.
     */
    void scaleImage(double factor);
    /*!
     * \brief adjustScrollBar Passt Scrollbar an vergrößerung an.
     * \param scrollBar
     * \param factor
     */
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
    /*!
     * \brief calculateVisible berechnet aktuell Sichtbares Bild.
     */
    void calculateVisible();

    QImage image;
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    QMenu *viewMenu;
    QDockWidget *layerDockW;
    QVector<QRgb> colorVect;
    QVector<QRgb> newColorVect;
    QPixmap *pixmap;
    QPoint move;
    bool moveStart = false;
    double scaleFactor = 1.0;
    bool hasLayer=false;
    toolParameters_t *param = nullptr;
    InteractionTool *interactionTool;
    QAction *makeToShaped;
    QAction *drawTool;
    QAction *newLayerAct;
    QAction *translateAct;
    QAction *drawToolAct;
    TranslationDock *transLationDock;
    NewLayerDock *newLayerDock;
    DrawDock *drawDock;
    LayerDock *layerDock;
    ColorDock *colorDock;
    QAction *saveAsAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;
    QAction *showColorsAct;
};

#endif
