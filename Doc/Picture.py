class Picture():
    def __inti__(self):
        self.currentLayer = []
        self.Layers = [self.currentLayer]
    def addLayer(self,pixels):
        self.Layers.append(pixels)
    #def removeLayer(self)
    def getLayer(self,i):
        if i > 0 and i < len(self.Layers):
            return self.Layers[i]
        else:
            print('out of range')
