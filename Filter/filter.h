#ifndef FILTER_H
#define FILTER_H

#include <QImage>
#include <QObject>
#include <QColor>

class Filter : public QObject {
    Q_OBJECT
protected:
    int width;
    int height;

    bool isRunning;

    QImage image;
public:
    void setHeight(int height) { this->height = height; }
    void setWidth(int width) { this->width = width; }


public slots:
    virtual void execute() {
        emit sendImage(image);
    }

    void setImage(QImage image) {
        this->image = image;
        emit sendRunning(true);
        execute();
        emit sendRunning(false);
    }

signals:
    void sendImage(QImage image);
    void sendRunning(bool var);
};

QColor getPixel(const QImage& image, int y, int x);
QImage applyConvolution3x3(const double kernel[3][3], QImage& image);
QImage applyConvolutionNxN(const double *kernel, QImage image, const int n);

#endif // FILTER_H
