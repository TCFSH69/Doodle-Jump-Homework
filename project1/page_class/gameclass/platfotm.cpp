#include "platform.h"

Platform::Platform(QWidget *parent, QString imagePath, int lastPlatformHeight) : QWidget(parent){
	platformPixmap.load(imagePath);
	platformLabel = Util::createImageLabel(PLATFORM_WIDTH, PLATFORM_HEIGHT, platformPixmap, parent);
	randomGenerator(lastPlatformHeight);
}	

void Platform::randomGenerator(int lastPlatformHeight){
	int x = Util::randomNumberGenerator(0, WINDOW_WIDTH - PLATFORM_WIDTH);
	int y = Util::randomNumberGenerator(lastPlatformHeight - 270, lastPlatformHeight - 60);
	platformLabel->move(x, y);
}

BasicPlatform::BasicPlatform(QWidget *parent, int lastPlatformHeight) : Platform(parent, "./dataset/images/stair-basic.png", lastPlatformHeight){
	platformKind = 0;
}

MovingPlatform::MovingPlatform(QWidget *parent, int lastPlatformHeight) : Platform(parent, "./dataset/images/stair-blue.png", lastPlatformHeight){
	platformKind = 1;
}

BrokenPlatform::BrokenPlatform(QWidget *parent, int lastPlatformHeight) : Platform(parent, "./dataset/images/stair-broken1.png", lastPlatformHeight){
	platformKind = 2;
}

VanishingPlatform::VanishingPlatform(QWidget *parent, int lastPlatformHeight) : Platform(parent, "./dataset/images/stair-disapear.png", lastPlatformHeight){
	platformKind = 3;
}
