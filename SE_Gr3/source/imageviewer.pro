QT += widgets
requires(qtConfig(filedialog))
qtHaveModule(printsupport): QT += printsupport

HEADERS       = imageviewer.h \
                ColorDock.h \
                DrawDock.h \
                InteractionTool.h \
                LayerDock.h \
                ManipulationTool.h \
                NewLayerDock.h \
                Picture.h \
                Tool.h \
                TranslationDock.h \
                tools/drawTool.h \
                tools/floydSteinberg.h \
                tools/merge.h \
                tools/movetool.h \
                tools/newLayer.h \
                tools/polygon.h \
                tools/translationTool.h
SOURCES       = imageviewer.cpp \
                ColorDock.cpp \
                DrawDock.cpp \
                InteractionTool.cpp \
                LayerDock.cpp \
                ManipulationTool.cpp \
                NewLayerDock.cpp \
                Picture.cpp \
                TranslationDock.cpp \
                main.cpp \
                tools/drawTool.cpp \
                tools/floydSteinberg.cpp \
                tools/merge.cpp \
                tools/movetool.cpp \
                tools/newLayer.cpp \
                tools/polygon.cpp \
                tools/translationTool.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/imageviewer
INSTALLS += target
