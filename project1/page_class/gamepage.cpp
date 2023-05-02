#include "gamepage.h"

GamePage::GamePage(QWidget *parent) : QMainWindow(parent){
	score = 0;
    brokenPlatformTargetScore = 0;
    movingPlatformTargetScore = 5000;
    vanishingPlatformTargetScore = 8000;
    itemGenerationTargetScore = 2000;
    monsterGenerationTargetScore = 2000;
    absoluteHeight = 0;
    hasTouchedViewBaseLine = false;
	leftKeyPressed = false;
	rightKeyPressed = false;
    viewBaseline = WINDOW_HEIGHT / 2;
}

void GamePage::gameStart(){
	gameBackgroundPixmap.load("./dataset/images/background.png");
	gameBackgroundLabel = Util::createImageLabel(gameBackgroundPixmap, this);
	gameBackgroundLabel->lower();
	
    doodle = new Doodle(this);
    generatePlatforms();
    monsterGenerator();

	gameLoopTimer = new QTimer(this);
    connect(gameLoopTimer, &QTimer::timeout, this, &GamePage::gameLoop);
    gameLoopTimer->setTimerType(Qt::PreciseTimer);
    gameLoopTimer->start(12);
}

void GamePage::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        Bullet *bullet = new Bullet(this, doodle->doodleLabel->pos(), event->pos());
        bulletVector.push_back(bullet);
    }
}

void GamePage::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Left){
    	leftKeyPressed = true;
    }
    else if (event->key() == Qt::Key_Right){
    	rightKeyPressed = true;
    }
}

void GamePage::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Left){
    	leftKeyPressed = false;
    }
    else if (event->key() == Qt::Key_Right){
    	rightKeyPressed = false;
    }
}

void GamePage::gameLoop() {
    //std::cout << "1\n";
    doodle->collisionCheck(gameObjectVector);
    //std::cout << "2\n";
	doodle->positionUpdate(leftKeyPressed, rightKeyPressed, &hasTouchedViewBaseLine);
    //std::cout << "3\n";
    resetView(doodle);
    //std::cout << "4\n";

    bulletUpdate();

    objectUpdate(doodle);
    //std::cout << "5\n";
    updatePlatformVector();
    //std::cout << "6\n";
    platformFrequencyManager();
    //std::cout << "7\n";
    itemGenerator();
    //std::cout << "8\n";
    monsterGenerator();
    //std::cout << "9\n";
    update();
}

void GamePage::resetView(Doodle *doodle){
    if (doodle->resetJump) {
        hasTouchedViewBaseLine = false;
        viewBaseline = WINDOW_HEIGHT / 2;
        doodle->resetJump = false;
        //doodle->state = "normal";
    }
}

void GamePage::generatePlatforms(){
    appendBasicPlatform(WINDOW_HEIGHT);
    replaceWithBrokenPlatforms(platformRangeIdx(0, 1000), 50);
}

void GamePage::objectUpdate(Doodle *doodle){
    for (GameObject* gameObject : gameObjectVector){
        if (gameObject->platform->platformKind == 2){
            MovingPlatform *movingPlatform = (MovingPlatform*) gameObject->platform;
            QLabel *itemLabel = (gameObject->item == NULL) ? NULL : gameObject->item->itemLabel;
            QLabel *monsterLabel = (gameObject->monster == NULL) ? NULL : gameObject->monster->monsterLabel;
            movingPlatform->updateX(itemLabel, monsterLabel);
        }
    }
    if (!hasTouchedViewBaseLine) {
        checkIfGameOver();
        return;
    }
    int doodleY = doodle->doodleLabel->pos().y();
    int deltaY = viewBaseline - doodleY;
    if (deltaY > 0){
        score += deltaY; // update score
        viewBaseline = doodleY;
        Util::moveLabel(doodle->doodleLabel, true, false, 0, WINDOW_HEIGHT / 2);
        for (GameObject* gameObject : gameObjectVector){
            Util::moveLabel(gameObject->platform->platformLabel, true, true, 0, deltaY);
            if (gameObject->item != NULL) Util::moveLabel(gameObject->item->itemLabel, true, true, 0, deltaY);
            if (gameObject->monster != NULL) Util::moveLabel(gameObject->monster->monsterLabel, true, true, 0, deltaY);
        }
        for (Bullet *bullet: bulletVector){
            if (bullet != NULL) Util::moveLabel(bullet->bulletLabel, true, true, 0, deltaY);
        }
    }
    else{
        Util::moveLabel(doodle->doodleLabel, true, false, 0, WINDOW_HEIGHT / 2 - deltaY);
        checkIfGameOver();
    }
}

