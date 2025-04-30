

#ifndef __MoveRoad__
#define __MoveRoad__

#include "cocos2d.h"

using namespace cocos2d;

class MoveRoad : public Component{
public:
    Node * SpriteOne;
    Node * SpriteTwo;
    MoveRoad();
    void setSpeed(int speed);
private:
    virtual void onEnter();
    virtual void update(float delta);
    void actionMove();
};

#endif /* defined(__MoveRoad__) */