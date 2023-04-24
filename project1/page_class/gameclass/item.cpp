#include "item.h"

Item::Item(QWidget *parent, QPoint platformPos) : QWidget(parent){
	isUsed = false;
}

Spring::Spring(QWidget *parent, QPoint platformPos) : Item(parent, platformPos){
	itemKind = 0;
	springPixmap1.load("./dataset/images/item-spring1.png");
	springPixmap2.load("./dataset/images/item-spring2.png");
	itemLabel = Util::createImageLabel(springPixmap1, parent);
	itemWidth = springPixmap1.width();
	itemHeight = springPixmap1.height();
}

void Spring::use(){
	if (isUsed) return;
	itemLabel->setPixmap(springPixmap2);
	itemLabel->setFixedSize(springPixmap2.size());
    itemLabel->move(itemLabel->pos().x(), itemLabel->pos().y() - (springPixmap2.height() - itemHeight));
    itemWidth = springPixmap2.width();
	itemHeight = springPixmap2.height();
    isUsed = true;
}

Trampoline::Trampoline(QWidget *parent, QPoint platformPos) : Item(parent, platformPos){
	itemKind = 1;
	trampolinePixmap1.load("./dataset/images/item-trampoline1.png");
	trampolinePixmap2.load("./dataset/images/item-trampoline3.png");
	itemLabel = Util::createImageLabel(trampolinePixmap1, parent);
}

void Trampoline::use(){
	if (isUsed) return;
	itemLabel->setPixmap(trampolinePixmap2);
	itemLabel->setFixedSize(trampolinePixmap2.size());
    itemLabel->move(itemLabel->pos().x(), itemLabel->pos().y() - (trampolinePixmap2.height() - itemHeight));
    itemWidth = trampolinePixmap2.width();
	itemHeight = trampolinePixmap2.height();
    isUsed = true;
}


PropellerHat::PropellerHat(QWidget *parent, QPoint platformPos) : Item(parent, platformPos){
	itemKind = 2;
	propellerHatPixmap1.load("./dataset/images/item-propeller-hat.png");
	itemLabel = Util::createImageLabel(propellerHatPixmap1, parent);
}

void PropellerHat::use(){
	if (isUsed) return;
	itemLabel->hide();
    isUsed = true;
}

JetPack::JetPack(QWidget *parent, QPoint platformPos) : Item(parent, platformPos){
	itemKind = 3;
	jetPackPixmap1.load("./dataset/images/item-jetpack.png");
	itemLabel = Util::createImageLabel(jetPackPixmap1, parent);
}

void JetPack::use(){
	if (isUsed) return;
	itemLabel->hide();
    isUsed = true;
}