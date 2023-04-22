#include "gamepage.h"

GamePage::GamePage(QWidget *parent) : QMainWindow(parent){
	score = 0;
    hasTouchedViewBaseLine = false;
	leftKeyPressed = false;
	rightKeyPressed = false;
    viewBaseline = WINDOW_HEIGHT / 2;
}

void GamePage::gameStart(){
	gameBackgroundPixmap.load("./dataset/images/background.png");
	gameBackgroundLabel = Util::createImageLabel(WINDOW_WIDTH, WINDOW_HEIGHT, gameBackgroundPixmap, this);
	gameBackgroundLabel->lower();
	
    doodle = new Doodle(this);
    initializeObjectVector();
	gameLoopTimer = new QTimer(this);
    connect(gameLoopTimer, &QTimer::timeout, this, &GamePage::gameLoop);
    gameLoopTimer->start(10);
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
    doodle->collisionCheck(objectVectors);
	doodle->positionUpdate(leftKeyPressed, rightKeyPressed, &hasTouchedViewBaseLine);
    if (doodle->resetJump) {
        std::cout << "hi\n";
        hasTouchedViewBaseLine = false;
        viewBaseline = WINDOW_HEIGHT / 2;
        doodle->resetJump = false;
    }
    objectUpdate(doodle);
    update();
}

void GamePage::initializeObjectVector(){
    for (int i = 0; i < 3; i++){
        QVector<Platform*> v;
        objectVectors.push_back(v);
    }
    generatePlatforms(objectVectors[0]);
}

void GamePage::generatePlatforms(QVector<Platform*> &platformVector){
    int lastPlatformHeight = (platformVector.size() == 0) ? WINDOW_HEIGHT : platformVector[platformVector.size()-1]->platformLabel->pos().y();
    while (platformVector.size() < PLATFORM_VECTOR_SIZE){
        BasicPlatform *basicPlatform = new BasicPlatform(this, lastPlatformHeight);
        lastPlatformHeight = basicPlatform->platformLabel->pos().y();
        basicPlatform->platformLabel->stackUnder(doodle->doodleLabel);
        platformVector.push_back(basicPlatform);
    }
}

void GamePage::objectUpdate(Doodle *doodle){
    if (!hasTouchedViewBaseLine) return;
    int doodleY = doodle->doodleLabel->pos().y();
    int deltaY = viewBaseline - doodleY;
    std::cout << "deltaY: " << deltaY << "\n";
    if (deltaY > 0){
        viewBaseline = doodleY;
        doodle->doodleLabel->move(doodle->doodleLabel->pos().x(), WINDOW_HEIGHT / 2);
        std::cout << doodle->doodleLabel->pos().x() << " " << doodle->doodleLabel->pos().y() << "\n";
        //TBD
        for (Platform* platform: objectVectors[0]){
            platform->platformLabel->move(platform->platformLabel->pos().x(), platform->platformLabel->pos().y() + deltaY);
            if (platform->platformLabel->pos().y() > WINDOW_HEIGHT){
                //delete platform;
            }
        }
    }
    else{
        std::cout << "deltaY<0\n";
        doodle->doodleLabel->move(doodle->doodleLabel->pos().x(), WINDOW_HEIGHT / 2 - deltaY);
    }
    std::cout << doodle->doodleLabel->pos().x() << " " << doodle->doodleLabel->pos().y() << "\n";
}