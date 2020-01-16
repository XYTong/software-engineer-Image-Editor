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
