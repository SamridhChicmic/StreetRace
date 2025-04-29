

#ifndef __MoveRoad__
#define __MoveRoad__

#include "cocos2d.h"

using namespace cocos2d;

class MoveRoad : public CCComponent{
public:
    MoveRoad();
    void setSpeed(int speed);
private:
    virtual void onEnter();
    virtual void update(float delta);
    void actionMove();
};

#endif /* defined(__MoveRoad__) */