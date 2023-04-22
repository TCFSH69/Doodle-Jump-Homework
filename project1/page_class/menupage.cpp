#include "menupage.h"
#include <iostream>

MenuPage::MenuPage(QWidget *parent) : QMainWindow(parent){
	menuBackgroundPixmap.load("./dataset/images/menu.jpg");
	menuBackgroundLabel = Util::createImageLabel(WINDOW_WIDTH, WINDOW_HEIGHT, menuBackgroundPixmap, this);
}

void MenuPage::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        QStackedWidget *stackedWidget = qobject_cast<QStackedWidget*>(parentWidget());
        if (stackedWidget){
        	GamePage *gamePage = qobject_cast<GamePage*>(stackedWidget->widget(1));
        	gamePage->setFocus();
        	gamePage->gameStart();
            stackedWidget->setCurrentIndex(1);
        }
    }
}