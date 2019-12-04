#include <opencv2/core/core.hpp>                                               
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <bits/stdc++.h>
#include "CV_RasterImage.h"
#ifndef CV_PICTURE_H_H
#define CV_PICTURE_H_H
using namespace cv;
using namespace std;

class Picture{
private:
    stack<RasterImage*> Layers;
    RasterImage* CurrentLayer;
public:
    Picture(){
        CurrentLayer = NULL;
    }
    void add_picture(RasterImage* new_layer){
        Layers.push(new_layer);
        CurrentLayer = new_layer;
    }
};
#endif
