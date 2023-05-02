#include "platform.h"	

Platform::Platform(QWidget *parent, QString imagePath, int lastPlatformHeight, int min, int max) : QWidget(parent){
	platformPixmap.load(imagePath);
	platformLabel = Util::createImageLabel(platformPixmap, parent);
	randomGenerator(lastPlatformHeight, min, max);
}

Platform::Platform(QWidget *parent, QString imagePath, int x, int y) : QWidget(parent){
	platformPixmap.load(imagePath);
	platformLabel = Util::createImageLabel(platformPixmap, parent);
	platformLabel->move(x, y);
}

// Platform::~Platform(){
// 	if (platformLabel != NULL){
// 		delete platformLabel;
// 		platformLabel = NULL;
// 	}
// }

void Platform::randomGenerator(int lastPlatformHeight, int min, int max){ //distance with other platform from min to max(e.g 60~270)
	int x = Util::randomNumberGenerator(0, WINDOW_WIDTH - PLATFORM_WIDTH);
	int y = Util::randomNumberGenerator(lastPlatformHeight - max, lastPlatformHeight - min);
	platformLabel->move(x, y);
}

BasicPlatform::BasicPlatform(QWidget *parent, int lastPlatformHeight) : Platform(parent, "./dataset/images/stair-basic.png", lastPlatformHeight, 60, 270){
	platformKind = 0;
}

BrokenPlatform::BrokenPlatform(QWidget *parent, int lastPlatformHeight, int min, int max) : Platform(parent, "./dataset/images/stair-broken1.png", lastPlatformHeight, min, max){
	platformKind = 1;
}

BrokenPlatform::BrokenPlatform(QWidget *parent, int x, int y) : Platform(parent, "./dataset/images/stair-broken1.png", x, y){
	platformKind = 1;
}

void BrokenPlatform::dropAnimation(QPoint platformPos, QWidget *parent, QLabel* doodleLabel){
	QPixmap frame4Pixmap;
	frame4Pixmap.load("./dataset/images/stair-broken4.png");
	QLabel *frame4Label = new QLabel(parent);
	frame4Label->show();
	frame4Label->stackUnder(doodleLabel);
	frame4Label->setFixedSize(frame4Pixmap.size());
	frame4Label->setPixmap(frame4Pixmap);
	QPropertyAnimation *brokenPlatformDropAnimation = new QPropertyAnimation(frame4Label, "pos");
    brokenPlatformDropAnimation->setDuration(1.25 * (WINDOW_HEIGHT - platformPos.y()));
    brokenPlatformDropAnimation->setStartValue(platformPos);
    brokenPlatformDropAnimation->setEndValue(QPoint(platformPos.x(), WINDOW_HEIGHT));
    brokenPlatformDropAnimation->start();
}


MovingPlatform::MovingPlatform(QWidget *parent, int x, int y) : Platform(parent, "./dataset/images/stair-blue.png", x, y){
	platformKind = 2;
	movingRight = false;
}

void MovingPlatform::updateX(QLabel *itemLabel, QLabel *monsterLabel){
	int movingSpeed = 3;
	int x = platformLabel->pos().x();
	int y = platformLabel->pos().y();
	if (!movingRight && x - movingSpeed < 0){
		x = movingSpeed - x;
		movingRight = true;
	}
	else if(movingRight && x + PLATFORM_WIDTH + movingSpeed > WINDOW_WIDTH){
		x = 2 * WINDOW_WIDTH - 2 * PLATFORM_WIDTH - movingSpeed - x;
		movingRight = false;
	}
	else if (movingRight){
		x += movingSpeed;
	}
	else{
		x -= movingSpeed;
	}

	QPoint originalPos = platformLabel->pos();
	platformLabel->move(x, y);

	if (itemLabel != NULL) {
		QPoint offset = itemLabel->pos() - originalPos;
		itemLabel->move(platformLabel->pos() + offset);
	}
	if (monsterLabel != NULL) {
		QPoint offset = monsterLabel->pos() - originalPos;
		monsterLabel->move(platformLabel->pos() + offset);
	}
	
}

VanishingPlatform::VanishingPlatform(QWidget *parent, int x, int y) : Platform(parent, "./dataset/images/stair-disapear.png", x, y){
	platformKind = 3;
}
