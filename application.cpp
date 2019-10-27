#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>

#include "application.h"

#include "global.h"

using namespace std;

Application::Application(int &argc, char *argv[]) : QApplication(argc, argv)
{
    graphicWidget = 0;
    mainWindow = 0;
}

Application::~Application()
{
    if (graphicWidget != 0)
        delete graphicWidget;
    graphicWidget = 0;
    
    if (mainWindow !=0)
        delete mainWindow;
    mainWindow = 0;
}

int Application::run()
{
    mainWindow = new QWidget;
    mainWindow->setWindowTitle("Program for displaying sequence from PDB file");
    
    graphicWidget = new GraphicWidget;

    graphicWidget->setMinimumSize(310, 950);
    QPushButton* buttonHide = new QPushButton("Hide");
    QPushButton* buttonShow = new QPushButton("Show");
    QPushButton* buttonOpenFile = new QPushButton("Open file");
    
    QObject::connect(buttonHide, SIGNAL(clicked()), graphicWidget, SLOT(hideGraphic()));
    
    QObject::connect(buttonShow, SIGNAL(clicked()), graphicWidget, SLOT(showGraphic()));
    
    QObject::connect(buttonOpenFile, SIGNAL(clicked()), graphicWidget, SLOT(openFile()));
    
    QVBoxLayout* rightLayout = new QVBoxLayout;
    rightLayout->addWidget(buttonHide);
    rightLayout->addWidget(buttonShow);
    rightLayout->addWidget(buttonOpenFile);
    rightLayout->addStretch();
    
    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(graphicWidget);
    mainLayout->addLayout(rightLayout);
    
    mainWindow->setLayout(mainLayout);

    mainWindow->show();
    
    return QApplication::exec();
}