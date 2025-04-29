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
