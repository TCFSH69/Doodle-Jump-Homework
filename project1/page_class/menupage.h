#ifndef MENUPAGE_H
#define MENUPAGE_H

#include "../util/util.h"
#include "gamepage.h"

class MenuPage : public QMainWindow{
    Q_OBJECT
    public:
        MenuPage(QWidget *parent);
        void mousePressEvent(QMouseEvent *event);
    protected:

    private:
    	QPixmap menuBackgroundPixmap;
    	QLabel *menuBackgroundLabel;
};
#endif