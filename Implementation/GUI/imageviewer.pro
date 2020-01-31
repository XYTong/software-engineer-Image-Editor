QT += widgets
requires(qtConfig(filedialog))
qtHaveModule(printsupport): QT += printsupport

HEADERS       = imageviewer.h \
                DrawDock.h \
                InteractionTool.h \
                ManipulationTool.h \
                NewLayerDock.h \
                Picture.h \
                Tool.h \
                TranslationDock.h \
                main.h \
                tools/drawTool.h \
                tools/floydSteinberg.h \
                tools/merge.h \
                tools/movetool.h \
                tools/newLayer.h \
                tools/polygon.h \
                tools/translationTool.h
SOURCES       = imageviewer.cpp \
                DrawDock.cpp \
                InteractionTool.cpp \
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
