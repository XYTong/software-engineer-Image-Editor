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
    unsigned char** Pixels;
    //Mat ColourMap;
public:
    RasterImage(int in_width, int in_height){
        this->_width = in_width;
        this->_height = in_height;
        //ColourMap(_height, _width, CV_8UC3, Scalar(0, 0, 0));
        Pixels = new unsigned char*[_height];
        for(int i = 0; i < _height; i++) Pixels[i] = new unsigned char[_width];
        cout << "Success of Initializing of RasterImage" << endl;
    }
    void change_pixel(int i , int j, unsigned char r, unsigned char g,unsigned char b,unsigned char t){
        r = r >> 6;
        g = g >> 6;
        b = b >> 6;
        t = t >> 6;
        Pixels[i][j] = (r<<6)+(g<<4)+(b<<2)+t;
        cout << (int)Pixels[i][j] << endl;
    }
    void print_pixels(){
        for (int i = 0; i < _height; i++){
            for (int j = 0; j < _width; j++){
                cout << (int)this->Pixels[i][j] << endl;                         

            }
        }
    }
    void show(){
        Mat ColourMap(_height,_width,CV_8UC3,Scalar(0,0,0));
        for(int i = 0; i < _height; i++){
            for(int j = 0; j < _width; j++){
                char temp = Pixels[i][j];
                ColourMap.at<Vec3b>(i,j)[3] = (int)temp%2;
                ColourMap.at<Vec3b>(i,j)[2] = (int)temp%8-(int)temp%2;
                ColourMap.at<Vec3b>(i,j)[1] = (int)temp%32-(int)temp%8-(int)temp%2;
                ColourMap.at<Vec3b>(i,j)[0] = temp>>6;
            }
        }
        imshow("picture",ColourMap);
        waitKey();
    }
};
#endif
