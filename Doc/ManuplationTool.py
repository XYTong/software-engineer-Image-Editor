from Interaction_Tool import *
from Tool import *
class ManuplationTool():
    def __init__(self):
        self.tool = Tool(self)
    def getTool(self,tool_name):
        self.tool.manipulate(tool_name,pic.currentLayer) 