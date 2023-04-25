#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <QMainWindow>
#include <QMouSeEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QPixmap>
#include <QLabel>
#include <QSound>
#include <QPropertyAnimation>
#include <QStackedWidget>
#include <QString>
#include <QTimer>
#include <QPoint>
#include <QVector>
#include <QCoreApplication>
#include <QPair>

#define WINDOW_WIDTH 540
#define WINDOW_HEIGHT 960
#define DOODLE_WIDTH 80
#define DOODLE_HEIGHT 80
#define DOODLE_FEET_OFFSET 26
#define SPEED_CONST 8
#define PLATFORM_WIDTH 120
#define PLATFORM_HEIGHT 30
#define NORMAL_JUMPING_PERIOD 40
#define SPRING_JUMPING_PERIOD 80
#define TRAMPOLINE_JUMPING_PERIOD 100
#define PLATFORM_VECTOR_SIZE 50 // 5000/100
#define MAX_PLATFORM_INTERVAL 300
#define PLATFORM_DROPPING_SPEED 10

class Util{
    public:
        static QLabel* createImageLabel(QPixmap image, QWidget *parent);
        static void setAlignment(QLabel* label, std::string horizontalAlignment, std::string verticalAlignment, QSize parentSize, QSize childSize);
        //static QPair<double, double> findVelocityAndGravity(double h, double t);
        static int xPositionSetting(int x, bool leftKeyPressed, bool rightKeyPressed);
        static int yPositionSetting(QString state, int t, int yBaseline);
        static int randomNumberGenerator(int start, int end);
        static void moveLabel(QLabel *label, bool useOriginalX, bool useOriginalY, int offsetX, int offsetY);
       
    private:
    	static const int normalJumpingDistance;
    	static const int springJumpingDistance;
    	static const int trampolineJumpingDistance;
    	static const double vNormal;
    	static const double gNormal;
    	static const double vSpring;
		static const double gSpring;
		static const double vTrampoline;
		static const double gTrampoline;
};
#endif