void GamePage::appendBasicPlatform(int lastPlatformHeight){
    int counter = PLATFORM_VECTOR_SIZE - gameObjectVector.size();
    while(counter-- > 0){
        BasicPlatform *basicPlatform = new BasicPlatform(this, lastPlatformHeight);
        absoluteHeight += (lastPlatformHeight - basicPlatform->platformLabel->pos().y());
        lastPlatformHeight = basicPlatform->platformLabel->pos().y();
        basicPlatform->platformLabel->stackUnder(doodle->doodleLabel);
        basicPlatform->platformLabel->show();
        gameObjectVector.push_back(new GameObject((Platform*)basicPlatform, NULL, NULL, absoluteHeight));
    }
}

void GamePage::updatePlatformVector(){
    while (gameObjectVector.size() > 0 && gameObjectVector[0]->platform->platformLabel->pos().y() >= WINDOW_HEIGHT){
        GameObject* gameObject = gameObjectVector.takeAt(0);
        Doodle::deleteObject(gameObject);
    }
    appendBasicPlatform(gameObjectVector.last()->platform->platformLabel->pos().y());
}

QPair<int, int> GamePage::platformRangeIdx(int rangeStart, int rangeEnd){ // inclusive on both sides []
    int rangeStartIndex = 0, rangeEndIndex = 0;
    for (; rangeStartIndex < gameObjectVector.size() && gameObjectVector[rangeStartIndex]->absoluteHeight < rangeStart; rangeStartIndex++)
        ;
    rangeEndIndex = rangeStartIndex;
    for (; rangeEndIndex < gameObjectVector.size() && gameObjectVector[rangeEndIndex]->absoluteHeight <= rangeEnd; rangeEndIndex++)
        ;

    if (rangeStartIndex == gameObjectVector.size()) rangeStartIndex--;
    rangeEndIndex--;
    return qMakePair(rangeStartIndex, rangeEndIndex);
}

void GamePage::replaceWithBrokenPlatforms(QPair<int, int> indexPair, int p){
    bool hasBrokenPlatform = false;
    int rangeStartIndex = indexPair.first, rangeEndIndex = indexPair.second;
    int leftIndex, middleIndex, rightIndex;
    int lastValidMiddleIndex = -1;
    for (middleIndex = rangeStartIndex; middleIndex <= rangeEndIndex; middleIndex++){ //substitute
        leftIndex = middleIndex - 1, rightIndex = middleIndex + 1;
        while (leftIndex >= 0 && gameObjectVector[leftIndex]->platform->platformKind == 1){
            leftIndex--;
        }
        if (leftIndex < 0) continue;
        while (rightIndex < gameObjectVector.size() && gameObjectVector[rightIndex]->platform->platformKind == 1){
            rightIndex++;
        }
        if (rightIndex >= gameObjectVector.size()) continue;
        if (gameObjectVector[rightIndex]->absoluteHeight - gameObjectVector[leftIndex]->absoluteHeight <= MAX_PLATFORM_INTERVAL){
            lastValidMiddleIndex = middleIndex;
            if ((rand() % 100) < p){
                hasBrokenPlatform = true;
                platformSubstitution(middleIndex, 1);
            }
        }
    }
    if (lastValidMiddleIndex == -1){ //insert
        middleIndex = (gameObjectVector[rangeStartIndex+1]->absoluteHeight - gameObjectVector[rangeStartIndex]->absoluteHeight >= MAX_PLATFORM_INTERVAL / 2) ? rangeStartIndex + 1: rangeStartIndex + 2;
        BrokenPlatform *brokenPlatform = new BrokenPlatform(this, gameObjectVector[middleIndex-1]->platform->platformLabel->pos().y(), 60, gameObjectVector[middleIndex]->absoluteHeight - gameObjectVector[middleIndex-1]->absoluteHeight - 60);
        brokenPlatform->platformLabel->stackUnder(doodle->doodleLabel);
        brokenPlatform->platformLabel->show();
        GameObject* gameObject = new GameObject((Platform*)brokenPlatform, NULL, NULL, gameObjectVector[middleIndex-1]->absoluteHeight + (brokenPlatform->platformLabel->pos().y() - gameObjectVector[middleIndex-1]->platform->platformLabel->pos().y()));
        gameObjectVector.insert(middleIndex, gameObject);
    }
    else if (!hasBrokenPlatform){ //substitute
        platformSubstitution(lastValidMiddleIndex, 1);
    }   
}

