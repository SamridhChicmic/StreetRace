#include "ScoreHandler.h"
#include "GameManager.h"
ScoreHandler::ScoreHandler(){
    setName("ScoreHandler");
}
void ScoreHandler::onEnter(){

}
void ScoreHandler::scoreUpdate() {
    auto newScore = GameManager::getInstance()->getGameScore() + 1;
    GameManager::getInstance()->setGameScore(newScore);
    if (auto label = dynamic_cast<cocos2d::Label*>(this->getOwner())) {
        label->setString(std::to_string(newScore));
    }
}
void ScoreHandler::update(float delta){
    
}
