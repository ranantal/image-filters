#ifndef ZONEB_H
#define ZONEB_H

#include <QtCore>
#include <QtGui>

#include <QWidget>

class ZoneB : public QWidget
{
    Q_OBJECT
public:
    explicit ZoneB(QWidget *parent = 0);

    void setOriginalImage(QImage originalImage) { this->originalImage = originalImage; }

    int getRealWidth() { return realWidth; }
    int getRealHeight() { return realHeight; }
    QImage getImage() { return image; }
    void setImage(QImage image) { this->image = image; repaint();}

protected:
    void paintEvent(QPaintEvent *) override;

private:
    QImage image;
    QImage originalImage;

    int realHeight;
    int realWidth;

signals:
    void imageChanged(QImage image);

public slots:
    void handleClickCoords(int x, int y);
};

#endif // ZONEB_H
