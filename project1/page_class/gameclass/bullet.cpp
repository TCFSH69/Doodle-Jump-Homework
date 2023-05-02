#include "bullet.h"

Bullet::Bullet(QWidget *parent, QPoint doodlePos, QPoint mousePos) : QWidget(parent){
	QPoint start = doodlePos + QPoint(DOODLE_WIDTH / 2, DOODLE_HEIGHT / 2);
	QPoint end = mousePos;
	bulletPixmap.load("./dataset/images/bullet.png");
	bulletLabel = Util::createImageLabel(bulletPixmap, parent);
	bulletLabel->setPixmap(bulletPixmap);
	bulletLabel->move(start);
	bulletLabel->show();
	const double c = 20.0f;
	if (mousePos.x() == doodlePos.x()){
		dx = 0;
		dy = c;
	}
	else{
		double m = 1.0f * (end.y() - start.y()) / (end.x() - start.x());
	
		dx = abs(c / sqrt(1 + m * m));
		dy = abs(m * dx);
	}
	
	if ((end - start).x() < 0){
		dx = -dx;
	}
	if ((end - start).y() < 0){
		dy = -dy;
	}
}

