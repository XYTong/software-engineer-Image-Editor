QT += widgets
requires(qtConfig(filedialog))
qtHaveModule(printsupport): QT += printsupport

HEADERS       = imageviewer.h \
                ColorMap.h \
                InteractionTool.h \
                ManipulationTool.h \
                Picture.h \
                Pixel.h \
                RasterImage.h \
                ShapedImage.h \
                ShowTool.h \
                Tool.h \
                main.h \
                tools/drawTool.h \
                tools/floydSteinberg.h \
                tools/merge.h \
                tools/newLayer.h \
                tools/translationTool.h
SOURCES       = imageviewer.cpp \
                ColorMap.cpp \
                InteractionTool.cpp \
                ManipulationTool.cpp \
                Picture.cpp \
                RasterImage.cpp \
                ShapedImage.cpp \
                ShowTool.cpp \
                main.cpp \
                tools/drawTool.cpp \
                tools/floydSteinberg.cpp \
                tools/merge.cpp \
                tools/newLayer.cpp \
                tools/translationTool.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/imageviewer
INSTALLS += target
