#include "RandomCar.h"
#include "GameManager.h"
RandomCar::RandomCar(){
    setName("RandomCar");
}
void RandomCar::onEnter(){

}
void RandomCar::createRandomCar(Size  s,Node * land, Node * canvas,NodePool carPool){
    this->carPool=carPool;
    Vec2 OriginalPos = Vec2(s.width/2, s.height);
    Vec2 maxOffsetRight = Vec2(OriginalPos.x + land->getContentSize().width / 6.5, s.height);
    Vec2 maxOffsetLeft = Vec2(OriginalPos.x - land->getContentSize().width / 6.5, s.height);

    // Static array for fixed positions
    Vec2 randomCarPositions[3] = {maxOffsetLeft, OriginalPos, maxOffsetRight};


    Sprite* car = dynamic_cast<Sprite*>(this->getOwner());
    int carId = cocos2d::RandomHelper::random_int(0, 14);
    std::string str = std::to_string(carId);
    if (car) {
        car->setTexture("Car/Car" + str + ".png");
    }
    car->setContentSize(Size(32.5, 75));
    car->setAnchorPoint(Vec2(0.5, 0.5));
    int randIndex = cocos2d::RandomHelper::random_int(0, 2);
    car->setPosition(randomCarPositions[randIndex]);
}
void RandomCar::moveRandomCar(){
    Vec2 CurrPos=this->_owner->getPosition();
    if(CurrPos.y>=-75){
        CurrPos.y=CurrPos.y-(GameManager::getInstance()->getCarSpeed()/2);
        this->_owner->setPosition(Vec2(CurrPos.x,CurrPos.y--));
    }
    else{

         this->getOwner()->removeFromParent();
        this->carPool.returnNode(dynamic_cast<Sprite*>(this->getOwner()));
    }
}

void RandomCar::collisionCheck() {
    bool value= this->getOwner()->getBoundingBox().intersectsRect(GameManager::getInstance()->getCarRef()->getBoundingBox());
    if(value){
        GameManager::getInstance()->setGameEndStatus(true);
    }
}
void RandomCar::update(float delta){
    bool gameStatus=GameManager::getInstance()->getGameEndStatus();
    if(gameStatus)return;
     moveRandomCar();
     collisionCheck();
}
