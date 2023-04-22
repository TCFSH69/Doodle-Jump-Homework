#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "page_class/menupage.h"
#include "page_class/gamepage.h"

class MainWindow : public QMainWindow{
    Q_OBJECT
    public:
        MainWindow(QWidget *parent = 0);
    protected:

    private:
    	MenuPage *menuPage;
    	GamePage *gamePage;
		QStackedWidget *stackedWidget;
};
#endif