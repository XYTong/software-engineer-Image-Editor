from Tool import Tool
class ManuplationTool():
    def __init__(self,CurrentLayer):
        self.tool = Tool(self,CurrentLayer)
    def getTool(self,CurrentLayer,tool_name):
        self.tool.manipulate(tool_name,CurrentLayer) 
