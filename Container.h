#ifndef CASE_H
#define CASE_H

#include <vector>
#include <memory>      
#include <random>
#include <string>
#include "Item.h"

class Container {
protected:
    std::string name_;
    double price_;
    std::vector<std::unique_ptr<Item>> items_; 
    std::mt19937 rng_; 
    virtual std::unique_ptr<Item> selectItem();

public:
    Container(std::string name, double price); 
    virtual ~Container() = default;

    virtual std::string getName() ;
    virtual double getPrice() ;
    virtual std::unique_ptr<Item> open();
    virtual void addItem(std::unique_ptr<Item> skin);
    virtual void displayContents();
    virtual Container& operator+=(std::unique_ptr<Item> item);
};

#endif // CASE_H
