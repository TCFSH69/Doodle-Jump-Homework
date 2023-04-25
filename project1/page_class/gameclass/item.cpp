#include "item.h"

Item::Item(QWidget *parent) : QWidget(parent){
	isUsed = false;
}

Spring::Spring(QWidget *parent, QPoint platformPos) : Item(parent){
	itemKind = 0;
	springPixmap1.load("./dataset/images/item-spring1.png");
	springPixmap2.load("./dataset/images/item-spring2.png");
	itemLabel = Util::createImageLabel(springPixmap1, parent);
	itemWidth = springPixmap1.width();
	itemHeight = springPixmap1.height();
	itemLabel->move(platformPos.x() + Util::randomNumberGenerator(0, PLATFORM_WIDTH - itemWidth), platformPos.y() - itemHeight);
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

Trampoline::Trampoline(QWidget *parent, QPoint platformPos) : Item(parent){
	itemKind = 1;
	trampolinePixmap1.load("./dataset/images/item-trampoline1.png");
	trampolinePixmap2.load("./dataset/images/item-trampoline3.png");
	itemLabel = Util::createImageLabel(trampolinePixmap1, parent);
	itemWidth = trampolinePixmap1.width();
	itemHeight = trampolinePixmap1.height();
	itemLabel->move(platformPos.x() + Util::randomNumberGenerator(0, PLATFORM_WIDTH - itemWidth), platformPos.y() - itemHeight);
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


PropellerHat::PropellerHat(QWidget *parent, QPoint platformPos) : Item(parent){
	itemKind = 2;
	propellerHatPixmap1.load("./dataset/images/item-propeller-hat.png");
	itemLabel = Util::createImageLabel(propellerHatPixmap1, parent);
	itemWidth = propellerHatPixmap1.width();
	itemHeight = propellerHatPixmap1.height();
	itemLabel->move(platformPos.x() + Util::randomNumberGenerator(0, PLATFORM_WIDTH - itemWidth), platformPos.y() - itemHeight);
}

void PropellerHat::use(){
	if (isUsed) return;
	itemLabel->hide();
    isUsed = true;
}

JetPack::JetPack(QWidget *parent, QPoint platformPos) : Item(parent){
	itemKind = 3;
	jetPackPixmap1.load("./dataset/images/item-jetpack.png");
	itemLabel = Util::createImageLabel(jetPackPixmap1, parent);
	itemWidth = jetPackPixmap1.width();
	itemHeight = jetPackPixmap1.height();
	itemLabel->move(platformPos.x() + Util::randomNumberGenerator(0, PLATFORM_WIDTH - itemWidth), platformPos.y() - itemHeight);
}

void JetPack::use(){
	if (isUsed) return;
	itemLabel->hide();
    isUsed = true;
}