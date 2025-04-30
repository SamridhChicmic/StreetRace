#include "CarMoveMent.h"
#include "GameManager.h"
CarMoveMent::CarMoveMent(){
    setName("CarMoveMent");
}
void CarMoveMent::setCar(Node * car){
    this->Car=car;
    OriginalPos = Car->getPosition();
}
Node* CarMoveMent::getCar(){
    return this->Car;
}
void CarMoveMent::onEnter(){
    Component::onEnter(); // Always call parent
    isMoving=false;
    land = this->_owner;
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(CarMoveMent::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(CarMoveMent::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, land);
}
bool CarMoveMent :: onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event){
    touchStart=touch->getLocation();
    CCLOG("Touch Began at: x=%f, y=%f", touchStart.x, touchStart.y);
    return true;
}
void CarMoveMent::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
    Vec2 touchEnd = touch->getLocation();
    CCLOG("Touch End at: x=%f, y=%f", touchEnd.x, touchEnd.y);

    float xDiff = touchEnd.x - touchStart.x;
    float threshold = land->getContentSize().width / 6.5;

    if (fabs(xDiff) < distanceDiff) return; // Ignore small swipes

    if (xDiff < 0) {
        moveCar(-threshold); // Swipe left
    } else {
        moveCar(threshold);  // Swipe right
    }
}

void CarMoveMent::moveCar(float diff) {
    if (!Car || !land || isMoving ) return;

    Vec2 currentPos = Car->getPosition();
    float maxOffsetRight = OriginalPos.x+land->getContentSize().width / 6.5;
    float maxOffsetLeft = OriginalPos.x-land->getContentSize().width / 6.5;
    float newX = currentPos.x + diff;
    CCLOG("OutSide  x=%f curr=%f", newX ,currentPos.x);
    if (newX >= maxOffsetLeft && newX <= maxOffsetRight) {
        float rotationAngle = (diff > 0) ? 15.0f : -15.0f;
        auto move = MoveTo::create(0.2f, Vec2(newX, currentPos.y));
        auto rotate = RotateTo::create(0.1f, rotationAngle);
        auto rotateBack = RotateTo::create(0.1f, 0.0f);
        auto onTweenFinished = CallFunc::create(CC_CALLBACK_0(CarMoveMent::onTweenFinished, this));
        isMoving=true;
        auto tween = Sequence::create(rotate, move, rotateBack,onTweenFinished, nullptr);
        Car->runAction(tween);
    } else {
        CCLOG("Car move blocked, out of bounds");
    }
}
void CarMoveMent::onTweenFinished() {
    isMoving=false;
}
void CarMoveMent::update(float delta){
   
}
