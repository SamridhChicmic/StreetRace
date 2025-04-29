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
USING_NS_CC;

Scene* GameLobby::createScene()
{
    return GameLobby::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameLobby::init()
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
                                           CC_CALLBACK_1(GameLobby::menuCloseCallback, this));

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
    addCanvas();
    addBackground();
    setGameTitle("Street Racer");
    addScrollView();
    addStartButton();
    return true;
}
void GameLobby::addCanvas(){
    s =  Director::getInstance()->getWinSize();
    canvas =Node::create();
    canvas->setContentSize(s);
    canvas->setAnchorPoint(Vec2(0.5,0.5));
    canvas->setPosition(s/2);
    this->addChild(canvas, 0);

}
void GameLobby:: addBackground(){
    auto background = Sprite::create(ASSET::BACKGROUND.c_str());
    background->setContentSize(canvas->getContentSize());
    background->setAnchorPoint(Vec2(0.5,0.5));
    background->setPosition(s/2);
    canvas->addChild(background, 0);

}
void GameLobby::setGameTitle(const std::string& titleName) {
    auto title = Label::createWithTTF(titleName, "fonts/Marker Felt.ttf", 40);
    title->setAnchorPoint(Vec2(0.5,0.5));
    title->setPosition(canvas->getContentSize().width/2,canvas->getContentSize().height- 2*title->getContentSize().height);
    canvas->addChild(title);
}

void GameLobby::addScrollView(){
    pageView = cocos2d::ui::PageView::create();
    pageView->ignoreContentAdaptWithSize(false);
    pageView->setContentSize(Size(s.width, s.height/2)); // visible area
    pageView->setPosition(Vec2(s.width/2, (s.height/2)));    // position on screen
    pageView->setAnchorPoint(Vec2(0.5, 0.5)); // center-x, bottom-y
    canvas->addChild(pageView,1);

// ✨ Create Pages and Add to PageView
    for (int i = 0; i < 15; ++i) {
        auto layout = cocos2d::ui::Layout::create();
        layout->setContentSize(pageView->getContentSize()); // must match PageView size


        auto Car = Sprite::create("Car/Car" + std::to_string(i)+".png");
        Car->setPosition(layout->getContentSize() / 2); // center inside layout
        layout->addChild(Car);

        pageView->addPage(layout);
    }
    pageView->setCurrentPageIndex(0);

}
void GameLobby::addStartButton(){
    auto startButton=cocos2d::ui::Button::create(ASSET::BUTTON_START.c_str());
    startButton->setAnchorPoint(Vec2 (0.5, - 0.5));
    startButton->setPosition(Vec2 (s.width/2,50));
    startButton->ignoreContentAdaptWithSize(false);
    startButton->setContentSize(Size(100, 100));
    startButton->setTitleText("Start");
    startButton->setTitleFontName("fonts/Marker Felt.ttf");
    startButton->setTitleFontSize(30);
    canvas->addChild(startButton,3);
    startButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
//                log("Start",pageView->getCurrentPageIndex());
                CCLOG("Start - Page Index: %zd", pageView->getCurrentPageIndex());
                GameManager::getInstance()->setSelectedCar(pageView->getCurrentPageIndex());
                Director::getInstance()->replaceScene(GamePlay::createScene());
                break;
            case ui::Widget::TouchEventType::ENDED:
                log("End");
                break;
            default:
                break;
        }
    });
}
void GameLobby::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