void GamePage::replaceWithMovingOrVanishingPlatforms(QPair<int, int> indexPair, int platformKind, int p){
    int rangeStartIndex = indexPair.first, rangeEndIndex = indexPair.second;
    bool hasValidPlatform = false;
    int lastValidIndex = -1;
    for (int i = rangeStartIndex; i <= rangeEndIndex; i++){
        if (gameObjectVector[i]->platform->platformKind == 0){
            lastValidIndex = i;
            if ((rand() % 100) < p){
                hasValidPlatform = true;
                platformSubstitution(i, platformKind);
            }
        }
    }
    if (!hasValidPlatform && lastValidIndex != -1){
        platformSubstitution(lastValidIndex, platformKind);
    }
}

void GamePage::platformSubstitution(int index, int platformKind){
    GameObject* gameObject = gameObjectVector.takeAt(index);
    Platform *newPlatform;
    switch (platformKind){
        case 1:
            newPlatform = (Platform*) (new BrokenPlatform(this, gameObject->platform->platformLabel->pos().x(), gameObject->platform->platformLabel->pos().y()));break;
        case 2:
            newPlatform = (Platform*) (new MovingPlatform(this, gameObject->platform->platformLabel->pos().x(), gameObject->platform->platformLabel->pos().y()));break;
        case 3:
            newPlatform = (Platform*) (new VanishingPlatform(this, gameObject->platform->platformLabel->pos().x(), gameObject->platform->platformLabel->pos().y()));break;
        default:
            newPlatform = NULL;
    }
    newPlatform->platformLabel->stackUnder(doodle->doodleLabel);
    newPlatform->platformLabel->show();
    GameObject *newGameObject = new GameObject(newPlatform, NULL, NULL, gameObject->absoluteHeight);
    Doodle::deleteObject(gameObject);
    gameObjectVector.insert(index, newGameObject);
}

void GamePage::platformFrequencyManager(){
    if (score >= brokenPlatformTargetScore){
        replaceWithBrokenPlatforms(platformRangeIdx(brokenPlatformTargetScore + 1000, brokenPlatformTargetScore + 2000), 50);
        brokenPlatformTargetScore += 1000;
    }
    if (score >= movingPlatformTargetScore){
        replaceWithMovingOrVanishingPlatforms(platformRangeIdx(movingPlatformTargetScore + 1000, movingPlatformTargetScore + 4000), 2, 20);
        movingPlatformTargetScore += 3000;
    }
    if (score >= vanishingPlatformTargetScore){
        replaceWithMovingOrVanishingPlatforms(platformRangeIdx(vanishingPlatformTargetScore + 1000, vanishingPlatformTargetScore + 6000), 3, 20);
        vanishingPlatformTargetScore += 5000;
    }
}

