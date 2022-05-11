#include "GildedRose.h"


/*
Special items:
Aged Brie
Backstage passes to a TAFKAL80ETC concert
Sulfuras, Hand of Ragnaros
Conjured

*/

void GildedRose::updateNormal(Item& item){
    if(item.m_quality > m_MINQUAILTY){
        item.m_quality-=1;
        if((item.m_sellIn<=0) && (item.m_quality != m_MINQUAILTY))
        {
            item.m_quality-=1;
        }
    }
}

void GildedRose::updateBrie(Item& item){
    item.m_quality = item.m_quality == m_MAXQUAILTY ? m_MAXQUAILTY : ++item.m_quality;

}

void GildedRose::updatePasses(Item& item){
    item.m_quality = item.m_sellIn < 0 ? 0 : item.m_quality + getIncrease(item);
}

void GildedRose::updateConjured(Item& item){
    for(int i = 0; i<=1; i++)
    {
        updateNormal(item);
    }
}

int GildedRose::getIncrease(const Item& item){
    int increase{0};
    if(item.m_sellIn > 10){
        increase = 1;
    }else if((5 < item.m_sellIn) && (item.m_sellIn <= 10)){
        increase = 2;
    }else{
        increase = 3;
    }
    return ((item.m_quality + increase >= m_MAXQUAILTY) ? (m_MAXQUAILTY-item.m_quality) : increase);
}

void GildedRose::updateEachItem(Item& item){
    switch (m_Map[item.m_name]) // Insert unknown as key = 0 so enum starts at 1
    {
        case m_specialItem::agedBrie :
            updateBrie(item);
            --item.m_sellIn;
            break;
        case m_specialItem::backstagePasses :
            updatePasses(item);
            --item.m_sellIn;
            break;
        case m_specialItem::sulfuras :
            break;
        case m_specialItem::conjured :
            updateConjured(item);
            --item.m_sellIn;
            break;
        default:
            updateNormal(item);
            --item.m_sellIn;
            break;
    }
}

void GildedRose::updateQuality(){
    for(auto& item : m_Stock) {
        updateEachItem(item);
    }
}

Item GildedRose::getItem(const int& position){ 
    return m_Stock[position]; 
}

void GildedRose::setItem(Item&& data){
    if (data.m_quality > m_MAXQUAILTY)
        data.m_quality = m_MAXQUAILTY;
    if (data.m_quality < m_MINQUAILTY)
        data.m_quality = m_MINQUAILTY;


    m_Stock.emplace_back(data);
}

void GildedRose::printItems(){
    for(auto& item : m_Stock){
    std::cout << "  name: " << item.m_name << "    SellIn: " <<  item.m_sellIn << "    Quality: "<< item.m_quality << std::endl;
    }
    
}

