#ifndef WEAPON_CASE_H
#define WEAPON_CASE_H
#include <memory>
#include <vector>
#include "Container.h"
#include "Item.h"

class WeaponCase : public Container {

    public:
    WeaponCase(std::string name, double price);
    std::unique_ptr<Item> selectItem() override;
    void addWeapon(std::unique_ptr<Weapon_Skin> skin);
    WeaponCase& operator +=(std::unique_ptr<Weapon_Skin>);
};

#endif 
