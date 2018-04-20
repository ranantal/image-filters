#ifndef SHARPENFILTER
#define SHARPENFILTER

#include "filter.h"

class SharpenFilter : public Filter {
public:
    void execute() {
        const double kernel[3][3] = {
            { -0.1, -0.1, -0.1 },
            { -0.1,  1.8, -0.1 },
            { -0.1, -0.1, -0.1 }
        };

        QImage result = applyConvolution3x3(kernel, image);

        emit sendImage(result);
    }
};

#endif // SHARPENFILTER

