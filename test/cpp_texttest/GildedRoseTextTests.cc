#include "GildedRose.h"


int main()
{
    vector<Item> items;
    GildedRose app;
    app.setItem({"Aged Brie", 4, 10});
    app.setItem({"+5 Dexterity Vest", 10, 20});
    app.setItem({"Aged Brie", 2, 0});
    app.setItem({"Elixir of the Mongoose", 5, 7});
    app.setItem({"Sulfuras, Hand of Ragnaros", 0, 80});
    app.setItem({"Sulfuras, Hand of Ragnaros", 13, 30});
    app.setItem({"Sulfuras, Hand of Ragnaros", -1, 80});
    app.setItem({"Backstage passes to a TAFKAL80ETC concert", 10, 49});
    app.setItem({"Backstage passes to a TAFKAL80ETC concert", 5, 49});
    app.setItem({"Conjured Mana Cake", 35, 6});
    app.setItem({"Conjured Mana Cake", 10, 36});

	std::cout << "OMGHAI!" << std::endl;


    for (int day = 0; day <= 17; day++)
    {
        std::cout << "-------- day " << day << " --------" << std::endl;
        app.updateQuality();
        app.printItems();

    }
    return 0;
}


