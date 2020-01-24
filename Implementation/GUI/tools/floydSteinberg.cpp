# include "floydSteinberg.h"

#include <sys/time.h>
#include <stdio.h>
#include <math.h>

QRgb FloydSteiberg::errorAdd(QColor orig, int err_r, int err_g, int err_b, int err_a, int weight){
    int new_rgb[4];
    new_rgb[0] = orig.red()+((err_r*weight)>>4);
    new_rgb[1] = orig.green()+((err_g*weight)>>4);
    new_rgb[2] = orig.blue()+((err_b*weight)>>4);
    new_rgb[3] = orig.alpha()+((err_a*weight)>>4);
    for (int i = 0; i < 4; i++){
        if (new_rgb[i] < 0){
            new_rgb[i] = 0;
        }
        if (new_rgb[i] >255){
            new_rgb[i] = 255;
        }
    }
    return QColor(new_rgb[0],new_rgb[1],new_rgb[2],new_rgb[3]).rgba();
}

//

QImage *FloydSteiberg::getIndexed(QImage* source, QVector<QRgb> colors){
    timeval t1;
    timeval t2;
    timeval t3;
    timeval t4;
    long t = 0;
    QImage *newImage = new QImage(source->size(),QImage::Format_Indexed8);
    newImage->setColorTable(colors);
    int width = source->width();
    int height = source->height();
    int k;
    int errorR;
    int errorG;
    int errorB;
    int errorA;
    QColor currentPixel;
    QColor nextPixel;
    QColor *nextRow = static_cast<QColor*>(malloc(sizeof (QColor)*width));
    QColor *thisRow = static_cast<QColor*>(malloc(sizeof (QColor)*width));
    QColor *x;
    // Floyd-Steinberg Dithering
    //  - * 7    where *=pixel being processed, -=previously processed pixel
    //  3 5 1    and pixel difference is distributed to neighbor pixels
    //           Note: 7+3+5+1=16 so we divide by 16 (>>4) before adding.

    for(int i = 1; i < width-1; i++){
        nextRow[i]=source->pixelColor(i,1);
    }
    gettimeofday(&t1,nullptr);
    for(int j = 0; j < height-1; j++){
        currentPixel = thisRow[0];
        for(int i = 0; i < width; i++){
            thisRow[i]=source->pixelColor(i,j);
        }
        //gettimeofday(&t3,nullptr);
        k = nearestColor(currentPixel, colors);
        //gettimeofday(&t4,nullptr);
        //t += (t4.tv_sec-t3.tv_sec)*1000000+t4.tv_usec-t3.tv_usec;
        newImage->setPixel(0,j,k);
        errorR = currentPixel.red() - qRed(colors[k]);
        errorG = currentPixel.green() - qGreen(colors[k]);
        errorB = currentPixel.blue() - qBlue(colors[k]);
        errorA = currentPixel.blue() - qAlpha(colors[k]);
        nextPixel=thisRow[1];
        nextPixel=errorAdd(nextPixel,errorR,errorG,errorB,errorA,7);
        nextRow[0]=errorAdd(nextRow[0],errorR,errorG,errorB,errorA,5);
        nextRow[1]=errorAdd(nextRow[1],errorR,errorG,errorB,errorA,1);
        for(int i = 1; i < width-1; i++){
            currentPixel = nextPixel;
            //gettimeofday(&t3,nullptr);
            k = nearestColor(currentPixel, colors);
            //gettimeofday(&t4,nullptr);
            //t += (t4.tv_sec-t3.tv_sec)*1000000+t4.tv_usec-t3.tv_usec;
            newImage->setPixel(i,j,k);
            errorR = currentPixel.red() - qRed(colors[k]);
            errorG = currentPixel.green() - qGreen(colors[k]);
            errorB = currentPixel.blue() - qBlue(colors[k]);
            errorA = currentPixel.blue() - qAlpha(colors[k]);
            nextPixel=thisRow[i+1];
            nextPixel=errorAdd(nextPixel,errorR,errorG,errorB,errorA,7);
            nextRow[i-1]=errorAdd(nextRow[i-1],errorR,errorG,errorB,errorA,3);
            nextRow[i]=errorAdd(nextRow[i],errorR,errorG,errorB,errorA,5);
            nextRow[i+1]=errorAdd(nextRow[i+1],errorR,errorG,errorB,errorA,1);
        }
        gettimeofday(&t3,nullptr);
        k = nearestColor(currentPixel, colors);
        gettimeofday(&t4,nullptr);
        t += (t4.tv_sec-t3.tv_sec)*1000000+t4.tv_usec-t3.tv_usec;
        newImage->setPixel(width-1,j,k);
        errorR = currentPixel.red() - qRed(colors[k]);
        errorG = currentPixel.green() - qGreen(colors[k]);
        errorB = currentPixel.blue() - qBlue(colors[k]);
        errorA = currentPixel.blue() - qAlpha(colors[k]);
        nextRow[width-2]=errorAdd(nextRow[width-2],errorR,errorG,errorB,errorA,5);
        nextRow[width-1]=errorAdd(nextRow[width-1],errorR,errorG,errorB,errorA,1);
        x = thisRow;
        thisRow=nextRow;
        nextRow=x;
    }
    for(int i = 0; i < width-1; i++){
        currentPixel = nextPixel;
        //gettimeofday(&t3,nullptr);
        k = nearestColor(currentPixel, colors);
        //gettimeofday(&t4,nullptr);
        //t += (t4.tv_sec-t3.tv_sec)*1000000+t4.tv_usec-t3.tv_usec;
        newImage->setPixel(i,height-1,k);
        errorR = currentPixel.red() - qRed(colors[k]);
        errorG = currentPixel.green() - qGreen(colors[k]);
        errorB = currentPixel.blue() - qBlue(colors[k]);
        errorA = currentPixel.blue() - qAlpha(colors[k]);
        nextPixel=thisRow[i+1];
        nextPixel=errorAdd(nextPixel,errorR,errorG,errorB,errorA,7);
    }
    k = nearestColor(thisRow[width-1], colors);
    newImage->setPixel(width-1,height-1,k);
    free(nextRow);
    free(thisRow);
    //gettimeofday(&t2,nullptr);
    //printf("%ld\n%ld\n%d x %d\n",(t2.tv_sec-t1.tv_sec)*1000000+t2.tv_usec-t1.tv_usec,t,width,height);
    //delete source;
    return newImage;
}

//

int FloydSteiberg::nearestColor(QColor color, QVector<QRgb> colorVect){
    int minDistanceSquared = 255 * 255 + 255 * 255 + 255 * 255 + 255 * 255 + 1;
    int bestIndex = 0;
    QRgb col = color.rgba();
    int Rdiff;
    int Gdiff;
    int Bdiff;
    int Adiff;
    int distanceSquared;
    for (int i = 0; i < 256; i++)
    {
        Rdiff = qRed(col) - qRed(colorVect[i]);
        Gdiff = qGreen(col) - qGreen(colorVect[i]);
        Bdiff = qBlue(col) - qBlue(colorVect[i]);
        Adiff = qAlpha(col) - qAlpha(colorVect[i]);
        if ((distanceSquared = Rdiff * Rdiff + Gdiff * Gdiff + Bdiff * Bdiff + Adiff * Adiff) < minDistanceSquared)
        {
            minDistanceSquared = distanceSquared;
            bestIndex = i;
            if (minDistanceSquared < 10) break;//TODO Find best value
        }
     }
     return bestIndex;
}
