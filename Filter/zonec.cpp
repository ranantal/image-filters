#include "zonec.h"

#include <iostream>

ZoneC::ZoneC(QWidget *parent) : QWidget(parent)
{
    image = QImage(350, 350, QImage::Format_RGB32);
    memset(image.bits(), 255, image.byteCount());

    repaint();
}

void ZoneC::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    painter.drawImage(0,\
                      0,\
                      image);
}
