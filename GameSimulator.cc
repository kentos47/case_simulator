#include "GameSimulator.h"
#include "WeaponCase.h"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <iomanip>


void initializeCaseWithItems(Container* container) {
    // Используем базу данных скинов из Item.cc
    for (const auto& skinData : skin_database) {
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
      player_(std::make_unique<Player>("Player", 10000.0)) {
    
    // Инициализация кейсов с предметами
    auto weaponCase1 = std::make_unique<WeaponCase>("Weapon Case", 105.0);
    // auto weaponCase2 = std::make_unique<WeaponCase>("Knife Case", 9.99);
    
    initializeCaseWithItems(weaponCase1.get());
    // initializeCaseWithItems(weaponCase2.get());
    
    shop_->addContainer(std::move(weaponCase1));
    // shop_->addContainer(std::move(weaponCase2));
}

void GameSimulator::openSingleCase() {
    shop_->displayAvailableContainers();
    
    if (shop_->getContainerCount() == 0) {
        std::cout << "No cases available!\n";
        return;
    }
    
    std::cout << "Select case (0 to cancel): ";
    int choice;
    std::cin >> choice;
    
    if (choice == 0 || choice < 1 || choice > shop_->getContainerCount()) {
        return;
    }
    
    Container* selected = shop_->getContainer(choice - 1);
    
    if (player_->spendBalance(selected->getPrice())) {
        try {
            auto item = selected->open();
            std::cout << "You got: " << item->get_info() << "\n";
            player_->addToInventory(std::move(item));
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    } else {
        std::cout << "Not enough money!\n";
    }
}


void GameSimulator::openMultipleCases() {
    shop_->displayAvailableContainers();
    
    std::cout << "\nSelect a case type to open (0 to cancel): ";
    size_t case_choice;
    std::cin >> case_choice;
    
    if (case_choice == 0) return;
    
    Container* selected = shop_->getContainer(case_choice - 1);
    if (!selected) {
        std::cout << "Invalid selection!\n";
        return;
    }
    
    std::cout << "How many cases to open? ";
    size_t count;
    std::cin >> count;
    
    double total_cost = selected->getPrice() * count;
    std::cout << "Total cost: $" << total_cost << "\n";
    
    if (player_->spendBalance(total_cost)) {
        std::cout << "\nOpening " << count << " " << selected->getName() << "(s)...\n";
        for (size_t i = 0; i < count; ++i) {
            try {
                auto item = selected->open();
                std::cout << "Case " << i + 1 << ": " << item->get_info() << "\n";
                player_->addToInventory(std::move(item));
            } catch (const std::exception& e) {
                std::cout << "Error in case " << i + 1 << ": " << e.what() << "\n";
            }
        }
    } else {
        std::cout << "Insufficient balance! Need $" << total_cost << "\n";
    }
}

void GameSimulator::sellItem() {
    player_->displayInventory();
    
    std::cout << "\nSelect item to sell (0 to cancel): ";
    size_t choice;
    std::cin >> choice;
    
    if (choice == 0) return;
    
    try {
        player_->sellItem(choice - 1);
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void GameSimulator::addBalance() {
    std::cout << "\nHow much balance to add? $";
    double amount;
    std::cin >> amount;
    
    if (amount > 0) {
        player_->addBalance(amount);
    } else {
        std::cout << "Invalid amount!\n";
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
        std::cout << "6. Add balance\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";
        
        int choice;
        std::cin >> choice;
        
        // Очистка буфера ввода
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        try {
            switch (choice) {
                case 1:
                    shop_->displayAvailableContainers();
                    break;
                case 2:
                    openSingleCase();
                    break;
                case 3:
                    openMultipleCases();
                    break;
                case 4:
                    player_->displayInventory();
                    break;
                case 5:
                    sellItem();
                    break;
                case 6:
                    addBalance();
                    break;
                case 0:
                    running = false;
                    std::cout << "Thanks for playing!\n";
                    break;
                default:
                    std::cout << "Invalid choice!\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
        
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }
}