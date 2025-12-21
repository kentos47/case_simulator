#include "WeaponCase.h"
#include <stdexcept>
#include <random>

WeaponCase::WeaponCase(std::string name, double price)
    : Container(std::move(name), price) {}

std::unique_ptr<Container> WeaponCase::clone()  {
    auto newCase = std::make_unique<WeaponCase>(name_, price_);
    for ( auto& skin : items_) {
        if (auto* wpn = dynamic_cast<Weapon_Skin*>(skin.get())) {
            newCase->addWeapon(wpn->clone());
        }
    }
    return newCase;
}

std::unique_ptr<Item> WeaponCase::selectItem() {
    if (items_.empty()) {
        throw std::runtime_error("The WeaponCase is empty!");
    }

    std::discrete_distribution<int> dist{
        80,   // Mil-Spec
        16,    // Restricted
        3.2,    // Classified
        0.64,   // Covert
        0.16    // Rare Special Item
    };

    int rarityIndex = dist(rng_);

    std::vector<Weapon_Skin*> candidates;

    for ( auto& skinPtr : items_) {
        if (auto* wpn = dynamic_cast<Weapon_Skin*>(skinPtr.get())) {
            std::string rarity = wpn->get_rarity();
            int itemRarity = -1;

            if (rarity == "Mil-Spec") itemRarity = 0;
            else if (rarity == "Restricted") itemRarity = 1;
            else if (rarity == "Classified") itemRarity = 2;
            else if (rarity == "Covert") itemRarity = 3;
            else if (rarity == "Rare Special Item") itemRarity = 4;

            if (itemRarity == rarityIndex) {
                candidates.push_back(wpn);
            }
        }
    }

    if (candidates.empty()) {
        std::uniform_int_distribution<size_t> idxDist(0, items_.size() - 1);
        return items_[idxDist(rng_)]->clone();
    }

    std::uniform_int_distribution<size_t> idxDist(0, candidates.size() - 1);
    return candidates[idxDist(rng_)]->clone();
}

void WeaponCase::addWeapon(std::unique_ptr<Item> skin) {
    if (skin) {
        items_.push_back(std::move(skin));
    }
}