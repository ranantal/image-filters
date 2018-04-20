#ifndef ZONEC_H
#define ZONEC_H

#include <QtCore>
#include <QtGui>

#include <QWidget>

class ZoneC : public QWidget
{
    Q_OBJECT
public:
    explicit ZoneC(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *) override;

private:
    QImage image;

public slots:
    void setImage(QImage image) { this->image = image; repaint();}
    QImage getImage() { return image; }
};

#endif // ZONEC_H
