#include "Player.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

Player::Player(std::string name, double initial_balance) 
    : name_(std::move(name)), balance_(initial_balance) {}

void Player::addBalance(double amount) {
    if (amount > 0) {
        balance_ += amount;
        std::cout << "Added $" << std::fixed << std::setprecision(2) 
                  << amount << " to your balance.\n";
    }
}

bool Player::spendBalance(double amount) {
    if (balance_ >= amount) {
        balance_ -= amount;
        return true;
    }
    return false;
}

void Player::addToInventory(std::unique_ptr<Item> item) {
    if (item) {
        inventory_.push_back(std::move(item));
    }
}

void Player::displayInventory() const {
    std::cout << "\n=== YOUR INVENTORY ===\n";
    std::cout << "Balance: $" << std::fixed << std::setprecision(2) << balance_ << "\n";
    std::cout << "Items (" << inventory_.size() << "):\n";
    
    if (inventory_.empty()) {
        std::cout << "Inventory is empty.\n";
        return;
    }
    
    for (size_t i = 0; i < inventory_.size(); ++i) {
        std::cout << i + 1 << ". " << inventory_[i]->get_info() << "\n";
    }
}

void Player::sellItem(size_t index) {
    if (index < inventory_.size()) {
        double price = inventory_[index]->get_price();
        balance_ += price;
        std::cout << "Sold item for $" << std::fixed << std::setprecision(2) 
                  << price << "\n";
        inventory_.erase(inventory_.begin() + index);
    } else {
        throw std::out_of_range("Invalid item index");
    }
}

double Player::getBalance() const {
    return balance_;
}

const std::string& Player::getName() const {
    return name_;
}

Item* Player::getLatestItem() const {
    if (inventory_.empty()) {
        return nullptr;
    }
    return inventory_.back().get();
}


Player& Player::operator+=(double amount) {
    addBalance(amount);
    return *this;
}

Player& Player::operator-=(double amount) {
    if (!spendBalance(amount)) {
        throw std::runtime_error("Insufficient balance");
    }
    return *this;
}

Player& Player::operator+=(std::unique_ptr<Item> item) {
    addToInventory(std::move(item));
    return *this;
}