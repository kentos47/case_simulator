#include "Container.h"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <random>

// Конструктор
Container::Container(std::string name, double price)
    : name_(std::move(name)), price_(price) {
    std::random_device rd;
    rng_ = std::mt19937(rd());
}

std::string Container::getName() {
    return name_;
}

double Container::getPrice() {
    return price_;
}

std::unique_ptr<Item> Container::selectItem() {
    if (items_.empty()) {
        throw std::runtime_error("The container is empty!");
    }

    std::uniform_int_distribution<size_t> dist(0, items_.size() - 1);
    return items_[dist(rng_)]->clone();
}

std::unique_ptr<Item> Container::open() {
    return selectItem();
}

void Container::addItem(std::unique_ptr<Item> item) {
    if (item) {
        items_.push_back(std::move(item));
    }
}

void Container::displayContents() {
    std::cout << "\n=== " << name_ << " ($" << price_ << ") ===" << std::endl;
    std::cout << "Content (" << items_.size() << " items):\n";
    for (auto& item : items_) {
        std::cout << "- " << item->get_info() << "\n";
    }
}

bool Container::operator==(Container& other) {
    return name_ == other.name_ && price_ == other.price_;
}

Container& Container::operator+=(std::unique_ptr<Item> item) {
    addItem(std::move(item));
    return *this;
}