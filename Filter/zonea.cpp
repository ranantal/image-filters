#include "zonea.h"

#include <iostream>

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

ZoneA::ZoneA(QWidget *parent) : QWidget(parent)
{
    image = QImage(350, 350, QImage::Format_RGB32);
    memset(image.bits(), 255, image.byteCount());

    oldX = -1;
    oldY = -1;

    repaint();
}

void ZoneA::paintEvent(QPaintEvent *) {
    QPainter painter(this);

   // memset(image.bits(), 255, image.byteCount());

    painter.drawImage(0,\
                      0,\
                      image);
}

void ZoneA::mouseReleaseEvent(QMouseEvent *event) {
   // if (event->x() != oldX && event->y() != oldY)
    drawRectangle(event->x(), event->y());

    emit sendClickCoords((int)(oldX / scaleCoef), (int)(oldY / scaleCoef));
    repaint();
}

void ZoneA::mousePressEvent(QMouseEvent *event) {
    drawRectangle(event->x(), event->y());

    oldX = event->x();
    oldY = event->y();

    emit sendClickCoords((int)(oldX / scaleCoef), (int)(oldY / scaleCoef));

    repaint();
}

void ZoneA::mouseMoveEvent(QMouseEvent *event) {
   // if (oldX != -1 && oldY != -1)
    drawRectangle(oldX, oldY);

    oldX = event->x();
    oldY = event->y();

    emit sendClickCoords((int)(oldX / scaleCoef), (int)(oldY / scaleCoef));

    drawRectangle(event->x(), event->y());
    repaint();
}

void ZoneA::setImage(QImage originalImage) {
    memset(image.bits(), 255, image.byteCount());

    if (originalImage.height() > 350 || originalImage.width() > 350) {
        scaleCoef = (double)350 / (double)MAX(originalImage.height(), originalImage.width());
//        std::cout << scaleSize << std::endl;
//        originalImage = originalImage.scaled(\
                    350,\
                    350,\
                    Qt::KeepAspectRatio,\
                    Qt::SmoothTransformation);

        originalImage = scale(originalImage);

    } else
        scaleCoef = 1;

    realHeight = originalImage.height();
    realWidth = originalImage.width();

    uint *originalBits = (uint *)originalImage.bits();
    uint *bits = (uint *)image.bits();

    for (int i = 0; i < originalImage.height(); ++i) {
        for (int j = 0; j < originalImage.width(); ++j) {
            bits[i * image.width() + j] = originalBits[i * originalImage.width() + j];
        }
    }

    repaint();
}

QImage ZoneA::scale(QImage &originalImage) {
   // double scaleCoef = (double)350 / (double)MAX(originalImage.height(), originalImage.width());

    int newHeight, newWidth;

    if (originalImage.width() > originalImage.height()) {
        newWidth = 350;
        newHeight = scaleCoef * originalImage.height();
    } else {
        newHeight = 350;
        newWidth = scaleCoef * originalImage.width();
    }

    const int oldHeight = originalImage.height();
    const int oldWidth = originalImage.width();

    int h, w;

    float t;
    float u;
    float tmp;
    float d1, d2, d3, d4;
    QColor p1, p2, p3, p4;

    QImage result = QImage(newWidth, newHeight, originalImage.format());

    QRgb *oldBits = (QRgb *)originalImage.bits();
    QRgb *newBits = (QRgb *)result.bits();

    for (int j = 0; j < newHeight; ++j) {
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
        for (int i = 0; i < newWidth; ++i) {
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

            /* Коэффициенты */
            d1 = (1 - t) * (1 - u);
            d2 = t * (1 - u);
            d3 = t * u;
            d4 = (1 - t) * u;

            /* Окрестные пиксели: a[i][j] */
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

            newBits[j * newWidth + i] = qRgb(red, green, blue);
        }
    }

    return result;
}

void ZoneA::drawRectangle(int x, int y) {
    if (scaleCoef == 1.0)
        return;

    int size = 350 * scaleCoef;
    int halfHeight = MIN(size / 2, realHeight / 2);
    int halfWidth = MIN(size / 2, realWidth / 2);

    if (x < halfWidth)
        x = halfWidth;
    else if (x > realWidth - halfWidth - 1)
        x = realWidth - halfWidth;
    if (y < halfHeight)
        y = halfHeight;
    else if (y > realHeight - halfHeight - 1)
        y = realHeight - halfHeight;

    uint *bits = (uint *)image.bits();


    for (int i = -halfWidth; i <= halfWidth; ++i) {
        bits[(y - halfHeight) * image.width() + (i + x)] = 0xffffffff - bits[(y - halfHeight) * image.width() + (i + x)];
    }
    for (int i = -halfWidth; i <= halfWidth; ++i) {
        bits[(y + halfHeight) * image.width() + (i + x)] = 0xffffffff - bits[(y + halfHeight) * image.width() + (i + x)];
    }
    for (int i = -halfHeight; i <= halfHeight; ++i) {
        bits[(i + y) * image.width() + (x - halfWidth)] = 0xffffffff - bits[(i + y) * image.width() + (x - halfWidth)];
    }
    for (int i = -halfHeight; i <= halfHeight; ++i) {
        bits[(i + y) * image.width() + (x + halfWidth)] = 0xffffffff - bits[(i + y) * image.width() + (x + halfWidth)];
    }
}
