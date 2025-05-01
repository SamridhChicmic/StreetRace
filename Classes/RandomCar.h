#ifndef __RandomCar__
#define __RandomCar__

#include "cocos2d.h"
#include "NodePool.h"
using namespace cocos2d;

class RandomCar : public Component{
public:
    RandomCar();
    void createRandomCar(Size  s,Node * land, Node * canvas, NodePool pool);
    void moveRandomCar();
    void collisionCheck();
    NodePool carPool;
private:
    virtual void onEnter();
    virtual void update(float delta);

};

#endif /* defined(__RandomCar__) */