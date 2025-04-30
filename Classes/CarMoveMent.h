

#ifndef __CarMoveMent__
#define __CarMoveMent__

#include "cocos2d.h"

using namespace cocos2d;

class CarMoveMent : public Component{
public:
    CarMoveMent();
    Vec2 touchStart;
    Vec2 OriginalPos;
    Node * land;
    bool isMoving;
    int distanceDiff=20;
    void setCar(Node * car);
    Node* getCar();
    bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    void moveCar(float diff);
    void onTweenFinished();
private:
    Node * Car;
    virtual void onEnter();
    virtual void update(float delta);

};

#endif /* defined(__CarMoveMent__) */