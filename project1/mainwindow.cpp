#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
	srand((unsigned) time(NULL));
	
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    stackedWidget = new QStackedWidget(this);
    
    menuPage = new MenuPage(this);
    stackedWidget->addWidget(menuPage);

    gamePage = new GamePage(this);
    stackedWidget->addWidget(gamePage);

    setCentralWidget(stackedWidget);

}



