#ifndef __RandomCar__
#define __RandomCar__

#include "cocos2d.h"

using namespace cocos2d;

class RandomCar : public Component{
public:
    RandomCar();
    void createRandomCar(Size  s,Node * land, Node * canvas);
    void moveRandomCar();
    void collisionCheck();

private:
    virtual void onEnter();
    virtual void update(float delta);

};

#endif /* defined(__RandomCar__) */