#ifndef GAME_SIMULATOR_H
#define GAME_SIMULATOR_H

#include "Shop.h"
#include "Player.h"
#include <memory>

class GameSimulator {
private:
    std::unique_ptr<Shop> shop_;
    std::unique_ptr<Player> player_;
    
    void openSingleCase();
    void openMultipleCases();
    void sellItem();
    void sellAllItems();
    void addBalance();
    
public:
    GameSimulator();
    void run();
};

#endif
