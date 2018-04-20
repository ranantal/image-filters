#ifndef ZONEA_H
#define ZONEA_H

#include <QtCore>
#include <QtGui>

#include <QWidget>

class ZoneA : public QWidget
{
    Q_OBJECT
public:
    explicit ZoneA(QWidget *parent = 0);

    void setImage(QImage originalImage);

    double getScale() {return scaleCoef; }

protected:
    void paintEvent(QPaintEvent *) override;

    void mouseReleaseEvent(QMouseEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;


private:
    QImage image;

    int realHeight;
    int realWidth;

    double scaleCoef;

    void drawRectangle(int x, int y);
    QImage scale(QImage &originalImage);

    int oldX;
    int oldY;

   // int currentX;
   // int currentY;

signals:
    void sendClickCoords(int x, int y);

public slots:
};

#endif // ZONEA_H
