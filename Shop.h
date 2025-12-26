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
    Container* getContainer(int index);
    void addContainer(std::unique_ptr<Container> container);
    int getContainerCount() const;
};

#endif
