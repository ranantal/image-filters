#ifndef ZOOMFILTER
#define ZOOMFILTER

#include "filter.h";

class ZoomFilter : public Filter {
public:
    void execute() {
       QImage result = image;

        const int oldHeight = image.height();
        const int oldWidth = image.width();
        const int newHeight = 2 * oldHeight;
        const int newWidth = 2 * oldWidth;

        int h, w;

        float t;
        float u;
        float tmp;
        float d1, d2, d3, d4;
        QColor p1, p2, p3, p4;

        QRgb *oldBits = (QRgb *)image.bits();
        QRgb *newBits = (QRgb *)result.bits();

        for (int j = 175; j < newHeight - 175; ++j) {
            tmp = (float) (j) / (float) (newHeight - 1) * (oldHeight - 1);
            h = (int) floor(tmp);

            if (h < 0) {
                h = 0;
            } else {
                if (h >= oldHeight - 1) {
                    h = oldHeight - 2;
                }
            }
            u = tmp - h;
            for (int i = 175; i < newWidth - 175; ++i) {
                tmp = (float) (i) / (float) (newWidth - 1) * (oldWidth - 1);

                w = (int) floor(tmp);
                if (w < 0) {
                    w = 0;
                } else {
                    if (w >= oldWidth - 1) {
                        w = oldWidth - 2;
                    }
                }
                t = tmp - w;

                d1 = (1 - t) * (1 - u);
                d2 = t * (1 - u);
                d3 = t * u;
                d4 = (1 - t) * u;

                p1 = oldBits[h * oldWidth + w];
                p2 = oldBits[h * oldWidth + w + 1];
                p3 = oldBits[(h + 1) * oldWidth + w + 1];
                p4 = oldBits[(h + 1) * oldWidth + w];

                u_char red = (u_char) p1.red() * d1 +
                        (u_char) p2.red() * d2 +
                        (u_char) p3.red() * d3 +
                        (u_char) p4.red() * d4;
                u_char green = (u_char) p1.green() * d1 +
                        (u_char) p2.green() * d2 +
                        (u_char) p3.green() * d3 +
                        (u_char) p4.green() * d4;
                u_char blue = (u_char) p1.blue() * d1 +
                        (u_char) p2.blue() * d2 +
                        (u_char) p3.blue() * d3 +
                        (u_char) p4.blue() * d4;

                newBits[(j - 175) * oldWidth + (i - 175)] = qRgb(red, green, blue);
            }
        }

        emit sendImage(result);
    }
};

#endif // ZOOMFILTER

