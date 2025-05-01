#include "GameManager.h"

USING_NS_CC;

GameManager::GameManager() {
    // Constructor code here (if needed)
}

GameManager::~GameManager() {
    // Destructor code here (if needed)
}

GameManager* GameManager::getInstance() {
    static GameManager instance;
    return &instance;
}

void GameManager::doSomething() {
    CCLOG("MyManager singleton is doing something!");
}
void GameManager:: setSelectedCar(int number){
    this->selectedCar=number;
}
int GameManager:: getSelectedCar(){
    return this->selectedCar;
}
void GameManager:: setCarSpeed(int number){
    this->carSpeed=number;
}
int GameManager:: getCarSpeed(){
    return this->carSpeed;
}
void GameManager::setCarRef(cocos2d::Sprite *car) {
    this->car=car;
}
cocos2d::Sprite* GameManager:: getCarRef(){
    return this->car;
}
void GameManager::setGameEndStatus(bool value) {
    this->gameEndStatus=value;
}
bool GameManager::getGameEndStatus() {
    return this->gameEndStatus;
}

void GameManager::setGameScore(int number){
    this->gameScore=number;
}
int GameManager:: getGameScore(){
    return this->gameScore;
}
int GameManager:: getSpeedIncreaseIndicator(){
    return this->speedIncreaseIndicator;
}
void GameManager:: setSpeedIncreaseIndicator(int number){
    this->speedIncreaseIndicator=number;
}