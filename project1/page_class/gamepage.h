#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include "../util/util.h"
#include "gameclass/doodle.h"
#include "gameclass/platform.h"

class GamePage : public QMainWindow{
    Q_OBJECT
    public:
        GamePage(QWidget *parent);
        void gameStart();
        void mousePressEvent(QMouseEvent *event);
        void keyPressEvent(QKeyEvent *event);
        void keyReleaseEvent(QKeyEvent *event);
        void gameLoop();
        void initializeObjectVector();
        void generatePlatforms(QVector<Platform*> &platformVector);
        void objectUpdate(Doodle *doodle);

    private:
    	QPixmap gameBackgroundPixmap;
    	QLabel *gameBackgroundLabel;
    	QTimer *gameLoopTimer;
    	Doodle *doodle;
    	QVector<QVector<Platform*>> objectVectors;

    	bool leftKeyPressed;
    	bool rightKeyPressed;
    	bool hasTouchedViewBaseLine;
    	int viewBaseline;
    	int score;
};
#endif