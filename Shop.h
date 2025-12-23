#ifndef SHOP_H
#define SHOP_H

#include <vector>
#include <memory>
#include "Container.h"

class Shop {
private:
    std::vector<std::unique_ptr<Container>> available_containers_;
    
public:
    Shop();
    
    void displayAvailableContainers() const;
    Container* getContainer(size_t index);
    void addContainer(std::unique_ptr<Container> container);
    size_t getContainerCount() const;
};

#endif