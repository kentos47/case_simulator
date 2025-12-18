#pragma once
#include <string>
#include <iostream>
#include <format>
#include <vector>

class Skin {
    protected:
    std::string name_;
    double price_;

    public:
        Skin(std::string name, double price) : 
            name_(std::move(name)),
            price_(price) {}

        virtual ~Skin() = default;
        virtual std::string get_info() = 0;

        virtual std::string get_type() = 0;
        virtual double get_price() = 0;
        virtual std::string get_options_to_interuct() = 0;

};

//class Sticker : public Skin {};

class Weapon_Skin : public Skin {
    private:
        std::string type_;
        std::string collection_;
        std::string rarity_;
        double skin_float_;
    public:
        Weapon_Skin(
        std::string name,
        std::string type,
        std::string collection,
        std::string rarity,
        double skin_float,
        double price) :
        Skin(std::move(name), price),
        type_(std::move(type)),
        collection_(std::move(collection)),
        rarity_(std::move(rarity)),
        skin_float_(skin_float) {}
        
        std::string get_type() override {return type_;};
        double get_price() override {return price_;};
        std::string get_options_to_interuct() override {return "-Использовать в контракте (Скоро)\n-Выбрать за сторону\n-Продать\n";};
        std::string get_info() override {
            std::string worness;
            if (skin_float_ < 0.07){worness = "Factory New";}
            else if (skin_float_ < 0.15){worness = "Minimal Wear";}
            else if (skin_float_ < 0.38){worness = "Field-Tested";}
            else if (skin_float_ < 0.45){worness = "Well-Worn";}
            else {worness = "Battle-Scarred";}
            
            return std::format("${:.2f}", price_)+" "+type_+
            " | "+name_+", "+rarity_+", "+worness;}

        std::string get_collection() {return collection_;};
        double get_float() {return skin_float_;};
        std::string get_rarity() {return rarity_;};
};

struct SkinData {
    std::string name;
    std::string type;
    std::string collection;
    std::string rarity;
    double skin_float;
    double price;
};

extern std::vector<SkinData> skin_database;