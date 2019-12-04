class Tool():
    def __init__(self,CurrentLayer):
        self.current_obj = CurrentLayer
    def manipulate(self,current_obj, tool_name):
        if tool_name == 'Rotate':
            angle,direction = [int(x) for x in input().split()]
            rotate = Rotate(self,current_obj,angle,direction)
        else:
            height,width = [int(x) for x in input().split()]
            resize = Resize(self,current_obj,height,width)
'''
        elif tool_name = 'ChangeResolution':
            height,weight = int(input())
            c_resolution = ChangeResolution(self,current_obj,heigt,weight)
        elif tool_name = 'Paint':

                    
        .........to be continue
'''

