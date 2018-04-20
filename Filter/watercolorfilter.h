#ifndef WATERCOLORFILTER_H
#define WATERCOLORFILTER_H

#include "filter.h"

class WaterColorFilter : public Filter {
public:
    void execute() {
        double kernel1[5][5] = {
            { 1, 2, 3, 2, 1 },
            { 2, 4, 5, 4, 2 },
            { 3, 5, 6, 5, 3 },
            { 2, 4, 5, 4, 2 },
            { 1, 2, 3, 2, 1 }
        };

        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                kernel1[i][j] = kernel1[i][j] / 74;
            }
        }

        QImage tmp = applyConvolutionNxN((double *)kernel1, image, 5);

        const double kernel2[3][3] = {
            { -0.5, -0.5, -0.5 },
            { -0.5,  5, -0.5 },
            { -0.5, -0.5, -0.5 }
        };

        QImage result = applyConvolutionNxN((double *)kernel2, tmp, 3);

        emit sendImage(result);
    }
};

#endif // WATERCOLORFILTER_H
