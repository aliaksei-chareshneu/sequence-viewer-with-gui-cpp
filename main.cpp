#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>

#include <QFileDialog>

#include "graphicwidget.h"
#include "application.h"

#include "global.h"

using namespace std;

// int error_number;

// int line_number;

int main(int argc, char *argv[])
{
//     int error_number = 0;
//     int line_number = 0;
    Application app(argc, argv);
    return app.run();
}