void GamePage::itemGenerator(){
    if (score < itemGenerationTargetScore) return;
    QPair<int, int> indexPair = platformRangeIdx(itemGenerationTargetScore + 1000, itemGenerationTargetScore + 2000);
    itemGenerationTargetScore += 1000;

    if ((rand() % 100) > 100) return;


    int randomIndex = Util::randomNumberGenerator(indexPair.first, indexPair.second);
    if (gameObjectVector[randomIndex]->monster != NULL) return;

    Platform* platform = gameObjectVector[randomIndex]->platform;
    if (platform->platformKind == 1) return;
    int randomNumber = rand() % 100;
    Item* item;
    if (score >= 11000){
        if (randomNumber < 20) item = (Item*)(new Spring(this, platform->platformLabel->pos()));
        else if (randomNumber < 45) item = (Item*)(new Trampoline(this, platform->platformLabel->pos()));
        else if (randomNumber < 70) item = (Item*)(new PropellerHat(this, platform->platformLabel->pos()));
        else item = (Item*)(new JetPack(this, platform->platformLabel->pos()));
    }
    else if (score >= 8000){
        if (randomNumber < 75) item = (Item*)(new Spring(this, platform->platformLabel->pos()));
        else if (randomNumber < 90) item = (Item*)(new Trampoline(this, platform->platformLabel->pos()));
        else item = (Item*)(new PropellerHat(this, platform->platformLabel->pos()));
    }
    else if (score >= 5000){
        if (randomNumber < 75) item = (Item*)(new Spring(this, platform->platformLabel->pos()));
        else item = (Item*)(new Trampoline(this, platform->platformLabel->pos()));
    }
    else{
        item = (Item*)(new Spring(this, platform->platformLabel->pos()));
    }
    item->itemLabel->stackUnder(doodle->doodleLabel);
    item->itemLabel->show();
    gameObjectVector[randomIndex]->item = item;

}

void GamePage::monsterGenerator(){
    if (score < monsterGenerationTargetScore) return;
    QPair<int, int> indexPair = platformRangeIdx(monsterGenerationTargetScore + 1000, monsterGenerationTargetScore + 3000);
    monsterGenerationTargetScore += 2000;

    if ((rand() % 100) > 50) return;

    int randomIndex = Util::randomNumberGenerator(indexPair.first, indexPair.second);
    if (gameObjectVector[randomIndex]->item != NULL) return;


    Monster *monster = new Monster(this, gameObjectVector[randomIndex]->platform->platformLabel->pos());
    monster->monsterLabel->stackUnder(doodle->doodleLabel);
    monster->monsterLabel->show();
    gameObjectVector[randomIndex]->monster = monster;
}

void GamePage::checkIfGameOver(){
    if (doodle->doodleLabel->pos().y() > WINDOW_HEIGHT - DOODLE_HEIGHT){
        /*
        doodleJumpingTime = 0;
        newY = WINDOW_HEIGHT - DOODLE_HEIGHT;
        jumpingBaseline = WINDOW_HEIGHT;
        */
            
         std::cout << "game over\n";
         QCoreApplication::quit();
    }
}

void GamePage::bulletUpdate(){
    for (Bullet *bullet: bulletVector){
        if (bullet != NULL){
            Util::moveLabel(bullet->bulletLabel, true, true, bullet->dx, bullet->dy);
        }
    }

    QVector<GameObject*> tmpVector;
    for (int i = 0; i < gameObjectVector.size(); i++){
        if (gameObjectVector[i]->monster != NULL){
            tmpVector.push_back(gameObjectVector[i]);
        }
    }

    //std::cout << gameObjectVector.size() << "\n";
    for (int i = 0; i < bulletVector.size(); i++){
        for (GameObject *gameObject: tmpVector){
            if (gameObject->monster != NULL && bulletVector[i] != NULL){
                //std::cout << "bullet: " << bulletVector[i]->bulletLabel->pos().x() << " " << bulletVector[i]->bulletLabel->pos().y() << "\n";
                //std::cout << "monster: " << gameObject->monster->monsterLabel->pos().x() << " " << gameObject->monster->monsterLabel->pos().y() << "\n";
                if (bulletVector[i]->bulletLabel->geometry().intersects(gameObject->monster->monsterLabel->geometry())){
                    std::cout << "hi\n";
                    delete gameObject->monster->monsterLabel;
                    delete gameObject->monster;
                    gameObject->monster = NULL;
                    delete bulletVector[i]->bulletLabel;
                    delete bulletVector[i];
                    bulletVector[i] = NULL;
                }
            }
        }
    }

    for (int i = 0; i < bulletVector.size(); i++){
        if (bulletVector[i] != NULL){
            int x = bulletVector[i]->bulletLabel->pos().x();
            int y = bulletVector[i]->bulletLabel->pos().y();
            if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT){
                delete bulletVector[i]->bulletLabel;
                bulletVector[i] = NULL;
            }
        }
    }
    bulletVector.removeAll(NULL);
}

void GamePage::print(){
    for (GameObject* gameObject : gameObjectVector){
        std::cout << gameObject->absoluteHeight << " ";
    }
    std::cout << "\n";
}