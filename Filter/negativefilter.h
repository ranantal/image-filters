#ifndef NEGATIVEFILTER_H
#define NEGATIVEFILTER_H

#include "filter.h"

class NegativeFilter : public Filter {
public:
    void execute() {
        QImage result = image;
        uint *bits = (uint *)result.bits();
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                bits[i * result.width() + j] = 0xffffffff - bits[i * result.width() + j];
            }
        }

        emit sendImage(result);
    }

};

#endif // NEGATIVEFILTER_H
