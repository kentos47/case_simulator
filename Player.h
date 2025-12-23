#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <memory>
#include <string>
#include "Item.h"

// Интерфейс для игрока
class IPlayer {
public:
    virtual ~IPlayer() = default;
    virtual void addBalance(double amount) = 0;
    virtual bool spendBalance(double amount) = 0;
    virtual void addToInventory(std::unique_ptr<Item> item) = 0;
    virtual void displayInventory() const = 0;
    virtual void sellItem(size_t index) = 0;
    virtual double getBalance() const = 0;
    virtual Item* getLatestItem() const = 0; // Новый метод
};

// Реализация игрока
class Player : public IPlayer {
private:
    double balance_;
    std::vector<std::unique_ptr<Item>> inventory_;
    std::string name_;
    
public:
    Player(std::string name, double initial_balance = 100.0);
    
    void addBalance(double amount) override;
    bool spendBalance(double amount) override;
    void addToInventory(std::unique_ptr<Item> item) override;
    void displayInventory() const override;
    void sellItem(size_t index) override;
    double getBalance() const override;
    Item* getLatestItem() const override; // Реализация нового метода
    
    const std::string& getName() const;
    
    // Перегрузка операторов
    Player& operator+=(double amount);
    Player& operator-=(double amount);
    Player& operator+=(std::unique_ptr<Item> item);
};

#endif