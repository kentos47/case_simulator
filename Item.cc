#include "Item.h"


Item::Item(std::string name, double price) : 
            name_(std::move(name)),
            price_(price) {}

double Item::get_price() {return price_;};


Weapon_Skin::Weapon_Skin(
        std::string name,
        std::string type,
        std::string rarity,
        double skin_float,
        double price
    ) :
        Item(std::move(name), price),
        type_(std::move(type)),
        rarity_(std::move(rarity)),
        skin_float_(skin_float) {}


std::string Weapon_Skin::get_info()  {
              std::string worness;
            if (skin_float_ < 0.07){worness = "Factory New";}
            else if (skin_float_ < 0.15){worness = "Minimal Wear";}
            else if (skin_float_ < 0.38){worness = "Field-Tested";}
            else if (skin_float_ < 0.45){worness = "Well-Worn";}
            else {worness = "Battle-Scarred";}
             return std::format("${:.2f}", price_)+" "+type_+
            " | "+name_+", "+rarity_+", "+worness;};

std::string Weapon_Skin::get_options_to_interuct() {return "-Использовать в контракте (Скоро)\n-Выбрать за сторону\n-Продать\n";}
double Weapon_Skin::get_float() {return skin_float_;};
std::string Weapon_Skin::get_rarity()  {return rarity_;}




std::vector<WeaponSkinData> skin_database = {
{"Lightning Strike","AWP",
    "Covert",
    0.03, 801.07},

    {"Case Hardened","AK-47",
    "Classified",
    0.23, 254.79},

    {"Hypnotic","Desert Eagle",
    "Classified",
    0.04, 246.77},
    
    {"Dragon Tatto","Glock-18",
    "Restricted",
    0.01, 194.80},
    
    {"Dark Water","M4A1-S",
    "Restricted",
    0.13, 121.88},
    
    {"Dark Water","USP-S",
    "Restricted",
    0.20, 116.52},

    {"Dark Water","USP-S",
    "Restricted",
    0.20, 116.52},
    
    {"Wings","AUG",
    "Mil-Spec",
    0.09, 17.93},
    
    {"Skulls","MP-7",
    "Mil-Spec",
    0.16, 14.36},
    
    {"Ultraviolet","SG-553",
    "Mil-Spec",
    0.51, 13.48},
    
    {"Fade", "Karambit", "Rare Special Item",
    0.01, 2479.58},

    {"Crimson Web", "M9 Bayonet", "Rare Special Item",
    0.33, 521.36},

    {"Case Hardened", "Flip Knife", "Rare Special Item",
    0.18, 175.38},

    {"Safari Mesh", "Gut Knife", "Rare Special Item",
    0.25, 58.98}
};
