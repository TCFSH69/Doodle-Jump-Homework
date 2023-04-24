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
#define SPEED_CONST 8
#define PLATFORM_WIDTH 120
#define PLATFORM_HEIGHT 30
#define JUMPING_PERIOD 80 //round-trip time
#define PLATFORM_VECTOR_SIZE 50 // 5000/100
#define MAX_PLATFORM_INTERVAL 300
#define PLATFORM_DROPPING_SPEED 10
#define G -0.4 // y = V0t+G/2*t^2 <= 320 for all 0<=t<=40 -> differentiate it and let t=40 be where maximum happens
#define V0 16 // 320=40V+1600G (t=40 -> y=320)

class Platform;
class Item;
class Monster;

typedef struct objectSet{
    Platform* platform = NULL;
    Item* item = NULL;
    Monster* monster = NULL;
}objectSet;

class Util{
    public:
        static QLabel* createImageLabel(QPixmap image, QWidget *parent);
        static void setAlignment(QLabel* label, std::string horizontalAlignment, std::string verticalAlignment, QSize parentSize, QSize childSize);
        static int xPositionSetting(int x, bool leftKeyPressed, bool rightKeyPressed);
        static int yPositionSetting(int t, int yBaseline);
        static int randomNumberGenerator(int start, int end);
        static void moveLabel(QLabel *label, bool useOriginalX, bool useOriginalY, int offsetX, int offsetY);
};
#endif