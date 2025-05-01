#ifndef __CAR_MOVEMENT_H__
#define __CAR_MOVEMENT_H__

#include "cocos2d.h"
using namespace cocos2d;
class CarMoveMent : public Component {
public:
    CarMoveMent();

    virtual void onEnter() override;
    virtual void update(float delta) override;

    void setCar(cocos2d::Node* car);
    cocos2d::Node* getCar();

protected:
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

private:
    void moveCar(float diff);
    void onTweenFinished();

private:
    cocos2d::Node* Car = nullptr;
    cocos2d::Node* land = nullptr;

    cocos2d::Vec2 OriginalPos;
    cocos2d::Vec2 touchStart;

    bool isMoving = false;
    bool swipeDetected = false;

    float distanceDiff = 30.0f; // Minimum swipe distance to trigger movement
};

#endif // __CAR_MOVEMENT_H__
