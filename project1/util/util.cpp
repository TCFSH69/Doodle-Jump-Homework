#include "util.h"


const int Util::normalJumpingDistance = 320;
const int Util::springJumpingDistance = 960;
const int Util::trampolineJumpingDistance = 1920;
const int Util::propellerHatJumpingDistance = 3840;
const int Util::jetPackJumpingDistance = 7680;
const double Util::vNormal = 2.0f * normalJumpingDistance / NORMAL_JUMPING_PERIOD;
const double Util::gNormal = -2.0f * normalJumpingDistance / (NORMAL_JUMPING_PERIOD * NORMAL_JUMPING_PERIOD);
const double Util::vSpring = 2.0f * springJumpingDistance / SPRING_JUMPING_PERIOD;
const double Util::gSpring = -2.0f * springJumpingDistance / (SPRING_JUMPING_PERIOD * SPRING_JUMPING_PERIOD);
const double Util::vTrampoline = 2.0f * trampolineJumpingDistance / TRAMPOLINE_JUMPING_PERIOD;
const double Util::gTrampoline = -2.0f * trampolineJumpingDistance / (TRAMPOLINE_JUMPING_PERIOD * TRAMPOLINE_JUMPING_PERIOD);
const double Util::vPropellerHat = 4.0f * propellerHatJumpingDistance / (3 * PROPELLERHAT_JUMPING_PERIOD);
const double Util::gPropellerHat = 16.0f * propellerHatJumpingDistance / (3 * PROPELLERHAT_JUMPING_PERIOD * PROPELLERHAT_JUMPING_PERIOD);
const double Util::vJetPack = 4.0f * jetPackJumpingDistance / (3 * JETPACK_JUMPING_PERIOD);
const double Util::gJetPack = 16.0f * jetPackJumpingDistance / (3 * JETPACK_JUMPING_PERIOD * JETPACK_JUMPING_PERIOD);


QLabel* Util::createImageLabel(QPixmap image, QWidget *parent){
	QLabel *imageLabel;

    imageLabel = new QLabel(parent);
    imageLabel->setPixmap(image);
    imageLabel->setFixedSize(image.size());
    
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

/*
QPair<double, double> Util::findVelocityAndGravity(double h, double t){
	double v = 2 * h / t;
	double g = -2 * h / (t * t);
	return qMakePair(v, g);
}
*/

int Util::xPositionSetting(int x, bool leftKeyPressed, bool rightKeyPressed){
	int newX = x + (rightKeyPressed - leftKeyPressed) * SPEED_CONST;
	newX = ((newX + DOODLE_WIDTH / 2 + WINDOW_WIDTH) % WINDOW_WIDTH) - DOODLE_WIDTH / 2;
	return newX;
}

int Util::yPositionSetting(QString state, int t, int yBaseline){
	int period;
	int distance;
	int deltaT;
	double v, g;

	if (state == "spring"){
		v = vSpring;
		g = gSpring;
		distance = springJumpingDistance;
		period = SPRING_JUMPING_PERIOD;
	}
	else if (state == "trampoline"){
		v = vTrampoline;
		g = gTrampoline;
		distance = trampolineJumpingDistance;
		period = TRAMPOLINE_JUMPING_PERIOD;
	}
	else if (state == "propellerHat"){
		if (t <= PROPELLERHAT_JUMPING_PERIOD / 4.0f){
			g = gPropellerHat;
			v = 0;
			return (int)(yBaseline - DOODLE_HEIGHT - (v * t + g * t * t / 2.0f));
		}
		else if (t <= PROPELLERHAT_JUMPING_PERIOD * 3 / 4.0f){
			g = 0;
			v = vPropellerHat;
			deltaT = t - PROPELLERHAT_JUMPING_PERIOD / 4.0f;
			return (int)(yBaseline - DOODLE_HEIGHT - (propellerHatJumpingDistance / 6.0f) - (v * deltaT));
		}
		else {
			g = -gPropellerHat;
			v = vPropellerHat;
			deltaT = t - PROPELLERHAT_JUMPING_PERIOD * 3 / 4.0f;
			return (int)(yBaseline - DOODLE_HEIGHT - (propellerHatJumpingDistance * 5 / 6.0f) - (v * deltaT + g * deltaT * deltaT / 2.0f));
		}
		distance = propellerHatJumpingDistance;
		period = PROPELLERHAT_JUMPING_PERIOD;
	}
	else if (state == "jetPack"){
		if (t <= JETPACK_JUMPING_PERIOD / 4.0f){
			g = gJetPack;
			v = 0;
			return (int)(yBaseline - DOODLE_HEIGHT - (v * t + g * t * t / 2.0f));
		}
		else if (t <= JETPACK_JUMPING_PERIOD * 3 / 4.0f){
			g = 0;
			v = vJetPack;
			deltaT = t - JETPACK_JUMPING_PERIOD / 4.0f;
			return (int)(yBaseline - DOODLE_HEIGHT - (jetPackJumpingDistance / 6.0f) - (v * deltaT));
		}
		else {
			g = -gJetPack;
			v = vJetPack;
			deltaT = t - JETPACK_JUMPING_PERIOD * 3 / 4.0f;
			return (int)(yBaseline - DOODLE_HEIGHT - (jetPackJumpingDistance * 5 / 6.0f) - (v * deltaT + g * deltaT * deltaT / 2.0f));
		}
		distance = jetPackJumpingDistance;
		period = JETPACK_JUMPING_PERIOD;
	}
	else{
		v = vNormal;
		g = gNormal;
		distance = normalJumpingDistance;
		period = NORMAL_JUMPING_PERIOD;
	}

	if (t <= period){
		return (int)(yBaseline - DOODLE_HEIGHT - (v * t + g * t * t / 2));
	}
	else{
		deltaT = t - period;
		return (int)(yBaseline - DOODLE_HEIGHT - distance - deltaT * (gNormal / 2 * deltaT + NORMAL_JUMPING_PERIOD * gNormal + vNormal));
	}

}


int Util::randomNumberGenerator(int start, int end){
	return start + (rand() % (end + 1 - start));
}

void Util::moveLabel(QLabel *label, bool useOriginalX, bool useOriginalY, int offsetX, int offsetY){
	int x = (useOriginalX) ? label->pos().x() : 0;
	int y = (useOriginalY) ? label->pos().y() : 0;
	x += offsetX;
	y += offsetY;
	label->move(x, y);
}

