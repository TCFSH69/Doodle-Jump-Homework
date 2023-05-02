#ifndef MONSTER_H
#define MONSTER_H

#include "../../util/util.h"

class Monster : public QWidget{
    Q_OBJECT
    public:
        Monster(QWidget *parent, QPoint platformPos);
        QLabel *monsterLabel;
        static void dropAnimation(QPoint platformPos, QWidget *parent, QLabel* doodleLabel, QPixmap monsterPixmap);
        bool intersecting;
        QPixmap monsterPixmap;

    protected:
    	
    	
};

#endif