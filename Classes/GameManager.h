#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "cocos2d.h"

class GameManager {
public:
    // Get the singleton instance
    static GameManager* getInstance();

    // Example function
    void doSomething();
    void setSelectedCar(int number);
    int getSelectedCar();
    void setCarSpeed(int number);
    int getCarSpeed();
    void setCarRef(cocos2d::Sprite* car);
    cocos2d::Sprite* getCarRef();
    void setGameEndStatus(bool value);
    bool getGameEndStatus();
private:
    // Private constructor and destructor
    GameManager();
    ~GameManager();
    int selectedCar;
    int carSpeed;
    cocos2d::Sprite* car;
    bool gameEndStatus;
    // Delete copy constructor and assignment operator to prevent copies
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;
};

#endif // __GAME_MANAGER_H__
