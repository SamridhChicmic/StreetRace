#ifndef __ScoreHandler__
#define __ScoreHandler__

#include "cocos2d.h"

using namespace cocos2d;

class ScoreHandler : public Component{
public:
    ScoreHandler();
    void scoreUpdate();
private:
    virtual void onEnter();
    virtual void update(float delta);

};
#endif /* defined(__ScoreHandler__) */