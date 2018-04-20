#ifndef BLURFILTER
#define BLURFILTER

#include "filter.h"

class BlurFilter : public Filter {
public:
    void execute() {

        double kernel[5][5] = {
            { 1, 2, 3, 2, 1 },
            { 2, 4, 5, 4, 2 },
            { 3, 5, 6, 5, 3 },
            { 2, 4, 5, 4, 2 },
            { 1, 2, 3, 2, 1 }
        };

        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                kernel[i][j] = kernel[i][j] / 74;
            }
        }


        QImage result = applyConvolutionNxN((double *)kernel, image, 5);

        emit sendImage(result);
    }
};

#endif // BLURFILTER

