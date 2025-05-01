#include "CarMoveMent.h"
#include "GameManager.h"

CarMoveMent::CarMoveMent() {
    setName("CarMoveMent");
}

void CarMoveMent::setCar(Node* car) {
    this->Car = car;
    OriginalPos = car->getPosition();
}

Node* CarMoveMent::getCar() {
    return this->Car;
}

void CarMoveMent::onEnter() {
    Component::onEnter(); // Always call parent
    isMoving = false;
    land = this->_owner;

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(CarMoveMent::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(CarMoveMent::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(CarMoveMent::onTouchEnded, this);

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, land);
}

bool CarMoveMent::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    if (GameManager::getInstance()->getGameEndStatus()) return false;
    touchStart = touch->getLocation();
    swipeDetected = false;
    return true;
}

void CarMoveMent::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
    if (GameManager::getInstance()->getGameEndStatus() || swipeDetected || isMoving) return;

    Vec2 touchEnd = touch->getLocation();
    float xDiff = touchEnd.x - touchStart.x;
    float threshold = land->getContentSize().width / 6.5;

    if (fabs(xDiff) >= distanceDiff) {
        swipeDetected = true; // Prevent further calls for same swipe
        if (xDiff < 0) {
            moveCar(-threshold); // Swipe left
        } else {
            moveCar(threshold);  // Swipe right
        }
    }
}

void CarMoveMent::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
    // No longer needed for responsiveness
}

void CarMoveMent::moveCar(float diff) {
    if (!Car || !land || isMoving) return;

    Vec2 currentPos = Car->getPosition();
    float laneWidth = land->getContentSize().width / 6.5;

    float maxOffsetRight = OriginalPos.x + laneWidth;
    float maxOffsetLeft = OriginalPos.x - laneWidth;
    float newX = currentPos.x + diff;

    // Clamp between lanes
    if (newX >= maxOffsetLeft && newX <= maxOffsetRight) {
        float rotationAngle = (diff > 0) ? 18.0f : -18.0f;
        auto move = MoveTo::create(0.08f, Vec2(newX, currentPos.y));
        auto rotate = RotateTo::create(0.08f, rotationAngle);
        auto rotateBack = RotateTo::create(0.08f, 0.0f);
        auto onTweenFinished = CallFunc::create(CC_CALLBACK_0(CarMoveMent::onTweenFinished, this));
        isMoving = true;
        auto tween = Sequence::create(rotate, move, rotateBack, onTweenFinished, nullptr);
        Car->runAction(tween);
    }
}

void CarMoveMent::onTweenFinished() {
    isMoving = false;
}

void CarMoveMent::update(float delta) {
    // optional future use
}
