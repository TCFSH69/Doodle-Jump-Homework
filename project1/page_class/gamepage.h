#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include "../util/util.h"
#include "gameclass/doodle.h"
#include "gameclass/platform.h"
#include "gameclass/item.h"

class GamePage : public QMainWindow{
    Q_OBJECT
    public:
        GamePage(QWidget *parent);
        void gameStart();
        void mousePressEvent(QMouseEvent *event);
        void keyPressEvent(QKeyEvent *event);
        void keyReleaseEvent(QKeyEvent *event);
        void gameLoop();
        void resetView(Doodle *doodle);
        void generatePlatforms();
        QPair<int, int> platformRangeIdx(int rangeStart, int rangeEnd);
        void objectUpdate(Doodle *doodle);
        void appendBasicPlatform(int lastPlatformHeight);
        void updatePlatformVector();
        void replaceWithBrokenPlatforms(QPair<int, int> indexPair, int p);
        void replaceWithMovingOrVanishingPlatforms(QPair<int, int> indexPair, int platformKind, int p);
        void platformSubstitution(int index, int platformKind);
        void platformFrequencyManager();
        void print();
        QVector<QPair<Platform*, int>> platformVector;

    private:
    	QPixmap gameBackgroundPixmap;
    	QLabel *gameBackgroundLabel;
    	QTimer *gameLoopTimer;
    	Doodle *doodle;
    	//QVector<<Monster*, int>> monsterVector;
    	//QVector<<Item*, int>> itemVector;

    	bool leftKeyPressed;
    	bool rightKeyPressed;
    	bool hasTouchedViewBaseLine;
    	int viewBaseline;
    	int score;
    	int brokenPlatformTargetScore;
    	int movingPlatformTargetScore;
    	int vanishingPlatformTargetScore;
    	int absoluteHeight;
};
#endif