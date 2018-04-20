#include "drawpanelwidget.h"
//#include "filterfactory.h"
#include <QSpacerItem>

#include <iostream>

DrawPanelWidget::DrawPanelWidget(QWidget *parent) : QWidget(parent) {
    layout = new QHBoxLayout(this);

    zoneA = new ZoneA();
    zoneB = new ZoneB();
    zoneC = new ZoneC();

    zoneA->setMinimumHeight(350);
    zoneA->setMinimumWidth(350);
    zoneA->setMaximumHeight(350);
    zoneA->setMaximumWidth(350);

    zoneB->setMinimumHeight(350);
    zoneB->setMinimumWidth(350);
    zoneB->setMaximumHeight(350);
    zoneB->setMaximumWidth(350);

    zoneC->setMinimumHeight(350);
    zoneC->setMinimumWidth(350);
    zoneC->setMaximumHeight(350);
    zoneC->setMaximumWidth(350);

    horizontalSpacer1 = new QSpacerItem(10, 10, QSizePolicy::Fixed, QSizePolicy::Fixed);
    horizontalSpacer2 = new QSpacerItem(10, 10, QSizePolicy::Fixed, QSizePolicy::Fixed);

    layout->addWidget(zoneA);
    layout->addItem(horizontalSpacer1);
    layout->addWidget(zoneB);
    layout->addItem(horizontalSpacer2);
    layout->addWidget(zoneC);

    connect(zoneA, SIGNAL(sendClickCoords(int,int)), zoneB, SLOT(handleClickCoords(int,int)));

    thread = new QThread();
    currentFilter = std::shared_ptr<Filter>(new Filter());

    currentFilter->moveToThread(thread);

    connect(currentFilter.get(), SIGNAL(sendRunning(bool)), this, SLOT(setRunning(bool)));
    connect(thread, SIGNAL(started()), currentFilter.get(), SLOT(execute()));
    connect(currentFilter.get(), SIGNAL(sendImage(QImage)), zoneC, SLOT(setImage(QImage)));
    connect(zoneB, SIGNAL(imageChanged(QImage)), currentFilter.get(), SLOT(setImage(QImage)));

    currentFilter->setImage(zoneB->getImage());

    thread->start();
}

void DrawPanelWidget::openImage(QString imageName) {
    QImage originalImage = QImage(imageName);

    if (originalImage.isNull())
        throw std::string("Can't open this file");

    zoneA->setImage(originalImage.convertToFormat(QImage::Format_RGB32));
    zoneB->setOriginalImage(originalImage.convertToFormat(QImage::Format_RGB32));

    currentFilter = std::shared_ptr<Filter>(new Filter());

    currentFilter->setHeight(zoneB->getRealHeight());
    currentFilter->setWidth(zoneB->getRealWidth());

   // thread = new QThread();

    currentFilter->moveToThread(thread);

    connect(thread, SIGNAL(started()), currentFilter.get(), SLOT(execute()));
    connect(currentFilter.get(), SIGNAL(sendImage(QImage)), zoneC, SLOT(setImage(QImage)));
    connect(zoneB, SIGNAL(imageChanged(QImage)), currentFilter.get(), SLOT(setImage(QImage)));

    currentFilter->setImage(zoneB->getImage());
}

void DrawPanelWidget::applyFilter(Filter *filter) {

    if (thread->isRunning())
        thread->quit();

    currentFilter = std::shared_ptr<Filter>(filter);

    currentFilter->setHeight(zoneB->getRealHeight());
    currentFilter->setWidth(zoneB->getRealWidth());
    currentFilter->setImage(zoneB->getImage());

    currentFilter->moveToThread(thread);

    connect(currentFilter.get(), SIGNAL(sendRunning(bool)), this, SLOT(setRunning(bool)));

    connect(thread, SIGNAL(started()), currentFilter.get(), SLOT(execute()));
    connect(currentFilter.get(), SIGNAL(sendImage(QImage)), zoneC, SLOT(setImage(QImage)));
    connect(zoneB, SIGNAL(imageChanged(QImage)), currentFilter.get(), SLOT(setImage(QImage)));


    thread->start();
}

void DrawPanelWidget::copyCtoB() {
    zoneB->setImage(zoneC->getImage());
}
