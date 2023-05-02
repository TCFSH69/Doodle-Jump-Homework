#include "doodle.h"

Doodle::Doodle(QWidget *parent) : QWidget(parent){
	doodleJumpingTime = 0;
	animationTick = 0;
	hp = 3;
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

	doodleH1L.load("./dataset/images/doodleH/doodleH1L.png");
	doodleH2L.load("./dataset/images/doodleH/doodleH2L.png");
	doodleH3L.load("./dataset/images/doodleH/doodleH3L.png");
	doodleH4L.load("./dataset/images/doodleH/doodleH4L.png");

	doodleHLVector = {doodleH1L, doodleH2L, doodleH3L, doodleH4L};

	doodleH1R.load("./dataset/images/doodleH/doodleH1R.png");
	doodleH2R.load("./dataset/images/doodleH/doodleH2R.png");
	doodleH3R.load("./dataset/images/doodleH/doodleH3R.png");
	doodleH4R.load("./dataset/images/doodleH/doodleH4R.png");

	doodleHRVector = {doodleH1R, doodleH2R, doodleH3R, doodleH4R};

	doodleJ1L.load("./dataset/images/doodleJ/doodleJ1L.png");
	doodleJ2L.load("./dataset/images/doodleJ/doodleJ2L.png");
	doodleJ3L.load("./dataset/images/doodleJ/doodleJ3L.png");
	doodleJ4L.load("./dataset/images/doodleJ/doodleJ4L.png");
	doodleJ5L.load("./dataset/images/doodleJ/doodleJ5L.png");
	doodleJ6L.load("./dataset/images/doodleJ/doodleJ6L.png");
	doodleJ7L.load("./dataset/images/doodleJ/doodleJ7L.png");
	doodleJ8L.load("./dataset/images/doodleJ/doodleJ8L.png");
	doodleJ9L.load("./dataset/images/doodleJ/doodleJ9L.png");
	doodleJ10L.load("./dataset/images/doodleJ/doodleJ10L.png");

	doodleJLVector = {doodleJ1L, doodleJ2L, doodleJ3L, doodleJ4L, doodleJ5L, doodleJ6L, doodleJ7L, doodleJ8L, doodleJ9L, doodleJ10L};

	doodleJ1R.load("./dataset/images/doodleJ/doodleJ1R.png");
	doodleJ2R.load("./dataset/images/doodleJ/doodleJ2R.png");
	doodleJ3R.load("./dataset/images/doodleJ/doodleJ3R.png");
	doodleJ4R.load("./dataset/images/doodleJ/doodleJ4R.png");
	doodleJ5R.load("./dataset/images/doodleJ/doodleJ5R.png");
	doodleJ6R.load("./dataset/images/doodleJ/doodleJ6R.png");
	doodleJ7R.load("./dataset/images/doodleJ/doodleJ7R.png");
	doodleJ8R.load("./dataset/images/doodleJ/doodleJ8R.png");
	doodleJ9R.load("./dataset/images/doodleJ/doodleJ9R.png");
	doodleJ10R.load("./dataset/images/doodleJ/doodleJ10R.png");

	doodleJRVector = {doodleJ1R, doodleJ2R, doodleJ3R, doodleJ4R, doodleJ5R, doodleJ6R, doodleJ7R, doodleJ8R, doodleJ9R, doodleJ10R};

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
	QPixmap leftPixmap = doodleLPixmap;
	QPixmap rightPixmap = doodleRPixmap;
	if (state == "propellerHat"){
		if (doodleJumpingTime <= PROPELLERHAT_JUMPING_PERIOD * 3 / 4.0f){
			leftPixmap = doodleHLVector[1 + (animationTick % (doodleHLVector.size() - 1))];
			rightPixmap = doodleHRVector[1 + (animationTick % (doodleHRVector.size()) - 1)];
		}
		else if (doodleJumpingTime <= PROPELLERHAT_JUMPING_PERIOD){
			leftPixmap = doodleHLVector[0];
			rightPixmap = doodleHRVector[0];
		}
		else{
			animationTick = 0;
		}
	}
	else if (state == "jetPack" && doodleJumpingTime <= JETPACK_JUMPING_PERIOD){
		if (doodleJumpingTime <= JETPACK_JUMPING_PERIOD / 12.0f){
			leftPixmap = doodleJLVector[0];
			rightPixmap = doodleJRVector[0];
		}
		else if (doodleJumpingTime <= JETPACK_JUMPING_PERIOD / 6.0f){
			leftPixmap = doodleJLVector[1];
			rightPixmap = doodleJRVector[1];
		}
		else if (doodleJumpingTime <= JETPACK_JUMPING_PERIOD / 4.0f){
			leftPixmap = doodleJLVector[2];
			rightPixmap = doodleJRVector[2];
		}
		else if (doodleJumpingTime <= JETPACK_JUMPING_PERIOD * 3 / 4.0f){
			leftPixmap = doodleJLVector[3 + (animationTick % 3)];
			rightPixmap = doodleJRVector[3 + (animationTick % 3)];
		}
		else if (doodleJumpingTime <= JETPACK_JUMPING_PERIOD * 13 / 16.0f){
			leftPixmap = doodleJLVector[6];
			rightPixmap = doodleJRVector[6];
		}
		else if (doodleJumpingTime <= JETPACK_JUMPING_PERIOD * 7 / 8.0f){
			leftPixmap = doodleJLVector[7];
			rightPixmap = doodleJRVector[7];
		}
		else if (doodleJumpingTime <= JETPACK_JUMPING_PERIOD * 15 / 16.0f){
			leftPixmap = doodleJLVector[8];
			rightPixmap = doodleJRVector[8];
		}
		else if (doodleJumpingTime <= JETPACK_JUMPING_PERIOD){
			leftPixmap = doodleJLVector[9];
			rightPixmap = doodleJRVector[9];
		}
		else{
			animationTick = 0;
		}
	}
	if (leftKeyPressed > rightKeyPressed) {
        doodleLabel->setPixmap(leftPixmap);
        doodleLabel->setFixedSize(leftPixmap.size());
        turnRight = false;
    } 
    else if (leftKeyPressed < rightKeyPressed) {
        doodleLabel->setPixmap(rightPixmap);
        doodleLabel->setFixedSize(rightPixmap.size());
        turnRight = true;
    }
    else{
    	if (!turnRight){
    		doodleLabel->setPixmap(leftPixmap);
        	doodleLabel->setFixedSize(leftPixmap.size());
    	}
    	else{
    		doodleLabel->setPixmap(rightPixmap);
        	doodleLabel->setFixedSize(rightPixmap.size());
    	}
    }
    animationTick++;
}


