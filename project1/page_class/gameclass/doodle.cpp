#include "doodle.h"

Doodle::Doodle(QWidget *parent) : QWidget(parent){
	doodleJumpingTime = 0;
	state = "normal";
	resetJump = false;
	invincible = false;
	turnRight = false;
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

void Doodle::positionUpdate(bool leftKeyPressed, bool rightKeyPressed, bool *hasTouchedViewBaseLine){ // update doodle position relative to the screen
	int newX, newY;

	newX = Util::xPositionSetting(doodleX, leftKeyPressed, rightKeyPressed);
	if (resetJump){
		doodleJumpingTime = 0;
		newY = jumpingBaseline - DOODLE_HEIGHT;
	}
	else{
		doodleJumpingTime++;
		newY = Util::yPositionSetting(state, doodleJumpingTime, jumpingBaseline);
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
        turnRight = false;
    } 
    else if (leftKeyPressed < rightKeyPressed) {
        doodleLabel->setPixmap(doodleRPixmap);
        turnRight = true;
    }
}


void Doodle::collisionCheck(QVector<GameObject*> &gameObjectVector){
	updateXY();
    if (state == "normal" && doodleJumpingTime <= NORMAL_JUMPING_PERIOD) return;
    if (state == "spring" && doodleJumpingTime <= SPRING_JUMPING_PERIOD) return;
    if (state == "trampoline" && doodleJumpingTime <= TRAMPOLINE_JUMPING_PERIOD) return;
    int platformX, monsterX, itemX;
    int platformY, monsterY, itemY;
    int i = 0;
    for (; i < gameObjectVector.size(); i++){
    	GameObject* gameObject = gameObjectVector[i];

    	Item *item = gameObject->item;
    	if (item != NULL){
    		itemX = item->itemLabel->pos().x();
    		itemY = item->itemLabel->pos().y();
    		if ((!turnRight && 
	    		doodleX >= itemX - DOODLE_WIDTH && 
	    		doodleX <= itemX + PLATFORM_WIDTH - DOODLE_FEET_OFFSET &&
	    		itemY - doodleY - DOODLE_HEIGHT <= 0 && 
	    		itemY - doodleY - DOODLE_HEIGHT >= -20)
				|| 
				(turnRight && 
				doodleX >= itemX - DOODLE_WIDTH + DOODLE_FEET_OFFSET &&
				doodleX <= itemX + PLATFORM_WIDTH && 
	    		itemY - doodleY - DOODLE_HEIGHT <= 0 && 
	    		itemY - doodleY - DOODLE_HEIGHT >= -20))
    		{
    			if (item->itemKind == 0){
    				Spring *spring = (Spring*) item;
    				spring->use();
    				state = "spring";
    				jumpingBaseline = itemY;
        			resetJump = true;
    			}
    			else if (item->itemKind == 1){
    				Trampoline *trampoline = (Trampoline*) item;
    				trampoline->use();
    				state = "trampoline";
    				jumpingBaseline = itemY;
        			resetJump = true;
    			}
    			break;
    		}
    	}


    	Platform *platform = gameObject->platform;
    	platformX = platform->platformLabel->pos().x();
    	platformY = platform->platformLabel->pos().y();
    	if ((!turnRight && 
    		doodleX >= platformX - DOODLE_WIDTH && 
    		doodleX <= platformX + PLATFORM_WIDTH - DOODLE_FEET_OFFSET &&
    		platformY - doodleY - DOODLE_HEIGHT <= 0 && 
    		platformY - doodleY - DOODLE_HEIGHT >= -20)
			|| 
			(turnRight && 
			doodleX >= platformX - DOODLE_WIDTH + DOODLE_FEET_OFFSET &&
			doodleX <= platformX + PLATFORM_WIDTH && 
    		platformY - doodleY - DOODLE_HEIGHT <= 0 && 
    		platformY - doodleY - DOODLE_HEIGHT >= -20))
    	{
    		if (platform->platformKind == 1){
    			BrokenPlatform::dropAnimation(platform->platformLabel->pos(), parentWidget(), doodleLabel);
    			gameObjectVector.removeOne(gameObject);
    			deleteObject(gameObject);
				i--;
    		}
    		else{
    			if (platform->platformKind == 3){
	    			gameObjectVector.removeOne(gameObject);
					deleteObject(gameObject);
					i--;
	    		}
	    		state = "normal";
    			jumpingBaseline = platformY;
        		resetJump = true;
    		}
    		break;
    	}
    }
}

void Doodle::updateXY(){
	doodleX = doodleLabel->pos().x();
	doodleY = doodleLabel->pos().y();
}

void Doodle::deleteObject(GameObject* gameObject){
	if (gameObject->platform != NULL && gameObject->platform->platformLabel != NULL) delete gameObject->platform->platformLabel;
    if (gameObject->platform != NULL) delete gameObject->platform;
    if (gameObject->item != NULL && gameObject->item->itemLabel != NULL) delete gameObject->item->itemLabel;
    if (gameObject->item != NULL) delete gameObject->item;
}