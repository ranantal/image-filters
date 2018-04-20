#ifndef EMBOSSINGFILTER_H
#define EMBOSSINGFILTER_H

#include "filter.h"
#define MIN(x, y) ((x) < (y) ? (x) : (y))

class EmbossingFilter : public Filter {
public:
    void execute() {
        const double kernel[3][3] = {
            { 0, 1, 0 },
            { -1, 0, 1 },
            { 0, -1, 0 }
        };

        QImage result = applyConvolutionNxN((double *)kernel, image, 3);

        QRgb *bits = (QRgb *)result.bits();
        QColor p;

        for (int i = 0; i < result.height(); ++i) {
            for (int j = 0; j < result.width(); ++j) {
                p = bits[i * result.width() + j];
                bits[i * result.width() + j] = qRgb(\
                           MIN(p.red() + 128, 255),\
                           MIN(p.green() + 128, 255),\
                           MIN(p.blue() + 128, 255)\
                           );
            }
        }

        emit sendImage(result);
    }
};

#endif // EMBOSSINGFILTER_H
