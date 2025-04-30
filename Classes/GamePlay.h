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

#ifndef __GamePlay_SCENE_H__
#define __GamePlay_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameManager.h"
#include "CarMoveMent.h"
#include "RandomCar.h"
class GamePlay : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    cocos2d::Node* canvas;
    cocos2d::Node* land;
    cocos2d::Sprite* car;
    // cocos2d::ui::PageView* pageView;
    cocos2d::Size s;
    virtual bool init();
    
    // a selector callback
    void addCanvas();
    // void setGameTitle(const std::string& titleName);
    void menuCloseCallback(cocos2d::Ref* pSender);
    // void addScrollView();
    void addBackground();
    void addCar();
    void addBackButton();
    void onBackButtonClicked(cocos2d::Ref* sender);
    void addRandomCars();
    void  spawnCarCallback(float dt);
    void updateSpawnRate();
    void checkGameStatus(float dt);
    // void addStartButton();
    // implement the "static create()" method manually
    CREATE_FUNC(GamePlay);
};

#endif // __GamePlay_SCENE_H__
