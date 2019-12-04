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
        Mat img = imread(pic_name);
        int w = img.rows;
        int h = img.cols;
        RasterImage* r_i = new RasterImage(w,h);
        for(int i = 0; i < w; i++)
            for(int j = 0; j < h; j++){
                char r = (char)img.at<Vec3b>(i,j)[0];
                char g = (char)img.at<Vec3b>(i,j)[1];
                char b = (char)img.at<Vec3b>(i,j)[2];
                r_i->change_pixel(i,j,r,g,b);
            }
        pic->add_picture(r_i);
    }
};
