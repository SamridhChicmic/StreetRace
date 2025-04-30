#include "MoveRoad.h"
#include "GameManager.h"
MoveRoad::MoveRoad(){
    setName("MoveRoad");
}

void MoveRoad::onEnter(){
    actionMove();
}
void MoveRoad::update(float delta){
    bool gameStatus=GameManager::getInstance()->getGameEndStatus();
    if(gameStatus)return;
     int speed=GameManager::getInstance()->getCarSpeed();
     if (this->_owner == NULL) return;
     Vec2 position=this->_owner->getPosition();
     int totalHeight=this->_owner->getContentSize().height;
     if(position.y> -totalHeight){
         position.y=position.y-speed;
         this->_owner->setPosition(Vec2(position.x,position.y));
     }else{
         this->_owner->setPosition(0,totalHeight-speed);
     }
}


void MoveRoad::actionMove(){

}