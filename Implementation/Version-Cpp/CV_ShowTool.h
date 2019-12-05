#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <bits/stdc++.h>
//#include "CV_Picture.h"
//#include "CV_RasterImage.h"

using namespace cv;
using namespace std;

class ShowTool{
public:
    void show(Picture* pic, string pic_name){
        cout << "succeeded in calling of ShowTool" << endl;
        Mat img = imread(pic_name);
        int w = img.rows;
        int h = img.cols;
        cout << "w = " << w << "h = " << h << endl;
        RasterImage* r_i = new RasterImage(w,h);
        for(int i = 0; i < h; i++)
            for(int j = 0; j < w; j++){
                //cout << (int)img.at<Vec3b>(i,j)[3] << endl;
                unsigned char r = img.at<Vec3b>(i,j)[0];
                unsigned char g = img.at<Vec3b>(i,j)[1];
                unsigned char b = img.at<Vec3b>(i,j)[2];
                unsigned char t = img.at<Vec3b>(i,g)[3];
                r_i->change_pixel(i,j,r,g,b,t);
            }
        //r_i->print_pixels();
        pic->add_picture(r_i);
        r_i->show();
    }
};
