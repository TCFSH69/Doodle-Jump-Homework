#ifndef DOODLE_H
#define DOODLE_H

#include "../../util/gameobject.h"

class Doodle : public QWidget{
	Q_OBJECT
	public:
		Doodle(QWidget *parent);
		void positionUpdate(bool leftKeyPressed, bool rightKeyPressed, bool *hasTouchedViewBaseLine);
		void collisionCheck(QVector<GameObject*> &gameObjectVector);
		void static deleteObject(GameObject* gameObject);
		QLabel *doodleLabel;
		bool resetJump;
		bool invincible;
		QString state;

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
    	bool turnRight;
    	int doodleX;
    	int doodleY;
    	int jumpingBaseline;
    	int doodleJumpingTime;
};

#endif