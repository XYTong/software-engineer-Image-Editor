#include <opencv2/core/core.hpp>                                               
#include <opencv2/highgui/highgui.hpp>
#include <bits/stdc++.h>
#ifndef CV_RASTERIMAGE_H_H
#define CV_RASTERIMAGE_H_H
using namespace cv;
using namespace std;

class RasterImage{
private:
    int _width;
    int _height;
    char** Pixels;
    //Mat ColourMap;
public:
    RasterImage(int width, int height){
        this->_width = width;
        this->_height = height;
        //ColourMap(_height, _width, CV_8UC3, Scalar(0, 0, 0));
        Pixels = new char*[_height];
        for(int i = 0; i < _height; i++) Pixels[i] = new char[_width];
    }
    void change_pixel(int i , int j, char r, char g, char b){
        r = r >> 5;
        g = g >> 5;
        b = b >> 6;
        Pixels[i][j] = (r<<5)+(g<<2)+b;
    }
};
#endif
