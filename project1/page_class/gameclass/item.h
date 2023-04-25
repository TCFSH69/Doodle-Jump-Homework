#ifndef ITEM_H
#define ITEM_H

#include "../../util/util.h"

class Item : public QWidget{
    Q_OBJECT
    public:
        Item(QWidget *parent);
        virtual void use() = 0;
        QLabel *itemLabel;
        int itemKind;
        int itemWidth;
        int itemHeight;
        bool isUsed;

    protected:
    	QPixmap itemPixmap;
    	
};

class Spring : public Item{
	Q_OBJECT
    public:
        Spring(QWidget *parent, QPoint platformPos);
        void use();
        

    private:
    	QPixmap springPixmap1;
        QPixmap springPixmap2;

};

class Trampoline : public Item{
	Q_OBJECT
    public:
        Trampoline(QWidget *parent, QPoint platformPos);
        void use();
        

    private:
    	QPixmap trampolinePixmap1;
        QPixmap trampolinePixmap2;
};

class PropellerHat : public Item{
	Q_OBJECT
    public:
        PropellerHat(QWidget *parent, QPoint platformPos);
        void use();
        

    private:
    	QPixmap propellerHatPixmap1;
};

class JetPack : public Item{
	Q_OBJECT
    public:
        JetPack(QWidget *parent, QPoint platformPos);
        void use();

    private:
    	QPixmap jetPackPixmap1;

};

#endif