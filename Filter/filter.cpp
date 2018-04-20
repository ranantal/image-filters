#include "filter.h"

QImage applyConvolution3x3(const double kernel[3][3], QImage& image) {
    QImage result = image;

  //  QRgb *oldBits = (uint *)image.bits();
    QRgb *newBits = (uint *)result.bits();

    QColor p1, p2, p3, p4, p5, p6, p7, p8, p9;
    short red, green, blue;

    for (int i = 0; i < image.height(); ++i) {
        for (int j = 0; j < image.width(); ++j) {

            p1 = getPixel(image, i - 1, j - 1);
            p2 = getPixel(image, i - 1, j - 0);
            p3 = getPixel(image, i - 1, j + 1);
            p4 = getPixel(image, i - 0, j - 1);
            p5 = getPixel(image, i - 0, j - 0);
            p6 = getPixel(image, i - 0, j + 1);
            p7 = getPixel(image, i + 1, j - 1);
            p8 = getPixel(image, i + 1, j - 0);
            p9 = getPixel(image, i + 1, j + 1);

            red = p1.red() * kernel[0][0] +
                    p2.red() * kernel[0][1] +
                    p3.red() * kernel[0][2] +
                    p4.red() * kernel[1][0] +
                    p5.red() * kernel[1][1] +
                    p6.red() * kernel[1][2] +
                    p7.red() * kernel[2][0] +
                    p8.red() * kernel[2][1] +
                    p9.red() * kernel[2][2];

            if (red < 0)
                red = 0;
            if (red > 255)
                red = 255;

            green = p1.green() * kernel[0][0] +
                    p2.green() * kernel[0][1] +
                    p3.green() * kernel[0][2] +
                    p4.green() * kernel[1][0] +
                    p5.green() * kernel[1][1] +
                    p6.green() * kernel[1][2] +
                    p7.green() * kernel[2][0] +
                    p8.green() * kernel[2][1] +
                    p9.green() * kernel[2][2];

            if (green < 0)
                green = 0;
            if (green > 255)
                green = 255;

            blue = p1.blue() * kernel[0][0] +
                    p2.blue() * kernel[0][1] +
                    p3.blue() * kernel[0][2] +
                    p4.blue() * kernel[1][0] +
                    p5.blue() * kernel[1][1] +
                    p6.blue() * kernel[1][2] +
                    p7.blue() * kernel[2][0] +
                    p8.blue() * kernel[2][1] +
                    p9.blue() * kernel[2][2];

            if (blue < 0)
                blue = 0;
            if (blue > 255)
                blue = 255;

            newBits[i * result.width() + j] = qRgb(red, green, blue);
        }
    }

    return result;
}

QImage applyConvolutionNxN(const double *kernel, QImage image, const int n) {
    if (n < 0)
        return image;
    if (n % 2 == 0)
        return image;

    QImage result = image;
    QRgb *newBits = (uint *)result.bits();

    float red, green, blue;
    QColor p;

    for (int i = 0; i < result.height(); ++i) {
        for (int j = 0; j < result.width(); ++j) {
            red = 0;
            green = 0;
            blue = 0;

            for (int k = 0; k < n; ++k) {
                for (int m = 0; m < n; ++m) {
                    p = getPixel(image, i + k - (n / 2), j + m - (n / 2));
                    red += (float)p.red() * kernel[k * n + m];
                    green += (float)p.green() * kernel[k * n + m];
                    blue += (float)p.blue() * kernel[k * n + m];
                }
            }

            if (red < 0)
                red = 0;
            if (red > 255)
                red = 255;

            if (green < 0)
                green = 0;
            if (green > 255)
                green = 255;

            if (blue < 0)
                blue = 0;
            if (blue > 255)
                blue = 255;

            newBits[i * result.width() + j] = qRgb((int)red, (int)green, (int)blue);

        }
    }

    return result;
}

QColor getPixel(const QImage& image, int y, int x) {
    if (x < 0)
        x = 0;
    if (x > image.width() - 1)
        x = image.width() - 1;
    if (y < 0)
        y = 0;
    if (y > image.height() - 1)
        y = image.height() - 1;


    QRgb *bits = (QRgb *)image.bits();

    return bits[y * image.width() + x];
}
