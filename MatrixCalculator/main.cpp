#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QCoreApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <QDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;      // creates a new window object

    w.showMaximized();
    w.setFixedSize(1200, 600);   // sets the window's size
    w.move(QApplication::desktop()->screen()->rect().center()-w.rect().center()); // window will appear in middle of screen
    w.show();

    return a.exec();
}