void Doodle::collisionCheck(QVector<GameObject*> &gameObjectVector){
	updateXY();
    if (state == "spring" && doodleJumpingTime <= SPRING_JUMPING_PERIOD) return;
    if (state == "trampoline" && doodleJumpingTime <= TRAMPOLINE_JUMPING_PERIOD) return;
    if (state == "propellerHat" && doodleJumpingTime <= PROPELLERHAT_JUMPING_PERIOD) return;
    if (state == "jetPack" && doodleJumpingTime <= JETPACK_JUMPING_PERIOD) return;
    int platformX, monsterX, itemX;
    int platformY, monsterY, itemY;
    int i = 0;

    for (; i < gameObjectVector.size(); i++){
    	GameObject* gameObject = gameObjectVector[i];
    	Monster *monster = gameObject->monster;
    	if (monster != NULL){
			monsterX = monster->monsterLabel->pos().x();
			monsterY = monster->monsterLabel->pos().y();
			if (monster->intersecting == false){
				if (doodleLabel->geometry().intersects(monster->monsterLabel->geometry())){
					if ((!turnRight && 
			    		doodleX >= monsterX - DOODLE_WIDTH && 
			    		doodleX <= monsterX + MONSTER_WIDTH - DOODLE_FEET_OFFSET &&
			    		monsterY - doodleY - DOODLE_HEIGHT <= 0 && 
			    		monsterY - doodleY - DOODLE_HEIGHT >= -20)
						|| 
						(turnRight && 
						doodleX >= monsterX - DOODLE_WIDTH + DOODLE_FEET_OFFSET &&
						doodleX <= monsterX + MONSTER_WIDTH && 
			    		monsterY - doodleY - DOODLE_HEIGHT <= 0 && 
			    		monsterY - doodleY - DOODLE_HEIGHT >= -20))
					{
						state = "normal";
		    			jumpingBaseline = monsterY;
		        		resetJump = true;
		        		Monster::dropAnimation(gameObject->platform->platformLabel->pos(), parentWidget(), doodleLabel, monster->monsterPixmap);
		        		delete monster->monsterLabel;
		        		delete monster;
		        		gameObject->monster = NULL;
					}
					else{
						hp -= 1;
						std::cout << hp << "\n";
						monster->intersecting = true;
					}
				}
			}
			else{
				if (!(doodleLabel->geometry().intersects(monster->monsterLabel->geometry()))){
					monster->intersecting = false;
				}
			}
    	}

    	Item *item = gameObject->item;
    	if (item != NULL){
    		itemX = item->itemLabel->pos().x();
    		itemY = item->itemLabel->pos().y();
    		if(doodleLabel->geometry().intersects(item->itemLabel->geometry())){
    			if (item->itemKind == 2){
    				PropellerHat *propellerHat = (PropellerHat*) item;
    				propellerHat->use();
    				state = "propellerHat";
    				jumpingBaseline = doodleLabel->pos().y() + DOODLE_HEIGHT;
        			resetJump = true;
        			break;
    			}
    			else if (item->itemKind == 3){
    				JetPack *jetPack = (JetPack*) item;
    				jetPack->use();
    				state = "jetPack";
    				jumpingBaseline = doodleLabel->pos().y() + DOODLE_HEIGHT;
        			resetJump = true;
        			break;
    			}
    		}
    		if (state == "normal" && doodleJumpingTime <= NORMAL_JUMPING_PERIOD) continue;
    		if ((!turnRight && 
	    		doodleX >= itemX - DOODLE_WIDTH && 
	    		doodleX <= itemX + item->itemLabel->width() - DOODLE_FEET_OFFSET &&
	    		itemY - doodleY - DOODLE_HEIGHT <= 0 && 
	    		itemY - doodleY - DOODLE_HEIGHT >= -20)
				|| 
				(turnRight && 
				doodleX >= itemX - DOODLE_WIDTH + DOODLE_FEET_OFFSET &&
				doodleX <= itemX + item->itemLabel->width() && 
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
    	if (state == "normal" && doodleJumpingTime <= NORMAL_JUMPING_PERIOD) continue;
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
    if (gameObject->platform != NULL){
    	delete gameObject->platform;
    	gameObject->platform = NULL;
    }
    if (gameObject->item != NULL && gameObject->item->itemLabel != NULL) delete gameObject->item->itemLabel;
    if (gameObject->item != NULL){
    	delete gameObject->item;
    	gameObject->item = NULL;
    }
    if (gameObject->monster != NULL && gameObject->monster->monsterLabel != NULL) delete gameObject->monster->monsterLabel;
    if (gameObject->monster != NULL){
    	delete gameObject->monster;
    	gameObject->monster = NULL;
    }
}