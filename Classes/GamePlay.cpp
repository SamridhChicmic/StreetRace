/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "GameLobby.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "Constant.h"
#include "GameManager.h"
#include "GamePlay.h"
#include "MoveRoad.h"
#include "CarMoveMent.h"
#include "RandomCar.h"
#include "ScoreHandler.h"
USING_NS_CC;

Scene* GamePlay::createScene()
{
    return GamePlay::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GamePlay::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GamePlay::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // // create menu, it's an autorelease object
    // auto menu = Menu::create(closeItem, NULL);
    // menu->setPosition(Vec2::ZERO);
    // this->addChild(menu, 1);
    ////////////////////////////
    // 3. add your codes below...
//    GameManager::getInstance()->setGameEndStatus(false);
    addCanvas();
    addBackground();
    addBackButton();
    addCar();
    updateSpawnRate();
    this->schedule(CC_SCHEDULE_SELECTOR(GamePlay::checkGameStatus), 0.1f);
    addGameScore();
    return true;
}
void GamePlay::addCanvas(){
    s =  Director::getInstance()->getWinSize();
    canvas =Node::create();
    canvas->setContentSize(s);
    canvas->setAnchorPoint(Vec2(0.5,0.5));
    canvas->setPosition(s/2);
    this->addChild(canvas, 0);
}
void GamePlay:: addBackground(){
     land= Node::create();
     land->setContentSize(canvas->getContentSize());
     land->setAnchorPoint(Vec2(0.5,0.5));
     land->setPosition(s/2);
     canvas->addChild(land, 0);
     land->addComponent(new CarMoveMent());
     GameManager::getInstance()->setCarSpeed(10);
     auto spriteOne=Sprite::create(ASSET::ROAD.c_str());
     spriteOne->setAnchorPoint(Vec2(0,0));
     spriteOne->setContentSize(s);
     spriteOne->addComponent(new MoveRoad());
     land->addChild(spriteOne);
     auto spriteTwo=Sprite::create(ASSET::ROAD.c_str());
     spriteTwo->setContentSize(s);
     spriteTwo->setPosition(0,land->getContentSize().height);
     spriteTwo->setAnchorPoint(Vec2(0,0));
     spriteTwo->addComponent(new MoveRoad());
     land->addChild(spriteTwo);
}

void GamePlay:: addCar(){
    int carId = GameManager::getInstance()->getSelectedCar();
    std::string str = std::to_string(carId);
     car=Sprite::create("Car/Car"+ str +".png");
     car->setContentSize(Size(32.5,75));
    car->setAnchorPoint(Vec2(0.5,0.5));
    car->setPosition(Vec2(s.width/2,car->getContentSize().height));
    canvas->addChild(car);
    // get Component
    auto carMoveComponent = dynamic_cast<CarMoveMent*>(land->getComponent("CarMoveMent"));
    if (carMoveComponent) {
        carMoveComponent->setCar(car);
    }
    GameManager::getInstance()->setCarRef(car);
}
void GamePlay::onBackButtonClicked(cocos2d::Ref* sender){
    auto scene = GameLobby::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
}
void GamePlay::addBackButton(){
    auto backbtn=cocos2d::ui::Button::create(ASSET::BACK_BTN.c_str());
    backbtn->ignoreContentAdaptWithSize(false);
    backbtn->setAnchorPoint(Vec2(0.5,0.5));
    backbtn->setContentSize(Size(40,40));
    backbtn->setPosition(Vec2(50,s.height-50));
    canvas->addChild(backbtn);
    backbtn->addClickEventListener(CC_CALLBACK_1(GamePlay::onBackButtonClicked, this));
}

