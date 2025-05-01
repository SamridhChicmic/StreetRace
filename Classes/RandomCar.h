#ifndef __RandomCar__
#define __RandomCar__

#include "cocos2d.h"
#include "NodePool.h"
#include "ScoreHandler.h"
using namespace cocos2d;

class RandomCar : public Component{
public:
    RandomCar();
    void createRandomCar(Size  s,Node * land, Node * canvas, NodePool pool,Label * score);
    void moveRandomCar();
    void collisionCheck();
    NodePool carPool;
    Label * score ;
private:
    virtual void onEnter();
    virtual void update(float delta);

};

#endif /* defined(__RandomCar__) */