#ifndef BULLET_H
#define BULLET_H

#include "../../util/util.h"

class Bullet : public QWidget{
    Q_OBJECT
    public:
        Bullet(QWidget *parent, QPoint doodlePos, QPoint mousePos);
        QPixmap bulletPixmap;
        QLabel *bulletLabel;
        double dx, dy;
};

#endif