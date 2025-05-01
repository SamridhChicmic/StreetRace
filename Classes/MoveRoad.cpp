#include "MoveRoad.h"
#include "GameManager.h"
MoveRoad::MoveRoad(){
    setName("MoveRoad");
}

void MoveRoad::onEnter(){
    actionMove();
}
void MoveRoad::update(float delta){
    if (GameManager::getInstance()->getGameEndStatus()) return;
    if (this->_owner == nullptr) return;

    int speed = GameManager::getInstance()->getCarSpeed();
    Vec2 position = this->_owner->getPosition();
    int height = this->_owner->getContentSize().height;

    position.y -= speed;

    // If completely off screen (moved below -height), move back to top
    if (position.y <= -height) {
        position.y += height * 2;  // move above the other sprite
    }

    this->_owner->setPosition(position);
}


void MoveRoad::actionMove(){

}