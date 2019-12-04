from Picture import Picture
#from ManuplationTool import*
from ShowTool import ShowTool
from ManuplationTool import ManuplationTool
class Interaction_Tool:
    def __init_(self):
        self.pic = None
        self.show_img = None
    def show(self,file_name):
        #print(self.pic.Layers)
        self.show_img = ShowTool()
        self.pic = Picture()
        self.show_img.show(self.pic, file_name)
        print(self.pic.CurrentLayer)
        #print(len(self.pic.CurrentLayer))
        #self.show_img.show(file_name)
    def usetool(self):
        manupl_tool = ManuplationTool(self.pic.CurrentLayer)
        manupl_tool.getTool(self.pic.CurrentLayer,'Rotate')
    #def createPic()
    #def importPic()
if __name__ == '__main__':
    new_IT = Interaction_Tool()
    new_IT.show('flower.jpeg')
