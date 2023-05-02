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
		int hp = 3;

	private:
		void pixmapLoad();
		void orientationUpdate(bool leftKeyPressed, bool rightKeyPressed);
		void updateXY();
		QPixmap doodleLPixmap;
    	QPixmap doodleRPixmap;
    	QPixmap doodleSPixmap;
    	QPixmap doodleLRPixmap;
    	QPixmap doodleURPixmap;

    	QPixmap doodleH1L;
    	QPixmap doodleH2L;
    	QPixmap doodleH3L;
    	QPixmap doodleH4L;

    	QPixmap doodleH1R;
    	QPixmap doodleH2R;
    	QPixmap doodleH3R;
    	QPixmap doodleH4R;

    	QPixmap doodleJ1L;
    	QPixmap doodleJ2L;
    	QPixmap doodleJ3L;
    	QPixmap doodleJ4L;
    	QPixmap doodleJ5L;
    	QPixmap doodleJ6L;
    	QPixmap doodleJ7L;
    	QPixmap doodleJ8L;
    	QPixmap doodleJ9L;
    	QPixmap doodleJ10L;

    	QPixmap doodleJ1R;
    	QPixmap doodleJ2R;
    	QPixmap doodleJ3R;
    	QPixmap doodleJ4R;
    	QPixmap doodleJ5R;
    	QPixmap doodleJ6R;
    	QPixmap doodleJ7R;
    	QPixmap doodleJ8R;
    	QPixmap doodleJ9R;
    	QPixmap doodleJ10R;

    	QVector<QPixmap> doodleHLVector;
    	QVector<QPixmap> doodleHRVector;
    	QVector<QPixmap> doodleJLVector;
    	QVector<QPixmap> doodleJRVector;

    	bool doodleIsJumping;
    	bool turnRight;
    	int doodleX;
    	int doodleY;
    	int jumpingBaseline;
    	int doodleJumpingTime;
    	int animationTick;
};

#endif