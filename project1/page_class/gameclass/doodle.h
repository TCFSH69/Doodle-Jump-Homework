#ifndef DOODLE_H
#define DOODLE_H

#include "../../util/util.h"
#include "platform.h"
#include "item.h"

class Doodle : public QWidget{
	Q_OBJECT
	public:
		Doodle(QWidget *parent);
		void positionUpdate(bool leftKeyPressed, bool rightKeyPressed, bool *hasTouchedViewBaseLine);
		void collisionCheck(QVector<QPair<Platform*, int>> &platformVector);
		QLabel *doodleLabel;
		bool resetJump;
		bool invincible;

	private:
		void pixmapLoad();
		void orientationUpdate(bool leftKeyPressed, bool rightKeyPressed);
		void updateXY();
		QPixmap doodleLPixmap;
    	QPixmap doodleRPixmap;
    	QPixmap doodleSPixmap;
    	QPixmap doodleLRPixmap;
    	QPixmap doodleURPixmap;
    	bool doodleIsJumping;
    	int doodleX;
    	int doodleY;
    	int jumpingBaseline;
    	int doodleJumpingTime;
};

#endif