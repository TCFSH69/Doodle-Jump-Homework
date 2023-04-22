#include "util.h"


QLabel* Util::createImageLabel(int width, int height, QPixmap image, QWidget *parent){
	QLabel *imageLabel;

    imageLabel = new QLabel(parent);
    imageLabel->setFixedSize(width, height);
    imageLabel->setPixmap(image);
    return imageLabel;
}

void Util::setAlignment(QLabel* label, std::string horizontalAlignment, std::string verticalAlignment, QSize parentSize, QSize childSize){
	int x, y;
	if (horizontalAlignment == "Left"){
		x = 0;
	}
	else if (horizontalAlignment == "Center"){
		x = (parentSize.width() - childSize.width()) / 2;
	}
	else if (horizontalAlignment == "Right"){
		x = (parentSize.width() - childSize.width());
	}
	else {
		return;
	}

	if (verticalAlignment == "Top"){
		y = 0;
	}
	else if (verticalAlignment == "Center"){
		y = (parentSize.height() - childSize.height()) / 2;
	}
	else if (verticalAlignment == "Bottom"){
		y = (parentSize.height() - childSize.height());
	}
	else {
		return;
	}

	label->move(x, y);
}

int Util::xPositionSetting(int x, bool leftKeyPressed, bool rightKeyPressed){
	int newX = x + (rightKeyPressed - leftKeyPressed) * SPEED_CONST;
	newX = ((newX + DOODLE_WIDTH / 2 + WINDOW_WIDTH) % WINDOW_WIDTH) - DOODLE_WIDTH / 2;
	return newX;
}

int Util::yPositionSetting(int t, int yBaseline){
	return (int)(yBaseline - DOODLE_HEIGHT - (V0 * t + G * t * t / 2));
}

int Util::randomNumberGenerator(int start, int end){
	return start + (rand() % (end + 1 - start));
}