#include <opencv2/core/core.hpp>    
#include <opencv2/highgui/highgui.hpp>
#include <bits/stdc++.h>
//#pragma once
#include "CV_Picture.h"
#include "CV_ShowTool.h"
#include "CV_RasterImage.h"
using namespace cv;
using namespace std;

class Interaction_Tool{
private:
    Picture* pic;
public:
    Interaction_Tool(){
        pic = new Picture();
    }
    ~Interaction_Tool(){
        delete pic;
    }
    void show(){
        ShowTool show_tool;
        show_tool.show(pic,"Tux.png");
    }
    void useToll();
};
int main(){
    Interaction_Tool ic;
    ic.show();
    return 0;
}
