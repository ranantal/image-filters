#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionTo_negative_triggered();

    void on_actionTo_B_W_triggered();

    void on_actionZoom_triggered();

    void on_actionBlur_triggered();

    void on_actionSharpen_triggered();

    void on_actionWaterColor_triggered();

    void on_actionC_to_B_triggered();

    void on_actionEmbossing_triggered();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
