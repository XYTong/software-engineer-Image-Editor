/* Class is responsible for correctly transforming an image from an arbitrary 4Byte
   format to IntelliPhoto 1Byte format by fitting it to current colormap granting
   a decent colour gradient. To this end the class implements the Floyd-Steinberg
   algorithm, a commonly used algorithm for such converting purposes.
   For further informations to the algoritm have a look at
   https://en.wikipedia.org/wiki/Floyd%E2%80%93Steinberg_dithering */

#include <QImage>

#ifndef FLOYDSTINBERG_H
#define FLOYDSTINBERG_H
class FloydSteiberg{
public:
    QImage *getIndexed(QImage* source, QVector<QRgb> colors);

private:
    int nearestColor(QColor color, QVector<QRgb> colorVect);
    QRgb errorAdd(QColor orig, int err_r, int err_g, int err_b, int err_a, int weight);
};




#endif // FLOYDSTINBERG_H
