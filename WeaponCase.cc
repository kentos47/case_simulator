#include "WeaponCase.h"
#include "Item.h"
#include <memory>
#include <stdexcept>
#include <random>

WeaponCase::WeaponCase(std::string name, double price)
    : Container(std::move(name), price) {}
    
std::unique_ptr<Item> WeaponCase::selectItem() {
    if (items_.empty()) {
        throw std::runtime_error("The WeaponCase is empty!");
    }

    std::uniform_real_distribution<double> dist(0.0, 100.0);
    double roll = dist(rng_);

    int rarityIndex;
    if (roll < 80.0) {
        rarityIndex = 0;
    } else if (roll < 96.0) {
        rarityIndex = 1;
    } else if (roll < 99.2) {
        rarityIndex = 2;
    } else if (roll < 99.84) {
        rarityIndex = 3;
    } else {
        rarityIndex = 4;
    }

    std::vector<Weapon_Skin*> candidates;
    for (auto& item : items_) {
        if (auto* wpn = dynamic_cast<Weapon_Skin*>(item.get())) {
            int itemRarity = -1;
            std::string r = wpn->get_rarity();
            if (r == "Mil-Spec") itemRarity = 0;
            else if (r == "Restricted") itemRarity = 1;
            else if (r == "Classified") itemRarity = 2;
            else if (r == "Covert") itemRarity = 3;
            else if (r == "Rare Special Item") itemRarity = 4;

            if (itemRarity == rarityIndex) {
                candidates.push_back(wpn);
            }
        }
    }

    std::uniform_int_distribution<size_t> idx(0, candidates.size() - 1);
    return candidates[idx(rng_)]->clone();
}

void WeaponCase::addWeapon(std::unique_ptr<Weapon_Skin> skin) {
    if (skin) {
        items_.push_back(std::move(skin));
    }
}

WeaponCase& WeaponCase::operator +=(std::unique_ptr<Weapon_Skin> skin) {
    addWeapon(std::move(skin));
    return *this;
}
