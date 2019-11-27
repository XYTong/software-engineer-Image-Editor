import os
from cv2 import cv2
import numpy as np
from Picture import Picture
from RasterImage import RasterImage
class ShowTool():
    def show(self,pic,file_name):
        #if no picture currently
        if pic.CurrentLayer == None:
            #array of pixels
            img = cv2.imread(file_name)
            pic.Layers.append(img)
            pic.CurrentLayer = img
            width = len(pic.CurrentLayer[1])
            height = len(pic.CurrentLayer[0])
            pic.raster_image = RasterImage(width,height,pic.CurrentLayer)
        else:
            img = pic.CurrentLayer
        #pic.Layers[0] = img
        #print(img)
        cv2.namedWindow("Image") 
        cv2.imshow("Image", img) 
        cv2.waitKey (0)
        cv2.destroyAllWindows()
#a = ShowTool()
#a.show()