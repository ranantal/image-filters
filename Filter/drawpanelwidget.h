#ifndef DRAWPANELWIDGET_H
#define DRAWPANELWIDGET_H

#include <QtCore>
#include <QtGui>

#include <QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QScrollArea>

#include "zonea.h"
#include "zoneb.h"
#include "zonec.h"

#include "filter.h"

#include <memory>

class DrawPanelWidget : public QWidget
{
    Q_OBJECT
public:
    bool isRunning;
    explicit DrawPanelWidget(QWidget *parent = 0);

    void openImage(QString imageName);
    void applyFilter(Filter *filter);

    void copyCtoB();

private:
    QHBoxLayout *layout;

    QSpacerItem *horizontalSpacer1;
    QSpacerItem *horizontalSpacer2;

    ZoneA *zoneA;
    ZoneB *zoneB;
    ZoneC *zoneC;

    std::shared_ptr<Filter> currentFilter;
    QThread *thread;

signals:
    void stopThread();

public slots:
    void setRunning(bool var) { isRunning = var; zoneB->blockSignals(var); }
};

#endif // DRAWPANELWIDGET_H
