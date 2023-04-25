#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "../page_class/gameclass/platform.h"
#include "../page_class/gameclass/item.h"

typedef struct GameObject{
    Platform* platform;
    Item* item;
    //Monster* monster;
    int absoluteHeight;
    // GameObject(Platform* platform, Item* item, Monster* monster, int absoluteHeight){
    //  this->platform = platform;
    //  this->item = item;
    //  this->monster = monster;
    //  this->absoluteHeight = absoluteHeight;
    // }
    GameObject(Platform* platform, Item* item, int absoluteHeight){
        this->platform = platform;
        this->item = item;
        this->absoluteHeight = absoluteHeight;
    }
    // ~GameObject(){
    //     std::cout << platform <<"\n";
    //     if (platform != NULL){
    //         delete platform;
    //         platform = NULL;
    //     }
    // }
}GameObject;

#endif