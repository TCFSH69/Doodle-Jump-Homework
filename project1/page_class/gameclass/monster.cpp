#include "monster.h"

Monster::Monster(QWidget *parent, QPoint platformPos) : QWidget(parent){
	switch (rand() % 4){
		case 0: monsterPixmap.load("./dataset/images/monster1.png"); monsterPixmap.scaledToWidth(MONSTER_WIDTH); break; //just to fit platform width
		case 1: monsterPixmap.load("./dataset/images/monster2.png"); monsterPixmap.scaledToWidth(MONSTER_WIDTH); break;
		case 2: monsterPixmap.load("./dataset/images/monster3.png"); monsterPixmap.scaledToWidth(MONSTER_WIDTH); break;
		case 3: monsterPixmap.load("./dataset/images/monster4.png"); monsterPixmap.scaledToWidth(MONSTER_WIDTH); break;
	}
	monsterLabel = Util::createImageLabel(monsterPixmap, parent);
	monsterLabel->setPixmap(monsterPixmap);
	monsterLabel->move(platformPos.x(), platformPos.y() - monsterLabel->height());
	intersecting = false;
}

void Monster::dropAnimation(QPoint platformPos, QWidget *parent, QLabel* doodleLabel, QPixmap monsterPixmap){
	QLabel *monsterLabel = new QLabel(parent);
	monsterLabel->show();
	monsterLabel->stackUnder(doodleLabel);
	monsterLabel->setFixedSize(monsterPixmap.size());
	monsterLabel->setPixmap(monsterPixmap);
	QPropertyAnimation *monsterDropAnimation = new QPropertyAnimation(monsterLabel, "pos");
    monsterDropAnimation->setDuration(1.25 * (WINDOW_HEIGHT - platformPos.y()));
    monsterDropAnimation->setStartValue(platformPos);
    monsterDropAnimation->setEndValue(QPoint(platformPos.x(), WINDOW_HEIGHT));
    monsterDropAnimation->start();
}