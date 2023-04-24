#include "gamepage.h"

GamePage::GamePage(QWidget *parent) : QMainWindow(parent){
	score = 0;
    brokenPlatformTargetScore = 0;
    movingPlatformTargetScore = 5000;
    vanishingPlatformTargetScore = 8000;
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

	gameLoopTimer = new QTimer(this);
    connect(gameLoopTimer, &QTimer::timeout, this, &GamePage::gameLoop);
    gameLoopTimer->setTimerType(Qt::PreciseTimer);
    gameLoopTimer->start(12);
}

void GamePage::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
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
    doodle->collisionCheck(platformVector);
	doodle->positionUpdate(leftKeyPressed, rightKeyPressed, &hasTouchedViewBaseLine);
    resetView(doodle);
    objectUpdate(doodle);
    updatePlatformVector();
    platformFrequencyManager();
    update();
}

void GamePage::resetView(Doodle *doodle){
    if (doodle->resetJump) {
        hasTouchedViewBaseLine = false;
        viewBaseline = WINDOW_HEIGHT / 2;
        doodle->resetJump = false;
    }
}

void GamePage::generatePlatforms(){
    appendBasicPlatform(WINDOW_HEIGHT);
    replaceWithBrokenPlatforms(platformRangeIdx(0, 1000), 50);
}

void GamePage::objectUpdate(Doodle *doodle){
    for (QPair<Platform*, int> pair: platformVector){
        if (pair.first->platformKind == 2){
            MovingPlatform *movingPlatform = (MovingPlatform*) pair.first;
            movingPlatform->updateX();
        }
    }
    if (!hasTouchedViewBaseLine) return;
    int doodleY = doodle->doodleLabel->pos().y();
    int deltaY = viewBaseline - doodleY;
    if (deltaY > 0){
        score += deltaY; // update score
        viewBaseline = doodleY;
        Util::moveLabel(doodle->doodleLabel, true, false, 0, WINDOW_HEIGHT / 2);
        for (QPair<Platform*, int> pair: platformVector){
            Util::moveLabel(pair.first->platformLabel, true, true, 0, deltaY);
        }
    }
    else{
        Util::moveLabel(doodle->doodleLabel, true, false, 0, WINDOW_HEIGHT / 2 - deltaY);
    }
}

void GamePage::appendBasicPlatform(int lastPlatformHeight){
    int counter = PLATFORM_VECTOR_SIZE - platformVector.size();
    while(counter-- > 0){
        BasicPlatform *basicPlatform = new BasicPlatform(this, lastPlatformHeight);
        absoluteHeight += (lastPlatformHeight - basicPlatform->platformLabel->pos().y());
        lastPlatformHeight = basicPlatform->platformLabel->pos().y();
        basicPlatform->platformLabel->stackUnder(doodle->doodleLabel);
        basicPlatform->platformLabel->show();
        platformVector.push_back(qMakePair((Platform*)basicPlatform, absoluteHeight));
    }
}

void GamePage::updatePlatformVector(){
    int count = 0;
    for (; count < platformVector.size() && platformVector[count].first->platformLabel->pos().y() >= WINDOW_HEIGHT; count++){
        QPair<Platform*, int> pair = platformVector.takeAt(count);
        delete pair.first->platformLabel;
        delete pair.first;
    }
    appendBasicPlatform(platformVector.last().first->platformLabel->pos().y());
}

QPair<int, int> GamePage::platformRangeIdx(int rangeStart, int rangeEnd){ // inclusive on both sides []
    int rangeStartIndex = 0, rangeEndIndex = 0;
    for (; rangeStartIndex < platformVector.size() && platformVector[rangeStartIndex].second < rangeStart; rangeStartIndex++)
        ;
    rangeEndIndex = rangeStartIndex;
    for (; rangeEndIndex < platformVector.size() && platformVector[rangeEndIndex].second <= rangeEnd; rangeEndIndex++)
        ;
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
        while (leftIndex >= 0 && platformVector[leftIndex].first->platformKind == 1){
            leftIndex--;
        }
        if (leftIndex < 0) continue;
        while (rightIndex < platformVector.size() && platformVector[rightIndex].first->platformKind == 1){
            rightIndex++;
        }
        if (rightIndex >= platformVector.size()) continue;
        if (platformVector[rightIndex].second - platformVector[leftIndex].second <= MAX_PLATFORM_INTERVAL){
            lastValidMiddleIndex = middleIndex;
            if ((rand() % 100) < p){
                hasBrokenPlatform = true;
                platformSubstitution(middleIndex, 1);
            }
        }
    }
    if (lastValidMiddleIndex == -1){ //insert
        middleIndex = (platformVector[rangeStartIndex+1].second - platformVector[rangeStartIndex].second >= MAX_PLATFORM_INTERVAL / 2) ? rangeStartIndex + 1: rangeStartIndex + 2;
        QPair<Platform*, int> pair = platformVector[middleIndex-1];
        BrokenPlatform *brokenPlatform = new BrokenPlatform(this, pair.first->platformLabel->pos().y(), 60, platformVector[middleIndex].second - platformVector[middleIndex-1].second - 60);
        brokenPlatform->platformLabel->stackUnder(doodle->doodleLabel);
        brokenPlatform->platformLabel->show();
        pair.first = (Platform*)brokenPlatform;
        platformVector.insert(middleIndex, pair);
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
        if (platformVector[i].first->platformKind == 0){
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
    QPair<Platform*, int> pair = platformVector.takeAt(index);
    Platform *newPlatform;
    switch (platformKind){
        case 1:
            newPlatform = (Platform*) (new BrokenPlatform(this, pair.first->platformLabel->pos().x(), pair.first->platformLabel->pos().y()));break;
        case 2:
            newPlatform = (Platform*) (new MovingPlatform(this, pair.first->platformLabel->pos().x(), pair.first->platformLabel->pos().y()));break;
        case 3:
            newPlatform = (Platform*) (new VanishingPlatform(this, pair.first->platformLabel->pos().x(), pair.first->platformLabel->pos().y()));break;
        default:
            newPlatform = NULL;
    }
    newPlatform->platformLabel->stackUnder(doodle->doodleLabel);
    newPlatform->platformLabel->show();
    delete pair.first->platformLabel;
    delete pair.first;
    pair.first = newPlatform;
    platformVector.insert(index, pair);
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

void GamePage::print(){
    for (QPair<Platform*, int> pair: platformVector){
        std::cout << pair.second << " ";
    }
    std::cout << "\n";
}