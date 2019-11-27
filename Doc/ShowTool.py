import os
from cv2 import cv2
import numpy as np
class ShowTool():
    def show(self,pic,file_name):
        img = cv2.imread(file_name)
        pic.Layers[0] = img
        #print(img)
#a = ShowTool()
#a.show()