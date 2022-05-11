#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <unordered_map>
using namespace std;

class Item
{
public:
    string m_name;
    int m_sellIn;
    int m_quality;
    Item(string name, int sellIn, int quality) : m_name(name), m_sellIn(sellIn), m_quality(quality) 
    {}
};



class GildedRose
{
public:
    GildedRose()=default;
    void updateQuality();
    void setItem(Item&& data);
    void printItems();
    Item getItem(const int& position);
private:
    int getIncrease(const Item& item);
    void updateEachItem(Item& item);
    void updateBrie(Item& item);
    void updateNormal(Item& item);
    void updatePasses(Item& item);
    void updateConjured(Item& item);
private:
    vector<Item> m_Stock;
    enum m_specialItem{
        agedBrie = 1,
        sulfuras,
        backstagePasses,
        conjured,
    };
    std::map<std::string, m_specialItem> m_Map{
        {"Aged Brie", m_specialItem::agedBrie}, 
        {"Backstage passes to a TAFKAL80ETC concert", m_specialItem::backstagePasses}, 
        {"Sulfuras, Hand of Ragnaros", m_specialItem::sulfuras}, 
        {"Conjured Mana Cake", m_specialItem::conjured}
    };
    const int m_MAXQUAILTY{50};
    const int m_MINQUAILTY{0};
};

