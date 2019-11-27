from Colormap import Colormap
class RasterImage():
    def __init__(self,width,height,CurrentLayer):
        self._width = width
        self._height = height
        self._pixels = CurrentLayer
        self.colormap = Colormap(width,height,CurrentLayer)

    