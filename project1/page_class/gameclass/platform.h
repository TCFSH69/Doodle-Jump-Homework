#ifndef PLATFORM_H
#define PLATFORM_H

#include "../../util/util.h"

class Platform : public QWidget{
    Q_OBJECT
    public:
        Platform(QWidget *parent, QString imagePath, int lastPlatformHeight);
        QLabel *platformLabel;

    protected:
    	void randomGenerator(int lastPlatformHeight);
    	int platformKind;
    	QPixmap platformPixmap;
    	
};

class BasicPlatform : public Platform{
    Q_OBJECT
    public:
        BasicPlatform(QWidget *parent, int lastPlatformHeight);

    private:
    	
};

class MovingPlatform : public Platform{
    Q_OBJECT
    public:
        MovingPlatform(QWidget *parent, int lastPlatformHeight);

    private:
    	
};

class BrokenPlatform : public Platform{
    Q_OBJECT
    public:
        BrokenPlatform(QWidget *parent, int lastPlatformHeight);

    private:
    	
};

class VanishingPlatform : public Platform{
    Q_OBJECT
    public:
        VanishingPlatform(QWidget *parent, int lastPlatformHeight);

    private:
    	
};

#endif