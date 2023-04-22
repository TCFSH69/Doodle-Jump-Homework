#include "doodle.h"

Doodle::Doodle(QWidget *parent) : QWidget(parent){
	doodleJumpingTime = 0;
	resetJump = false;
	jumpingBaseline = WINDOW_HEIGHT;
	pixmapLoad();
	doodleLabel = Util::createImageLabel(DOODLE_WIDTH, DOODLE_HEIGHT, doodleLPixmap, parent);
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
	//std::cout << newX << " " << newY << "\n";
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


void Doodle::collisionCheck(QVector<QVector<Platform*>> &objectVector){
	updateXY();
    //std::cout << doodle->doodleJumpingTime << "\n";
    if (doodleJumpingTime <= JUMPING_PERIOD / 2) return;
    int platformX, monsterX, itemX;
    int platformY, monsterY, itemY;
    for (Platform* platform: objectVector[0]){
    	QLabel *platformLabel = platform->platformLabel;
    	platformX = platformLabel->pos().x();
    	platformY = platformLabel->pos().y();
    	if (doodleX >= platformX - DOODLE_WIDTH && 
    	doodleX <= platformX + PLATFORM_WIDTH && 
    	platformY - doodleY - DOODLE_HEIGHT <= 0 && 
    	platformY - doodleY - DOODLE_HEIGHT >= -20){
        	jumpingBaseline = platformY;
        	resetJump = true;
    	}
    }
}

    /*
    }
    for (QLabel monsterLabel: objectVector[1]){
    	monsterX = monsterLabel->pos().x();
    	monsterY = monsterLabel->pos().y();
    }
    for (QLabel itemLabel: objectVector[2]){
    	itemX = itemLabel->pos().x();
    	itemY = itemLabel->pos().y();
    }
    */
    /*
    if (doodleX >= platformX - DOODLE_WIDTH && 
    	doodleX <= platformX + PLATFORM_WIDTH && 
    	platformY - doodleY - DOODLE_HEIGHT <= 0 && 
    	platformY - doodleY - DOODLE_HEIGHT >= -20){
        jumpingBaseline = platformY;
        resetJump = true;
    }
    */

void Doodle::updateXY(){
	doodleX = doodleLabel->pos().x();
	doodleY = doodleLabel->pos().y();
}

/*
bool Doodle::isPlatformCollide(){

}

bool Doodle::isMonsterCollide(){

}

bool Doodle::isItemCollide(){

}
*/


