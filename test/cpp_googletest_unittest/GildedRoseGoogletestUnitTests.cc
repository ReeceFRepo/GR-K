#include <gtest/gtest.h>
#include "GildedRose.h"


// TEST(GildedRoseTest, Foo) {
//     vector<Item> items;
//     items.push_back(Item("Foo", 0, 0));
//     GildedRose app(items);
//     app.updateQuality();
//     EXPECT_EQ("fixme", app.m_Stock[0].m_name);
// }

TEST(GildedRoseTest, GetItemProperties)
{
    GildedRose app;
    app.setItem({"Aged Brie", 4, 10});
    EXPECT_EQ("Aged Brie", app.getItem(0).m_name);
    EXPECT_EQ(4, app.getItem(0).m_sellIn);
    EXPECT_EQ(10, app.getItem(0).m_quality);
}
TEST(GildedRoseTest, QualityNeverNegative)
{
    GildedRose app;
    app.setItem({"Aged Brie", 6, -4});
    EXPECT_EQ(0, app.getItem(0).m_quality);

    app.setItem({"Sulfuras, Hand of Ragnaros", 4, 10});
    app.setItem({"Backstage passes to a TAFKAL80ETC concert", 20, 10});
    app.setItem({"Conjured Mana Cake", 4, 10});
    app.setItem({"Cake", 4, 14});
    for(int i = 0; i<40; i++)
    {
        app.updateQuality();

        EXPECT_GE(app.getItem(0).m_quality, 0); // Brie
        EXPECT_GE(app.getItem(1).m_quality, 0); // Sulfuras
        EXPECT_GE(app.getItem(2).m_quality, 0);  // Backstage
        EXPECT_GE(app.getItem(3).m_quality, 0);  // Conjured
        EXPECT_GE(app.getItem(4).m_quality, 0);  // Cake
    }
}

TEST(GildedRoseTest, AgedBrie)
{
    GildedRose app;

    app.setItem({"Aged Brie", 6, 35});
    for(int i = 0; i<20; ++i)
    {
        int lastQuality = app.getItem(0).m_quality;
        app.updateQuality();
        int diff = std::abs(app.getItem(0).m_quality - lastQuality);
        if(app.getItem(0).m_quality<50){
            EXPECT_EQ(1, diff);
        }
        EXPECT_LE(app.getItem(0).m_quality, 50);
    }

    
    EXPECT_EQ(app.getItem(0).m_sellIn, -14);
}

TEST(GildedRoseTest, BackstagePass)
{
    GildedRose app;
    app.setItem({"Backstage passes to a TAFKAL80ETC concert", 15, 25});
    for(int i = 0; i<20; ++i)
    {
        int lastQuality = app.getItem(0).m_quality;
        app.updateQuality();

        if(app.getItem(0).m_sellIn > 10){
            int diff = std::abs(app.getItem(0).m_quality - lastQuality);
            EXPECT_EQ(1, diff);
        }
        if((5 <= app.getItem(0).m_sellIn) && (app.getItem(0).m_sellIn < 10)){
            int diff = std::abs(app.getItem(0).m_quality - lastQuality);
            EXPECT_EQ(2, diff);
        }
        if((0 <= app.getItem(0).m_sellIn) && (app.getItem(0).m_sellIn < 5)){
            int diff = std::abs(app.getItem(0).m_quality - lastQuality);
            if(app.getItem(0).m_quality <= 47){
                EXPECT_EQ(3, diff);
            }
        }
        if(app.getItem(0).m_sellIn < -1){ // decreases after quality change
            EXPECT_EQ(app.getItem(0).m_quality, 0);
        }
        EXPECT_LE(app.getItem(0).m_quality, 50);
    }

    EXPECT_EQ(-5, app.getItem(0).m_sellIn);
}

TEST(GildedRoseTest, Sulfuras)
{
    GildedRose app;
    app.setItem({"Sulfuras, Hand of Ragnaros", 4, 10});

    for(int i = 0; i<20; ++i)
    {
        app.updateQuality();

        EXPECT_EQ(app.getItem(0).m_quality, 10);
        EXPECT_EQ(app.getItem(0).m_sellIn, 4);
    }
}

TEST(GildedRoseTest, Conjured)
{
    GildedRose app;
    app.setItem({"Conjured Mana Cake", 10, 35});

    for(int i = 0; i<20; ++i)
    {
        int lastQuality = app.getItem(0).m_quality;
        app.updateQuality();
        
        int diff = std::abs(app.getItem(0).m_quality - lastQuality);


        if(app.getItem(0).m_sellIn >= 0 && app.getItem(0).m_quality >= 2){
            EXPECT_EQ(diff, 2);
        }
        if(app.getItem(0).m_sellIn < 0 && app.getItem(0).m_quality >= 4){
            EXPECT_EQ(diff, 4);
        }


        EXPECT_GE(app.getItem(0).m_quality, 0);
    }

}
