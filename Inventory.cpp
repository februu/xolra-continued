#include <iostream>
#include <vector>
#include "include/Constants.h"
#include "include/Inventory.h"

using std::cout;

InventoryItem::InventoryItem()
{
    this->amount = -1;
    this->spriteId = -1;
}

InventoryItem::InventoryItem(int amount, int spriteId)
{
    this->amount = amount;
    this->spriteId = spriteId;
}

InventoryItem::~InventoryItem()
{
}

int InventoryItem::getAmount()
{
    return amount;
}

void InventoryItem::setAmount(int amount)
{
    this->amount = amount;
}

int InventoryItem::getSpriteId()
{
    return spriteId;
}

Inventory::Inventory()
{
}

Inventory::~Inventory()
{
}

void Inventory::addToInventory(int amount, int spriteId)
{
    for (auto item = begin(items); item != end(items); ++item)
    {
        cout << "1";
        if (item->getSpriteId() == spriteId && item->getAmount() < INT_MAX_STACK_SIZE)
        {
            if (item->getAmount() + amount <= INT_MAX_STACK_SIZE)
                item->setAmount(item->getAmount() + amount);
            else
            {
                InventoryItem newItem = InventoryItem((item->getAmount() + amount) % INT_MAX_STACK_SIZE, spriteId);
                item->setAmount(INT_MAX_STACK_SIZE);
                items.push_back(newItem);
            }
            return;
        }
    }
    InventoryItem newItem = InventoryItem(amount, spriteId);
    items.push_back(newItem);
}

void Inventory::dropFromInventory(InventoryItem item)
{
    // for (auto i = begin(items); i != end(items); ++i)
    //     if (i->getSpriteId() == i->getSpriteId())
    //     {
    //         // TODO: Drop item on ground.
    //         items.erase(i--);
    //         break;
    //     }
}

InventoryItem Inventory::getHeldItem()
{
}

std::vector<InventoryItem> Inventory::getItems()
{
    return items;
}

int Inventory::getCurrentSlot()
{
    return currentHotbatSlot;
}

void Inventory::setCurrentSlot(int slot)
{
    if (slot >= INT_HOTBAR_SIZE)
        currentHotbatSlot = 0;
    else if (slot < 0)
        currentHotbatSlot = 9;
    else
        currentHotbatSlot = slot;
}