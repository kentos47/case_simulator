#include "GameSimulator.h"
#include "WeaponCase.h"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <iomanip>


void initCase(Container* container) {
    for (auto& skinData : skin_database) {
        auto skin = std::make_unique<Weapon_Skin>(
            skinData.name, 
            skinData.type, 
            skinData.rarity, 
            skinData.skin_float, 
            skinData.price
        );
        container->addItem(std::move(skin));
    }
}

GameSimulator::GameSimulator() 
    : shop_(std::make_unique<Shop>()), 
      player_(std::make_unique<Player>(42000.0)) {
    
    auto weaponCase1 = std::make_unique<WeaponCase>("Weapon Case", 105.0);
    // auto weaponCase2 = std::make_unique<WeaponCase>("Knife Case", 9.99);
    
    initCase(weaponCase1.get());
    // initCase(weaponCase2.get());
    
    shop_->addContainer(std::move(weaponCase1));
    // shop_->addContainer(std::move(weaponCase2));
}

void GameSimulator::openSingleCase() {
    shop_->displayAvailableContainers();
    
    
    std::cout << "Select case (0 to cancel): ";
    int choice;
    std::cin >> choice;
    
    if ((choice > shop_->getContainerCount())||(choice < 0)) {
        std::cout << "\nIncorrect input\n";
        return;
    }
    
    if (choice == 0) {return;}

    Container* selected = shop_->getContainer(choice - 1);
    
    if (player_->spendBalance(selected->getPrice())) {
        auto item = selected->open();
        std::cout << "\n";
        std::cout << "===================================================================\n";
        std::cout << "You got: " << item->get_info() << "\n";
        std::cout << "===================================================================\n";
        player_->addToInventory(std::move(item));   
    } else {
        std::cout << "Not enough money!\n";
    }
}


void GameSimulator::openMultipleCases() {
    shop_->displayAvailableContainers();
    
    std::cout << "\nSelect a case type to open (0 to cancel): ";
    int case_choice;
    std::cin >> case_choice;
    
    if (case_choice == 0) {return;}
    
    if ((case_choice > shop_->getContainerCount())||(case_choice < 0)) {
        std::cout << "\nIncorrect input\n";
        return;
    }


    Container* selected = shop_->getContainer(case_choice - 1);
    
    std::cout << "How many cases to open? ";
    int count;
    std::cin >> count;
    
    if (count == 0) {return;}
    if (count < 0) {
        std::cout << "\nIncorrect input\n";
        return;
    }

    double total_cost = selected->getPrice() * count;
    std::cout << "Total cost: $" << total_cost << "\n";
    
    if (player_->spendBalance(total_cost)) {
        std::cout << "\nOpening " << count << " " << selected->getName() << "s...\n";
        for (int i = 0; i < count; ++i) {
            auto item = selected->open();
            std::cout << "Case " << i + 1 << ": " << item->get_info() << "\n";
            player_->addToInventory(std::move(item));   
        }
    } else {
        std::cout << "Insufficient balance! Need $" << total_cost - (player_->getBalance()) << "\n";
    }
}

void GameSimulator::sellItem() {
    player_->displayInventory();
    
    std::cout << "\nSelect item to sell (0 to cancel): ";
    int choice;
    std::cin >> choice;
    
    if (choice == 0) return;
    
    if ((choice > player_->getCountOfItems())||(choice < 0)) {
        std::cout << "\nIncorrect input\n";
        return;
    }

    player_->sellItem(choice - 1);
    
}

void GameSimulator::sellAllItems(){
    std::cout << "\nAre u sure? All items will be sold(Y/N)\n";
    char choice;
    std::cin >> choice;
    if (choice != 'Y' && choice != 'N'){
        std::cout << "\nI don't understand you\n";
        return;
    }
    else {
        if (choice == 'Y') {
        player_->sellAllItems();
        std::cout << "\nAll items succesfully sold";
        }
    }
}



void GameSimulator::addBalance() {
    std::cout << "\nHow much balance to add? $";
    double value;
    std::cin >> value;
    
    if (value > 0) {
        player_->addBalance(value);
    } else {
        std::cout << "Invalid value!\n";
    }
}

void GameSimulator::run() {
    bool running = true;
    
    while (running) {
        std::cout << "\n=== CASE OPENING SIMULATOR ===\n";
        std::cout << "Balance: $" << player_->getBalance() << "\n";
        std::cout << "1. View available cases\n";
        std::cout << "2. Open a single case\n";
        std::cout << "3. Open multiple cases\n";
        std::cout << "4. Show inventory\n";
        std::cout << "5. Sell item\n";
        std::cout << "6. Sell all items\n";
        std::cout << "7. Add balance\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";
        
        int choice;
        std::cin >> choice;
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        

        switch (choice) {
            case 1:
                shop_->displayAvailableContainers();
                std::cout << "\nPress Enter to continue...";
                std::cin.get();
                break;
            case 2:
                openSingleCase();
                break;
            case 3:
                openMultipleCases();
                break;
            case 4:
                player_->displayInventory();
                std::cout << "\nPress Enter to continue...";
                std::cin.get();
                break;
            case 5:
                sellItem();
                break;
            case 6:
                sellAllItems();
                break;
            case 7:
                addBalance();
                break;
            case 0:
                running = false;
                std::cout << "Thanks for playing!\n";
                break;
            default:
                std::cout << "Invalid choice!\n";
            }
        
        // std::cout << "\nPress Enter to continue...";
        // std::cin.get();
    }
}