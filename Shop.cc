#include "Shop.h"
#include "WeaponCase.h"
#include <iostream>


Shop::Shop() = default;

void Shop::displayAvailableContainers() const {
    std::cout << "\n=== AVAILABLE CASES ===\n";
    for (size_t i = 0; i < available_containers_.size(); ++i) {
        std::cout << i + 1 << ". ";
        available_containers_[i]->displayContents();
    }
}

Container* Shop::getContainer(size_t index) {
    if (index < available_containers_.size()) {
        return available_containers_[index].get();
    }
    return nullptr;
}

void Shop::addContainer(std::unique_ptr<Container> container) {
    if (container) {
        available_containers_.push_back(std::move(container));
    }
}

size_t Shop::getContainerCount() const {
    return available_containers_.size();
}