void GamePlay::addRandomCars() {
    auto car = carPool.getNode();
    if(car){
        auto RandomCarComponent = dynamic_cast<RandomCar*>(car->getComponent("RandomCar"));
        if (RandomCarComponent) {
            RandomCarComponent->createRandomCar(s,land,canvas,carPool,score );
        }
        canvas->addChild(car);
    }else{
        Sprite * obstacleCar=Sprite::create();
        obstacleCar->addComponent(new RandomCar());
        auto RandomCarComponent = dynamic_cast<RandomCar*>(obstacleCar->getComponent("RandomCar"));
        if (RandomCarComponent) {
            RandomCarComponent->createRandomCar(s,land,canvas,carPool,score);
        }

        canvas->addChild(obstacleCar);

    }

}
void GamePlay::spawnCarCallback(float dt) {
    addRandomCars();
}
void GamePlay::updateSpawnRate() {
    this->unschedule(CC_SCHEDULE_SELECTOR(GamePlay::spawnCarCallback));

    float carHeight = 75.0f;
    float carSpeed = GameManager::getInstance()->getCarSpeed()*10;
    float spawnInterval = carHeight / carSpeed;

    this->schedule(CC_SCHEDULE_SELECTOR(GamePlay::spawnCarCallback), spawnInterval);
}
void GamePlay::checkGameStatus(float dt) {
    if (GameManager::getInstance()->getGameEndStatus()) {
        this->unschedule(CC_SCHEDULE_SELECTOR(GamePlay::spawnCarCallback));
        this->unschedule(CC_SCHEDULE_SELECTOR(GamePlay::checkGameStatus)); // stop checking after it's ended
//        this->car->removeFromParentAndCleanup(true);
        CCLOG("Game ended. Callback unscheduled.");
        gameEndPopUp();
    }
}
void GamePlay::gameEndPopUp(){
    CCLOG(" Game Play PopUp  state=%d",GameManager::getInstance()->getGameEndStatus());
    auto base=Sprite::create(ASSET::Base);
    base->setPosition(s/2);
    Vec2 sizeBase=base->getBoundingBox().size;
    base->setContentSize(Size(s.width/1.2,sizeBase.y));
    canvas->addChild(base);
    auto title = Label::createWithTTF("Game Over", "fonts/Marker Felt.ttf", 40);
    base->addChild(title);
    title->setAnchorPoint(Vec2(0.5,0.5));
    title->setTextColor(Color4B(117, 53, 0, 100));
    title->setAlignment(TextHAlignment::CENTER);
    title->setPosition(Vec2(base->getContentSize().width/2,sizeBase.y-40));

    auto score = Label::createWithTTF("Score : "+std::to_string(GameManager::getInstance()->getGameScore()), "fonts/Marker Felt.ttf", 30);
    base->addChild(score);
    score->setAnchorPoint(Vec2(0.5,0.5));
    score->setTextColor(Color4B(117, 53, 0, 100));
    score->setAlignment(TextHAlignment::CENTER);
    score->setPosition(Vec2(base->getContentSize().width/2,sizeBase.y-100));
    // Button

    auto restartButton=cocos2d::ui::Button::create(ASSET::Blue_Button.c_str());
    restartButton->setAnchorPoint(Vec2 (0.5, 0.5));
    restartButton->setPosition(Vec2 (base->getContentSize().width/2,50));
    restartButton->ignoreContentAdaptWithSize(false);
    restartButton->setContentSize(Size(100, 50));
//    restartButton->setTitleText("Restart");
//    restartButton->setTitleFontName("fonts/Marker Felt.ttf");
//    restartButton->setTitleFontSize(20);
    auto buttonTitle = Label::createWithTTF("Restart", "fonts/Marker Felt.ttf", 20);
    restartButton->addChild(buttonTitle);
    buttonTitle->setAnchorPoint(Vec2(0.5,0.5));
    buttonTitle->setPosition(Vec2(restartButton->getContentSize().width/2,restartButton->getContentSize().height/2  + 5));
    base->addChild(restartButton,3);
    restartButton->addClickEventListener(CC_CALLBACK_1(GamePlay::onRestartButtonClicked, this));
}
void GamePlay:: onRestartButtonClicked(cocos2d::Ref* sender){
    this->unscheduleAllCallbacks();
    GameManager::getInstance()->setGameEndStatus(false);
    this->canvas->removeAllChildren();
    CCLOG(" In Reset Game PopUp State Change:: %d", GameManager::getInstance()->getGameEndStatus());
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, GamePlay::createScene()));
}
void GamePlay::addGameScore() {
    GameManager::getInstance()->setGameScore(0);
    auto scorebase= Sprite::create(ASSET::BaseCard.c_str());
    scorebase->setContentSize(Size(60,60));
    scorebase->setPosition(Vec2(s.width - 60 ,s.height - 60 ));
    canvas->addChild(scorebase);
    scorebase->setAnchorPoint(Vec2(0.5,0.5));


    score = Label::createWithTTF(std::to_string(GameManager::getInstance()->getGameScore()), "fonts/Marker Felt.ttf", 25);
    canvas->addChild(score);
    scorebase->setAnchorPoint(Vec2(0.5,0.5));
//    score->setTextColor(Color4B(255, 221, 85, 255));
    score->setPosition(Vec2(s.width - 60 ,s.height - 55 ));
    score->addComponent(new ScoreHandler());

}

void GamePlay::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
