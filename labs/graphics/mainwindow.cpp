#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    plane_ = new Plane(this);
    setCentralWidget(plane_);
    setWindowTitle("RayCaster");
}

MainWindow::~MainWindow() = default;
