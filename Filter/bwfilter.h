#ifndef BWFILTER_H
#define BWFILTER_H

#include "filter.h";

class BWFilter : public Filter {
public:
    void execute() {

        QImage result = image;

        const double redWeight = 0.299;
        const double greenWeight = 0.587;
        const double blueWeight = 0.114;

        QRgb *bits = (QRgb *)result.bits();

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                int average = 0;

                QColor color = bits[i * image.width() + j];

                average = (double)color.red() * redWeight +
                        (double)color.green() * greenWeight  +
                        (double)color.blue() * blueWeight;

                bits[i * image.width() + j] = qRgb(average, average, average);

            }
        }

        emit sendImage(result);
    }
};

#endif // BWFILTER_H
