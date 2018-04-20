#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "negativefilter.h"
#include "bwfilter.h"
#include "zoomfilter.h"
#include "blurfilter.h"
#include "sharpenfilter.h"
#include "watercolorfilter.h"
#include "embossingfilter.h"

#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (fileName.isEmpty())
        return;

    try {
        ui->drawPanelWidget->openImage(fileName);
    } catch (std::string str) {
        QMessageBox::information(0, "Error", str.c_str());
    }
}

void MainWindow::on_actionTo_negative_triggered()
{
   // FilterFactory::getInstance().reg("NEGATIVE", NegativeFilter());
    ui->drawPanelWidget->applyFilter(new NegativeFilter());
}

void MainWindow::on_actionTo_B_W_triggered()
{
    ui->drawPanelWidget->applyFilter(new BWFilter());
}

void MainWindow::on_actionZoom_triggered()
{
    ui->drawPanelWidget->applyFilter(new ZoomFilter());
}

void MainWindow::on_actionBlur_triggered()
{
    ui->drawPanelWidget->applyFilter(new BlurFilter());
}

void MainWindow::on_actionSharpen_triggered()
{
    ui->drawPanelWidget->applyFilter(new SharpenFilter());
}

void MainWindow::on_actionWaterColor_triggered()
{
    ui->drawPanelWidget->applyFilter(new WaterColorFilter());
}

void MainWindow::on_actionC_to_B_triggered()
{
    ui->drawPanelWidget->copyCtoB();
}

void MainWindow::on_actionEmbossing_triggered()
{
    ui->drawPanelWidget->applyFilter(new EmbossingFilter());
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(0, "About", "Filter by Nikita Bychkov, group 14202\n\n2017 (c)");
}
