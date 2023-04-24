#include "doodle.h"

Doodle::Doodle(QWidget *parent) : QWidget(parent){
	doodleJumpingTime = 0;
	resetJump = false;
	invincible = false;
	jumpingBaseline = WINDOW_HEIGHT;
	pixmapLoad();
	doodleLabel = Util::createImageLabel(doodleLPixmap, parent);
	Util::setAlignment(doodleLabel, "Center", "Bottom", parentWidget()->parentWidget()->size(), doodleLabel->size());
	updateXY();
	doodleLabel->raise();
}

void Doodle::pixmapLoad(){
	doodleLPixmap.load("./dataset/images/doodleL.png");
	doodleRPixmap.load("./dataset/images/doodleR.png");
	doodleSPixmap.load("./dataset/images/doodleS.png");
	doodleLRPixmap.load("./dataset/images/doodleUL.png");
	doodleURPixmap.load("./dataset/images/doodleUR.png");
}

void Doodle::positionUpdate(bool leftKeyPressed, bool rightKeyPressed, bool *hasTouchedViewBaseLine){
	int newX, newY;

	newX = Util::xPositionSetting(doodleX, leftKeyPressed, rightKeyPressed);
	if (resetJump){
		doodleJumpingTime = 0;
		newY = jumpingBaseline - DOODLE_HEIGHT;
	}
	else{
		doodleJumpingTime++;
		newY = Util::yPositionSetting(doodleJumpingTime, jumpingBaseline);
	}

	
	if (newY > WINDOW_HEIGHT - DOODLE_HEIGHT){
		/*
		doodleJumpingTime = 0;
		newY = WINDOW_HEIGHT - DOODLE_HEIGHT;
		jumpingBaseline = WINDOW_HEIGHT;
		*/
		std::cout << "game over\n";
		QCoreApplication::quit();
	}


	if (!(*hasTouchedViewBaseLine) && newY < WINDOW_HEIGHT / 2){
		*hasTouchedViewBaseLine = true;
	}
    doodleLabel->move(newX, newY);
    updateXY();
    orientationUpdate(leftKeyPressed, rightKeyPressed);
}

void Doodle::orientationUpdate(bool leftKeyPressed, bool rightKeyPressed){
	if (leftKeyPressed > rightKeyPressed) {
        doodleLabel->setPixmap(doodleLPixmap);
    } 
    else if (leftKeyPressed < rightKeyPressed) {
        doodleLabel->setPixmap(doodleRPixmap);
    }
}


void Doodle::collisionCheck(QVector<QPair<Platform*, int>> &platformVector){
	updateXY();
    if (doodleJumpingTime <= JUMPING_PERIOD / 2) return;
    int platformX, monsterX, itemX;
    int platformY, monsterY, itemY;

    for (int i = 0; i < platformVector.size(); i++){
    	Platform *platform = platformVector[i].first;
    	platformX = platform->platformLabel->pos().x();
    	platformY = platform->platformLabel->pos().y();
    	if (doodleX >= platformX - DOODLE_WIDTH && 
    	doodleX <= platformX + PLATFORM_WIDTH && 
    	platformY - doodleY - DOODLE_HEIGHT <= 0 && 
    	platformY - doodleY - DOODLE_HEIGHT >= -20){
    		if (platform->platformKind == 1){
    			BrokenPlatform::dropAnimation(platform->platformLabel->pos(), parentWidget(), doodleLabel);
    			platformVector.remove(i);
				delete platform->platformLabel;
				delete platform;
				i--;
    		}
    		else{
    			if (platform->platformKind == 3){
	    			platformVector.remove(i);
					delete platform->platformLabel;
					delete platform;
					i--;
	    		}
    			jumpingBaseline = platformY;
        		resetJump = true;
    		}
    	}
    }
}

void Doodle::updateXY(){
	doodleX = doodleLabel->pos().x();
	doodleY = doodleLabel->pos().y();
}

