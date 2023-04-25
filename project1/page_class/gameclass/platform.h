#ifndef PLATFORM_H
#define PLATFORM_H

#include "../../util/util.h"

class Platform : public QWidget{
    Q_OBJECT
    public:
        Platform(QWidget *parent, QString imagePath, int lastPlatformHeight, int min, int max);
        Platform(QWidget *parent, QString imagePath, int x, int y);
        //virtual ~Platform();
        QLabel *platformLabel;
        int platformKind;

    protected:
    	void randomGenerator(int lastPlatformHeight, int min, int max);
    	QPixmap platformPixmap;
    	
};

class BasicPlatform : public Platform{
    Q_OBJECT
    public:
        BasicPlatform(QWidget *parent, int lastPlatformHeight);

    private:
    	
};

class BrokenPlatform : public Platform{
    Q_OBJECT
    public:
        BrokenPlatform(QWidget *parent, int lastPlatformHeight, int min, int max);
        BrokenPlatform(QWidget *parent, int x, int y);
        static void dropAnimation(QPoint platformPos, QWidget *parent, QLabel* doodleLabel);

    private:
    	
};

class MovingPlatform : public Platform{
    Q_OBJECT
    public:
        MovingPlatform(QWidget *parent, int x, int y);
        void updateX(QLabel *itemLabel);
    private:
    	bool movingRight;
    	
};

class VanishingPlatform : public Platform{
    Q_OBJECT
    public:
        VanishingPlatform(QWidget *parent, int x, int y);

    private:
    	
};

#endif