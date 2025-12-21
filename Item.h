#pragma once
#include <memory>
#include <string>
#include <iostream>
#include <format>
#include <vector>

class Item {
    protected:
    std::string name_;
    double price_;

    public:
        Item(std::string name, double price);

        virtual ~Item() = default;
        virtual std::string get_info() = 0;

        virtual std::string get_rarity() = 0;
        virtual std::string get_type() = 0;
        virtual double get_price() = 0;
        virtual std::string get_options_to_interuct() = 0;
        virtual std::unique_ptr<Item> clone() = 0;

};


class Weapon_Skin : public Item {
    private:
        std::string type_;
        std::string rarity_;
        double skin_float_;
        
    public:
        Weapon_Skin(
        std::string name,
        std::string type,
        std::string rarity,
        double skin_float,
        double price);
        
        std::string get_type() override;
        double get_price() override;
        std::string get_options_to_interuct() override;
        std::string get_info() override;
        double get_float();
        std::string get_rarity() override;

};




struct WeaponSkinData {
    std::string name;
    std::string type;
    std::string rarity;
    double skin_float;
    double price;
};

extern std::vector<WeaponSkinData> skin_database;
