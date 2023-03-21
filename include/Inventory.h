#pragma once

#include <vector>

class InventoryItem
{
private:
    int amount;
    int spriteId;

public:
    InventoryItem();
    InventoryItem(int amount, int spriteId);
    virtual ~InventoryItem();

    // Functions
    int getAmount();
    void setAmount(int amount);
    int getSpriteId();
};

class Inventory
{
private:
    std::vector<InventoryItem> items;
    int currentHotbatSlot = 0;

public:
    Inventory();
    virtual ~Inventory();

    // Functions
    void addToInventory(int spriteId, int amount);
    void dropFromInventory(InventoryItem item);
    InventoryItem getHeldItem();
    std::vector<InventoryItem> getItems();
    int getCurrentSlot();
    void setCurrentSlot(int slot);
};
