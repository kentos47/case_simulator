#include "Player.h"
#include <iostream>
#include <stdexcept>

Player::Player(double start_balance) : balance_(start_balance) {}

void Player::addBalance(double value) {
    if (value > 0) {
        balance_ += value;
        std::cout << "Added $" << value << " to your balance.\n";
    }
}

bool Player::spendBalance(double value) {
    if (balance_ >= value) {
        balance_ -= value;
        return true;
    }
    return false;
}

void Player::addToInventory(std::unique_ptr<Item> item) {
    if (item) {
        inventory_.push_back(std::move(item));
    }
}

void Player::displayInventory() {
    std::cout << "\n=== YOUR INVENTORY ===\n";
    std::cout << "Balance: $" <<  balance_ << "\n";
    std::cout << "Items (" << inventory_.size() << "):\n";
    
    if (inventory_.empty()) {
        std::cout << "Inventory is empty.\n";
        return;
    }
    
    for (int i = 0; i < inventory_.size(); ++i) {
        std::cout << i + 1 << ". " << inventory_[i]->get_info() << "\n";
    }
}

void Player::sellItem(int index) {
    if (index < inventory_.size()) {
        double price = inventory_[index]->get_price();
        balance_ += price;
        std::cout << "Sold item for $" << price << "\n";
        inventory_.erase(inventory_.begin() + index);
    } else {
        throw std::out_of_range("Invalid item index");
    }
}

void Player::sellAllItems(){
    if (!(inventory_.empty())){
        for (int i = 0; i<inventory_.size(); i++){
            double price = inventory_[i]->get_price();
            balance_ += price;
        }
        inventory_.clear();
    } else {
        throw std::out_of_range("Inventory is empty");
    }
}



double Player::getBalance() {
    return balance_;
}

int Player::getCountOfItems() {
    return inventory_.size();
}




