class Picture:
    def __init__(self):
        self.Layers = []
        self.CurrentLayer = None
        self.raster_image = None 
    def addLayer(self,pixels):
        self.Layers.append(pixels)
        self.CurrentLayer
    #def removeLayer(self)
    def getLayer(self,i):
        if i > 0 and i < len(self.Layers):
            return self.Layers[i]
        else:
            print('out of range')
