# include "floydSteinberg.h"

QRgb FloydSteiberg::errorAdd(QColor orig, int err_r, int err_g, int err_b, int weight){
    int new_rgb[3];
    new_rgb[0] = orig.red()+((err_r*weight)>>4);
    new_rgb[1] = orig.green()+((err_g*weight)>>4);
    new_rgb[2] = orig.blue()+((err_b*weight)>>4);
    for (int i = 0; i < 3; i++){
        if (new_rgb[i] < 0){
            new_rgb[i] = 0;
        }
        if (new_rgb[i] >255){
            new_rgb[i] = 255;
        }
    }
    return QColor(new_rgb[0],new_rgb[1],new_rgb[2]).rgb();
}

QImage *FloydSteiberg::getIndexed(QImage* source, QVector<QRgb> colors){
    QImage *newImage = new QImage(source->size(),QImage::Format_Indexed8);
    newImage->setColorTable(colors);
    int w = source->width();
    int h = source->height();
    int k;
    int errorR;
    int errorG;
    int errorB;
    QColor currentPixel;
    QColor nextPixel;
    QColor *nextRow = static_cast<QColor*>(malloc(sizeof (QColor)*w));
    QColor *thisRow = static_cast<QColor*>(malloc(sizeof (QColor)*w));
    QColor *x;
    // Floyd-Steinberg Dithering

    //  - * 7    where *=pixel being processed, -=previously processed pixel
    //  3 5 1    and pixel difference is distributed to neighbor pixels
    //           Note: 7+3+5+1=16 so we divide by 16 (>>4) before adding.
    for(int i = 1; i < w-1; i++){
        nextRow[i]=source->pixelColor(i,1);
    }
    for(int j = 0; j < h-1; j++){
        currentPixel = thisRow[0];
        for(int i = 1; i < w-1; i++){
            thisRow[i]=source->pixelColor(i,j);
        }
        k = nearestColor(currentPixel, colors);
        newImage->setPixel(0,j,k);
        errorR = currentPixel.red() - qRed(colors[k]);
        errorG = currentPixel.green() - qGreen(colors[k]);
        errorB = currentPixel.blue() - qBlue(colors[k]);
        nextPixel=thisRow[1];
        nextPixel=errorAdd(nextPixel,errorR,errorG,errorB,7);
        nextRow[0]=errorAdd(nextRow[0],errorR,errorG,errorB,5);
        nextRow[1]=errorAdd(nextRow[1],errorR,errorG,errorB,1);
        for(int i = 1; i < w-1; i++){
            currentPixel = nextPixel;
            k = nearestColor(currentPixel, colors);
            newImage->setPixel(i,j,k);
            errorR = currentPixel.red() - qRed(colors[k]);
            errorG = currentPixel.green() - qGreen(colors[k]);
            errorB = currentPixel.blue() - qBlue(colors[k]);
            nextPixel=thisRow[i+1];
            nextPixel=errorAdd(nextPixel,errorR,errorG,errorB,7);
            nextRow[i-1]=errorAdd(nextRow[i-1],errorR,errorG,errorB,3);
            nextRow[i]=errorAdd(nextRow[i],errorR,errorG,errorB,5);
            nextRow[i+1]=errorAdd(nextRow[i+1],errorR,errorG,errorB,1);
        }
        k = nearestColor(currentPixel, colors);
        newImage->setPixel(w-1,j,k);
        errorR = currentPixel.red() - qRed(colors[k]);
        errorG = currentPixel.green() - qGreen(colors[k]);
        errorB = currentPixel.blue() - qBlue(colors[k]);
        nextRow[w-2]=errorAdd(nextRow[w-2],errorR,errorG,errorB,5);
        nextRow[w-1]=errorAdd(nextRow[w-1],errorR,errorG,errorB,1);
        x = thisRow;
        thisRow=nextRow;
        nextRow=x;
    }
    free(nextRow);
    free(thisRow);
    delete source;
    return newImage;
}
int FloydSteiberg::nearestColor(QColor color, QVector<QRgb> colorVect){
    int minDistanceSquared = 255 * 255 + 255 * 255 + 255 * 255 + 1;
    int bestIndex = 0;
    QColor col = QColor(color);
    int Rdiff;
    int Gdiff;
    int Bdiff;
    int distanceSquared;
    for (int i = 0; i < 256; i++)
    {
        Rdiff = col.red() - QColor(colorVect[i]).red();
        Gdiff = col.green() - QColor(colorVect[i]).green();
        Bdiff = col.blue() - QColor(colorVect[i]).blue();
        distanceSquared = Rdiff * Rdiff + Gdiff * Gdiff + Bdiff * Bdiff;
        if (distanceSquared < minDistanceSquared)
        {
            minDistanceSquared = distanceSquared;
            bestIndex = i;
            if (minDistanceSquared < 100) break;//TODO Find best value
        }
     }
     return bestIndex;
}
