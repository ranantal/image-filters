#include "zoneb.h"

#include <iostream>

ZoneB::ZoneB(QWidget *parent) : QWidget(parent)
{
    image = QImage(350, 350, QImage::Format_RGB32);
    memset(image.bits(), 255, image.byteCount());

    realHeight = 350;
    realWidth = 350;

    repaint();
}

void ZoneB::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    painter.drawImage(0,\
                      0,\
                      image);
}

void ZoneB::handleClickCoords(int x, int y) {
    int halfHeight = 175;
    int halfWidth = 175;

    if (x < halfWidth)
        x = halfWidth;
    if (y < halfHeight)
        y = halfHeight;

    if (x >= originalImage.width() - halfWidth) {
        x = originalImage.width() - halfWidth - 1;
        if (x < halfWidth) {
            halfWidth = originalImage.width() / 2;
            x = halfWidth;
        }
    }

    if (y >= originalImage.height() - halfHeight) {
        y = originalImage.height() - halfHeight - 1;
        if (y < halfHeight) {
            halfHeight = originalImage.height() / 2;
            y = halfHeight;
        }
    }

    realHeight = halfHeight * 2;
    realWidth = halfWidth * 2;

    memset(image.bits(), 255, image.byteCount());

    uint *bits = (uint *)image.bits();
    uint *originalBits = (uint *)originalImage.bits();

    for (int i = -halfHeight; i < halfHeight; ++i) {
        for (int j = -halfWidth; j < halfWidth; ++j) {
            bits[(i + halfHeight) * 350 + j + halfWidth] = originalBits[(i + y) * originalImage.width() + j + x];
        }
    }

    emit imageChanged(image);

    repaint();
}
