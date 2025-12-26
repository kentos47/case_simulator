#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <memory>
#include <string>
#include "Item.h"

class IPlayer {
public:
    virtual ~IPlayer() = default;
    virtual void addBalance(double value) = 0;
    virtual bool spendBalance(double value) = 0;
    virtual void addToInventory(std::unique_ptr<Item> item) = 0;
    virtual void displayInventory() = 0;
    virtual void sellItem(int index) = 0;
    virtual void sellAllItems() = 0;
    virtual double getBalance() = 0;
    virtual int getCountOfItems() = 0;
    virtual Item* getLatestItem() = 0; 
};

class Player : public IPlayer {
private:
    double balance_;
    std::vector<std::unique_ptr<Item>> inventory_;
    
public:
    Player(double start_balance);
    
    void addBalance(double value) override;
    bool spendBalance(double value) override;
    void addToInventory(std::unique_ptr<Item> item) override;
    void displayInventory() override;
    void sellItem(int index) override;
    void sellAllItems() override;
    double getBalance() override;
    int getCountOfItems() override;
    Item* getLatestItem() override;
    
};

#endif